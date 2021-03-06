#pragma once

#include <Windows.h>

struct IBehaviour
{
	virtual ~IBehaviour() { };

	virtual void		Init() { }
	virtual void		Update() { }
	virtual void		Render(HDC hdc) { }
	virtual void		Release() { }

	virtual void		OnTrigger() {}
};