# Add

#include <unordered_map>

# Search

void SECTREE_MANAGER::InsertNPCPosition(long lMapIndex, BYTE bType, const char* szName, long x, long y)
{
	m_mapNPCPosition[lMapIndex].push_back(npc_info(bType, szName, x, y));
}

# Change

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
void SECTREE_MANAGER::InsertNPCPosition(long lMapIndex, BYTE bType, DWORD vnum, long x, long y, DWORD respawn_time)
{
	m_mapNPCPosition[lMapIndex].push_back(npc_info(bType, vnum, x, y, respawn_time));
	if (respawn_time > 0)
		sys_log(0, "InsertNPCPosition: map=%ld vnum=%u type=%u x=%ld y=%ld respawn=%u", lMapIndex, vnum, bType, x, y, respawn_time);
}

bool SECTREE_MANAGER::MarkNPCPositionDead(long lMapIndex, DWORD vnum, long x, long y, DWORD remain_seconds)
{
	const DWORD dwNow = get_global_time();
	const long lKeyMapIndex = (lMapIndex >= 10000) ? (lMapIndex / 10000) : lMapIndex;
	auto itMap = m_mapNPCPosition.find(lKeyMapIndex);
	if (itMap == m_mapNPCPosition.end())
	{
		if (test_server)
			sys_log(0, "MarkNPCPositionDead: map=%ld key=%ld vnum=%u not-found(map)", lMapIndex, lKeyMapIndex, vnum);
		return false;
	}

	npc_info* pBest = nullptr;
	uint64_t bestDist2 = 0;
	int iMatches = 0;
	for (auto & info : itMap->second)
	{
		if (info.vnum != vnum)
			continue;
		++iMatches;
		if (info.respawn_time == 0)
			continue;

		const int64_t dx = (int64_t)info.x - (int64_t)x;
		const int64_t dy = (int64_t)info.y - (int64_t)y;
		const uint64_t dist2 = (uint64_t)(dx * dx + dy * dy);
		if (!pBest || dist2 < bestDist2)
		{
			pBest = &info;
			bestDist2 = dist2;
		}
	}

	if (iMatches == 0)
	{
		if (test_server)
			sys_log(0, "MarkNPCPositionDead: map=%ld key=%ld vnum=%u not-found(vnum)", lMapIndex, lKeyMapIndex, vnum);
		return false;
	}

	if (!pBest)
	{
		if (test_server)
			sys_log(0, "MarkNPCPositionDead: map=%ld key=%ld vnum=%u respawn_time=0 (check boss.txt time column)", lMapIndex, lKeyMapIndex, vnum);
		return false;
	}

	const DWORD dwRemain = (remain_seconds > 0) ? remain_seconds : pBest->respawn_time;
	pBest->dead_until = dwNow + dwRemain;
	sys_log(0, "MarkNPCPositionDead: map=%ld key=%ld vnum=%u matches=%d chosen=(%ld,%ld) respawn=%u remain=%u dead_until=%u", lMapIndex, lKeyMapIndex, vnum, iMatches, pBest->x, pBest->y, pBest->respawn_time, dwRemain, pBest->dead_until);
	return true;
}

bool SECTREE_MANAGER::MarkNPCPositionAlive(long lMapIndex, DWORD vnum)
{
	const long lKeyMapIndex = (lMapIndex >= 10000) ? (lMapIndex / 10000) : lMapIndex;
	auto itMap = m_mapNPCPosition.find(lKeyMapIndex);

	if (itMap == m_mapNPCPosition.end())
		return false;

	bool bChanged = false;

	for (auto & info : itMap->second)
	{
		if (info.vnum != vnum)
			continue;
		if (info.dead_until != 0)
		{
			info.dead_until = 0;
			bChanged = true;
		}
	}

	return bChanged;
}

