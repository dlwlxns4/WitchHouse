#include "Player.h"

#include "../stdafx.h"

#include "../Component/RectComponent.h"
#include "../Component/CircleComponent.h"

#include "../Component/Player/PlayerMovement.h"
#include "../Component/Player/PlayerSpriteRenderer.h"

void Player::Init()
{
	//MoveMent-----------------------------------------------------
	PlayerMovement* movement = new PlayerMovement(this, 1);
	movement->SetSpeed(0.2f);

	//SpriteRender-------------------------------------------------
	this->SetPivot(Pivot::Center);
	PlayerSpriteRenderer* spriteRenderer = new PlayerSpriteRenderer(this, 1);
	wstring wCharacterPath = L"Image/Character/$vivi.png";
	spriteRenderer->SetImage(wCharacterPath.c_str());
	
	SetSize(200, 100);
}
