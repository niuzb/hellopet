
#include "SkillDispMgr.h"
#include "../../Particle/ParticleManager.h"
#include "GameResourceManager.h"
#include <libxml/parser.h>

SkillDispMgr::SkillDispMgr()
{
}

SkillDispMgr::~SkillDispMgr()
{
	ClearCollisionBoxAnim();
//	m_roleAllSkillID.clear();
	//m_mapSkillIdAndUserSkillInfo.clear();
//	m_ownCD.clear();
//    m_shareCD.clear();
	m_TableAnimatiionMap.clear();
	m_TableBoxAnimation.clear();
	m_TableSkillInfo.clear();
	m_mapSlotIndexAndInfo.clear();
}

bool SkillDispMgr::AddSkillInfo(SKILL_INFO & skill)
{
	if (m_TableSkillInfo.find(skill.Id) != m_TableSkillInfo.end())
	{
		return false;
	}

	m_TableSkillInfo[skill.Id] = skill;
	return true;
}

void SkillDispMgr::RemoveSkillInfo(SKILL_INFO & skill)
{
	map<unsigned int , SKILL_INFO>::iterator it = m_TableSkillInfo.find(skill.Id);
	if ( it != m_TableSkillInfo.end())
	{
		m_TableSkillInfo.erase(it);
	}
}

const SKILL_INFO* SkillDispMgr::GetSkillInfo(unsigned int skillId /* = 0 */)
{
	map<unsigned int , SKILL_INFO>::iterator it = m_TableSkillInfo.find(skillId);
	if ( it != m_TableSkillInfo.end())
	{
		return &(it->second);
	}

	return NULL;
}

const	FAIRY_SKILL_INFO* SkillDispMgr::GetFairySkillInfo( unsigned int skillId /*= 0*/ )
{
	map<unsigned int , FAIRY_SKILL_INFO>::iterator it = m_fairySkillInfo.find(skillId);
	if ( it != m_fairySkillInfo.end())
	{
		return &(it->second);
	}

	return NULL;
}

void SkillDispMgr::StopLoopSound(int skillId)
{
	const SKILL_INFO *pInfo = GetSkillInfo(skillId);
	if (0 != pInfo)
	{
		if (pInfo->bSoundLoop)
		{
//			GameAudioManager::sharedManager()->stopEffect(pInfo->SoundId);
		}		
	}	
}


bool SkillDispMgr::AddCollisionBoxAnim(unsigned int Id, ABoxAnimation* boxAnimation)
{
	if (m_TableBoxAnimation.find(Id) != m_TableBoxAnimation.end())
	{
		return false;
	}

	m_TableBoxAnimation[Id] = boxAnimation;
	return true;
}

ABoxAnimation* SkillDispMgr::GetCollisionBoxAnim(unsigned int Id)
{
	map<unsigned int , ABoxAnimation* >::iterator it = m_TableBoxAnimation.find(Id);
	if (it != m_TableBoxAnimation.end())
	{
		return it->second;
	}

	return NULL;
}

void SkillDispMgr::ClearCollisionBoxAnim()
{
	map<unsigned int , ABoxAnimation* >::iterator it = m_TableBoxAnimation.begin();
	for (; it != m_TableBoxAnimation.end(); it++)
	{
		ABoxAnimation* ety = it->second;
		delete ety;
		it->second = NULL;
	}

	m_TableBoxAnimation.clear();
}

void SkillDispMgr::Load( const char* pSkillFile, const char* pAnimationTableFile )
{
	LoadAnimationTable(pAnimationTableFile);
	LoadSkill(pSkillFile);
}

