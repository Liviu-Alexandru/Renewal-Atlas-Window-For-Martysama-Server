# Search

struct TNPCPosition

#Change

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
struct TNPCPosition
{
	BYTE bType;
	DWORD vnum;
	long x;
	long y;
	DWORD time;
};
#else
struct TNPCPosition
{
	BYTE bType;
	char name[CHARACTER_NAME_MAX_LEN + 1];
	long x;
	long y;
};
#endif
