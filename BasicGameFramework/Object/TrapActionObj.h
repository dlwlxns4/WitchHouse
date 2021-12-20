#pragma once

#include "GameObject.h"

class TrapActionable;
class TrapActionObj : public GameObject
{
public:
	GameObject::GameObject;
	virtual ~TrapActionObj() = default;

	virtual void Init() override;

private:
};


