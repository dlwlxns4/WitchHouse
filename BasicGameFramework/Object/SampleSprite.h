#pragma once

#include "GameObject.h"

class SampleSprite : public GameObject
{
	using GameObject::GameObject;
	SampleSprite();
	virtual ~SampleSprite() noexcept = default;

	virtual void Init() override;
};
