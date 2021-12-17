#include "Item.h"

void Scissors::UseItem()
{
}

Item::Item(GameObject* owner)
	: _owner{ owner }
{
}