void SkillDispMgr::LoadAnimationTable( const  char* pFile )
{
	char *xmlString =(char*) GameResourceManager::sharedManager()->loadXml(pFile);
	xmlDocPtr pDoc = xmlReadMemory(xmlString, strlen(xmlString), NULL, "UTF-8", XML_PARSE_RECOVER);
	xmlNodePtr pRoot = xmlDocGetRootElement(pDoc);
	if(pRoot != NULL)
	{



		xmlNodePtr pAnimationNode = pRoot->children;
		while (pAnimationNode != NULL)
		{
			if(xmlStrcmp(pAnimationNode->name, BAD_CAST"animation") == 0)
			{
				unsigned int id = -1;
				ANIMATION_DIRECTION_ID adi;
				xmlNodePtr pChildren = pAnimationNode->children;
				while(pChildren != NULL)
				{
					if(xmlStrcmp(pChildren->name, BAD_CAST"left") == 0)
					{
						char* pIDString = (char*)xmlNodeGetContent(pChildren);
						if(pIDString)
						{
							id = (unsigned int)atoi(pIDString);
							xmlFree(pIDString);
						}

					}
					else if(xmlStrcmp(pChildren->name, BAD_CAST"down") == 0)
					{
						char* pIDString = (char*)xmlNodeGetContent(pChildren);
						if(pIDString)
						{
							adi.down = (unsigned int)atoi(pIDString);
							xmlFree(pIDString);
						}

					}
					else if(xmlStrcmp(pChildren->name, BAD_CAST"up") == 0)
					{
						char* pIDString = (char*)xmlNodeGetContent(pChildren);
						if(pIDString)
						{
							adi.up = (unsigned int)atoi(pIDString);
							xmlFree(pIDString);
						}

					}
					pChildren = pChildren->next;
				}

				if(id != -1)
				{
					m_TableAnimatiionMap[id] = adi;
				}
			}
			pAnimationNode = pAnimationNode->next;
		}
	}
	free(xmlString);
	xmlFreeDoc(pDoc);
}

