#pragma once
#include "GameObject.h"

class ChatPanel : public GameObject
{
	using GameObject::GameObject;

	virtual ~ChatPanel() noexcept = default;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc)override;
};