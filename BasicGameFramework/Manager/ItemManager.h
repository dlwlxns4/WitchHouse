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
	void	RemoveItem(int id);
	bool	CanObtainItem(int id);

	void	Clear();

	const vector<Item*>&	GetInventory() const;
	int						GetInventorySize();

	virtual void Write(std::ostream& os) const;
	friend std::ostream& operator<<(std::ostream& os, const ItemManager& itemManager);
	virtual void Read(std::istream& is);
	friend std::istream& operator>>(std::istream& is, ItemManager& itemManager);
private:
	vector<Item*>	inventory = {};
	ItemFactory*	itemFactory = {};
	int				currFindItem = -1;
};