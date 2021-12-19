#include "QuestObj.h"
#include "../Component/SpriteRenderer.h"
#include "../Manager/PhysicsManager.h"
#include "../Manager/QuestManager.h"

void QuestObj::Init()
{
	SpriteRenderer* sr = new SpriteRenderer(this, 1);
	this->renderer = sr;
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
}
