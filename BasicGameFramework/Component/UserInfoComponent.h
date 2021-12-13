#pragma once

#include "Component.h"

class Sprite;
class UserInfoComponent : public Component
{
public:
	using Component::Component;
	virtual ~UserInfoComponent() noexcept = default;

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetSprite(const wchar_t* leftfileName, const wchar_t* rightFileName);
	void SetIsShow(bool isShow);

private:
	Sprite* leftPanel = nullptr;
	Sprite* rightPanel = nullptr;
	Sprite* portrait = nullptr;
	Sprite* healthBar = nullptr;
	float panelOpacity = 0;
	bool isShow = false;
};