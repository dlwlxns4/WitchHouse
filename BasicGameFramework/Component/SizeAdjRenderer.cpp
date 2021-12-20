#include "SizeAdjRenderer.h"

#include "../Manager/ImageManager.h"
#include "../Object/GameObject.h"

#include "../Util/Sprite.h"
void SizeAdjRenderer::Render(HDC hdc)
{
	sprite->Render(
		_owner->GetRenderPos().x,
		_owner->GetRenderPos().y,
		frameX,
		frameY,
		maxFrameX,
		maxFrameY
	);
}


void SizeAdjRenderer::Write(std::ostream& os) const
{
	os << 102 << "\t";
	Component::Write(os);
	os << spriteindex << "\t";
	os << frameX << "\t";
	os << frameY << "\t";
	os << maxFrameX << "\t";
	os << maxFrameY << "\t";
}

void SizeAdjRenderer::Read(istream& is)
{
	Component::Read(is);
	is >> spriteindex
		>> frameX
		>> frameY
		>> maxFrameX
		>> maxFrameY;

	wstring path =ImageManager::GetInstance()->GetSpriteName(spriteindex);
	sprite = ImageManager::GetInstance()->FindSprite(path.c_str());
}

void SizeAdjRenderer::SetSprite(const wchar_t* fileName, int frameX, int frameY)
{
	sprite = ImageManager::GetInstance()->FindSprite(fileName);
	this->frameX = frameX;
	this->frameY = frameY;
}

void SizeAdjRenderer::SetSprite(int spriteindex, int frameX, int frameY)
{
	wstring path = ImageManager::GetInstance()->GetSpriteName(spriteindex);
	sprite = ImageManager::GetInstance()->FindSprite(path.c_str());
	this->spriteindex = spriteindex;
	this->frameX = frameX;
	this->frameY = frameY;
}

void SizeAdjRenderer::SetSprite(const wchar_t* fileName)
{
	sprite = ImageManager::GetInstance()->FindSprite(fileName);
}

void SizeAdjRenderer::SetFrameX(int x)
{
	this->frameX = x;
}

void SizeAdjRenderer::SetFrameY(int y)
{
	this->frameY = y;
}

void SizeAdjRenderer::SetIndex(int index)
{
	this->spriteindex = index;
}

void SizeAdjRenderer::SetMaxFrame(int x, int y)
{
	this->maxFrameX = x;
	this->maxFrameY = y;
}

