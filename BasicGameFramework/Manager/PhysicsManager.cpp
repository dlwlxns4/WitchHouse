#include "PhysicsManager.h"
#include "../stdafx.h"

#include <iostream>

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

void PhysicsManager::addId_1(int posX, int posY)
{
	triggerObj[posX][posY] += 1;
}

void PhysicsManager::addId_10(int posX, int posY)
{
	triggerObj[posX][posY] += 10;

}

void PhysicsManager::addId_100(int posX, int posY)
{
	triggerObj[posX][posY] += 100;
}

void PhysicsManager::addId_1000(int posX, int posY)
{
	triggerObj[posX][posY] += 1000;

}

void PhysicsManager::SetTrigger(int posX, int posY)
{
	triggerObj[posX][posY] = 0;
}

int PhysicsManager::GetTriggerId(int posX, int posY)
{
	int id = 0;
	
	auto it = triggerObj.find(posX);
	
	

	if (it != triggerObj.end())
	{
		auto itt = it->second.find(posY);
		if (itt != it->second.end())
		{
			id = itt->second;
		}
	}
	cout << id << endl;
	return id;
}
