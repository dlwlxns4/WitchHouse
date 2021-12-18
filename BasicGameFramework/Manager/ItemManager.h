#pragma once
#include "../Util/Singleton.h"


#include "../stdafx.h"


class Item;
class ItemFactory;
class ItemManager : public Singleton<ItemManager>
{
public:
	ItemManager() = default;
	~ItemManager();

	void Init();
	void UseItem(int index);
	void AddItem(Item* item);
	void Release();
	wstring GetItemName(int index);
	wstring GetitemInfo(int index);
	int		GetItemCount(int index);

	const vector<Item*>&	GetInventory() const;
	int						GetInventorySize();
private:
	vector<Item*> inventory;
	ItemFactory* itemFactory;
};