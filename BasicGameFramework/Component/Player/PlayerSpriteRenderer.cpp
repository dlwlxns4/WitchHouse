#include "PlayerSpriteRenderer.h"

#include "../../Manager/ImageManager.h"

#include "../../Object/GameObject.h"

#include "../../Util/Sprite.h"

void PlayerSpriteRenderer::Render(HDC hdc)
{
	sprite->Render(_owner->GetRenderPos().x, 
		_owner->GetRenderPos().y, 
		0,
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
