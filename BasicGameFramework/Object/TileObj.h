#pragma once
#include "GameObject.h"

class TileObj : public GameObject
{
	using GameObject::GameObject;
	
	virtual ~TileObj() noexcept = default;

	virtual void Init() override;
	virtual void Render(HDC hdc)override;
};