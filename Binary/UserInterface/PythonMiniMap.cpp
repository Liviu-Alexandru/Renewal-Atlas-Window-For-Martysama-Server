# Search

void CPythonMiniMap::AddWayPoint(BYTE byType, DWORD dwID, float fX, float fY, std::string strText, DWORD dwChrVID)

	aAtlasMarkInfo.m_fX = fX;
	aAtlasMarkInfo.m_fY = fY;

# Add after

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
	aAtlasMarkInfo.m_dwMobVnum = 0;
	aAtlasMarkInfo.time = 0;
#endif

# Search

void CPythonMiniMap::__LoadAtlasMarkInfo()

# In

		TAtlasMarkInfo aAtlasMarkInfo;

# Add after

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
		aAtlasMarkInfo.m_dwMobVnum = 0;
		aAtlasMarkInfo.time = 0;
#endif

# Search

#ifdef ENABLE_NEW_ATLAS_MARK_INFO
		if (rVector.size() == 3)
		{
			const std::string & c_rstrType = strType[3]; // FULL NPC
			const std::string & c_rstrPositionX = rVector[0].c_str();
			const std::string & c_rstrPositionY = rVector[1].c_str();
			const std::string & c_rstrText = rVector[2].c_str();
			int iVNum = atoi(c_rstrText.c_str());

			aAtlasMarkInfo.m_fX = atof(c_rstrPositionX.c_str());
			aAtlasMarkInfo.m_fY = atof(c_rstrPositionY.c_str());
			aAtlasMarkInfo.m_strText = CPythonNonPlayer::Instance().GetMonsterName(iVNum);

		aAtlasMarkInfo.m_byType = TYPE_NPC;
		}
		else
#endif

# Change

#ifdef ENABLE_NEW_ATLAS_MARK_INFO
		if (rVector.size() == 3)
		{
			const std::string & c_rstrType = strType[3]; // FULL NPC
			const std::string & c_rstrPositionX = rVector[0].c_str();
			const std::string & c_rstrPositionY = rVector[1].c_str();
			const std::string & c_rstrText = rVector[2].c_str();
			int iVNum = atoi(c_rstrText.c_str());

			aAtlasMarkInfo.m_fX = atof(c_rstrPositionX.c_str());
			aAtlasMarkInfo.m_fY = atof(c_rstrPositionY.c_str());
			aAtlasMarkInfo.m_strText = CPythonNonPlayer::Instance().GetMonsterName(iVNum);

		aAtlasMarkInfo.m_byType = TYPE_NPC;
#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
		aAtlasMarkInfo.m_dwMobVnum = iVNum;
#endif
		}
		else
#endif

# Search

			aAtlasMarkInfo.m_fX = atof(c_rstrPositionX.c_str());
			aAtlasMarkInfo.m_fY = atof(c_rstrPositionY.c_str());
			aAtlasMarkInfo.m_strText = c_rstrText;

# Add after

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
			bool bAllDigits = !aAtlasMarkInfo.m_strText.empty();

			for (size_t k = 0; k < aAtlasMarkInfo.m_strText.size() && bAllDigits; ++k)
				bAllDigits = (aAtlasMarkInfo.m_strText[k] >= '0' && aAtlasMarkInfo.m_strText[k] <= '9');

			if (bAllDigits)
			{
				const DWORD dwVnum = (DWORD)atoi(aAtlasMarkInfo.m_strText.c_str());
				if (dwVnum)
				{
					aAtlasMarkInfo.m_dwMobVnum = dwVnum;
					aAtlasMarkInfo.m_strText = CPythonNonPlayer::Instance().GetMonsterName(dwVnum);
				}
			}
#endif

# Search

		aAtlasMarkInfo.m_fScreenX = aAtlasMarkInfo.m_fX / m_fAtlasMaxX * m_fAtlasImageSizeX - (float)m_WhiteMark.GetWidth() / 2.0f;
		aAtlasMarkInfo.m_fScreenY = aAtlasMarkInfo.m_fY / m_fAtlasMaxY * m_fAtlasImageSizeY - (float)m_WhiteMark.GetHeight() / 2.0f;

