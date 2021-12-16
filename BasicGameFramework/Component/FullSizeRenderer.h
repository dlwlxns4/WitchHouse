#pragma once
#include "Component.h"

using namespace std;


class Sprite;
class FullSizeRenderer : public Component
{
public:
	using Component::Component;
	virtual ~FullSizeRenderer() noexcept = default;

	virtual void	Render(HDC hdc) override;


	void			SetSprite(const wchar_t* fileName);

private:
	Sprite* sprite = nullptr;
	int spriteindex = 0;
	int frameX = 0;
	int frameY = 0;
	int sizeX = 0;
	int sizeY = 0;
};