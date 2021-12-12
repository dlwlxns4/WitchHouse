#include "SpriteRenderer.h"

#include "../Manager/ImageManager.h"
#include "../Object/GameObject.h"

#include "../Util/Sprite.h"
void SpriteRenderer::Render(HDC hdc)
{
	sprite->Render(_owner->GetRenderPos().x,
		_owner->GetRenderPos().y,
		frameX,
		frameY
	);
}

void SpriteRenderer::SetSprite(const wchar_t* fileName, int frameX, int frameY)
{
	sprite = ImageManager::GetInstance()->FindSprite(fileName);
	this->frameX = frameX;
	this->frameY = frameY;
}

void SpriteRenderer::SetSprite(const wchar_t* fileName)
{
	sprite = ImageManager::GetInstance()->FindSprite(fileName);
}
