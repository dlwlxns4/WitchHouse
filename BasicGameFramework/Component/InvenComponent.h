#pragma once

#include "Component.h"

class Sprite;
class InvenComponent : public Component
{
public:
	using Component::Component;
	virtual ~InvenComponent() noexcept = default;

	virtual void	Update() override;
	virtual void	Render(HDC hdc) override;

	void			SetSprite(const wchar_t* leftfileName, const wchar_t* rightFileName,
					const wchar_t* selectPanelFileName);
	void			SetIsShow(bool isShow);
	void PrintString();
private:
	Sprite* upPanel				= nullptr;
	Sprite* downPanel			= nullptr;
	Sprite* selectPanel			= nullptr;
	float	panelOpacity		= 0;
	float	selectPanelOpacity	= 0;
	int		selectInvenItem		= 0;
	bool	isShow				= false;
	bool	isDecrease			= true;
};