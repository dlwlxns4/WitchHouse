#include "TrapAction.h"
#include "../Object/GameObject.h"
#include "../Manager/CameraManager.h"
#include "../Manager/GameManager.h"

#include "../Component/SpriteRenderer.h"
#include "../Component/Player/PlayerMovement.h"
TrapAction::~TrapAction()
{
	Release();

}

void TrapAction::Init()
{
	TrapNullAction* nullAction = new TrapNullAction(this->_owner);
	actions[0] = nullAction;

	ActionID0* actionID0 = new ActionID0(this->_owner);
	actions[1] = actionID0;

	ActionID1* actionID1 = new ActionID1(this->_owner);
	actions[2] = actionID1;

	ActionID2* actionID2 = new ActionID2(this->_owner);
	actions[3] = actionID2;
	
	ActionID3* actionID3 = new ActionID3(this->_owner);
	actions[4] = actionID3;

	ActionID4* actionID4 = new ActionID4(this->_owner);
	actions[5] = actionID4;

	_actionSterategy = nullAction;

}

void TrapAction::Update()
{
	_actionSterategy->DoAction();
}

void TrapAction::Release()
{
	if (actions.empty() == false)
	{
		for (size_t i = 0; i < actions.size(); ++i)
		{
			delete actions[i];
			actions[i] = nullptr;
		}
	}
}

void TrapAction::Write(ostream& os) const
{
	os << "103" << "\t";
	Component::Write(os);
}


void TrapAction::Read(istream& is)
{
	Component::Read(is);
}

void TrapAction::SetActionStartegy(TrapActionState action)
{
	_actionSterategy = actions[static_cast<int>(action)];
}

void ActionID0::DoAction()
{
	moveDelay++;
	if (moveDelay >= 3)
	{
		POINT pos = _obj->GetPosition();
		_obj->SetPosition(pos.x + 16, pos.y);
		moveDelay = 0;
		cycleCount++;
		if (cycleCount >= 11)
		{
			cycleCount = 0;
			_obj->GetComponent<TrapAction>()->SetActionStartegy(TrapActionState::Null);
		}
	}
}

void ActionID1::DoAction()
{
	moveDelay++;
	if (moveDelay >= 3)
	{
		POINT pos = _obj->GetPosition();
		_obj->SetPosition(pos.x - 16, pos.y);
		moveDelay = 0;
		cycleCount++;
		if (cycleCount >= 11)
		{
			cycleCount = 0;
			_obj->GetComponent<TrapAction>()->SetActionStartegy(TrapActionState::Null);
			CameraManager::GetInstance()->SetActionStrategy(CameraActionState::Shake);
		}
	}
}

void ActionID2::DoAction()
{
	animDelay++;
	if (cycleCount <= 2)
	{
		if (animDelay >= 3)
		{
			animDelay = 0;
			int currFrameY = _obj->GetComponent<SpriteRenderer>()->GetCurrFrameY();
			_obj->GetComponent<SpriteRenderer>()->SetFrameY(currFrameY + 2);
			cycleCount++;
		}
	}
	else
	{
		if (animDelay >= 30)
		{
			animDelay = 0;
			cycleCount = 0;
			_obj->GetComponent<TrapAction>()->SetActionStartegy(TrapActionState::Null);
			GameManager::GetInstance()->GetPlayer()->GetComponent<PlayerMovement>()->SetActionStartegy(PlayerActionState::Input);
		}
	}
}

void ActionID3::DoAction()
{
	if (cycleCount == 0)
	{
		cycleCount++;
		int currFrameY = _obj->GetComponent<SpriteRenderer>()->GetCurrFrameY();
		_obj->GetComponent<SpriteRenderer>()->SetFrameX(currFrameY + 1);
	}
	else
	{
		animDelay++;
		if (animDelay >= 20)
		{
			cycleCount = 0;
			animDelay = 0;
			_obj->GetComponent<TrapAction>()->SetActionStartegy(TrapActionState::Null);
			GameManager::GetInstance()->GetPlayer()->GetComponent<PlayerMovement>()->SetActionStartegy(PlayerActionState::Input);
		}
	}
}

void ActionID4::DoAction()
{
	int currFrameX = _obj->GetComponent<SpriteRenderer>()->GetCurrFrameX();
	_obj->GetComponent<SpriteRenderer>()->SetFrameX(currFrameX + 1);
	_obj->GetComponent<TrapAction>()->SetActionStartegy(TrapActionState::Null);
}