# Add after

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
		bool bHandledBossDungeon = false;

		if (aAtlasMarkInfo.m_dwMobVnum)
		{
			if (IsBoss(aAtlasMarkInfo.m_dwMobVnum))
			{
				aAtlasMarkInfo.m_fScreenX = aAtlasMarkInfo.m_fX / m_fAtlasMaxX * m_fAtlasImageSizeX - (float)m_BossMark.GetWidth() / 2.0f;
				aAtlasMarkInfo.m_fScreenY = aAtlasMarkInfo.m_fY / m_fAtlasMaxY * m_fAtlasImageSizeY - (float)m_BossMark.GetHeight() / 2.0f;

				m_AtlasBossInfoVector.push_back(aAtlasMarkInfo);

				bHandledBossDungeon = true;
			}
			else if (GetDungeonNPC(aAtlasMarkInfo.m_dwMobVnum))
			{
				aAtlasMarkInfo.m_fScreenX = aAtlasMarkInfo.m_fX / m_fAtlasMaxX * m_fAtlasImageSizeX - (float)m_DungeonMark.GetWidth() / 2.0f;
				aAtlasMarkInfo.m_fScreenY = aAtlasMarkInfo.m_fY / m_fAtlasMaxY * m_fAtlasImageSizeY - (float)m_DungeonMark.GetHeight() / 2.0f;

				m_AtlasDungeonInfoVector.push_back(aAtlasMarkInfo);

				bHandledBossDungeon = true;
			}
		}

		if (bHandledBossDungeon)
			continue;
#endif

# Search

	m_AtlasMarkInfoVectorIterator = m_AtlasWayPointInfoVector.begin();
	while (m_AtlasMarkInfoVectorIterator != m_AtlasWayPointInfoVector.end())
	{
		TAtlasMarkInfo& rAtlasMarkInfo = *m_AtlasMarkInfoVectorIterator;
		if (rAtlasMarkInfo.m_fScreenX > 0.0f)
			if (rAtlasMarkInfo.m_fScreenY > 0.0f)
				if (rAtlasMarkInfo.m_fX - fCheckWidth / 2 < fRealX && rAtlasMarkInfo.m_fX + fCheckWidth > fRealX &&
					rAtlasMarkInfo.m_fY - fCheckWidth / 2 < fRealY && rAtlasMarkInfo.m_fY + fCheckHeight > fRealY)
				{
					rReturnString = rAtlasMarkInfo.m_strText;
					*pReturnPosX = rAtlasMarkInfo.m_fX;
					*pReturnPosY = rAtlasMarkInfo.m_fY;
					*pdwTextColor = CInstanceBase::GetIndexedNameColor(CInstanceBase::NAMECOLOR_WAYPOINT);
					return true;
				}
		++m_AtlasMarkInfoVectorIterator;
	}

