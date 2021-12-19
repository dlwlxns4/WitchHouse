#pragma once
#include "GameObject.h"
#include <vector>

using namespace std;

class Item
{
public:
	Item(GameObject* owner);
	virtual ~Item() = default;

	virtual void		Init() = 0;

	void				SetOwner(GameObject* owner);
	virtual void		UseItem() = 0;
	void				AddCount() { count++; };
	int					GetId() { return id; }
	int					GetCount() { return count; }
	bool				CompareId(int id) { if (this->id == id) return true; return false; }
	wstring				GetName();
	wstring				GetInfo();
protected:
	int					id = 0;
	GameObject*			_owner = nullptr;
	wstring				name = L"";
	wstring				info = L"";
	wstring				useString = L"";
	int			count = 0;
};

class Letter : public Item
{
public:
	using Item::Item;
	virtual ~Letter() = default;

	virtual void Init()			 override;
	virtual void UseItem()		 override;

protected:
};

class Scissors : public Item
{
public:
	using Item::Item;
	virtual ~Scissors() = default;

	virtual void Init()			 override;
	virtual void UseItem() override;
protected:

};