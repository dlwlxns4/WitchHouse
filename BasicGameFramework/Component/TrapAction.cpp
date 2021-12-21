#include "TrapAction.h"
#include "../Object/GameObject.h"

TrapAction::~TrapAction()
{
	Release();

}

void TrapAction::Init()
{
	NullAction* nullAction = new NullAction(this->_owner);
	actions[0] = nullAction;

	ActionID0* actionID0 = new ActionID0(this->_owner);
	actions[1] = actionID0;

	ActionID1* actionID1 = new ActionID1(this->_owner);
	actions[2] = actionID1;

	_actionSterategy= nullAction;

}

void TrapAction::Update()
{
	_actionSterategy->DoAction();
}

void TrapAction::Release()
{
	for (size_t i = 0; i < actions.size(); ++i)
	{
		delete actions[i];
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
	if (moveDelay >= 5)
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
	if (moveDelay >= 5)
	{
		POINT pos = _obj->GetPosition();
		_obj->SetPosition(pos.x - 16, pos.y);
		moveDelay = 0;
		cycleCount++;
		if (cycleCount >= 11)
		{
			cycleCount = 0;
			_obj->GetComponent<TrapAction>()->SetActionStartegy(TrapActionState::Null);
		}
	}
}
