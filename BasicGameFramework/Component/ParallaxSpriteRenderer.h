#pragma once

#include "Component.h"

class Sprite;
class ParallaxSpriteRenderer : public Component
{
public:
	using Component::Component;
	virtual ~ParallaxSpriteRenderer() noexcept = default;


	virtual void Render(HDC hdc) override;
	virtual void Update() override;

	void SetSprite(const wchar_t* fileName, int frameX, int frameY);
	void SetSprite();
	void SetSprite(int spriteIndex);
	void SetSprite(int spriteIndex, int frameX, int frameY);
	void SetSprite(const wchar_t* fileName);

	virtual void		Write(std::ostream& os) const;
	virtual void		Read(std::istream& is);
private:
	Sprite* sprite = nullptr;
	int frameX = 0;
	int frameY = 0;
	int sizeX = 0;
	int sizeY = 0;
	int renderPosX = 0;
	int renderPosY = 0;
	int renderDelayTime = 0;
	int spriteIndex = 0;

};