void SkillDispMgr::LoadSkill( const char* pFile )
{
	// 这个地方一定需要手动释放!!!!!!
	char *xmlString =(char*) GameResourceManager::sharedManager()->loadXml(pFile);

//	m_roleAllSkillID.clear();

	xmlDocPtr pDoc = xmlReadMemory(xmlString, strlen(xmlString), NULL, "UTF-8", XML_PARSE_RECOVER);
	xmlNodePtr pRoot = xmlDocGetRootElement(pDoc);
	xmlNodePtr pSkillNode = pRoot->children;
	while (pSkillNode != NULL)
	{
		if(xmlStrcmp(pSkillNode->name, BAD_CAST"skill") == 0)
		{
			SKILL_INFO skillInfo;
			skillInfo.Id = -1;
			xmlNodePtr pChildren = pSkillNode->children;
			while(pChildren != NULL)
			{
				if(xmlStrcmp(pChildren->name, BAD_CAST"skill_id") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.Id = (unsigned int)atoi(pString);
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"part") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.partID = (unsigned int)atoi(pString);
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"action_name") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.actionName = pString;
						skillInfo.type = GetTypeFromActionName(skillInfo.actionName);
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"skill_icon") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.actionIcon = pString;
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"animation_id") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.animationID = (unsigned int)atoi(pString);
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"link_skill") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.linkSkillId = atoi(pString);
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"link_time") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.linkTime = (float)atoi(pString);
						skillInfo.linkTime /= 1000.0f; 
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"displacement") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.displacement = (unsigned int)atoi(pString);
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"beat_back_distance") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.beatBackDistance = (unsigned int)atoi(pString);
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"is_special") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.isSpecial = atoi(pString) ? true : false;
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"can_common_break") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.canCommonBreak = atoi(pString) ? true : false;
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"can_special_break") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.canSpecialBreak = atoi(pString) ? true : false;
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"damage") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.damage = (unsigned int)atoi(pString);
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"critical_rate") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.criticalRate = (unsigned int)atoi(pString);
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"sound_id") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.SoundId = (unsigned int)atoi(pString);
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"effectsoundID") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.effectsoundID = (unsigned int)atoi(pString);
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"continue_time") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.continueTime = (unsigned int)atof(pString);
						skillInfo.continueTime /= 1000.0f;
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"can_control") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.canControl = atoi(pString) ? true : false;
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"which_time") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.whichTime = atoi(pString);
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"can_attack_number") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.attackNumber = atoi(pString);
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"sound_loop") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.bSoundLoop = (atoi(pString) != 0);
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"is_aim") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.aim = (SKILL_INFO::AIM_TYPE)atoi(pString);
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"effectID") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.effectId = atoi(pString);
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"linkeffectID") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.linkEffectId = atoi(pString);
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"longdistance_attackrange") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.longDistanceAttackRange = atoi(pString);
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"longdistance_effectspeed") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.longDistanceEffectSpeed = atof(pString);
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"is_showfaraway") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.bShowFarWay = atoi(pString) ? true : false;
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"is_disappear") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.bDisappear = atoi(pString) ? true : false;
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"transparency") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.alpha = atof(pString) / 100.0f;
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"own_cd") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.ownCD = atof(pString) / 1000.0f;
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"share_cd") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.shareCD = atof(pString) / 1000.0f;
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"adaptation_distance") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.bAdaptationDistance = atoi(pString) == 1;
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"based_on_frame") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.bBasedOnFrame = atoi(pString) == 1;
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"is_buff") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.bBuff = atoi(pString) == 1 ? true : false;
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"skill_type") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.attackType = (tagSkillInfo::ATTACK_TYPE)atoi(pString);
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"when_shakescreen") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.iShakeCamera = atoi(pString);
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"sound_voice_id") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.boyVoiceID = (unsigned int)atoi(pString);
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"sound_voice_woman_id") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.girleVoiceID = (unsigned int)atoi(pString);
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"rage_point") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.ragePoint = (unsigned int)atoi(pString);
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"is_invincible") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.bInvincible = (unsigned int)atoi(pString) == 1;
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"skill_priority") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.skillPriority = (unsigned int)atoi(pString);
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"skill_conflict") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.skillConflict = (unsigned int)atoi(pString);
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"effectLayer") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.effectZOrder = (SKILL_INFO::EFFECT_Z_ORDER)atoi(pString);
						xmlFree(pString);
					}

				}
				else if(xmlStrcmp(pChildren->name, BAD_CAST"is_effectrotate") == 0)
				{
					char* pString = (char*)xmlNodeGetContent(pChildren);
					if(pString)
					{
						skillInfo.bRotateEffect = atoi(pString) > 0 ? true : false;
						xmlFree(pString);
					}

				}

				pChildren = pChildren->next;
			}

			if(skillInfo.Id != -1)
			{
				if(skillInfo.partID == 1)
				{
				//	std::map< RoleJobType, std::vector<int> >::iterator iter = m_roleAllSkillID.find(skillInfo.roleType);
				//	if(iter == m_roleAllSkillID.end())
				//	{
				//		std::vector<int> skillID;
				//		if(skillInfo.type == ToNormalAttack)
				//		{
				//			skillID.push_back(skillInfo.Id);
				//		}
				//		else
				//		{
				//			skillID.push_back(-1);
				//			skillID.push_back(skillInfo.Id);
				//		}
				//		m_roleAllSkillID.insert(std::make_pair((RoleJobType)skillInfo.roleType, skillID));		// 男性角色
				//		m_roleAllSkillID.insert(std::make_pair((RoleJobType)(skillInfo.roleType + 1), skillID));	// 女性角色

				//	}
				//	else
				//	{
				//		if(skillInfo.type == ToNormalAttack)
				//		{
				//			iter->second[0] = skillInfo.Id;
				//			m_roleAllSkillID[(RoleJobType)(skillInfo.roleType + 1)][0] = skillInfo.Id;
				//		}
				//		else
				//		{
				//			iter->second.push_back(skillInfo.Id);
				//			m_roleAllSkillID[(RoleJobType)(skillInfo.roleType + 1)].push_back(skillInfo.Id);
				//		}


				//	}
				}
				
				m_TableSkillInfo[skillInfo.Id] = skillInfo;
			}
		}
		pSkillNode = pSkillNode->next;
	}

	free(xmlString);
	xmlFreeDoc(pDoc);

	for(std::map<unsigned int, SKILL_INFO>::iterator iter = m_TableSkillInfo.begin(); iter != m_TableSkillInfo.end(); iter++)
	{
		if(iter->second.partID == 1)
		{
			iter->second.firstSkillID = iter->second.Id;
			std::map<unsigned int, SKILL_INFO>::iterator iterChild = iter;
			while(true)
			{
				
				if(iterChild->second.linkSkillId > 0)
				{
					iterChild = m_TableSkillInfo.find(iterChild->second.linkSkillId);
					/*if(iterChild->second.type == ToNormalAttack)
						iterChild->second.firstSkillID = iterChild->second.Id;
					else
						iterChild->second.firstSkillID = iter->second.Id;*/
				}
				else
				{
					break;
				}
				
			}

		}
	}
}

EventType SkillDispMgr::GetTypeFromActionName( const std::string& name )
{
	EventType type = ToNormalAttack;

	return type;
}

void SkillDispMgr::clearCD()
{
 //   m_shareCD.clear();
//    m_ownCD.clear();
}

