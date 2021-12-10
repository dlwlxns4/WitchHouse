#include "PlayerMovement.h"
#include "../CircleComponent.h"

#include "../../Object/GameObject.h"
#include "../../Util/Input.h"
#include "../../Util/Timer.h"


#include "PlayerSpriteRenderer.h"

#define DOWN_DIR	0
#define LEFT_DIR	1
#define RIGHT_DIR	2
#define UP_DIR		3

void PlayerMovement::Update()
{
	POINT pos = _owner->GetPosition();

	if (Input::GetButton('W'))
	{
		pos.y -= static_cast<LONG>(_speed * Timer::GetDeltaTime());
		_owner->GetComponent<PlayerSpriteRenderer>()->SetDirection(UP_DIR);
	}

	if (Input::GetButton('S'))
	{
		pos.y += static_cast<LONG>(_speed * Timer::GetDeltaTime());
		_owner->GetComponent<PlayerSpriteRenderer>()->SetDirection(DOWN_DIR);

	}

	if (Input::GetButton('A'))
	{
		pos.x -= static_cast<LONG>(_speed * Timer::GetDeltaTime());
		_owner->GetComponent<PlayerSpriteRenderer>()->SetDirection(LEFT_DIR);

	}

	if (Input::GetButton('D'))
	{
		pos.x += static_cast<LONG>(_speed * Timer::GetDeltaTime());
		_owner->GetComponent<PlayerSpriteRenderer>()->SetDirection(RIGHT_DIR);

	}

	_owner->SetPosition(pos);
}

void PlayerMovement::SetSpeed(float speed) noexcept
{
	_speed = speed;
}

float PlayerMovement::GetSpeed() const noexcept
{
	return _speed;
}
