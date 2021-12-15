#include "PlayerMovement.h"
#include "../CircleComponent.h"

#include "../../Object/GameObject.h"
#include "../../Util/Input.h"
#include "../../Util/Timer.h"


#include "PlayerSpriteRenderer.h"

#include "../../Manager/GameManager.h"
#include "../../Manager/PhysicsManager.h"
#include <iostream>
#include "../../Util/AboutTile.h"



PlayerMovement::~PlayerMovement()
{
	Release();
}

void PlayerMovement::Init()
{
	NullAction* nullAction = new NullAction(this->_owner);
	actions[0] = nullAction;

	InputAction* inputAction = new InputAction(this->_owner);
	actions[1] = inputAction;

	InitialAction* initialAction = new InitialAction(this->_owner);
	actions[2] = initialAction;

	_actionSterategy = actions[1];
}

void PlayerMovement::Update()
{
	_actionSterategy->DoAction();

	//POINT pos = _owner->GetPosition();

	//if (GameManager::GetInstance()->GetState() == State::None)
	//{
	//	/*if (Input::GetButton(VK_UP))
	//	{
	//		if (PhysicsManager::GetInstance()->IsCollide(_owner->GetPosition().x / TILE_SIZE, _owner->GetPosition().y / TILE_SIZE - 1) == false)
	//		{
	//			GameManager::GetInstance()->SetState(State::Move);
	//			prevPosX = _owner->GetPosition().x / TILE_SIZE;
	//			prevPosY = _owner->GetPosition().y / TILE_SIZE;
	//		}
	//		_owner->GetComponent<PlayerSpriteRenderer>()->SetDirection(UP_DIR);
	//	}
	//	else if (Input::GetButton(VK_DOWN))
	//	{
	//		if (PhysicsManager::GetInstance()->IsCollide(_owner->GetPosition().x / TILE_SIZE, _owner->GetPosition().y / TILE_SIZE + 1) == false)
	//		{
	//			GameManager::GetInstance()->SetState(State::Move);
	//			prevPosX = _owner->GetPosition().x / TILE_SIZE;
	//			prevPosY = _owner->GetPosition().y / TILE_SIZE;
	//		}
	//		_owner->GetComponent<PlayerSpriteRenderer>()->SetDirection(DOWN_DIR);
	//	}
	//	else if (Input::GetButton(VK_LEFT))
	//	{
	//		if (PhysicsManager::GetInstance()->IsCollide(_owner->GetPosition().x / TILE_SIZE - 1, _owner->GetPosition().y / TILE_SIZE) == false)
	//		{
	//			GameManager::GetInstance()->SetState(State::Move);
	//			prevPosX = _owner->GetPosition().x / TILE_SIZE;
	//			prevPosY = _owner->GetPosition().y / TILE_SIZE;
	//		}
	//		_owner->GetComponent<PlayerSpriteRenderer>()->SetDirection(LEFT_DIR);
	//	}
	//	else if (Input::GetButton(VK_RIGHT))
	//	{
	//		if (PhysicsManager::GetInstance()->IsCollide(_owner->GetPosition().x / TILE_SIZE + 1, _owner->GetPosition().y / TILE_SIZE) == false)
	//		{
	//			GameManager::GetInstance()->SetState(State::Move);
	//			prevPosX = _owner->GetPosition().x / TILE_SIZE;
	//			prevPosY = _owner->GetPosition().y / TILE_SIZE;
	//		}
	//		_owner->GetComponent<PlayerSpriteRenderer>()->SetDirection(RIGHT_DIR);
	//	}*/
	//}

	//if (GameManager::GetInstance()->GetState() == State::Move)
	//{
	//	Direction dir = _owner->GetComponent<PlayerSpriteRenderer>()->GetDirection();
	//	POINTFLOAT* camera = (GameManager::GetInstance()->GetCameraPos());

	//	int dx[] = { 0,-1,1,0 };
	//	int dy[] = { 1,-0,0,-1 };

	//	//static_cast<LONG>(_speed * Timer::GetDeltaTime());
	//	//static_cast<LONG>(_speed * Timer::GetDeltaTime());
	//	pos.x += dx[(int)dir] * 4;
	//	pos.y += dy[(int)dir] * 4;

	//	camera->x += dx[(int)dir] * 0.125f;
	//	camera->y += dy[(int)dir] * 0.125f;

	//	_owner->SetPosition(pos);
	//	moveDistance += 4;
	//	if (moveDistance >= 16)
	//	{
	//		_owner->GetComponent<PlayerSpriteRenderer>()->SetAlternateWalk();
	//	}

	//	if (moveDistance >= 32)
	//	{
	//		moveDistance = 0;
	//		GameManager::GetInstance()->SetState(State::None);
	//		_owner->GetComponent<PlayerSpriteRenderer>()->SetFeet(1);
	//	}

	//	PhysicsManager::GetInstance()->RePosCollider(prevPosX, prevPosY, (int)dir);
	//}
}

void PlayerMovement::SetSpeed(float speed) noexcept
{
	_speed = speed;
}

float PlayerMovement::GetSpeed() const noexcept
{
	return _speed;
}

void PlayerMovement::SetActionStartegy(PlayerActionState action)
{
	_actionSterategy = actions[static_cast<int>(action)];
}

void PlayerMovement::Release()
{
	for (size_t i = 0; i < actions.size(); ++i)
	{
		delete actions[i];
	}
}


