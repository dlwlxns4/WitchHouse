#include "TriggerObj.h"
#include "../Component/SizeAdjRenderer.h"

#include "../Manager/GameManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/CameraManager.h"
#include "../Manager/PhysicsManager.h"

void TriggerObj::Init()
{

}

void TriggerObj::OnTrigger()
{
}

void TriggerObj::Render(HDC hdc)
{
	POINT* cameraPos = CameraManager::GetInstance()->GetCameraPos();
	if (this->GetPosition().x >= TILE_SIZE * (cameraPos->x / TILE_SIZE - 1) && this->GetPosition().x < TILE_SIZE * MAP_SIZE_X + TILE_SIZE * cameraPos->x / TILE_SIZE)
	{
		if (this->GetPosition().y >= TILE_SIZE * (cameraPos->y / TILE_SIZE - 1) && this->GetPosition().y < TILE_SIZE * MAP_SIZE_Y + TILE_SIZE * cameraPos->y / TILE_SIZE)
		{
			GameObject::Render(hdc);
		}
	}
}

void DoorObj::Init()
{
	SizeAdjRenderer* sr = new SizeAdjRenderer(this, 1);
	sr->SetSprite(L"Image/Graphics/Obj/HouseDoor.png");
	sr->SetMaxFrame(4, 1);
	renderer = sr;
}

void DoorObj::OnTrigger()
{
	isActable = true;
	GameManager::GetInstance()->GetPlayer()->GetComponent<PlayerMovement>()->SetActionStartegy(PlayerActionState::IntoHouse);
}

void DoorObj::Update()
{
	if (isActable)
	{
		animDelay++;
		if (animDelay >= 20)
		{
			animDelay = 0;
			frameX++;
			if (frameX > 3)
			{
				isActable = false;
			}
			renderer->SetFrameX(frameX);
		}
	}
}

void DoorObj::Write(std::ostream& os) const
{
	os << 7 << "\t";
	GameObject::Write(os);
	os << frameX << "\t";
	os << animDelay << "\t";
	os << isActable << "\t";
}

void DoorObj::Read(std::istream& is)
{
	GameObject::Read(is);
	is >> frameX
		>> animDelay
		>> isActable;

	this->renderer=this->GetComponent<SizeAdjRenderer>();
	PhysicsManager::GetInstance()->SetTriggerObj(this->GetPosition().x / 32, this->GetPosition().y / 32 + 1, this);
}

void DoorObj::SetLoadMap(int index)
{
}

void DoorObj::SetSpriteIndex(int index)
{
	renderer->SetIndex(index);
}




