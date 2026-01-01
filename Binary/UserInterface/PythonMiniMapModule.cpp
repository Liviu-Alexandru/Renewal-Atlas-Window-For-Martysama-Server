# Search

PyObject* miniMapGetAtlasInfo(PyObject* poSelf, PyObject* poArgs)

# Change

PyObject* miniMapGetAtlasInfo(PyObject* poSelf, PyObject* poArgs)
{
	float fScrrenX;
	if (!PyTuple_GetFloat(poArgs, 0, &fScrrenX))
		return Py_BuildException();
	float fScrrenY;
	if (!PyTuple_GetFloat(poArgs, 1, &fScrrenY))
		return Py_BuildException();

	std::string aString = "";
	float fPosX = 0.0f;
	float fPosY = 0.0f;
	DWORD dwTextColor = 0;
	DWORD dwGuildID = 0;
#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
	bool isBoss = false;
	DWORD time = 0;
	bool bFind = CPythonMiniMap::Instance().GetAtlasInfo(fScrrenX, fScrrenY, aString, &fPosX, &fPosY, &dwTextColor, &dwGuildID, &time, &isBoss);
#else
	bool bFind = CPythonMiniMap::Instance().GetAtlasInfo(fScrrenX, fScrrenY, aString, &fPosX, &fPosY, &dwTextColor, &dwGuildID);
#endif
	int iPosX, iPosY;
#ifdef _WIN64
	PR_FLOAT_TO_INT(fPosX, iPosX)
	PR_FLOAT_TO_INT(fPosY, iPosY)
#else
	PR_FLOAT_TO_INT(fPosX, iPosX);
	PR_FLOAT_TO_INT(fPosY, iPosY);
#endif
	iPosX /= 100;
	iPosY /= 100;
#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
	return Py_BuildValue("isiiliii", (int)bFind, aString.c_str(), iPosX, iPosY, (signed)dwTextColor, dwGuildID, time, isBoss);
#else
	return Py_BuildValue("isiili", (int)bFind, aString.c_str(), iPosX, iPosY, (signed)dwTextColor, dwGuildID);
#endif
}