void SECTREE_MANAGER::BroadcastNPCPosition(long lMapIndex)
{
	const long lKeyMapIndex = (lMapIndex >= 10000) ? (lMapIndex / 10000) : lMapIndex;
	auto itMap = m_mapNPCPosition.find(lKeyMapIndex);

	if (itMap == m_mapNPCPosition.end() || itMap->second.empty())
	{
		if (test_server)
			sys_log(0, "BroadcastNPCPosition: map=%ld key=%ld empty", lMapIndex, lKeyMapIndex);
		return;
	}

	TEMP_BUFFER buf;
	TPacketGCNPCPosition p;

	p.header = HEADER_GC_NPC_POSITION;
	std::unordered_map<DWORD, const npc_info*> chosenByVnum;
	chosenByVnum.reserve(itMap->second.size());

	TNPCPosition np;
	const DWORD dwNow = get_global_time();

	for (const auto & info : itMap->second)
	{
		auto it = chosenByVnum.find(info.vnum);
		if (it == chosenByVnum.end())
		{
			chosenByVnum.emplace(info.vnum, &info);
			continue;
		}

		const npc_info* cur = it->second;
		const bool curDead = (cur->dead_until > dwNow);
		const bool infoDead = (info.dead_until > dwNow);

		if (!curDead && infoDead)
			it->second = &info;
	}

	p.count = chosenByVnum.size();

	for (const auto & kv : chosenByVnum)
	{
		const npc_info* it = kv.second;
		np.bType = it->bType;
		np.vnum = it->vnum;
		DWORD dwRemain = 0;

		if (it->dead_until > dwNow)
			dwRemain = it->dead_until - dwNow;

		np.time = dwRemain;
		np.x = it->x;
		np.y = it->y;
		buf.write(&np, sizeof(np));
	}

	p.size = sizeof(p) + buf.size();

	if (!buf.size())
		return;

	sys_log(0, "BroadcastNPCPosition: map=%ld key=%ld count=%u size=%u", lMapIndex, lKeyMapIndex, (unsigned)p.count, (unsigned)p.size);

	const DESC_MANAGER::DESC_SET & c_ref_set = DESC_MANAGER::instance().GetClientSet();

	for (DESC_MANAGER::DESC_SET::const_iterator itDesc = c_ref_set.begin(); itDesc != c_ref_set.end(); ++itDesc)
	{
		LPDESC d = *itDesc;

		if (!d)
			continue;

		LPCHARACTER ch = d->GetCharacter();

		if (!ch)
			continue;

		if (ch->GetMapIndex() != lMapIndex)
			continue;

		d->BufferedPacket(&p, sizeof(TPacketGCNPCPosition));
		d->Packet(buf.read_peek(), buf.size());
	}
}
#else
void SECTREE_MANAGER::InsertNPCPosition(long lMapIndex, BYTE bType, const char* szName, long x, long y)
{
	m_mapNPCPosition[lMapIndex].push_back(npc_info(bType, szName, x, y));
}
#endif

# Search

	for (auto it = m_mapNPCPosition[lMapIndex].begin(); it != m_mapNPCPosition[lMapIndex].end(); ++it)
	{
		np.bType = it->bType;
		strlcpy(np.name, it->name, sizeof(np.name));
		np.x = it->x;
		np.y = it->y;
		buf.write(&np, sizeof(np));
	}

#Change

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
	for (const auto & kv : chosenByVnum)
	{
		const npc_info* it = kv.second;
		np.bType = it->bType;
		np.vnum = it->vnum;
		DWORD dwRemain = 0;
		if (it->dead_until > dwNow)
			dwRemain = it->dead_until - dwNow;
		np.time = dwRemain;
		np.x = it->x;
		np.y = it->y;
		buf.write(&np, sizeof(np));
	}
#else
	for (auto it = m_mapNPCPosition[lMapIndex].begin(); it != m_mapNPCPosition[lMapIndex].end(); ++it)
	{
		np.bType = it->bType;
		strlcpy(np.name, it->name, sizeof(np.name));
		np.x = it->x;
		np.y = it->y;
		buf.write(&np, sizeof(np));
	}
#endif


