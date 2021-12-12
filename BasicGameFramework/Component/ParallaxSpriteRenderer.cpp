#include "ParallaxSpriteRenderer.h"

#include "../Util/Sprite.h"

#include "../Util/AboutTile.h"
#include "../Manager/ImageManager.h"

void ParallaxSpriteRenderer::Render(HDC hdc)
{
	sprite->LoopRender(0, 0, renderPosX, renderPosY);
}

void ParallaxSpriteRenderer::Update()
{
	renderDelayTime++;
	if (renderDelayTime >= 2)
	{
		renderDelayTime = 0;
		renderPosX++;
		renderPosY++;

		//무한루프
		if (renderPosX == sprite->GetHeight()/2)
		{
			renderPosX = 0;
		}
		if (renderPosY == sprite->GetHeight() / 2)
		{
			renderPosY = 0;
		}
	}
}

void ParallaxSpriteRenderer::SetSprite(const wchar_t* fileName, int frameX, int frameY)
{
	sprite = ImageManager::GetInstance()->FindSprite(fileName);
	this->frameX = frameX;
	this->frameY = frameY;
}

void ParallaxSpriteRenderer::SetSprite(const wchar_t* fileName)
{
	sprite = ImageManager::GetInstance()->FindSprite(fileName);

}