# Add after

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
	STATEMANAGER.SetRenderState(D3DRS_TEXTUREFACTOR, 0xFFFFFFFF);
	m_AtlasMarkInfoVectorIterator = m_AtlasDungeonInfoVector.begin();

	while (m_AtlasMarkInfoVectorIterator != m_AtlasDungeonInfoVector.end())
	{
		TAtlasMarkInfo& rAtlasMarkInfo = *m_AtlasMarkInfoVectorIterator;

		m_DungeonMark.SetPosition(rAtlasMarkInfo.m_fScreenX, rAtlasMarkInfo.m_fScreenY);
		m_DungeonMark.Render();

		++m_AtlasMarkInfoVectorIterator;
	}

	STATEMANAGER.SetRenderState(D3DRS_TEXTUREFACTOR, 0xFFFFFFFF);
	m_AtlasMarkInfoVectorIterator = m_AtlasBossInfoVector.begin();

	while (m_AtlasMarkInfoVectorIterator != m_AtlasBossInfoVector.end())
	{
		TAtlasMarkInfo& rAtlasMarkInfo = *m_AtlasMarkInfoVectorIterator;

		m_BossMark.SetPosition(rAtlasMarkInfo.m_fScreenX, rAtlasMarkInfo.m_fScreenY);
		m_BossMark.Render();

		++m_AtlasMarkInfoVectorIterator;
	}

	// Alex Work
	{
		CPythonCharacterManager& rkChrMgr = CPythonCharacterManager::Instance();
		CPythonCharacterManager::CharacterIterator it = rkChrMgr.CharacterInstanceBegin();

		for (; it != rkChrMgr.CharacterInstanceEnd(); ++it)
		{
			CInstanceBase* pkInstEach = *it;

			if (!pkInstEach)
				continue;

			const DWORD dwRace = pkInstEach->GetRace();
			const bool bBoss = IsBoss(dwRace);
			const bool bDungeon = !bBoss && GetDungeonNPC(dwRace);

			if (!bBoss && !bDungeon)
				continue;

			TPixelPosition kInstancePosition;
			pkInstEach->NEW_GetPixelPosition(&kInstancePosition);

			// Alex Work
			{
				const TAtlasMarkInfoVector& rVec = bBoss ? m_AtlasBossInfoVector : m_AtlasDungeonInfoVector;
				bool bHasSameSpotMark = false;
				const float fMatch = ((float)CTerrainImpl::CELLSCALE) * 6.0f;

				for (TAtlasMarkInfoVector::const_iterator vit = rVec.begin(); vit != rVec.end(); ++vit)
				{
					if (vit->m_dwMobVnum != dwRace)
						continue;

					if (fabs(vit->m_fX - kInstancePosition.x) < fMatch && fabs(vit->m_fY - kInstancePosition.y) < fMatch)
					{
						bHasSameSpotMark = true;
						break;
					}
				}

				if (bHasSameSpotMark)
					continue;
			}

			if (bBoss)
			{
				const float fx = kInstancePosition.x / m_fAtlasMaxX * m_fAtlasImageSizeX - (float)m_BossMark.GetWidth() / 2.0f;
				const float fy = kInstancePosition.y / m_fAtlasMaxY * m_fAtlasImageSizeY - (float)m_BossMark.GetHeight() / 2.0f;

				m_BossMark.SetPosition(fx, fy);
				m_BossMark.Render();
			}
			else
			{
				const float fx = kInstancePosition.x / m_fAtlasMaxX * m_fAtlasImageSizeX - (float)m_DungeonMark.GetWidth() / 2.0f;
				const float fy = kInstancePosition.y / m_fAtlasMaxY * m_fAtlasImageSizeY - (float)m_DungeonMark.GetHeight() / 2.0f;

				m_DungeonMark.SetPosition(fx, fy);
				m_DungeonMark.Render();
			}
		}
	}
#endif

# Search

bool CPythonMiniMap::GetAtlasInfo(float fScreenX, float fScreenY, std::string& rReturnString, float* pReturnPosX, float* pReturnPosY, DWORD* pdwTextColor, DWORD* pdwGuildID)

# Change only func name

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
bool CPythonMiniMap::GetAtlasInfo(float fScreenX, float fScreenY, std::string& rReturnString, float* pReturnPosX, float* pReturnPosY, DWORD* pdwTextColor, DWORD* pdwGuildID, DWORD* time, bool* isBoss)
#else
bool CPythonMiniMap::GetAtlasInfo(float fScreenX, float fScreenY, std::string& rReturnString, float* pReturnPosX, float* pReturnPosY, DWORD* pdwTextColor, DWORD* pdwGuildID)
#endif

# Search

	float fRealX = (fScreenX - m_fAtlasScreenX) * (m_fAtlasMaxX / m_fAtlasImageSizeX);
	float fRealY = (fScreenY - m_fAtlasScreenY) * (m_fAtlasMaxY / m_fAtlasImageSizeY);

#Add after

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
	if (time)
		*time = 0;

	if (isBoss)
		*isBoss = false;
#endif

