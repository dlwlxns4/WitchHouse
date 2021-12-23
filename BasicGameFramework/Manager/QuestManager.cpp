#include "QuestManager.h"
#include "../Object/QuestObj.h"
#include "../Object/TrapActionObj.h"
#include "../Object/PortalObj.h"

#include "../Component/TrapAction.h"

#include "../Manager/PhysicsManager.h"

#include <iostream>
using namespace std;

void QuestManager::SetQuest(int quest)
{
	currQuest = quest;
	cout << "id : " << currQuest << "\"" << (questName[currQuest]) << "\"" << endl;

}

void QuestManager::NextQuest()
{
	currQuest++;
	cout << "id : " << currQuest << "\"" << (questName[currQuest]) << "\"" << endl;

}

int QuestManager::GetQuest()
{
	return currQuest;
}

int* QuestManager::GetQuestPtr()
{


	return &currQuest;
}

void QuestManager::Init()
{
	currQuest = 10;

	questName[10] = "외딴 숲 속 한가운데";
	questName[11] = "장미를 잘라라";
	questName[12] = "마녀의 집에 들어가라";
	questName[13] = "쪽지를 읽어라";
	questName[14] = "곰인형을 얻어라";
	questName[15] = "선물상자 떨어지는 함정";
	questName[16] = "곰인형의 팔을 짤라라";

	cout << "id : " << currQuest << "\"" << (questName[currQuest]) << "\"" << endl;

}

GameObject* QuestManager::GetQuestObj(int posX, int posY)
{
	return nullptr;
}

int QuestManager::GetQuestActionObjId(int posX, int posY)
{
	return 0;
}

void QuestManager::SetQuestActionObj(int posX, int posY, GameObject* obj)
{
	questActionObjMap[posX][posY] = obj;
}

void QuestManager::AddQuestActionId(int posX, int posY)
{
	TrapActionObj* trapActionObj = (TrapActionObj*)(questActionObjMap[posX][posY]);
	if (trapActionObj != nullptr)
	{
		trapActionObj->AddMainId();
	}
}

void QuestManager::SetOffQuestActionObj(int id)
{

}

void QuestManager::SetTrapAction(int id)
{
	for (auto it = questActionObjMap.begin(); it != questActionObjMap.end(); ++it)
	{
		for (auto itt = it->second.begin(); itt != it->second.end(); ++itt)
		{
			if (((TrapActionObj*)(itt->second))->GetId() == id)
			{
				((TrapActionObj*)(itt->second))->GetComponent<TrapAction>()->SetActionStartegy((TrapActionState)(id+1));
			}
		}
	}
}

void QuestManager::DoActivateQuestObj(int id)
{
	switch (id)
	{
	case 10:
		for (auto it = questObjMap.begin(); it != questObjMap.end(); ++it)
		{
			for (auto itt = it->second.begin(); itt != it->second.end(); ++itt)
			{
				if (((QuestObj*)(itt->second))->GetId() == 1)
				{
					cout << "찾았다." << endl;
					((QuestObj*)(itt->second))->SetActionStrategy(QuestObjStrategy::SetFrameAnim);
					TriggerObj* portal = (TriggerObj*)(PhysicsManager::GetInstance()->GetTriggerObj(3));
					((DoorObj*)(portal))->SetLoadMap(5);
					cout << portal->GetMainId() << endl;
					break;
				}
			}
		}
		break;
	case 11: // 곰돌이 얻었을 때 
		//곰돌이 이미지 없애기 
		for (auto it = questActionObjMap.begin(); it != questActionObjMap.end(); ++it)
		{
			for (auto itt = it->second.begin(); itt != it->second.end(); ++itt)
			{
				if (((TrapActionObj*)(itt->second))->GetId() == 2)
				{
					int frameX = (itt->second)->GetComponent<SpriteRenderer>()->GetCurrFrameX();
					(itt->second)->GetComponent<SpriteRenderer>()->SetFrameX(frameX-2);
				}
			}
		}
		break;
	case 12:
		//for (auto it = questActionObjMap.begin(); it != questActionObjMap.end(); ++it)
		//{
		//	for (auto itt = it->second.begin(); itt != it->second.end(); ++itt)
		//	{
		//		if (((TrapActionObj*)(itt->second))->GetId() == 2)
		//		{
		//			int frameX = (itt->second)->GetComponent<SpriteRenderer>()->GetCurrFrameX();
		//			(itt->second)->GetComponent<SpriteRenderer>()->SetFrameX(frameX - 2);
		//		}
		//	}
		//}
		break;
	}
}

int QuestManager::GetQuestObjId(int posX, int posY)
{
	auto it = questObjMap.find(posX);

	if (it == questObjMap.end())
	{
		return -1;
	}
	auto itt = it->second.find(posY);

	if (itt != it->second.end())
	{
		int id = ((QuestObj*)(itt->second))->GetId();
		return id;
	}
	return -1;
}

void QuestManager::SetQuestObj(int posX, int posY, GameObject* obj)
{
	questObjMap[posX][posY] = obj;
}

void QuestManager::AddQuestId(int posX, int posY)
{
	QuestObj* questObj = (QuestObj*)(questObjMap[posX][posY]);
	if (questObj != nullptr)
	{
		questObj->AddId();
	}
}

void QuestManager::SetOffQuestObj(int id)
{
	for (auto it = questObjMap.begin(); it != questObjMap.end(); ++it)
	{
		for (auto itt = it->second.begin(); itt != it->second.end(); ++itt)
		{
			QuestObj* quest = ((QuestObj*)(itt->second));
			if (quest->GetId() == id)
			{
				quest->SetIsActable(false);
			}
		}
	}
}

void QuestManager::RemoveQuestObj(int id)
{
	for (auto it = questObjMap.begin(); it != questObjMap.end(); ++it)
	{
		for (auto itt = it->second.begin(); itt != it->second.end(); ++itt)
		{
			QuestObj* quest = ((QuestObj*)(itt->second));
			if (quest->GetId() == id)
			{
				(it->second).erase(itt);
			}
		}
	}
}

void QuestManager::Clear()
{
	for (auto it : questObjMap)
	{
		it.second.clear();
	}
	questObjMap.clear();
}
