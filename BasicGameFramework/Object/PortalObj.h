#pragma once

#include "TriggerObj.h"

class PortalObj : public TriggerObj
{
public:
	using TriggerObj::TriggerObj;
	virtual ~PortalObj() = default;

	/*virtual void	Init() override;
	virtual void	Update() override;
	virtual void	Render(HDC hdc) override;*/
	virtual void	OnTrigger() override;

	virtual void	AddNextMapNum() override{ nextMapNum++; };
	virtual int		GetNextMap() override { return nextMapNum; } ;


	virtual void	Write(std::ostream& os) const override;
	virtual void	Read(std::istream& is) override;
private:
	int				nextMapNum = 0;
};