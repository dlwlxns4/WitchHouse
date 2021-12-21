#pragma once
#include "GameObject.h"

class GameOverObj : public GameObject
{
public:
	using GameObject::GameObject;
	virtual ~GameOverObj() = default;

	virtual void Init() override;
};