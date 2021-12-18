#include "QuestManager.h"

void QuestManager::SetQuest(int quest)
{
	currQuest = quest;
}

void QuestManager::NextQuest()
{
	currQuest++;
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
}
