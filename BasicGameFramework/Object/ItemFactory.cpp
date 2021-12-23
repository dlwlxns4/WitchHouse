#include "ItemFactory.h"
#include "../Manager/ItemManager.h"
#include "../Manager/GameManager.h"
#include "../Object/GameObject.h"

Item* ItemFactory::CreateItem(ItemKinds item)
{
	GameObject* _owner = GameManager::GetInstance()->GetPlayer();
	switch (item)
	{
	case ItemKinds::Letter:
	{
		Letter* letter = new Letter(_owner);
		letter->Init();
		return letter;
		break;
	}
	case ItemKinds::Scissors:
	{
		Scissors* scissors = new Scissors(_owner);
		scissors->Init();
		return scissors;
		break;
	}
	case ItemKinds::TeddyBear:
	{
		TeddyBear* teddyBear = new TeddyBear(_owner);
		teddyBear->Init();
		return teddyBear;
		break;
	}
	default:
		break;
	}

	return nullptr;
}