//void SkillDispMgr::SetCD( PLAYER_ID userID, int skillID )
//{
//	UserSkillInfo info;
//	if(GetOneSkillInfoById(userID, skillID, info))
//	{
//		std::map<PLAYER_ID, float>::iterator shareCDIter = m_shareCD.find(userID);
//		if(shareCDIter != m_shareCD.end())
//		{
//			shareCDIter->second = info.share_cd();
//		}
//		else
//		{
//			m_shareCD.insert(std::make_pair(userID, info.share_cd()));
//		}
//		
//		std::map<PLAYER_ID, std::map<int, float> >::iterator userOwnCDIter = m_ownCD.find(userID);
//
//		float exSpeed = 0.0f;
//		USERINFO* pUserInfo = UserData::Get()->GetUserInfo(userID);
//		if(pUserInfo)
//		{
//			exSpeed = pUserInfo->speed;
//		}
//
//		float ownTime = info.own_cd();
//		ownTime *= (1.0f - 0.001f * exSpeed);
//		if(ownTime < 0.0f)
//			ownTime = 0.0f;
//
//		if(userOwnCDIter != m_ownCD.end())
//		{
//			std::map<int, float>::iterator iter = userOwnCDIter->second.find(skillID);
//			if(iter != userOwnCDIter->second.end())
//			{
//				iter->second = ownTime;
//
//			}
//			else
//			{
//				userOwnCDIter->second.insert(std::make_pair(skillID, ownTime));
//			}
//		}
//		else
//		{
//			std::map<int, float> skillOwnCD;
//			skillOwnCD.insert(std::make_pair(skillID, ownTime));
//			m_ownCD[userID] = skillOwnCD;
//		}
//		// CCLOG("SetCD : %f, %f", m_shareCD, m_ownCD[skillID]);
//	}
//}

//bool SkillDispMgr::IsCD( PLAYER_ID userID, int skillID )
//{
//	std::map<PLAYER_ID, float>::iterator shareCDIter = m_shareCD.find(userID);
//	if(shareCDIter != m_shareCD.end())
//	{
//		if(shareCDIter->second <= 0.0f)
//		{
//			std::map<PLAYER_ID, std::map<int, float> >::iterator userOwnCDIter = m_ownCD.find(userID);
//			if(userOwnCDIter != m_ownCD.end())
//			{
//				std::map<int, float>::iterator iter = userOwnCDIter->second.find(skillID);
//				if(iter != userOwnCDIter->second.end())
//				{
//					if(iter->second <= 0.0f)
//					{
//						return false;
//					}
//					else
//					{
//						return true;
//					}
//				}
//				else
//				{
//					return false;
//				}
//			}
//		}
//		else
//		{
//			return true;
//		}
//	}
//	return false;
//}

//bool  SkillDispMgr::PushOneSKillUserInfoToTable(PLAYER_ID userID, unsigned int skillId,UserSkillInfo skillInfo)
//{
//	std::map<PLAYER_ID, std::map< unsigned int, UserSkillInfo > >::iterator iterSkillInfo = m_mapSkillIdAndUserSkillInfo.find(userID);
//	if(iterSkillInfo != m_mapSkillIdAndUserSkillInfo.end())
//	{
//		std::map< unsigned int, UserSkillInfo >::iterator iter = iterSkillInfo->second.find(skillId);
//		if (iter == iterSkillInfo->second.end())
//		{
//			iterSkillInfo->second.insert(std::make_pair(skillId,skillInfo));
//		}
//		else
//		{
//			(*iter).second = skillInfo;
//		}
//	}
//	else
//	{
//		std::map< unsigned int, UserSkillInfo > userSkillmap;
//		userSkillmap.insert(std::make_pair(skillId, skillInfo));
//		m_mapSkillIdAndUserSkillInfo.insert(std::make_pair(userID, userSkillmap));
//	}
//	
//	return true;
//}

void SkillDispMgr::ClearUserSkillData()
{
//	m_mapSkillIdAndUserSkillInfo.clear();
	m_mapSlotIndexAndInfo.clear();
//	m_shareCD.clear();
//	m_ownCD.clear();
}

