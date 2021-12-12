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

};