#pragma once
#include "GameObject.h"

class Sprite;
class ChatPanel : public GameObject
{
public:
	using GameObject::GameObject;

	virtual ~ChatPanel() noexcept = default;

	virtual void Init() override;

private:
	int slatePosY = 0;
};