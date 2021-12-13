#include "PlayerAction.h"
#include "../../Util/Input.h"


#include "../../stdafx.h"
#include <iostream>

#include "../../Object/GameObject.h"
#include "../../Manager/PhysicsManager.h"
#include "../../Manager/GameManager.h"
#include "../../Manager/TalkManager.h"

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

		int id = PhysicsManager::GetInstance()->GetTriggerId(posX, posY);
		
		DoChaating(id);
	}
}

void PlayerAction::DoChaating(int id)
{
	
	string text = TalkManager::GetInstance()->GetTalkData(id);
	cout << text << endl;
	
}

