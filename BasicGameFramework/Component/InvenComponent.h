#pragma once

#include "Component.h"

class Sprite;
class InvenComponent : public Component
{
public:
	using Component::Component;
	virtual ~InvenComponent() noexcept = default;

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetSprite(const wchar_t* leftfileName, const wchar_t* rightFileName);
	void SetIsShow(bool isShow);
private:
	Sprite* upPanel = nullptr;
	Sprite* downPanel = nullptr;
	float panelOpacity = 0;
	bool isShow = false;
};