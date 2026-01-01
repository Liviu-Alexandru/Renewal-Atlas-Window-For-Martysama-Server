# Search

static void regen_spawn_dungeon(LPREGEN regen, LPDUNGEON pDungeon, bool bOnce)

# Add the final function

		if (ch && !bOnce)
		{
			ch->SetRegen(regen);
#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
			if (SECTREE_MANAGER::instance().MarkNPCPositionAlive(ch->GetMapIndex(), regen->vnum))
				SECTREE_MANAGER::instance().BroadcastNPCPosition(ch->GetMapIndex());
#endif
		}
	}

# Search

static void regen_spawn(LPREGEN regen, bool bOnce)

# Add the final function

		if (ch && !bOnce)
		{
			ch->SetRegen(regen);
#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
			if (SECTREE_MANAGER::instance().MarkNPCPositionAlive(ch->GetMapIndex(), regen->vnum))
				SECTREE_MANAGER::instance().BroadcastNPCPosition(ch->GetMapIndex());
#endif
		}
	}

# Search

			if (regen->type == REGEN_TYPE_MOB)
			{
				const CMob* p = CMobManager::instance().Get(regen->vnum);
				if (!p)
				{
					sys_err("No mob data by vnum %u", regen->vnum);
				}
				else if (p->m_table.bType == CHAR_TYPE_NPC || p->m_table.bType == CHAR_TYPE_WARP || p->m_table.bType == CHAR_TYPE_GOTO)
				{
					SECTREE_MANAGER::instance().InsertNPCPosition(lMapIndex,
						p->m_table.bType,
						p->m_table.szLocaleName,
						(regen->sx + regen->ex) / 2 - base_x,
						(regen->sy + regen->ey) / 2 - base_y);
				}
			}

# Change

			if (regen->type == REGEN_TYPE_MOB)
			{
				const CMob* p = CMobManager::instance().Get(regen->vnum);
				if (!p)
				{
					sys_err("No mob data by vnum %u", regen->vnum);
				}
#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
				else if (p->m_table.bType == CHAR_TYPE_NPC || p->m_table.bType == CHAR_TYPE_WARP || p->m_table.bType == CHAR_TYPE_GOTO || (p->m_table.bType == CHAR_TYPE_MONSTER && (p->m_table.bRank >= MOB_RANK_BOSS || tmp.time > 0)))
				{
					SECTREE_MANAGER::instance().InsertNPCPosition(lMapIndex,
						p->m_table.bType,
						regen->vnum,
						(regen->sx + regen->ex) / 2 - base_x,
						(regen->sy + regen->ey) / 2 - base_y, tmp.time);
				}
#else
				else if (p->m_table.bType == CHAR_TYPE_NPC || p->m_table.bType == CHAR_TYPE_WARP || p->m_table.bType == CHAR_TYPE_GOTO)
				{
					SECTREE_MANAGER::instance().InsertNPCPosition(lMapIndex,
						p->m_table.bType,
						p->m_table.szLocaleName,
						(regen->sx + regen->ex) / 2 - base_x,
						(regen->sy + regen->ey) / 2 - base_y);
				}
#endif
			}
#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
			else if (regen->type == REGEN_TYPE_GROUP)
			{
				CMobGroup * pkGroup = CMobManager::Instance().GetGroup(regen->vnum);
				if (pkGroup)
				{
					const std::vector<DWORD> & c_rdwMembers = pkGroup->GetMemberVector();
					const CMob * p = CMobManager::instance().Get(c_rdwMembers[0]);

					if (!p)
					{
						sys_err("In %s, No mob data by vnum %u", filename, c_rdwMembers[0]);
					}
					else if (p->m_table.bType == CHAR_TYPE_MONSTER && (p->m_table.bRank >= MOB_RANK_BOSS || tmp.time > 0))
					{
						SECTREE_MANAGER::instance().InsertNPCPosition(lMapIndex,
							p->m_table.bType,
							c_rdwMembers[0],
							(regen->sx + regen->ex) / 2 - base_x,
							(regen->sy + regen->ey) / 2 - base_y, tmp.time);
					}
				}
			}
			else if (regen->type == REGEN_TYPE_GROUP_GROUP)
			{
				const DWORD dwGroupID = CMobManager::Instance().GetGroupFromGroupGroup(regen->vnum);
				if(dwGroupID != 0)
				{
					CMobGroup * pkGroup = CMobManager::Instance().GetGroup(dwGroupID);
					if (pkGroup)
					{
						const std::vector<DWORD> & c_rdwMembers = pkGroup->GetMemberVector();
						const CMob * p = CMobManager::instance().Get(c_rdwMembers[0]);
						if (!p)
						{
							sys_err("In %s, No mob data by vnum %u", filename, c_rdwMembers[0]);
						}
						else if (p->m_table.bType == CHAR_TYPE_MONSTER && (p->m_table.bRank >= MOB_RANK_BOSS || tmp.time > 0))
						{
							SECTREE_MANAGER::instance().InsertNPCPosition(lMapIndex,
								p->m_table.bType,
								c_rdwMembers[0],
								(regen->sx + regen->ex) / 2 - base_x,
								(regen->sy + regen->ey) / 2 - base_y, tmp.time);
						}
					}
				}
			}
#endif
