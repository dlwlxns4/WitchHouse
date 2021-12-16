#include "PlayerMovement.h"
#include "../CircleComponent.h"

#include "../../Object/GameObject.h"
#include "../../Util/Input.h"
#include "../../Util/Timer.h"


#include "PlayerSpriteRenderer.h"

#include "../../Manager/GameManager.h"
#include "../../Manager/PhysicsManager.h"
#include "../../Manager/GameManager.h"
#include "../../Manager/CameraManager.h"

#include "../../Util/AboutTile.h"
#include <iostream>


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

	_actionSterategy = actions[0];
}

void PlayerMovement::Update()
{
	_actionSterategy->DoAction();
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

void InputAction::DoAction()
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
		POINT* camera = (CameraManager::GetInstance()->GetCameraPos());

		int dx[] = { 0,-1,1,0 };
		int dy[] = { 1,-0,0,-1 };



		int tmpCameraPosX = camera->x + dx[(int)dir] * 1;
		int tmpCameraPosY = camera->y + dy[(int)dir] * 1;

		if (CameraManager::GetInstance()->CheckOutOfTile(tmpCameraPosX, tmpCameraPosY) == false)
		{
			camera->x += dx[(int)dir] * 4;
			camera->y += dy[(int)dir] * 4;
		}
		pos.x += dx[(int)dir] * 4;
		pos.y += dy[(int)dir] * 4;

		cout << pos.y << endl;

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

void InitialAction::DoAction()
{
#define LEFT 2
#define RIGHT 0
#define FRONT 1

	motionDelay++;
	if (motionDelay > 22)
	{
		int frameX = _obj->GetComponent<PlayerSpriteRenderer>()->GetFrameX();

		if (isMotionFinish)
		{
			_obj->GetComponent<PlayerSpriteRenderer>()->SetState(PlayerSpriteState::Move);
			_obj->GetComponent<PlayerMovement>()->SetActionStartegy(PlayerActionState::Input);
		}

		if (frameX == FRONT && isFront)
		{
			_obj->GetComponent<PlayerSpriteRenderer>()->SetFrameX(LEFT);
			isFront = false;
		}
		else if (frameX == LEFT && isFront == false)
		{
			_obj->GetComponent<PlayerSpriteRenderer>()->SetFrameX(FRONT);
		}
		else if (frameX == 1 && isFront == false)
		{
			_obj->GetComponent<PlayerSpriteRenderer>()->SetFrameX(RIGHT);
			isFront = false;
		}
		else
		{
			_obj->GetComponent<PlayerSpriteRenderer>()->SetFrameX(FRONT);
			isFront = true;
			isMotionFinish = true;
		}
		motionDelay = 0;
	}
}
