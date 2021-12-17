#pragma once

#include "../Util/Singleton.h"

class QuestManager : public Singleton<QuestManager>
{
public:
	QuestManager() = default;
	~QuestManager() = default;
	void SetQuest(int quest);
	void NextQuest();

	int GetQuest();
	int* GetQuestPtr();
private:
	int currQuest=0;
};