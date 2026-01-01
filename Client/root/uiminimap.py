# Search 

class AtlasWindow(ui.ScriptWindow):


#Search in 

	def OnUpdate(self):

# Change

	def OnUpdate(self):

		if not self.tooltipInfo:
			return

		if not self.infoGuildMark:
			return

		self.infoGuildMark.Hide()
		self.tooltipInfo.Hide()
		if app.ENABLE_DUNGEON_BOSS_ICON_IN_MAP:
			self.tooltipInfoEx.Hide()

		if FALSE == self.board.IsIn():
			return

		(mouseX, mouseY) = wndMgr.GetMousePosition()
		if app.ENABLE_DUNGEON_BOSS_ICON_IN_MAP:
			(bFind, sName, iPosX, iPosY, dwTextColor, dwGuildID, respawnTime, isBoss) = miniMap.GetAtlasInfo(mouseX, mouseY)
		else:
			(bFind, sName, iPosX, iPosY, dwTextColor, dwGuildID) = miniMap.GetAtlasInfo(mouseX, mouseY)

		if FALSE == bFind:
			return

		if "empty_guild_area" == sName:
			sName = localeInfo.GUILD_EMPTY_AREA
	
		(x, y) = self.GetGlobalPosition()
		if isBoss:
			self.tooltipInfoEx.SetText(localeInfo.ATLAS_WINDOW_RESPAWN % self.FormatTime(respawnTime))
			self.tooltipInfoEx.SetTooltipPosition(mouseX - x - 5, mouseY - y - 14)
			self.tooltipInfoEx.Show()
			self.tooltipInfoEx.SetTop()

			self.tooltipInfo.SetText("%s(%d, %d)" % (sName, iPosX, iPosY))
			self.tooltipInfo.SetTooltipPosition(mouseX - x - 5, mouseY - y)
		else:
			self.tooltipInfo.SetText("%s(%d, %d)" % (sName, iPosX, iPosY))
			self.tooltipInfo.SetTooltipPosition(mouseX - x, mouseY - y)
		self.tooltipInfo.SetTextColor(dwTextColor)
		self.tooltipInfo.Show()
		self.tooltipInfo.SetTop()

		if 0 != dwGuildID:
			textWidth, textHeight = self.tooltipInfo.GetTextSize()
			self.infoGuildMark.SetIndex(dwGuildID)
			self.infoGuildMark.SetPosition(mouseX - x - textWidth - 18 - 5, mouseY - y)
			self.infoGuildMark.Show()

# Add in class AtlasWindow(ui.ScriptWindow):

	if app.ENABLE_DUNGEON_BOSS_ICON_IN_MAP:
		def FormatTime(self, milliseconds):
			if milliseconds <= 0:
				return "Alive"
			seconds = int((milliseconds + 999) / 1000)
			m, s = divmod(seconds, 60)
			h, m = divmod(m, 60)
			d, h = divmod(h, 24)
			text = ""
			if d > 0:
				text+="{}d ".format(d)
			if h > 0:
				text+="{}h ".format(h)
			if m > 0:
				text+="{}m ".format(m)
			if s > 0:
				text+="{}s ".format(s)

			return text[:len(text)-1] if len(text) > 0 else "None"

# Search

		self.tooltipInfo.SetParent(self.board)

# Add after

		if app.ENABLE_DUNGEON_BOSS_ICON_IN_MAP:
			self.tooltipInfoEx.SetParent(self.board)

# Search

		self.tooltipInfo = MapTextToolTip()
		self.tooltipInfo.Hide()

# Add after

		if app.ENABLE_DUNGEON_BOSS_ICON_IN_MAP:
			self.tooltipInfoEx = MapTextToolTip()
			self.tooltipInfoEx.Hide()

