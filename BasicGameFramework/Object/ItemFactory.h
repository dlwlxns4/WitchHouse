#pragma once

#include "Item.h"

enum class ItemKinds
{
	Scissors=0,
	Letter=1
};

class ItemFactory
{
public:
	ItemFactory() = default;
	~ItemFactory() = default;

	Item* CreateItem(ItemKinds item);
};