# Search

	STATEMANAGER.SetRenderState(D3DRS_TEXTUREFACTOR, CInstanceBase::GetIndexedNameColor(CInstanceBase::NAMECOLOR_WARP));
	m_AtlasMarkInfoVectorIterator = m_AtlasWarpInfoVector.begin();
	while (m_AtlasMarkInfoVectorIterator != m_AtlasWarpInfoVector.end())
	{
		TAtlasMarkInfo& rAtlasMarkInfo = *m_AtlasMarkInfoVectorIterator;
		m_WhiteMark.SetPosition(rAtlasMarkInfo.m_fScreenX, rAtlasMarkInfo.m_fScreenY);
		m_WhiteMark.Render();
		++m_AtlasMarkInfoVectorIterator;
	}

#Add after

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
	m_AtlasMarkInfoVectorIterator = m_AtlasDungeonInfoVector.begin();

	while (m_AtlasMarkInfoVectorIterator != m_AtlasDungeonInfoVector.end())
	{
		TAtlasMarkInfo& rAtlasMarkInfo = *m_AtlasMarkInfoVectorIterator;

		if (rAtlasMarkInfo.m_fX - fCheckWidth / 2 < fRealX && rAtlasMarkInfo.m_fX + fCheckWidth > fRealX &&
			rAtlasMarkInfo.m_fY - fCheckWidth / 2 < fRealY && rAtlasMarkInfo.m_fY + fCheckHeight > fRealY)
		{
			if (time)
			{
				DWORD dwRemain = 0;
				const DWORD dwNow = ELTimer_GetMSec();
				if (rAtlasMarkInfo.time > dwNow)
					dwRemain = (rAtlasMarkInfo.time - dwNow);
				*time = dwRemain;
			}

			if (isBoss)
				*isBoss = false;

			rReturnString = rAtlasMarkInfo.m_strText;
			*pReturnPosX = rAtlasMarkInfo.m_fX;
			*pReturnPosY = rAtlasMarkInfo.m_fY;

			*pdwTextColor = CInstanceBase::GetIndexedNameColor(CInstanceBase::NAMECOLOR_MOB);

			return true;
		}
		++m_AtlasMarkInfoVectorIterator;
	}

	m_AtlasMarkInfoVectorIterator = m_AtlasBossInfoVector.begin();

	while (m_AtlasMarkInfoVectorIterator != m_AtlasBossInfoVector.end())
	{
		TAtlasMarkInfo& rAtlasMarkInfo = *m_AtlasMarkInfoVectorIterator;

		if (rAtlasMarkInfo.m_fX - fCheckWidth / 2 < fRealX && rAtlasMarkInfo.m_fX + fCheckWidth > fRealX &&
			rAtlasMarkInfo.m_fY - fCheckWidth / 2 < fRealY && rAtlasMarkInfo.m_fY + fCheckHeight > fRealY)
		{
			if (time)
			{
				DWORD dwRemain = 0;
				const DWORD dwNow = ELTimer_GetMSec();
				if (rAtlasMarkInfo.time > dwNow)
					dwRemain = (rAtlasMarkInfo.time - dwNow);
				*time = dwRemain;
			}

			if (isBoss)
				*isBoss = true;

			rReturnString = rAtlasMarkInfo.m_strText;
			*pReturnPosX = rAtlasMarkInfo.m_fX;
			*pReturnPosY = rAtlasMarkInfo.m_fY;

			//*pdwTextColor = CInstanceBase::GetIndexedNameColor(CInstanceBase::NAMECOLOR_BOSS);
			*pdwTextColor = CInstanceBase::GetIndexedNameColor(CInstanceBase::NAMECOLOR_MOB);

			return true;
		}
		++m_AtlasMarkInfoVectorIterator;
	}

	// Alex Work
	{
		CPythonCharacterManager& rkChrMgr = CPythonCharacterManager::Instance();
		CPythonCharacterManager::CharacterIterator it = rkChrMgr.CharacterInstanceBegin();
		for (; it != rkChrMgr.CharacterInstanceEnd(); ++it)
		{
			CInstanceBase* pkInstEach = *it;
			if (!pkInstEach)
				continue;

			const DWORD dwRace = pkInstEach->GetRace();
			const bool bBoss = IsBoss(dwRace);
			const bool bDungeon = !bBoss && GetDungeonNPC(dwRace);

			if (!bBoss && !bDungeon)
				continue;

			TPixelPosition kInstancePosition;
			pkInstEach->NEW_GetPixelPosition(&kInstancePosition);

			if (kInstancePosition.x - fCheckWidth / 2 < fRealX && kInstancePosition.x + fCheckWidth > fRealX &&
				kInstancePosition.y - fCheckWidth / 2 < fRealY && kInstancePosition.y + fCheckHeight > fRealY)
			{
				if (time)
					*time = 0;

				if (isBoss)
					*isBoss = bBoss;

				rReturnString = pkInstEach->GetNameString();
				*pReturnPosX = kInstancePosition.x;
				*pReturnPosY = kInstancePosition.y;
					*pdwTextColor = pkInstEach->GetNameColor();

				return true;
			}
		}
	}