bool SkillDispMgr::PushOneSlotInfoToTable(unsigned int slotIndex,unsigned int skillId)
{
	if (skillId == 0)
	{
		std::map< unsigned int, SKILL_SLOT_INFO >::iterator iter = m_mapSlotIndexAndInfo.find(slotIndex);
		if (iter != m_mapSlotIndexAndInfo.end())
		{
			m_mapSlotIndexAndInfo.erase(iter);
		}
	}
	else
	{
		std::map< unsigned int, SKILL_SLOT_INFO >::iterator iter = m_mapSlotIndexAndInfo.find(slotIndex);
		if (iter == m_mapSlotIndexAndInfo.end())
		{
			SKILL_SLOT_INFO slotInfo;
			slotInfo.slotIndex = slotIndex;
			slotInfo.skillId = skillId;
			m_mapSlotIndexAndInfo.insert(std::make_pair(slotIndex,slotInfo));
		}
		else
		{
			(*iter).second.skillId = skillId;
		}
	}
	return true;
}

//bool SkillDispMgr::GetOneSkillInfoById(PLAYER_ID userID, unsigned int skillid,UserSkillInfo& userSkillInfo)
//{
//	std::map<unsigned int, SKILL_INFO>::iterator skillIter = m_TableSkillInfo.find(skillid);
//	if(skillIter != m_TableSkillInfo.end())
//	{
//		skillid = skillIter->second.firstSkillID;
//		std::map<PLAYER_ID, std::map< unsigned int, UserSkillInfo > >::iterator iterSkillInfo = m_mapSkillIdAndUserSkillInfo.find(userID);
//		if(iterSkillInfo != m_mapSkillIdAndUserSkillInfo.end())
//		{
//			std::map< unsigned int, UserSkillInfo >::iterator iter = iterSkillInfo->second.find(skillid);
//			if (iter != iterSkillInfo->second.end())
//			{
//				userSkillInfo = (*iter).second;
//				return true;
//			}
//		}
//	}
//	return false;
//}

void SkillDispMgr::Update( float dt )
{
	/*for(std::map<PLAYER_ID, float>::iterator iter = m_shareCD.begin(); iter != m_shareCD.end(); iter++)
	{
	iter->second -= dt;
	}*/

	// CCLOG("m_shareCD : %f, dt : %f", m_shareCD, dt);
	//for(std::map<PLAYER_ID, std::map<int, float> >::iterator userIter = m_ownCD.begin(); userIter != m_ownCD.end(); userIter++)
	//{
	//	for(std::map<int, float>::iterator iter = userIter->second.begin(); iter != userIter->second.end(); )
	//	{
	//		//CCLOG(" ownCD : %ld, %f", iter->first, iter->second);
	//		iter->second -= dt;
	//		if(iter->second <= 0.0f)
	//		{
	//			userIter->second.erase(iter++);
	//		}
	//		else
	//		{
	//			iter++;
	//		}
	//	}
	//}
	
}

void SkillDispMgr::LoadFairy( const char* pSkillFile, const char* pAnimationTableFile )
{
	LoadFairyAnimationTable(pAnimationTableFile);
	LoadFairySkill(pSkillFile);
}

void SkillDispMgr::LoadFairyAnimationTable( const char* pFile )
{
	char *xmlString =(char*) GameResourceManager::sharedManager()->loadXml(pFile);
	xmlDocPtr pDoc = xmlReadMemory(xmlString, strlen(xmlString), NULL, "UTF-8", XML_PARSE_RECOVER);
	xmlNodePtr pRoot = xmlDocGetRootElement(pDoc);
	
	if(pRoot != NULL)
	{
		xmlNodePtr pAnimationNode = pRoot->children;
		while (pAnimationNode != NULL)
		{
			if(xmlStrcmp(pAnimationNode->name, BAD_CAST"fairyanimation") == 0)
			{
				unsigned int upID = 0;
				unsigned int downID = 0;

				xmlAttrPtr attrPtr = pAnimationNode->properties;
				while (attrPtr != NULL)
				{
					if (!xmlStrcmp(attrPtr->name, BAD_CAST "face_up"))
					{
						xmlChar* szAttr = xmlGetProp(pAnimationNode,BAD_CAST "face_up");
						upID = (unsigned int)atoi((const char*)szAttr);
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "face_down"))
					{
						xmlChar* szAttr = xmlGetProp(pAnimationNode, BAD_CAST "face_down");
						downID = (unsigned int)atoi((const char*)szAttr);
						xmlFree(szAttr);
					}
					attrPtr = attrPtr->next;
				}

				m_fairyAnimationMap.insert(std::make_pair(upID, downID));

			}
			pAnimationNode = pAnimationNode->next;
		}
	}

	free(xmlString);
	xmlFreeDoc(pDoc);
}

