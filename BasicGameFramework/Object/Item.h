#pragma once
#include "GameObject.h"

class Item
{
public:
	Item(GameObject* owner);
	virtual ~Item() = default;

	virtual void UseItem() = 0;

private:
	int id = 0;
	GameObject* _owner=nullptr;
};


class Scissors : public Item
{
public:
	using Item::Item;
	virtual ~Scissors() = default;

	virtual void UseItem() override;
};