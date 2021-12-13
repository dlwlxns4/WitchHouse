#pragma once


#include "Layer.h"

class UILayer : public Layer
{
public:
	virtual void		Init() override;
	virtual void		Update() override;
	virtual void		Render(HDC hdc) override;
	virtual void		Release() override;

private:

};