void SkillDispMgr::LoadFairySkill( const char* pFile )
{
	char *xmlString =(char*) GameResourceManager::sharedManager()->loadXml(pFile);
	xmlDocPtr pDoc = xmlReadMemory(xmlString, strlen(xmlString), NULL, "UTF-8", XML_PARSE_RECOVER);
	xmlNodePtr pRoot = xmlDocGetRootElement(pDoc);

	if(pRoot != NULL)
	{
		xmlNodePtr pChildrenNode = pRoot->children;
		while (pChildrenNode != NULL)
		{
			if(xmlStrcmp(pChildrenNode->name, BAD_CAST"fairyskill") == 0)
			{
				FAIRY_SKILL_INFO skillInfo;

				xmlAttrPtr attrPtr = pChildrenNode->properties;
				while (attrPtr != NULL)
				{
					if (!xmlStrcmp(attrPtr->name, BAD_CAST "skill_ID"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "skill_ID");
						//skillInfo.id.setPlayId((uint32_t)atoi((const char*)szAttr),0,0);
						xmlFree(szAttr);
					}
					if (!xmlStrcmp(attrPtr->name, BAD_CAST "fairy_ID"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "fairy_ID");
						skillInfo.fairy_ID = (unsigned int)atoi((const char*)szAttr);
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "skill_type"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "skill_type");
						skillInfo.type = (FAIRY_SKILL_INFO::TYPE)atoi((const char*)szAttr);
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "aim_at"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "aim_at");
						skillInfo.aim = (FAIRY_SKILL_INFO::AIM)atoi((const char*)szAttr);
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "is_aim"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "is_aim");
						skillInfo.bLock = atoi((const char*)szAttr) == 1 ? true : false;
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "animation_id"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "animation_id");
						unsigned int id = (unsigned int)atoi((const char*)szAttr);
						/*skillInfo.animation[(int)DIRECTION_UP].animationID = id;
						skillInfo.animation[(int)DIRECTION_LEFT].animationID = id;
						skillInfo.animation[(int)DIRECTION_RIGHT].animationID = id;
						skillInfo.animation[(int)DIRECTION_BOTTOM].animationID = m_fairyAnimationMap[id];*/
												
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "can_attack_number"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "can_attack_number");
						skillInfo.attack_number = atoi((const char*)szAttr);
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "continue_time"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "continue_time");
						skillInfo.continueTime = atof((const char*)szAttr) / 1000.0f;
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "effect_id"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "effect_id");
						skillInfo.effectID = atoi((const char*)szAttr);
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "effect_layer"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "effect_layer");
						skillInfo.effectZOrder = (FAIRY_SKILL_INFO::EFFECT_Z_ORDER)atoi((const char*)szAttr);
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "longdistance_attackrange"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "longdistance_attackrange");
						skillInfo.longDistanceAttackRange = atoi((const char*)szAttr);
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "longdistance_effectspeed"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "longdistance_effectspeed");
						skillInfo.longDistanceEffectSpeed = atoi((const char*)szAttr);
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "sound_id"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "sound_id");
						skillInfo.soundID = atoi((const char*)szAttr);
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "effectsound_id"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "effectsound_id");
						skillInfo.effectSoundID = atoi((const char*)szAttr);
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "hurt"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "hurt");
						skillInfo.hurt = atoi((const char*)szAttr);
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "hurt_add"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "hurt_add");
						skillInfo.hurtAddValue = atoi((const char*)szAttr);
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "PhyAttack"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "PhyAttack");
						skillInfo.physical_attack = (unsigned int)atoi((const char*)szAttr);
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "MagAttack"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "MagAttack");
						skillInfo.magic_attack = (unsigned int)atoi((const char*)szAttr);
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "SkiAttack"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "SkiAttack");
						skillInfo.skill_attack = (unsigned int)atoi((const char*)szAttr);
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "PhyDefense"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "PhyDefense");
						skillInfo.physical_defence = (unsigned int)atoi((const char*)szAttr);
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "MagDefense"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "MagDefense");
						skillInfo.magic_defence = (unsigned int)atoi((const char*)szAttr);
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "SkiDefense"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "SkiDefense");
						skillInfo.skill_defence = (unsigned int)atoi((const char*)szAttr);
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "HP"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "HP");
						skillInfo.health_point = (unsigned int)atoi((const char*)szAttr);
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "Accurate"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "Accurate");
						skillInfo.accurate = (unsigned int)atoi((const char*)szAttr);
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "Dodge"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "Dodge");
						skillInfo.dodge = (unsigned int)atoi((const char*)szAttr);
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "Wreck"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "Wreck");
						skillInfo.wreck = (unsigned int)atoi((const char*)szAttr);
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "Parry"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "Parry");
						skillInfo.parry = (unsigned int)atoi((const char*)szAttr);
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "CriticalStrike"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "CriticalStrike");
						skillInfo.critical_strike = (unsigned int)atoi((const char*)szAttr);
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "Tenacity"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "Tenacity");
						skillInfo.tenacity = (unsigned int)atoi((const char*)szAttr);
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "Slay"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "Slay");
						skillInfo.slay = (unsigned int)atoi((const char*)szAttr);
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "Slowdown_speed"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "Slowdown_speed");
						skillInfo.speed = (unsigned int)atoi((const char*)szAttr);
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "own_cd"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "own_cd");
						skillInfo.ownCD = atof((const char*)szAttr);
						skillInfo.ownCD /= 1000.0f;
						xmlFree(szAttr);
					}
					attrPtr = attrPtr->next;
				}

