#pragma once

#include "Component.h"

class Sprite;
class SlateRenderer : public Component
{
public:
	using Component::Component;
	virtual ~SlateRenderer() noexcept = default;

	virtual void Init()override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	
	void SetSprite(const wchar_t* fileName);
	void SetSlatePos(int pos);
	int GetSlatePos(int pos);
private:
	Sprite* sprite = nullptr;
	int slatePos = 0;
	bool isOpen = false;
	bool isClose = false;
};