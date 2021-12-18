#include "Item.h"


Item::Item(GameObject* owner)
	: _owner{ owner }
{
}

wstring Item::GetName()
{
	return name;
}

wstring Item::GetInfo()
{
	return info;
}

void Letter::Init()
{
	info = L"주머니에 들어있던 편지.";
	name = L"편지";
	count += 1;
}

void Letter::UseItem()
{
}

void Letter::GetnerateChat()
{
	
}
