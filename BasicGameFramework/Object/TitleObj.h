#pragma once

#include "GameObject.h"

class TitleObj : public GameObject
{
public:
	using GameObject::GameObject;
	virtual ~TitleObj() = default;

	virtual void Init() override;
};