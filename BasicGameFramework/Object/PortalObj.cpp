#include "PortalObj.h"

#include <iostream>

#include "../Manager/PhysicsManager.h"
#include "../Manager/SceneManager.h"
#include "../Scene/MainScene.h"

void PortalObj::OnTrigger()
{
	((MainScene*)(SceneManager::GetInstance()->GetCurrentScene()))->TransMap(nextMapNum);
}

void PortalObj::Write(std::ostream& os) const
{
	os << 3 << "\t";
	GameObject::Write(os);
	os << nextMapNum << "\t";
}

void PortalObj::Read(std::istream& is)
{
	GameObject::Read(is);
	is >> nextMapNum;

	PhysicsManager::GetInstance()->SetTriggerObj(this->GetPosition().x / 32,
		this->GetPosition().y / 32, this);

}
