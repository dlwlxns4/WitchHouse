#include "PlayerSpriteRenderer.h"

#include "../../Manager/ImageManager.h"

#include "../../Object/GameObject.h"

#include "../../Util/Sprite.h"

void PlayerSpriteRenderer::Render(HDC hdc)
{
	sprite->PlayerRender(_owner->GetPosition().x, 
		_owner->GetPosition().y-16,
		frontFeet,
		(int)dir
	);
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

void PlayerSpriteRenderer::SetFeet(int feet)
{
	frontFeet = feet;
}
