#pragma once

#include "../Component.h"

enum class Direction { Down = 0, Left = 1, Right = 2, Up = 3 };

class Sprite;
class PlayerSpriteRenderer : public Component
{

public:
	using Component::Component;
	virtual ~PlayerSpriteRenderer() noexcept = default;

	virtual void Render(HDC hdc) override;


	void SetImage(const wchar_t* filePath);
	void SetDirection(int dir);
	Direction GetDirection();
	void SetFeet(int feet);
	void SetAlternateWalk() { frontFeet = frontFeet == 0 ? 0 : 2; }
private:

	int frontFeet = 0;
	Direction		dir;
	Sprite* sprite;
};