#pragma once

#include "Component.h"

class Sprite;
class SpriteRenderer : public Component
{
	using Component::Component;
	virtual ~SpriteRenderer() noexcept = default;


	virtual void Render(HDC hdc) override;


public:
	void SetSprite(const wchar_t* fileName, int frameX, int frameY);
	void SetSprite(const wchar_t* fileName);

private:
	Sprite* sprite=nullptr;
	int frameX=0;
	int frameY = 0;
};