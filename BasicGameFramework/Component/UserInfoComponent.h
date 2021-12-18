#pragma once

#include "Component.h"

class Sprite;
class UserInfoComponent : public Component
{
	enum class SelectUI
	{
		Inven = 0,
		Load = 1
	};
public:
	using Component::Component;
	virtual ~UserInfoComponent() noexcept = default;

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetSprite(const wchar_t* leftfileName, const wchar_t* rightFileName);
	void SetIsShow(bool isShow);

	void PrintText();

private:
	Sprite* leftPanel = nullptr;
	Sprite* rightPanel = nullptr;
	Sprite* portrait = nullptr;
	Sprite* healthBar = nullptr;
	Sprite* selectPanel = nullptr;
	Sprite* opacityPanel = nullptr;

	float panelOpacity = 0;
	float selectPanelOpacity = 1;
	bool isDecrease = true;

	bool isShow = false;

	SelectUI selectState = SelectUI::Inven;

};