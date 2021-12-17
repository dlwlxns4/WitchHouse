#pragma once

#include "GameObject.h"

class SpriteRenderer;
class TwinkleObj : public GameObject
{
public:
	GameObject::GameObject;
	virtual ~TwinkleObj() = default;

	virtual void	Init()		override;
	virtual void	Update()	override;
	
	virtual void	Write(std::ostream& os) const override;
	virtual void	Read(std::istream& is) override;

private:
	int frameX = 0;
	int animDelay = 0;

	SpriteRenderer* renderer = nullptr;
};