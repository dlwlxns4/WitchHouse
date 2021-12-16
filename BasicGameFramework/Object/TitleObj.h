#pragma once

#include "GameObject.h"

class TitleObj : public GameObject
{
public:
	using GameObject::GameObject;

	virtual void Init() override;
};