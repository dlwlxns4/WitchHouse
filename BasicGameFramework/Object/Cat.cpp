#include "Cat.h"
#include "../Component/SpriteRenderer.h"
#include "../Manager/QuestManager.h"

void Cat::Init()
{
	SpriteRenderer* sr = new SpriteRenderer(this, 1);
}

void Cat::Render(HDC hdc)
{
	switch (id)
	{
	case 0:
		if (QuestManager::GetInstance()->GetQuest() <= 12)
		{
			GameObject::Render(hdc);
		}
		break;
	}
}

void Cat::Write(std::ostream& os) const
{
	os << 10 << "\t";
	GameObject::Write(os);
	os << id << "\t";
}

void Cat::Read(std::istream& is)
{
	GameObject::Read(is);
	is >> id;
}
