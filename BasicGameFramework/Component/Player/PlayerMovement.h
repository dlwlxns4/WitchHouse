#pragma once

#include "../Component.h"

#include "../Player/PlayerSpriteRenderer.h"
#include "../../Util/AboutTile.h"
#include <array>

#include "../../Manager/PhysicsManager.h"

#include "../../Util/Input.h"
#include "../../Object/GameObject.h"

#define DOWN_DIR	0
#define LEFT_DIR	1
#define RIGHT_DIR	2
#define UP_DIR		3

enum class PlayerActionState
{
	Null,
	Input,
	Initial
};


class PlayerMovement : public Component
{
public:

	using Component::Component;
	virtual ~PlayerMovement();

	virtual void	Init() override;
	virtual void	Update() override;
	void			SetSpeed(float speed) noexcept;
	float			GetSpeed() const noexcept;
	void			SetActionStartegy(PlayerActionState action);
	virtual void	Release() override;

	//virtual void	OnTrigger() override;
	void			TiggerHelper(int posX, int posY);
private:
	float			_speed;
	int				prevPosX = 0;
	int				prevPosY = 0;

	std::array<class IActionable*, 3> actions;
	class IActionable* _actionSterategy = actions[0];
};

class IActionable abstract
{
public:
	IActionable(GameObject* _owner)
		: _obj{ _owner }
	{ 
	}
	virtual ~IActionable() = default;

	virtual void	DoAction() = 0;

protected:
	GameObject* _obj;
};

class NullAction : public IActionable
{
public:
	using		IActionable::IActionable;
	virtual		~NullAction() = default;

	void DoAction() override
	{

	}
};

class InputAction : public IActionable
{
public:
	using		IActionable::IActionable;
	virtual		~InputAction() = default;

	void		DoAction();

private:
	int			prevPosX = 0;
	int			prevPosY = 0;
	int			moveDistance = 0;

};

class InitialAction : public IActionable
{
public:
	using		IActionable::IActionable;
	virtual		~InitialAction() = default;
	
	void		DoAction();

private:
	int			motionDelay = 0;
	int			motionCount = 0;
	bool		isFront = true;
	bool		isMotionFinish = false;
};