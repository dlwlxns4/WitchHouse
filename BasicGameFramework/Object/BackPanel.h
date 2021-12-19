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

	void SetActive(bool active) { isActive = active; }
	void SetIsItemEffect(bool active) { isItemEffect = active; }
	void SetIsBright(bool isBright) { this->isBright = isBright; }
	void SetOpaicty(float opacity) { panelOpacity = opacity; }
	float GetPanelOpacity() { return panelOpacity; }
private:
	Sprite* backPanel = nullptr;

	bool isBright = true;
	bool isActive = true;
	bool isFirst = true;
	float panelOpacity = 1;
	int rotationDelay = 0;
	bool isItemEffect = false;
};