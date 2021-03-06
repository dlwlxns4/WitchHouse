#include "Player.h"

#include "../stdafx.h"

#include "../Component/RectComponent.h"
#include "../Component/CircleComponent.h"

#include "../Component/Player/PlayerMovement.h"
#include "../Component/Player/PlayerSpriteRenderer.h"
#include "../Component/Player/PlayerAction.h"

#include <iostream>
void Player::Init()
{
	this->Clear();

	//MoveMent-----------------------------------------------------
	PlayerMovement* movement = new PlayerMovement(this, 1);
	movement->Init();
	movement->SetSpeed(0.2f);

	//SpriteRender-------------------------------------------------
	this->SetPivot(Pivot::Center);
	PlayerSpriteRenderer* spriteRenderer = new PlayerSpriteRenderer(this, 2);
	wstring wCharacterPath = L"Image/Character/$vivi.png";
	spriteRenderer->SetImage(wCharacterPath.c_str());
	

	//Action---------------------
	PlayerAction* action = new PlayerAction(this, 3);

}

void Player::Update()
{
	GameObject::Update();
}
