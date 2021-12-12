#pragma once

#include "../Util/Singleton.h"
#include <unordered_set>

using namespace std;

struct pair_hash {
	inline std::size_t operator()(const std::pair<int, int>& v) const {
		return v.first * 31 + v.second;
	}
};

class PhysicsManager : public Singleton<PhysicsManager>
{
private:
	unordered_set<pair<int, int>, pair_hash> collisionObj = {};




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
};