#pragma once

#include "Item.h"

enum class ItemKinds
{
	Letter=0,
	Scissors=1
};

class ItemFactory
{
public:
	ItemFactory() = default;
	~ItemFactory() = default;

	Item* CreateItem(ItemKinds item);
};