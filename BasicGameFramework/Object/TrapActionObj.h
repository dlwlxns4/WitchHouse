#pragma once

#include "GameObject.h"

class ITrapActionable;
class TrapActionObj : public GameObject
{
public:
	GameObject::GameObject;
	virtual ~TrapActionObj() = default;

	virtual void Init() override;

private:
};


