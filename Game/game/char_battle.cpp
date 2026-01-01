# Add

#include "sectree_manager.h"

# Search

	// BOSS_KILL_LOG
	if (GetMobRank() >= MOB_RANK_BOSS && pkKiller && pkKiller->IsPC())
	{
		char buf[51];
		snprintf(buf, sizeof(buf), "%d %ld", g_bChannel, pkKiller->GetMapIndex());
		if (IsStone())
			LogManager::instance().CharLog(pkKiller, GetRaceNum(), "STONE_KILL", buf);
		else
			LogManager::instance().CharLog(pkKiller, GetRaceNum(), "BOSS_KILL", buf);
	}
	// END_OF_BOSS_KILL_LOG

# Add after

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
	if (!IsPC())
	{
		DWORD dwRemainSeconds = 0;

		if (m_pkRegen && m_pkRegen->event)
		{
			const long lPulses = event_time(m_pkRegen->event);

			if (lPulses > 0)
				dwRemainSeconds = (DWORD)((lPulses + PASSES_PER_SEC(1) - 1) / PASSES_PER_SEC(1));
		}

		if (SECTREE_MANAGER::instance().MarkNPCPositionDead(GetMapIndex(), GetRaceNum(), GetX(), GetY(), dwRemainSeconds))
			SECTREE_MANAGER::instance().BroadcastNPCPosition(GetMapIndex());
	}
#endif


