#include "TriggerObj.h"
#include "../Component/SizeAdjRenderer.h"

#include "../Scene/MainScene.h"

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
	sr->SetMaxFrame(4, 4);
	renderer = sr;
}

void DoorObj::OnTrigger()
{
	GameObject* player = GameManager::GetInstance()->GetPlayer();
	isActable = true;
	player->GetComponent<PlayerMovement>()->SetActionStartegy(PlayerActionState::IntoHouse);
	
	if (QuestManager::GetInstance()->GetQuest() <= 12)
	{
		((IntoHouseAction*)(player->GetComponent<PlayerMovement>()->GetActionStartegy()))->SetLimitTime(100,10);
	}
	else
	{
		((IntoHouseAction*)(player->GetComponent<PlayerMovement>()->GetActionStartegy()))->SetLimitTime(2,3);

	}
	if (QuestManager::GetInstance()->GetQuest() <= 12)
	{
		QuestManager::GetInstance()->SetQuest(13);
	}
	((IntoHouseAction*)(player->GetComponent<PlayerMovement>()->GetActionStartegy()))->SetNextScene(loadMap);
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
	os << loadMap << "\t";
}

void DoorObj::Read(std::istream& is)
{
	GameObject::Read(is);
	is >> frameX
		>> animDelay
		>> isActable
		>> loadMap;
	this->renderer=this->GetComponent<SizeAdjRenderer>();
	PhysicsManager::GetInstance()->SetTriggerObj(this->GetPosition().x / 32, this->GetPosition().y / 32 + 1, this);
}

void DoorObj::SetLoadMap(int index)
{
	loadMap = index;
}

void DoorObj::SetSpriteIndex(int index)
{
	renderer->SetIndex(index);
}

void TrapObj::OnTrigger()
{
	cout << "วิมค" << endl;
	((MainScene*)(SceneManager::GetInstance()->GetCurrentScene()))->DoTrap(id);
}

void TrapObj::Write(std::ostream& os) const
{
	os << 8 << "\t";
	GameObject::Write(os);
	os << id << "\t";
}

void TrapObj::Read(std::istream& is)
{
	GameObject::Read(is);
	is >> id;
	PhysicsManager::GetInstance()->SetTriggerObj(this->GetPosition().x / 32, this->GetPosition().y / 32, this);
}
