#include "PlayerAction.h"
#include "../../Util/Input.h"


#include "../../stdafx.h"
#include <iostream>

#include "../../Object/GameObject.h"
#include "../../Manager/PhysicsManager.h"
#include "../../Manager/GameManager.h"
#include "../../Manager/TalkManager.h"
#include "../../Manager/ItemManager.h"

#include "PlayerSpriteRenderer.h"
void PlayerAction::Update()
{
	if (Input::GetButtonDown('Z'))
	{
		int dx[] = { 0,-1,1,0 };
		int dy[] = { 1,-0,0,-1 };
		int dir = (int)(_owner->GetComponent<PlayerSpriteRenderer>()->GetDirection());
		int posX = _owner->GetPosition().x / 32 + dx[dir];
		int posY = _owner->GetPosition().y / 32 + dy[dir];

		if (GameManager::GetInstance()->GetState() == State::None)
		{
			int chatId = PhysicsManager::GetInstance()->GetChatId(posX, posY);
			int itemid = PhysicsManager::GetInstance()->GetItemId(posX, posY);

			if (chatId != 0 || itemid != -1)
			{
				GameManager::GetInstance()->SetState(State::Chat);
				DoChatting(chatId, itemid);
			}
		}

	}
}

void PlayerAction::DoChatting(int chatId, int itemid)
{
	if (itemid != -1)
	{
		TalkManager::GetInstance()->SetCurrInteractId(itemid);
		TalkManager::GetInstance()->SaveItemTalkData(itemid);
		ItemManager::GetInstance()->SetCurrFindItem(itemid);
		return;
	}

	if (chatId != 0)
	{
		TalkManager::GetInstance()->SetCurrInteractId(chatId);
		TalkManager::GetInstance()->SaveTalkData(chatId);
	}
}

