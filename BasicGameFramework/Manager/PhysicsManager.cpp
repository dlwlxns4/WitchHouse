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

void PhysicsManager::RePosCollider(int posX, int posY, int dir)
{
	int dx[] = { 0,-1,1,0 };
	int dy[] = { 1,-0,0,-1 };
	collisionObj.erase({ posX, posY });
	collisionObj.insert({ posX + dx[dir], posY + dy[dir] });
}

bool PhysicsManager::GetCollider(int posX, int posY)
{
	if (collisionObj.find({ posX,posY }) != collisionObj.end())
	{
		return true;
	}
	return false;
}

void PhysicsManager::addId_1(int posX, int posY)
{
	chatObj[posX][posY] += 1;
}

void PhysicsManager::addId_10(int posX, int posY)
{
	chatObj[posX][posY] += 10;

}

void PhysicsManager::addId_100(int posX, int posY)
{
	chatObj[posX][posY] += 100;
}

void PhysicsManager::addId_1000(int posX, int posY)
{
	chatObj[posX][posY] += 1000;

}

void PhysicsManager::SetChat(int posX, int posY)
{
	chatObj[posX][posY] = 0;
}

int PhysicsManager::GetChatId(int posX, int posY)
{
	int id = 0;
	auto it = chatObj.find(posX);

	if (it != chatObj.end())
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

void PhysicsManager::SetItem(int posX, int posY)
{

	auto it = itemObj.find(posX);
	if (it != itemObj.end())
	{
		auto itt = it->second.find(posY);
		if (itt != it->second.end())
		{
			(*itt).second++;
			return;
		}
	}

	itemObj[posX][posY] = 0;
}

void PhysicsManager::RemoveItem(int posX, int posY)
{
	auto it = itemObj.find(posX);

	if (it == itemObj.end())
		return;

	it->second.erase(posY);
}

int PhysicsManager::GetItemId(int posX, int posY)
{
	auto it = itemObj.find(posX);

	if (it != itemObj.end())
	{
		auto itt = it->second.find(posY);
		if (itt != it->second.end())
		{
			int id = itt->second;
			return id;
		}
	}
	return -1;
}

void PhysicsManager::RemoveChat(int posX, int posY)
{
	auto it = chatObj.find(posX);

	if (it == chatObj.end())
		return;

	it->second.erase(posY);
}

void PhysicsManager::SetTriggerObj(int posX, int posY, GameObject* obj)
{
	triggerObj[posX][posY] = obj;
}

void PhysicsManager::addPortalNum(int posX, int posY)
{
	PortalObj* portal = (PortalObj*)(triggerObj[posX][posY]);
	if (portal != nullptr)
	{
		portal->AddNextMapNum();
	}
}

GameObject* PhysicsManager::GetTriggerObj(int posX, int posY)
{
	if (triggerObj[posX].find(posY) == triggerObj[posX].end())
	{
		return nullptr;
	}
	else
	{
		return ((triggerObj[posX].find(posY))->second);
	}

}

void PhysicsManager::RemoveTriggerObj(int posX, int posY)
{

}

void PhysicsManager::AllClear()
{
	collisionObj.clear();
	
	for (auto it : chatObj)
	{
		it.second.clear();
	}
	chatObj.clear();

	for (auto it : triggerObj)
	{
		it.second.clear();
	}
	triggerObj.clear();

	for (auto it : itemObj)
	{
		it.second.clear();
	}
	itemObj.clear();
	
}

std::ostream& operator<<(std::ostream& os, const PhysicsManager& physicManager)
{
	physicManager.Write(os);
	return os;

}

std::istream& operator>>(std::istream& is, PhysicsManager& physicManager)
{
	physicManager.Read(is);
	return is;
}

void PhysicsManager::Write(std::ostream& os) const
{

	unordered_set<pair<int, int>, pair_hash>* collisionTmp = &(PhysicsManager::GetInstance()->collisionObj);
	unordered_map<int, unordered_map<int, int>>* chatTmp = &(PhysicsManager::GetInstance()->chatObj);
	unordered_map<int, unordered_map<int, int>>* itemTmp = &(PhysicsManager::GetInstance()->itemObj);

	os << collisionTmp->size() << "\t";
	for (auto it : *collisionTmp)
	{
		os << it.first << "\t";
		os << it.second << endl;
	}

	os << chatTmp->size() << "\t";
	for (auto it : *chatTmp)
	{
		for (auto itt : it.second)
		{
			os << it.first << "\t";
			os << itt.first << "\t";
			os << itt.second << endl;
		}
	}

	os << itemTmp->size() << "\t";
	for (auto it : *itemTmp)
	{
		for (auto itt : it.second)
		{
			os << it.first << "\t";
			os << itt.first << "\t";
			os << itt.second << endl;
		}
	}
}

void PhysicsManager::Read(std::istream& is)
{
	unordered_set<pair<int, int>, pair_hash>* collisionTmp = &(PhysicsManager::GetInstance()->collisionObj);
	unordered_map<int, unordered_map<int, int>>* triggerTmp = &(PhysicsManager::GetInstance()->chatObj);
	unordered_map<int, unordered_map<int, int>>* itemTmp = &(PhysicsManager::GetInstance()->itemObj);

	int collisionSize;
	is >> collisionSize;
	for (int i = 0; i < collisionSize; ++i)
	{
		int x, y;
		is >> x
			>> y;
		collisionTmp->insert({ x,y });
	}

	int triggerSize;
	is >> triggerSize;
	for (int i = 0; i < triggerSize; ++i)
	{
		int x, y, id;
		is >> x
			>> y
			>> id;
		(*triggerTmp)[x][y] = id;
	}

	int itemSize;
	is >> itemSize;
	for (int i = 0; i < itemSize; ++i)
	{
		int x, y, id;
		is >> x
			>> y
			>> id;
		(*itemTmp)[x][y] = id;
	}
}