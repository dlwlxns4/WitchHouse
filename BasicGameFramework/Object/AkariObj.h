#pragma once

#include "GameObject.h"

class SizeAdjRenderer;
class AkariObj : public GameObject
{
public:
	GameObject::GameObject;
	virtual ~AkariObj() = default;

	virtual void	Init()		override;
	virtual void	Update()	override;

	virtual void	Write(std::ostream& os) const override;
	virtual void	Read(std::istream& is) override;
private:
	int frameX = 0;
	int animDelay = 0;

	SizeAdjRenderer* renderer = nullptr;
};