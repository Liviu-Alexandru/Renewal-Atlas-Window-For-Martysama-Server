# Add like other module in end file

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
	PyModule_AddIntConstant(poModule, "ENABLE_DUNGEON_BOSS_ICON_IN_MAP", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_DUNGEON_BOSS_ICON_IN_MAP", 0);
#endif
