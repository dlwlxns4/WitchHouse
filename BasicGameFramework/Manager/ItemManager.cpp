#include "ItemManager.h"
#include "../Object/Item.h"
#include "../Object/ItemFactory.h"


ItemManager::~ItemManager()
{
}

void ItemManager::Init()
{
	itemFactory = new ItemFactory;
	AddItem(itemFactory->CreateItem(ItemKinds::Letter));
}

void ItemManager::UseItem(int index)
{
}

void ItemManager::AddItem(Item* item)
{
	for (auto it : inventory)
	{
		if (it->CompareId(item->GetId()))
		{
			it->AddCount();
			return;
		}
	}
	inventory.push_back(item);
}

void ItemManager::Release()
{
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


const vector<Item*>& ItemManager::GetInventory() const
{
	return inventory;
}

int ItemManager::GetInventorySize()
{
	int size = inventory.size();
	return size;
}
