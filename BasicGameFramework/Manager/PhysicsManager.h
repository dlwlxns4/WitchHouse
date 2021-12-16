#pragma once

#include "../Util/Singleton.h"
#include <unordered_set>
#include <unordered_map>

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

class PhysicsManager : public Singleton<PhysicsManager>
{
private:
	unordered_set<pair<int, int>, pair_hash> collisionObj = {};
	unordered_map<int, unordered_map<int, int>> chatObj;		//ÁÂÇ¥, referenceId



	virtual void Write(std::ostream& os) const;
	virtual void Read(std::istream& is);
	friend std::ostream& operator<<(std::ostream& os, const PhysicsManager& physicManager);
	friend std::istream& operator>>(std::istream& is, PhysicsManager& physicManager);

public:
	void SetCollision(int posX, int posY);
	bool IsCollide(int posX, int posY);

	unordered_set<pair<int,int>, pair_hash>* GetCollisionObj() { return &collisionObj; }
	void RemoveCollider(int posX, int posY) { collisionObj.erase({ posX, posY }); }
	void RePosCollider(int posX, int posY, int dir)
	{
		int dx[] = { 0,-1,1,0 };
		int dy[] = { 1,-0,0,-1 };
		collisionObj.erase({ posX, posY });
		collisionObj.insert({ posX + dx[dir], posY + dy[dir] });
	}
	void addId_1(int posX, int posY);
	void addId_10(int posX, int posY);
	void addId_100(int posX, int posY);
	void addId_1000(int posX, int posY);

	void SetTrigger(int posX, int posY);
	int GetTriggerId(int posX, int posY);
	unordered_map<int, unordered_map<int,int>>* GetTriggerObj() { return &chatObj; }
	void RePosTrigger(int posX, int posY, int dir);
	void RemoveTrigger(int posX, int posY) 
	{
		auto it = chatObj.find(posX);

		if (it == chatObj.end())
			return;
		
		it->second.erase(posY);

	}
};