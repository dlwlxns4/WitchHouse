#include "ItemManager.h"
#include "../Object/Item.h"

#include <iostream>
ItemManager::~ItemManager()
{
	Release();
}

void ItemManager::Init()
{
	itemFactory = new ItemFactory;
	AddItem(1);
}

void ItemManager::UseItem(int index)
{
	inventory[index]->UseItem();
}

void ItemManager::AddItem(int id)
{
	Item* item = itemFactory->CreateItem((ItemKinds)id);

	for (auto it : inventory)
	{
		if (it->CompareId(id))
		{
			it->AddCount();
			return;
		}
	}
	inventory.push_back(item);
}

void ItemManager::Release()
{
	for (int i = 0; i < inventory.size(); ++i)
	{
		delete inventory[i];
	}
	delete itemFactory;
}

wstring ItemManager::GetItemName(int index)
{
	wstring name = inventory[index]->GetName();
	return name;
}

wstring ItemManager::GetitemInfo(int index)
{
	wstring info = inventory[index]->GetInfo();
	return info;
}

int ItemManager::GetItemCount(int index)
{
	int count = inventory[index]->GetCount();
	return count;
}

void ItemManager::SetCurrFindItem(int id)
{
	currFindItem = id;
}

void ItemManager::SetOwner(GameObject* owner)
{
	for (int i = 0; i < inventory.size(); ++i)
	{
		inventory[i]->SetOwner(owner);
	}
}

void ItemManager::RemoveItem(int id)
{


	for (auto it = inventory.begin(); it!= inventory.end(); ++it)
	{
		if ((*it)->CompareId(id))
		{

			if ((*it)->GetCount() == 0)
			{
				inventory.erase(it);
				break;
			}
		}
	}
}

int ItemManager::GetCurrFindItem()
{
	return currFindItem;
}


const vector<Item*>& ItemManager::GetInventory() const
{
	return inventory;
}

int ItemManager::GetInventorySize()
{
	int size = inventory.size();
	return size;
}