//				m_fairySkillInfo.insert(std::make_pair(skillInfo.id.getID(), skillInfo));


			}
			pChildrenNode = pChildrenNode->next;
		}
	}

	free(xmlString);
	xmlFreeDoc(pDoc);
}

unsigned int SkillDispMgr::GetSkillIDFromSlot( int slotIndex )
{
	std::map< unsigned int, SKILL_SLOT_INFO>::iterator iter = m_mapSlotIndexAndInfo.find(slotIndex);
	if(iter != m_mapSlotIndexAndInfo.end())
	{
		return iter->second.skillId;
	}

	return 0;
}

unsigned int SkillDispMgr::GetFairySkillID( unsigned int fairyID )
{
	for(std::map<unsigned int, FAIRY_SKILL_INFO>::iterator iter = m_fairySkillInfo.begin(); iter != m_fairySkillInfo.end(); iter++)
	{
		if(iter->second.fairy_ID == fairyID)
		{
//			return iter->second.id.getID();
		}
	}

	return 0;
}

bool SkillDispMgr::IsEquipSkill( unsigned int id )
{
	for(std::map< unsigned int, SKILL_SLOT_INFO>::iterator iter = m_mapSlotIndexAndInfo.begin(); iter != m_mapSlotIndexAndInfo.end(); iter++)
	{
		if(iter->second.skillId == id)
			return true;
	}
	return false;
}
//
//unsigned int SkillDispMgr::GetNormalAttackID( PLAYER_ID userID, int roleType )
//{
//	std::map<PLAYER_ID, std::map< unsigned int, UserSkillInfo > >::iterator iterUserSkill = m_mapSkillIdAndUserSkillInfo.find(userID);
//	if(iterUserSkill != m_mapSkillIdAndUserSkillInfo.end())
//	{
//		for(std::map< unsigned int, UserSkillInfo >::iterator iter = iterUserSkill->second.begin(); iter != iterUserSkill->second.end(); iter++)
//		{
//			const SKILL_INFO* pSkill = GetSkillInfo(iter->first);
//			if(pSkill)
//			{
//				if(pSkill->type == ToNormalAttack && pSkill->partID == 1 && (pSkill->roleType == roleType || pSkill->roleType + 1 == roleType))
//				{
//					return pSkill->Id;
//				}
//			}
//		}
//	}
//	return 0;
//}

//float SkillDispMgr::getShareCDTime( PLAYER_ID userID )
//{
//	std::map<PLAYER_ID, float>::iterator iter = m_shareCD.find(userID);
//	if(iter != m_shareCD.end())
//	{
//		return iter->second;
//	}
//	return 0.0f;
//}
//
//float SkillDispMgr::getOwnCDTime( PLAYER_ID userID, int skillId )
//{
//	std::map<PLAYER_ID, std::map<int, float> >::iterator userIter = m_ownCD.find(userID);
//	if(userIter != m_ownCD.end())
//	{
//		std::map<int, float>::iterator iter = userIter->second.find(skillId);
//		if(iter != userIter->second.end())
//		{
//			
//			return iter->second;
//		}
//	}
//
//	return 0.0f;
//}
