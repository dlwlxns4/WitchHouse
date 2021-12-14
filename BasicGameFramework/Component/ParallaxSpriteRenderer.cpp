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

void ParallaxSpriteRenderer::SetSprite()
{
	sprite = ImageManager::GetInstance()->FindSprite(L"Image/Parallax/001-Fog01.png");
}

void ParallaxSpriteRenderer::SetSprite(const wchar_t* fileName)
{
	sprite = ImageManager::GetInstance()->FindSprite(fileName);

}

void ParallaxSpriteRenderer::Write(std::ostream& os) const
{
	os << 101 << "\t";
	Component::Write(os);
	os << frameX			<<"\t";
	os << frameY			<<"\t";
	os << sizeX 			<<"\t";
	os << sizeY 			<<"\t";
	os << renderPosX 		<<"\t";
	os << renderPosY 		<<"\t";
	os << renderDelayTime 	<<"\t";
	os << spriteIndex 		<<"\t";
}

void ParallaxSpriteRenderer::Read(std::istream& is)
{
	Component::Read(is);

	is >> frameX
		>> frameY
		>> sizeX
		>> sizeY
		>> renderPosX
		>> renderPosY
		>> renderDelayTime
		>> spriteIndex;

	SetSprite();
}