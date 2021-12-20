#pragma once

#include "../Component.h"

enum class Direction { Down = 0, Left = 1, Right = 2, Up = 3 };
enum class PlayerSpriteState
{ 
	Move=0, 
	Init=1,
	Door=2
};

class Sprite;
class PlayerSpriteRenderer : public Component
{
public:
	using Component::Component;
	virtual ~PlayerSpriteRenderer() noexcept = default;

	virtual void Render(HDC hdc) override;


	Direction	GetDirection();
	void		SetOpacity(float opacity);
	void		SetImage(const wchar_t* filePath);
	void		SetDirection(int dir);
	void		SetFeet(int feet);
	void		SetAlternateWalk() { frontFeet = frontFeet == 0 ? 0 : 2; }
	void		SetState(PlayerSpriteState state) { this->state = state; }
	void		SetFrameX(int frameX);
	int			GetFrameX();
private:

	int frontFeet = 1;
	int frameX = 1;
	float opacity = 1.0f;

	Direction		dir;
	PlayerSpriteState state = PlayerSpriteState::Init;
	Sprite* sprite;
};