#endif

# Search

void CPythonMiniMap::RegisterAtlasMark(BYTE byType, const char* c_szName, long lx, long ly)

# Change

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
void CPythonMiniMap::RegisterAtlasMark(BYTE byType, const char* c_szName, long lx, long ly, DWORD mobVnum, DWORD time)
#else
void CPythonMiniMap::RegisterAtlasMark(BYTE byType, const char* c_szName, long lx, long ly)
#endif
{
	TAtlasMarkInfo aAtlasMarkInfo;

	aAtlasMarkInfo.m_fX = float(lx);
	aAtlasMarkInfo.m_fY = float(ly);
	aAtlasMarkInfo.m_strText = c_szName;

	aAtlasMarkInfo.m_fScreenX = aAtlasMarkInfo.m_fX / m_fAtlasMaxX * m_fAtlasImageSizeX - (float)m_WhiteMark.GetWidth() / 2.0f;
	aAtlasMarkInfo.m_fScreenY = aAtlasMarkInfo.m_fY / m_fAtlasMaxY * m_fAtlasImageSizeY - (float)m_WhiteMark.GetHeight() / 2.0f;

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
	aAtlasMarkInfo.m_dwMobVnum = mobVnum;
	aAtlasMarkInfo.time = 0;

	if (IsBoss(mobVnum))
	{
		if (time > 0)
			aAtlasMarkInfo.time = ELTimer_GetMSec() + (time * 1000);

		aAtlasMarkInfo.m_byType = TYPE_NPC;
		aAtlasMarkInfo.m_fScreenX = aAtlasMarkInfo.m_fX / m_fAtlasMaxX * m_fAtlasImageSizeX - (float)m_BossMark.GetWidth() / 2.0f;
		aAtlasMarkInfo.m_fScreenY = aAtlasMarkInfo.m_fY / m_fAtlasMaxY * m_fAtlasImageSizeY - (float)m_BossMark.GetHeight() / 2.0f;

		for (TAtlasMarkInfoVector::iterator it = m_AtlasBossInfoVector.begin(); it != m_AtlasBossInfoVector.end(); ++it)
		{
			if (it->m_dwMobVnum == mobVnum && (long)it->m_fX == lx && (long)it->m_fY == ly)
			{
				*it = aAtlasMarkInfo;
				return;
			}
		}

		m_AtlasBossInfoVector.push_back(aAtlasMarkInfo);
	}
	else if (GetDungeonNPC(mobVnum))
	{
		if (time > 0)
			aAtlasMarkInfo.time = ELTimer_GetMSec() + (time * 1000);

		aAtlasMarkInfo.m_byType = TYPE_NPC;
		aAtlasMarkInfo.m_fScreenX = aAtlasMarkInfo.m_fX / m_fAtlasMaxX * m_fAtlasImageSizeX - (float)m_DungeonMark.GetWidth() / 2.0f;
		aAtlasMarkInfo.m_fScreenY = aAtlasMarkInfo.m_fY / m_fAtlasMaxY * m_fAtlasImageSizeY - (float)m_DungeonMark.GetHeight() / 2.0f;

		for (TAtlasMarkInfoVector::iterator it = m_AtlasDungeonInfoVector.begin(); it != m_AtlasDungeonInfoVector.end(); ++it)
		{
			if (it->m_dwMobVnum == mobVnum && (long)it->m_fX == lx && (long)it->m_fY == ly)
			{
				*it = aAtlasMarkInfo;
				return;
			}
		}

		m_AtlasDungeonInfoVector.push_back(aAtlasMarkInfo);
	}
	else
#endif
	{
		switch (byType)
		{
		case CActorInstance::TYPE_NPC:
			aAtlasMarkInfo.m_byType = TYPE_NPC;
			m_AtlasNPCInfoVector.push_back(aAtlasMarkInfo);
			break;

		case CActorInstance::TYPE_WARP:
			aAtlasMarkInfo.m_byType = TYPE_WARP;
			{
				int iPos = aAtlasMarkInfo.m_strText.find(" ");
				if (iPos >= 0)
					aAtlasMarkInfo.m_strText[iPos] = 0;
			}

			m_AtlasWarpInfoVector.push_back(aAtlasMarkInfo);

			break;
		}
	}
}

