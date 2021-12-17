#pragma once
#include "GameObject.h"



class ParallaxObj : public GameObject
{
	using GameObject::GameObject;
	virtual ~ParallaxObj() noexcept = default;

	virtual void Init() override;

	virtual void Write(std::ostream& os)const override;

};