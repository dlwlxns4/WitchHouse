#pragma once

#include "../Component.h"

#include "../Player/PlayerSpriteRenderer.h"
#include "../../Util/AboutTile.h"
#include <array>

#include "../../Manager/GameManager.h"
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
	using IActionable::IActionable;
	virtual ~NullAction() = default;

	void DoAction() override
	{

	}
};

class InputAction : public IActionable
{
public:
	using IActionable::IActionable;
	virtual ~InputAction() = default;

	void DoAction()
	{
		POINT pos = _obj->GetPosition();

		if (GameManager::GetInstance()->GetState() == State::None)
		{
			if (Input::GetButton(VK_UP))
			{
				if (PhysicsManager::GetInstance()->IsCollide(_obj->GetPosition().x / TILE_SIZE, _obj->GetPosition().y / TILE_SIZE - 1) == false)
				{
					GameManager::GetInstance()->SetState(State::Move);
					prevPosX = _obj->GetPosition().x / TILE_SIZE;
					prevPosY = _obj->GetPosition().y / TILE_SIZE;
				}
				_obj->GetComponent<PlayerSpriteRenderer>()->SetDirection(UP_DIR);
			}
			else if (Input::GetButton(VK_DOWN))
			{
				if (PhysicsManager::GetInstance()->IsCollide(_obj->GetPosition().x / TILE_SIZE, _obj->GetPosition().y / TILE_SIZE + 1) == false)
				{
					GameManager::GetInstance()->SetState(State::Move);
					prevPosX = _obj->GetPosition().x / TILE_SIZE;
					prevPosY = _obj->GetPosition().y / TILE_SIZE;
				}
				_obj->GetComponent<PlayerSpriteRenderer>()->SetDirection(DOWN_DIR);
			}
			else if (Input::GetButton(VK_LEFT))
			{
				if (PhysicsManager::GetInstance()->IsCollide(_obj->GetPosition().x / TILE_SIZE - 1, _obj->GetPosition().y / TILE_SIZE) == false)
				{
					GameManager::GetInstance()->SetState(State::Move);
					prevPosX = _obj->GetPosition().x / TILE_SIZE;
					prevPosY = _obj->GetPosition().y / TILE_SIZE;
				}
				_obj->GetComponent<PlayerSpriteRenderer>()->SetDirection(LEFT_DIR);
			}
			else if (Input::GetButton(VK_RIGHT))
			{
				if (PhysicsManager::GetInstance()->IsCollide(_obj->GetPosition().x / TILE_SIZE + 1, _obj->GetPosition().y / TILE_SIZE) == false)
				{
					GameManager::GetInstance()->SetState(State::Move);
					prevPosX = _obj->GetPosition().x / TILE_SIZE;
					prevPosY = _obj->GetPosition().y / TILE_SIZE;
				}
				_obj->GetComponent<PlayerSpriteRenderer>()->SetDirection(RIGHT_DIR);
			}
		}
		if (GameManager::GetInstance()->GetState() == State::Move)
		{
			Direction dir = _obj->GetComponent<PlayerSpriteRenderer>()->GetDirection();
			POINTFLOAT* camera = (GameManager::GetInstance()->GetCameraPos());

			int dx[] = { 0,-1,1,0 };
			int dy[] = { 1,-0,0,-1 };

			//static_cast<LONG>(_speed * Timer::GetDeltaTime());
			//static_cast<LONG>(_speed * Timer::GetDeltaTime());
			pos.x += dx[(int)dir] * 4;
			pos.y += dy[(int)dir] * 4;

			camera->x += dx[(int)dir] * 0.125f;
			camera->y += dy[(int)dir] * 0.125f;

			_obj->SetPosition(pos);
			moveDistance += 4;
			if (moveDistance >= 16)
			{
				_obj->GetComponent<PlayerSpriteRenderer>()->SetAlternateWalk();
			}

			if (moveDistance >= 32)
			{
				moveDistance = 0;
				GameManager::GetInstance()->SetState(State::None);
				_obj->GetComponent<PlayerSpriteRenderer>()->SetFeet(1);
			}

			PhysicsManager::GetInstance()->RePosCollider(prevPosX, prevPosY, (int)dir);
		}
	}

private:
	int prevPosX = 0;
	int prevPosY = 0;
	int	moveDistance = 0;

};

class InitialAction : public IActionable
{
public:
	using IActionable::IActionable;
	virtual ~InitialAction() = default;
	void DoAction()
	{
		//
	}
};