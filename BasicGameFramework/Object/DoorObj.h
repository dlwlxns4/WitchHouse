#pragma once
#include "GameObject.h"

class DoorObj : public GameObject
{
public:
	virtual void	Init()		override;
	virtual void	Update()	override;
	virtual void	OnTrigger() override;

	virtual void	Write(std::ostream& os) const override;
	virtual void	Read(std::istream& is) override;

private:
	int frameX = 0;
	int animDelay = 0;
};