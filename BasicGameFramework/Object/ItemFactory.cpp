#include "ItemFactory.h"
#include "../Manager/ItemManager.h"
#include "../Manager/GameManager.h"
#include "../Manager/SoundManager.h"
#include "../Manager/QuestManager.h"
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
		SoundManager::GetInstance()->startInfSound(L"Item");

		return scissors;
		break;
	}
	case ItemKinds::TeddyBear:
	{
		TeddyBear* teddyBear = new TeddyBear(_owner);
		teddyBear->Init();
		SoundManager::GetInstance()->startInfSound(L"Item");
		return teddyBear;
		break;
	}
	case ItemKinds::TeddyBearWithoutLimbs:
	{
		TeddyBearWithoutLimbs* teddyBearWithousLimbs = new TeddyBearWithoutLimbs(_owner);
		teddyBearWithousLimbs->Init();
		SoundManager::GetInstance()->startInfSound(L"Item");

		return teddyBearWithousLimbs;
		break;
	}
	default:
		break;
	}

	return nullptr;
}
