#pragma once

#include "Component.h"
#include <array>

class ITrapActionable;
class TrapAction : public Component
{
public:
	using Component::Component;
	virtual ~TrapAction() = default;


private:
	std::array<class ITrapActionable*, 4> actions;
	class ITrapActionable* _actionSterategy = actions[0];
};

class ITrapActionable abstract
{
public:
	ITrapActionable(GameObject* _owner)
		: _obj{ _owner }
	{
	}
	virtual ~ITrapActionable() = default;

	virtual void	DoAction() = 0;

protected:
	GameObject* _obj;
};

class NullAction : public ITrapActionable
{
public:
	using		ITrapActionable::ITrapActionable;
	virtual		~NullAction() = default;

	void DoAction() override
	{

	}
};