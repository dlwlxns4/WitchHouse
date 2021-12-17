#pragma once

#include "GameObject.h"

class PortalObj : public GameObject
{
public:
	using GameObject::GameObject;
	virtual ~PortalObj() = default;

	/*virtual void	Init() override;
	virtual void	Update() override;
	virtual void	Render(HDC hdc) override;*/

	virtual void	OnTrigger() override;
	void			AddNextMapNum() { nextMapNum++; }
	int				GetNextMap()	{ return nextMapNum; }

private:
	int				nextMapNum = 0;
};