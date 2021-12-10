#pragma once

#include "../Component.h"


class Image;
class PlayerSpriteRenderer : public Component
{

public:
	using Component::Component;
	virtual ~PlayerSpriteRenderer() noexcept = default;

	virtual void Render(HDC hdc) override;


	void SetImage(const wchar_t* filePath);
	void SetDirection(int dir);
private:
	enum class Direction { Down = 0, Left = 1, Right = 2, Up = 3 };
	
	Direction		dir;
	Image*			img;
};