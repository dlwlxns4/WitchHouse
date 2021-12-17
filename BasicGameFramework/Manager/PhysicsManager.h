#pragma once

#include "../Util/Singleton.h"
#include <unordered_set>
#include <unordered_map>
#include "../Object/PortalObj.h"

using namespace std;

//struct pair_hash {
//	inline std::size_t operator()(const std::pair<int, int>& v) const {
//		return v.first * 31 + v.second;
//	}
//};

struct pair_hash {
	template <class T1, class T2>
	std::size_t operator () (const std::pair<T1, T2>& p) const {
		auto h1 = std::hash<T1>{}(p.first);
		auto h2 = std::hash<T2>{}(p.second);

		// Mainly for demonstration purposes, i.e. works but is overly simple
		// In the real world, use sth. like boost.hash_combine
		return h1 ^ h2;
	}
};

class GameObject;
class PhysicsManager : public Singleton<PhysicsManager>
{
private:
	unordered_set<pair<int, int>, pair_hash> collisionObj = {};
	unordered_map<int, unordered_map<int, int>> chatObj;		//��ǥ, referenceId
	unordered_map<int, unordered_map<int, GameObject*>> triggerObj;

	virtual void Write(std::ostream& os) const;
	virtual void Read(std::istream& is);
	friend std::ostream& operator<<(std::ostream& os, const PhysicsManager& physicManager);
	friend std::istream& operator>>(std::istream& is, PhysicsManager& physicManager);

public:
	PhysicsManager() = default;
	~PhysicsManager() = default;
	void SetCollision(int posX, int posY);
	bool IsCollide(int posX, int posY);

	unordered_set<pair<int,int>, pair_hash>* GetCollisionObj() { return &collisionObj; }
	void RemoveCollider(int posX, int posY) { collisionObj.erase({ posX, posY }); }
	void RePosCollider(int posX, int posY, int dir);

	void addId_1(int posX, int posY);
	void addId_10(int posX, int posY);
	void addId_100(int posX, int posY);
	void addId_1000(int posX, int posY);

	void SetChat(int posX, int posY);
	int GetChatId(int posX, int posY);
	unordered_map<int, unordered_map<int,int>>* GetChatObjs() { return &chatObj; }
	void RemoveChat(int posX, int posY);


	unordered_map<int, unordered_map<int, GameObject*>>* GetTriggerObjs() { return &triggerObj; }

	void SetTriggerObj(int posX, int posY, GameObject* obj);

	GameObject* GetTriggerObj(int posX, int posY);
	void addPortalNum(int posX, int posY);
	void RemoveTriggerObj(int posX, int posY);

	void AllClear();
};