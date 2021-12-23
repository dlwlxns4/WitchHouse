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
	int					GetCount() { return count; }
	wstring				GetName();
	wstring				GetInfo();

	virtual bool CompareId(int id) =0;
protected:
	GameObject*			_owner = nullptr;
	wstring				name = L"";
	wstring				info = L"";
	wstring				useString = L"";
	int					count = 0;
};

class Letter : public Item
{
public:
	using Item::Item;
	virtual ~Letter() = default;

	virtual void Init()			 override;
	virtual void UseItem()		 override;
	virtual bool CompareId(int id) override{ if (this->id == id) return true; return false; }

	int GetId() { return id; }
protected:
	int id = 1;
};

class Scissors : public Item
{
public:
	using Item::Item;
	virtual ~Scissors() = default;

	virtual void Init()			 override;
	virtual void UseItem() override;
	virtual bool CompareId(int id) override { if (this->id == id) return true; return false; }

	int GetId() { return id; }

protected:
	int id = 0;
};

class TeddyBear : public Item
{
public:
	using Item::Item;
	virtual ~TeddyBear() = default;

	virtual void Init()			 override;
	virtual void UseItem() override;
	virtual bool CompareId(int id) override { if (this->id == id) return true; return false; }

	int GetId() { return id; }

protected:
	int id = 2;
};