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
	info = L"�ָӴϿ� ����ִ� ����.";
	name = L"����";
	count += 1;
}

void Letter::UseItem()
{
}

void Letter::GetnerateChat()
{
	
}
