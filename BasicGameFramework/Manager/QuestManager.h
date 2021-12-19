#pragma once

#include "../Util/Singleton.h"

#include <unordered_map>
using namespace std;

class GameObject;
class QuestManager : public Singleton<QuestManager>
{
public:
	QuestManager() = default;
	~QuestManager() = default;
	void	SetQuest(int quest);
	void	NextQuest();

	int		GetQuest();
	int*	GetQuestPtr();

	void	Init();

	unordered_map<int, unordered_map<int, GameObject*>>*	GetQuestObjMap() { return &questObjMap; }
	GameObject*												GetQuestObj(int posX, int posY);
	int GetQuestObjId(int posX, int posY);
	void													SetQuestObj(int posX, int posY, GameObject* obj);
	void													AddQuestId(int posX, int posY);
	void													SetOffQuestObj(int id);
	void													RemoveQuestObj(int posX, int posY);
	void													Clear();
private:
	int currQuest=10;
	unordered_map<int, unordered_map<int, GameObject*>>		questObjMap;
};