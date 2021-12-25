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
	int														GetQuestObjId(int posX, int posY);
	void													SetQuestObj(int posX, int posY, GameObject* obj);
	void													AddQuestId(int posX, int posY);
	void													SetOffQuestObj(int id);
	void													RemoveQuestObj(int id);

	unordered_map<int, unordered_map<int, GameObject*>>*	GetQuestActionObjMap() { return &questActionObjMap; }
	GameObject*												GetQuestActionObj(int posX, int posY);
	int														GetQuestActionObjId(int posX, int posY);
	void													SetQuestActionObj(int posX, int posY, GameObject* obj);
	void													AddQuestActionId(int posX, int posY);
	void													SetOffQuestActionObj(int id);

	void													SetTrapAction(int id);

	void													DoActivateQuestObj(int id);

	void													Clear();

	virtual void Write(std::ostream& os) const;
	friend std::ostream& operator<<(std::ostream& os, const QuestManager& questManager);
	virtual void Read(std::istream& is);
	friend std::istream& operator>>(std::istream& is, QuestManager& questManager);
private:
	int currQuest=10;
	unordered_map<int, string>								questName;
	
	unordered_map<int, unordered_map<int, GameObject*>>		questObjMap;

	unordered_map<int, unordered_map<int, GameObject*>>		questActionObjMap;
};