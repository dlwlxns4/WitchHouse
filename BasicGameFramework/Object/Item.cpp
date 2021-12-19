#include "Item.h"
#include "../Manager/SceneManager.h"


#include <iostream>
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
	id = 0;
}

void Letter::UseItem()
{
}


void Scissors::Init()
{
	info = L"�ܵ�� ������ �����ϱ� ���� ����. �콽�� �־� �������ϴ�.";
	name = L"���� ����";
	useString = L"\t��̸��ڸ���.\n\n\t�׸��д�.";
	count += 1;
	id = 1;
}

void Scissors::UseItem()
{
	cout << _owner->GetPosition().x << " " << _owner->GetPosition().y << endl;
}
