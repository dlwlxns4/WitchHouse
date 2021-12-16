#include "CameraManager.h"
#include "../Util/AboutTile.h"

#include "../Manager/GameManager.h"
#include "../Component/Player/PlayerMovement.h"

void CameraManager::SetCameraMinX(int x)
{
	if (x < minPosX)
	{
		minPosX = x;
	}
}

void CameraManager::SetCameraMinY(int y)
{
	if (y < minPosY)
	{
		minPosY = y;
	}
}

void CameraManager::SetCameraMaxX(int x)
{
	if (x > maxPosX)
	{
		maxPosX = x;
	}
}

void CameraManager::SetCameraMaxY(int y)
{
	if (y > maxPosY)
	{
		maxPosY = y;
	}
}

bool CameraManager::CheckOutOfTile(int x, int y)
{
	if (x/32 < minPosX-1 || x/32 > (maxPosX-1)-MAP_SIZE_X)
		return true;
	if (y/32 < minPosY-1 || y/32 > (maxPosY)-MAP_SIZE_Y)
		return true;

	return false;
}

void CameraManager::Init()
{
	cameraPos.x = 32;
	cameraPos.y = -96;
}

void CameraManager::Update()
{
	const int* currQuest = QuestManager::GetInstance()->GetQuestPtr();
	if (*currQuest == 0)
	{
		cameraDelay++;
		if (cameraDelay >= 3)
		{
			cameraDelay = 0;
			cameraPos.y += 1;
		}
		if (cameraPos.y >= 96)
		{
			QuestManager::GetInstance()->NextQuest();
			GameManager::GetInstance()->SetPlayerSprite(PlayerSpriteState::Init);
			GameManager::GetInstance()->SetPlayerAction(PlayerActionState::Initial);
		}
	}
}
