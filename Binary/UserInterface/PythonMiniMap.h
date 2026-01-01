# Search

	TAtlasMarkInfoVector						m_AtlasWarpInfoVector;

#Add after

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
		TAtlasMarkInfoVector					m_AtlasDungeonInfoVector;
		TAtlasMarkInfoVector					m_AtlasBossInfoVector;
#endif

# Search

		TInstanceMarkPositionVector		m_WarpPositionVector;

# Add after

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
		TInstanceMarkPositionVector		m_BossPositionVector;
		TInstanceMarkPositionVector		m_DungeonPositionVector;
#endif

# Search

		CGraphicImageInstance			m_WhiteMark;

# Add after

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
		CGraphicImageInstance			m_BossMark;
		CGraphicImageInstance			m_DungeonMark;
#endif

# Search

			std::string m_strText;

# add after

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
			DWORD m_dwMobVnum;
			DWORD time;
#endif

# Search

		void RegisterAtlasMark(BYTE byType, const char* c_szName, long lx, long ly);

# Change

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
		void RegisterAtlasMark(BYTE byType, const char* c_szName, long lx, long ly, DWORD mobVnum, DWORD time);
#else
		void RegisterAtlasMark(BYTE byType, const char* c_szName, long lx, long ly);
#endif

# Search

		bool GetAtlasInfo(float fScreenX, float fScreenY, std::string& rReturnString, float* pReturnPosX, float* pReturnPosY, DWORD* pdwTextColor, DWORD* pdwGuildID);

# Change

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
		bool GetAtlasInfo(float fScreenX, float fScreenY, std::string& rReturnString, float* pReturnPosX, float* pReturnPosY, DWORD* pdwTextColor, DWORD* pdwGuildID, DWORD* time, bool* isBoss);
#else
		bool GetAtlasInfo(float fScreenX, float fScreenY, std::string& rReturnString, float* pReturnPosX, float* pReturnPosY, DWORD* pdwTextColor, DWORD* pdwGuildID);
#endif

