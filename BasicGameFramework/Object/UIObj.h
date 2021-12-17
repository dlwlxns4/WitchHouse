#pragma once
#include "GameObject.h"

class Sprite;
class UIObj : public GameObject
{
public:
	using GameObject::GameObject;
	virtual ~UIObj() noexcept = default;

	virtual void Init() override;

private:
	int slatePosY = 0;
};