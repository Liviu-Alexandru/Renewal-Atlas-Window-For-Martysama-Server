# Add

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
#include "PythonNonPlayer.h"
bool GetDungeonNPC(DWORD mobIndex)
{
	switch (mobIndex) // Adauga un Npc pentru dungeon
	{
		case 20423:
			return true;
	}
	return false;
}

bool IsBoss(DWORD race)
{
	if (GetDungeonNPC(race))
		return false;

	switch (race) // Adauga un Mob
	{
		case 191:
			return true;
	}

	const CPythonNonPlayer::TMobTable* pMobTable = CPythonNonPlayer::Instance().GetTable(race);

	if (pMobTable && pMobTable->bType == 0 && pMobTable->bRank >= 4)
		return true;

	return false;
}
#endif
