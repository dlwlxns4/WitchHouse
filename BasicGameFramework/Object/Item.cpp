#include "Item.h"
#include "../Manager/SceneManager.h"
#include "../Manager/PhysicsManager.h"
#include "../Manager/QuestManager.h"
#include "../Component/Player/PlayerSpriteRenderer.h"
#include "../Scene/MainScene.h"

#include <iostream>
Item::Item(GameObject* owner)
	: _owner{ owner }
{
}

void Item::SetOwner(GameObject* owner)
{
	_owner = owner;
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
	id = 0;
}

void Letter::UseItem()
{
}


void Scissors::Init()
{
	info = L"잔디와 가지를 정리하기 위한 가위. 녹슬어 있어 지저분하다.";
	name = L"정원 가위";
	useString = L"\t장미를자른다.\n\n\t그만둔다.";
	count += 1;
	id = 1;
}

void Scissors::UseItem()
{
	int dx[] = { 0,-1,1,0 };
	int dy[] = { 1,-0,0,-1 };

	int dir = (int)(_owner->GetComponent<PlayerSpriteRenderer>()->GetDirection());
	
	int posX = _owner->GetPosition().x / 32 + dx[dir];
	int posY = _owner->GetPosition().y / 32 + dy[dir];

	if (QuestManager::GetInstance()->GetQuestObjId(posX, posY) == 0)
	{
		((MainScene*)(SceneManager::GetInstance()->GetCurrentScene()))->SetActiveBackPanelFlag(true);
		if (PhysicsManager::GetInstance()->GetCollider( posX, posY ) )
		{
			PhysicsManager::GetInstance()->RemoveCollider(posX, posY);
		}
		
		QuestManager::GetInstance()->SetOffQuestObj(0);
	}

	
	cout << _owner->GetPosition().x << " " << _owner->GetPosition().y << endl;
}
