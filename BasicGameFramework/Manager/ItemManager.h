#pragma once
#include "../Util/Singleton.h"
#include "../Object/ItemFactory.h"


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
	void AddItem(int id);
	void Release();
	wstring GetItemName(int index);
	wstring GetitemInfo(int index);
	int		GetItemCount(int index);
	int		GetCurrFindItem();
	void	SetCurrFindItem(int id);
	void	SetOwner(GameObject* owner);

	const vector<Item*>&	GetInventory() const;
	int						GetInventorySize();
private:
	vector<Item*>	inventory;
	ItemFactory*	itemFactory;
	int				currFindItem = -1;
};