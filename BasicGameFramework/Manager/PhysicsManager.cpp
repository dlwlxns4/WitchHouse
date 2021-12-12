#include "PhysicsManager.h"
#include "../stdafx.h"

void PhysicsManager::SetCollision(int posX, int posY)
{
	collisionObj.insert({ posX, posY });
}

bool PhysicsManager::IsCollide(int posX, int posY)
{
	if (collisionObj.find(make_pair(posX, posY)) == collisionObj.end())
	{
		return false;
	}
	else
	{
		return true;
	}
}