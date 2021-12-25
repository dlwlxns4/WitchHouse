#pragma once

#include "Component.h"


class Sprite;
class TitleComp : public Component
{
public:
	using Component::Component;
	virtual ~TitleComp() = default;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	void		 SetSprite(const wchar_t* fileName);

	void MapCopy();

private:
	enum class SelectState
	{
		StartOver=0,
		Load =1,
		Exit =2,
		None =3
	};

	Sprite* SelectPanel = nullptr;
	Sprite* backPanel = nullptr;

	float selectPanelOpacity = 1;
	float backPanelOpacity = 0;

	bool isDecrease = true;

	bool isSelect = false;
	SelectState state = SelectState::StartOver;
};