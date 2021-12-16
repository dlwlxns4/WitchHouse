#pragma once

#include "GameObject.h"

class Sprite;
class BackPanel :public GameObject
{
public:
	using GameObject::GameObject;
	virtual ~BackPanel() = default;

	virtual void Init() override;
	virtual void Render(HDC hdc) override;
	virtual void Update() override;
private:
	Sprite* backPanel= nullptr;

	bool isBright = true;
	bool isActive = true;
	bool isFirst = true;
	float panelOpacity = 1;
};