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

void ItemManager::LoadInit()
{
	itemFactory = new ItemFactory;
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
		inventory[i] = nullptr;
	}
	delete itemFactory;
	itemFactory = nullptr;
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

bool ItemManager::RemoveItem(int id)
{
	for (auto it = inventory.begin(); it!= inventory.end(); ++it)
	{
		if ((*it)->CompareId(id))
		{

			if ((*it)->GetCount() == 0)
			{
				delete (*it);
				inventory.erase(it);
				return true;
			}
		}
	}
	return false;
}

bool ItemManager::CanObtainItem(int id)
{
	switch (id)
	{
	case 3:
		return false;
	default:
		return true;
	}
}

void ItemManager::Clear()
{
	for (auto it = inventory.begin(); it != inventory.end(); ++it)
	{
		delete *it;
	}
	inventory.clear();
	delete itemFactory;
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

void ItemManager::Write(std::ostream& os) const
{
	os << inventory.size() << "\n";
	for (int i = 0; i < inventory.size(); ++i)
	{
		os << inventory[i]->GetId() << "\t";
		os << inventory[i]->GetCount() << "\n";
	}
}

void ItemManager::Read(std::istream& is)
{
	inventory.clear();
	int size;
	is >> size;
	for(int i=0; i<size; ++i)
	{
		int id = 0;
		is >> id;
		inventory.push_back(itemFactory->CreateItem((ItemKinds)id));
		int count = 0;
		is >> count;
		for (int i = 0; i < count - 1; ++i)
		{
			inventory.push_back(itemFactory->CreateItem((ItemKinds)id));
		}
	}
}

std::ostream& operator<<(std::ostream& os, const ItemManager& itemManager)
{
	itemManager.Write(os);
	return os;
}

std::istream& operator>>(std::istream& is, ItemManager& itemManager)
{
	itemManager.Read(is);
	return is;
}
