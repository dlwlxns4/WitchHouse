#pragma once

#include "Component.h"

class Sprite;
class SaveLoadInterface : public Component
{
public:
	using Component::Component;
	virtual ~SaveLoadInterface() = default;

	void SetSprite(const wchar_t* infoName, const wchar_t* PanelName);

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetIsSave(bool isSave) { this->isSave = isSave; }

	void Save(int currSelect);
	void Load(int currSelect);
private:
	Sprite* saveLoadInfo = nullptr;
	Sprite* saveLoadPanel[4] = {nullptr};
	Sprite* selectPanel = nullptr;
	Sprite* portrait = nullptr;
	int currSelect = 0;

	float selectPanelOpacity = 1;
	bool isDecrease = true;

	int isSave = true;
	float delay = 0;
};