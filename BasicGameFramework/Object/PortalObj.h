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


	virtual void	Write(std::ostream& os) const override;
	virtual void	Read(std::istream& is) override;
private:
	int				nextMapNum = 0;
};