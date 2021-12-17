#pragma once
#include "Component.h"

using namespace std;


class Sprite;
class SpriteRenderer : public Component
{
public:
	using Component::Component;
	virtual ~SpriteRenderer() noexcept = default;


	virtual void		Render(HDC hdc) override;

	virtual void Write(ostream& os) const override;
	virtual void Read(istream& is) override;
	void SetSprite(const wchar_t* fileName, int frameX, int frameY);

	void SetSprite(int sampleIndex, int frameX, int frameY);
	void SetSprite(const wchar_t* fileName);
	void SetFrameX(int x);
	void SetFrameY(int y);
private:
	Sprite* sprite = nullptr;
	int spriteindex = 0;
	int frameX = 0;
	int frameY = 0;
	int sizeX = 0;
	int sizeY = 0;
};