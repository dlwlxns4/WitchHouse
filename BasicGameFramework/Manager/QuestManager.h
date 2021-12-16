#pragma once

#include "../Util/Singleton.h"

class QuestManager : public Singleton<QuestManager>
{
public:
	void SetQuest(int quest);
	void NextQuest();

	int GetQuest();
	int* GetQuestPtr();
private:
	int currQuest=0;
};