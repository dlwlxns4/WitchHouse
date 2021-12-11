#include "PlayerMovement.h"
#include "../CircleComponent.h"

#include "../../Object/GameObject.h"
#include "../../Util/Input.h"
#include "../../Util/Timer.h"


#include "PlayerSpriteRenderer.h"

#include "../../Manager/GameManager.h"
#include <iostream>

#define DOWN_DIR	0
#define LEFT_DIR	1
#define RIGHT_DIR	2
#define UP_DIR		3

void PlayerMovement::Update()
{
	POINT pos = _owner->GetPosition();
	POINTFLOAT* camera = (GameManager::GetInstance()->GetCameraPos());

	if (GameManager::GetInstance()->GetState() == State::None)
	{
		if (Input::GetButton(VK_UP))
		{
			GameManager::GetInstance()->SetState(State::Move);
			_owner->GetComponent<PlayerSpriteRenderer>()->SetDirection(UP_DIR);
			(camera->y)++;
		}
		if (Input::GetButton(VK_DOWN))
		{
			GameManager::GetInstance()->SetState(State::Move);

			_owner->GetComponent<PlayerSpriteRenderer>()->SetDirection(DOWN_DIR);

		}
		if (Input::GetButton(VK_LEFT))
		{
			GameManager::GetInstance()->SetState(State::Move);
			_owner->GetComponent<PlayerSpriteRenderer>()->SetDirection(LEFT_DIR);

		}
		if (Input::GetButton(VK_RIGHT))
		{
			GameManager::GetInstance()->SetState(State::Move);
			_owner->GetComponent<PlayerSpriteRenderer>()->SetDirection(RIGHT_DIR);

		}
	}

	if (GameManager::GetInstance()->GetState() == State::Move)
	{
		Direction dir = _owner->GetComponent<PlayerSpriteRenderer>()->GetDirection();
		int dx[] = { 0,-1,1,0 };
		int dy[] = { 1,-0,0,-1 };

		//static_cast<LONG>(_speed * Timer::GetDeltaTime());
		//static_cast<LONG>(_speed * Timer::GetDeltaTime());
		pos.x += dx[(int)dir] * 4;
		pos.y += dy[(int)dir] * 4;
		_owner->SetPosition(pos);
		std::cout << pos.x << " " << pos.y << "\n";
		moveDistance += 4;
		if (moveDistance >= 32)
		{
			moveDistance = 0;
			GameManager::GetInstance()->SetState(State::None);
		}

	}
}

void PlayerMovement::SetSpeed(float speed) noexcept
{
	_speed = speed;
}

float PlayerMovement::GetSpeed() const noexcept
{
	return _speed;
}
