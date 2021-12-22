#include "QuestObj.h"
#include "../Component/SpriteRenderer.h"
#include "../Manager/PhysicsManager.h"
#include "../Manager/QuestManager.h"

QuestObj::~QuestObj()
{
	Release();
}

void QuestObj::Init()
{
	SpriteRenderer* sr = new SpriteRenderer(this, 1);
	this->renderer = sr;

	NullQuestAction* nullAction = new NullQuestAction(this);
	_actions[0] = nullAction;

	SetFrameAction* setFrameAction = new SetFrameAction(this);
	_actions[1] = setFrameAction;

	_actionStrategy = _actions[0];
}

void QuestObj::SetSprite(int spriteIndex, int frameX, int frameY)
{
	renderer->SetSprite(spriteIndex, frameX, frameY);
}

void QuestObj::AddId()
{
	id++;
}

int QuestObj::GetId()
{
	return id;
}

void QuestObj::Update()
{
	_actionStrategy->DoUpdate();
	if (isActable)
	{
		GameObject::Update();
	}
}

void QuestObj::Render(HDC hdc)
{
	if (isActable)
	{
		GameObject::Render(hdc);
	}
}

void QuestObj::Release()
{
	if (_actions.empty() == false)
	{
		for (size_t i = 0; i < _actions.size(); ++i)
		{
			delete _actions[i];
		}
	}
}

void QuestObj::SetIsActable(bool isActive)
{
	this->isActable = isActive;
}

void QuestObj::Write(std::ostream& os) const
{
	os << 6 << "\t";
	GameObject::Write(os);
	os << id << "\t";
	os << isActable << "\t";
}

void QuestObj::Read(std::istream& is)
{
	GameObject::Read(is);
	is >> id;
	is >> isActable;
	QuestManager::GetInstance()->SetQuestObj(GetPosition().x / 32, GetPosition().y / 32, this);


	NullQuestAction* nullAction = new NullQuestAction(this);
	_actions[0] = nullAction;

	SetFrameAction* setFrameAction = new SetFrameAction(this);
	_actions[1] = setFrameAction;

	_actionStrategy = _actions[0];
}

void QuestObj::SetActionStrategy(QuestObjStrategy state)
{
	_actionStrategy = _actions[static_cast<int>(state)];
}

void SetFrameAction::DoUpdate()
{
	SpriteRenderer* renderer = _owner->GetComponent<SpriteRenderer>();
	int maxFrameX = renderer->GetMaxFrameX();
	int currFrameX = renderer->GetCurrFrameX();

	currFrameX++;
	animDelay++;
	cout << currFrameX << " " << maxFrameX << endl;
	if (animDelay >= 2)
	{
		animDelay = 0;
		if (currFrameX < maxFrameX)
		{
			renderer->SetFrameX(currFrameX);
		}
		else
		{
			((QuestObj*)(_owner))->SetActionStrategy(QuestObjStrategy::Null);
		}
	}
}
