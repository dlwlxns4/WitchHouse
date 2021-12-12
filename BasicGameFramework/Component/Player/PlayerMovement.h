#pragma once

#include "../Component.h"

class PlayerMovement : public Component
{
public:
	using Component::Component;
	virtual ~PlayerMovement() noexcept = default;

	virtual void	Update() override;

	void			SetSpeed(float speed) noexcept;

	float			GetSpeed() const noexcept;
private:
	float			_speed;
	int moveDistance = 0;
	int prevPosX = 0;
	int prevPosY = 0;
};