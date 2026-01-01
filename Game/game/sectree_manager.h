# Search

		void		InsertNPCPosition(long lMapIndex, BYTE bType, const char* name, long x, long y);

# Change

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
		void		InsertNPCPosition(long lMapIndex, BYTE bType, DWORD vnum, long x, long y, DWORD respawn_time);
		bool		MarkNPCPositionDead(long lMapIndex, DWORD vnum, long x, long y, DWORD remain_seconds = 0);
		bool		MarkNPCPositionAlive(long lMapIndex, DWORD vnum);
		void		BroadcastNPCPosition(long lMapIndex);
#else
		void		InsertNPCPosition(long lMapIndex, BYTE bType, const char* name, long x, long y);
#endif

# Search

struct npc_info

# Change

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
struct npc_info
{
	BYTE bType;
	DWORD vnum;
	long x, y;
	DWORD respawn_time;
	DWORD dead_until;
	npc_info(BYTE bType, DWORD vnum, long x, long y, DWORD respawn_time)
		: bType(bType), vnum(vnum), x(x), y(y), respawn_time(respawn_time), dead_until(0) {}
};
#else
struct npc_info
{
	BYTE bType;
	const char* name;
	long x, y;
	npc_info(BYTE bType, const char* name, long x, long y): bType(bType), name(name), x(x), y(y){}
};
#endif