# Search

	m_AtlasWarpInfoVector.clear();

# Add after

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
	m_AtlasDungeonInfoVector.clear();
	m_AtlasBossInfoVector.clear();
#endif

# Search

	pSubImage = (CGraphicSubImage*)CResourceManager::Instance().GetResourcePointer(strWhiteMark.c_str());
	m_WhiteMark.SetImagePointer(pSubImage);

# Add after

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
	CGraphicImage* pDungeonMarkImage = (CGraphicImage*)CResourceManager::Instance().GetResourcePointer(strDungeonMark.c_str());
	if (!pDungeonMarkImage || pDungeonMarkImage->IsEmpty())
		pDungeonMarkImage = (CGraphicImage*)CResourceManager::Instance().GetResourcePointer(strDungeonMark.c_str());
	m_DungeonMark.SetImagePointer(pDungeonMarkImage);

	CGraphicImage* pBossMarkImage = (CGraphicImage*)CResourceManager::Instance().GetResourcePointer(strBossMark.c_str());
	if (!pBossMarkImage || pBossMarkImage->IsEmpty())
		pBossMarkImage = (CGraphicImage*)CResourceManager::Instance().GetResourcePointer(strBossMark.c_str());
	m_BossMark.SetImagePointer(pBossMarkImage);
#endif

# Search

	const std::string strBossMark = strImageRoot + "minimap/bossmark.tga";

# Change

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
	const std::string strDungeonMark = strImageRoot + "minimap/dungeon_mark.tga";
	const std::string strBossMark = strImageRoot + "minimap/boss_mark_new.tga";
#else
	const std::string strBossMark = strImageRoot + "minimap/bossmark.tga";
#endif

# Search

	STATEMANAGER.SetRenderState(D3DRS_TEXTUREFACTOR, CInstanceBase::GetIndexedNameColor(CInstanceBase::NAMECOLOR_WARP));
	aIterator = m_WarpPositionVector.begin();
	while (aIterator != m_WarpPositionVector.end())
	{
		TMarkPosition& rPosition = *aIterator;
		m_WhiteMark.SetPosition(rPosition.m_fX, rPosition.m_fY);
		m_WhiteMark.Render();
		++aIterator;
	}

# Add after

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
	STATEMANAGER.SetRenderState(D3DRS_TEXTUREFACTOR, 0xFFFFFFFF);
	aIterator = m_DungeonPositionVector.begin();

	while (aIterator != m_DungeonPositionVector.end())
	{
		TMarkPosition& rPosition = *aIterator;
		m_DungeonMark.SetPosition(rPosition.m_fX, rPosition.m_fY);
		m_DungeonMark.Render();
		++aIterator;
	}

	//STATEMANAGER.SetRenderState(D3DRS_TEXTUREFACTOR, CInstanceBase::GetIndexedNameColor(CInstanceBase::NAMECOLOR_BOSS));
	STATEMANAGER.SetRenderState(D3DRS_TEXTUREFACTOR, 0xFFFFFFFF);
	aIterator = m_BossPositionVector.begin();

	while (aIterator != m_BossPositionVector.end())
	{
		TMarkPosition& rPosition = *aIterator;
		m_BossMark.SetPosition(rPosition.m_fX, rPosition.m_fY);
		m_BossMark.Render();
		++aIterator;
	}
