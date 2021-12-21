#include "TrapActionObj.h"

#include "../Component/SpriteRenderer.h"
#include "../Component/TrapAction.h"

#include "../Manager/QuestManager.h"
void TrapActionObj::Init()
{
	TrapAction* trapAction = new TrapAction(this, 1);
	trapAction->Init();
	SpriteRenderer* sr = new SpriteRenderer(this, 2);
}



void TrapActionObj::Write(std::ostream& os) const
{
	os << 9 << "\t";
	GameObject::Write(os);
	os << id << "\t";
}

void TrapActionObj::Read(std::istream& is)
{
	GameObject::Read(is);
	is >> id;

	QuestManager::GetInstance()->SetQuestActionObj(this->GetPosition().x / 32,
		this->GetPosition().y / 32, this);

}