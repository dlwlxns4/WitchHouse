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


void SpriteRenderer::Write(std::ostream& os) const
{
	os << 100 << "\t";
	Component::Write(os);
	os << spriteindex << "\t";
	os << frameX << "\t";
	os << frameY << "\t";
	os << sizeX << "\t";
	os << sizeY << "\t";
}

void SpriteRenderer::Read(istream& is)
{
	Component::Read(is);
	is >> spriteindex
		>> frameX
		>> frameY
		>> sizeX
		>> sizeY;
	SetSprite(spriteindex, frameX, frameY);
}

void SpriteRenderer::SetSprite(const wchar_t* fileName, int frameX, int frameY)
{
	sprite = ImageManager::GetInstance()->FindSprite(fileName);
	this->frameX = frameX;
	this->frameY = frameY;
}

void SpriteRenderer::SetSprite(int spriteindex, int frameX, int frameY)
{
	wstring path = ImageManager::GetInstance()->GetSpriteName(spriteindex);
	sprite = ImageManager::GetInstance()->FindSprite(path.c_str());
	this->spriteindex = spriteindex;
	this->frameX = frameX;
	this->frameY = frameY;
}

void SpriteRenderer::SetSprite(const wchar_t* fileName)
{
	sprite = ImageManager::GetInstance()->FindSprite(fileName);
}


void SpriteRenderer::SetFrameX(int x)
{
	this->frameX = x;
}

void SpriteRenderer::SetFrameY(int y)
{
	this->frameY = y;
}