#endif

#Search

		else if (pkInstEach->IsEnemy())
		{
			aMarkPosition.m_fX = (m_fWidth - (float)m_WhiteMark.GetWidth()) / 2.0f + fDistanceFromCenterX + m_fScreenX;
			aMarkPosition.m_fY = (m_fHeight - (float)m_WhiteMark.GetHeight()) / 2.0f + fDistanceFromCenterY + m_fScreenY;
			m_MonsterPositionVector.push_back(aMarkPosition);
		}

# Change

		else if (pkInstEach->IsEnemy())
		{
#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
			//if (pkInstEach->IsBoss())
			if (IsBoss(pkInstEach->GetRace()))
			{
				aMarkPosition.m_fX = (m_fWidth - (float)m_BossMark.GetWidth()) / 2.0f + fDistanceFromCenterX + m_fScreenX;
				aMarkPosition.m_fY = (m_fHeight - (float)m_BossMark.GetHeight()) / 2.0f + fDistanceFromCenterY + m_fScreenY;

				m_BossPositionVector.push_back(aMarkPosition);
			}
			else
#endif
			{
				aMarkPosition.m_fX = (m_fWidth - (float)m_WhiteMark.GetWidth()) / 2.0f + fDistanceFromCenterX + m_fScreenX;
				aMarkPosition.m_fY = (m_fHeight - (float)m_WhiteMark.GetHeight()) / 2.0f + fDistanceFromCenterY + m_fScreenY;

				m_MonsterPositionVector.push_back(aMarkPosition);
			}
		}

# Search

		else if (pkInstEach->IsNPC())
		{
			aMarkPosition.m_fX = (m_fWidth - (float)m_WhiteMark.GetWidth()) / 2.0f + fDistanceFromCenterX + m_fScreenX;
			aMarkPosition.m_fY = (m_fHeight - (float)m_WhiteMark.GetHeight()) / 2.0f + fDistanceFromCenterY + m_fScreenY;
			m_NPCPositionVector.push_back(aMarkPosition);
		}

# Change

		else if (pkInstEach->IsNPC())
		{

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
			if (IsBoss(pkInstEach->GetRace()))
			{
				aMarkPosition.m_fX = (m_fWidth - (float)m_BossMark.GetWidth()) / 2.0f + fDistanceFromCenterX + m_fScreenX;
				aMarkPosition.m_fY = (m_fHeight - (float)m_BossMark.GetHeight()) / 2.0f + fDistanceFromCenterY + m_fScreenY;
				m_BossPositionVector.push_back(aMarkPosition);
			}
			else if (GetDungeonNPC(pkInstEach->GetRace()))
			{
				aMarkPosition.m_fX = (m_fWidth - (float)m_DungeonMark.GetWidth()) / 2.0f + fDistanceFromCenterX + m_fScreenX;
				aMarkPosition.m_fY = (m_fHeight - (float)m_DungeonMark.GetHeight()) / 2.0f + fDistanceFromCenterY + m_fScreenY;
				m_DungeonPositionVector.push_back(aMarkPosition);
			}
			else
#endif
			{
				aMarkPosition.m_fX = (m_fWidth - (float)m_WhiteMark.GetWidth()) / 2.0f + fDistanceFromCenterX + m_fScreenX;
				aMarkPosition.m_fY = (m_fHeight - (float)m_WhiteMark.GetHeight()) / 2.0f + fDistanceFromCenterY + m_fScreenY;
				m_NPCPositionVector.push_back(aMarkPosition);
			}
		
		}

# Search

	m_NPCPositionVector.clear();

# Add after

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
	m_BossPositionVector.clear();
	m_DungeonPositionVector.clear();
#endif