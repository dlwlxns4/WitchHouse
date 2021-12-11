#pragma once


#include "GameObject.h"

class MapFrame : public GameObject
{
	using GameObject::GameObject;
	virtual ~MapFrame() noexcept = default;

	virtual void Init() override;
};