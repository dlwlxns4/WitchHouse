#pragma once

#include "GameObject.h"

class MovableObj : public GameObject
{
public:
	using GameObject::GameObject;
	virtual ~MovableObj() = default;

};


class AstarTeddy : public MovableObj
{
public:
	using MovableObj::MovableObj;
	virtual ~AstarTeddy() = default;

	virtual void Init() override;
};