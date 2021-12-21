#include "QuestManager.h"
#include "../Object/QuestObj.h"
#include "../Object/TrapActionObj.h"

#include "../Component/TrapAction.h"

#include <iostream>
using namespace std;

void QuestManager::SetQuest(int quest)
{
	currQuest = quest;
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

void QuestManager::Clear()
{
	for (auto it : questObjMap)
	{
		it.second.clear();
	}
	questObjMap.clear();
}
