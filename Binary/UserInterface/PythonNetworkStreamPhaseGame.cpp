# Search

		CPythonMiniMap::Instance().RegisterAtlasMark(NPCPosition.bType, name.c_str(), NPCPosition.x, NPCPosition.y);

# Change

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
		const std::string name = CPythonNonPlayer::Instance().GetMonsterName(NPCPosition.vnum);
		CPythonMiniMap::Instance().RegisterAtlasMark(NPCPosition.bType, name.c_str(), NPCPosition.x, NPCPosition.y, NPCPosition.vnum, NPCPosition.time);
#else
		CPythonMiniMap::Instance().RegisterAtlasMark(NPCPosition.bType, name.c_str(), NPCPosition.x, NPCPosition.y);
#endif
