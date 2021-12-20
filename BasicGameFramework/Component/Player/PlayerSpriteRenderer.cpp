#include "PlayerSpriteRenderer.h"

#include "../../Manager/ImageManager.h"

#include "../../Object/GameObject.h"

#include "../../Util/Sprite.h"

#define MOVE 0
#define NANAME 4
#define DOOR  5

void PlayerSpriteRenderer::Render(HDC hdc)
{
	if (state == PlayerSpriteState::Move)
	{
		sprite->PlayerRender(_owner->GetPosition().x, 
			_owner->GetPosition().y-16,
			frontFeet,
			MOVE+(int)dir,
			opacity
		);
	}
	else if (state == PlayerSpriteState::Init)
	{
		sprite->PlayerRender(_owner->GetPosition().x,
			_owner->GetPosition().y - 16,
			frameX,
			NANAME,
			opacity
		);
	}
}

void PlayerSpriteRenderer::SetImage(const wchar_t* filePath)
{
	sprite = ImageManager::GetInstance()->FindSprite(filePath);
}

void PlayerSpriteRenderer::SetDirection(int dir)
{
	this->dir = (Direction)dir; 
}

Direction PlayerSpriteRenderer::GetDirection()
{
	return dir;
}

void PlayerSpriteRenderer::SetOpacity(float opacity)
{
	this->opacity = opacity;
}

void PlayerSpriteRenderer::SetFeet(int feet)
{
	frontFeet = feet;
}

void PlayerSpriteRenderer::SetFrameX(int frameX)
{
	this->frameX = frameX;
}

int PlayerSpriteRenderer::GetFrameX()
{
	return frameX;
}
