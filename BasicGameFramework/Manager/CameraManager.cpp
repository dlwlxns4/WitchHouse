#include "CameraManager.h"
#include "../Util/AboutTile.h"

#include "../Manager/GameManager.h"
#include "../Component/Player/PlayerMovement.h"

CameraManager::~CameraManager()
{
	Release();
}

void CameraManager::SetCameraPos(POINT pos)
{
	cameraPos = pos;
}

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

bool CameraManager::CheckOutOfTileX(int x)
{
	if (x / 32 <= minPosX - 1 || x / 32 > (maxPosX + 1) - MAP_SIZE_X)
		return true;

	return false;
}

bool CameraManager::CheckOutOfTileY(int y)
{
	int posY = minPosY;
	if (GameManager::GetInstance()->GetCurrScene() == 2)
	{
		posY += 2;
	}
	if (y / 32 <= posY - 1 || y / 32 > (maxPosY + 1) - MAP_SIZE_Y)
		return true;

	return false;
}

void CameraManager::Clear()
{
	maxPosX = 0;
	maxPosY = 0;
	minPosX = 10000;
	minPosY = 10000;
}

void CameraManager::SetActionStrategy(CameraActionState state)
{
	if (_actionSterategy != actions[static_cast<int>(state)])
	{
		_actionSterategy = actions[static_cast<int>(state)];
	}
}

void CameraManager::Init()
{
	cameraPos.x = 32;
	cameraPos.y = -96;

	if (actions[0] == nullptr)
	{
		CameraNullAction* nullAction = new CameraNullAction(this);
		actions[0] = (nullAction);

		CameraShakeAction* shakeAction = new CameraShakeAction(this);
		actions[1] = (shakeAction);
	}


	_actionSterategy = actions[0];
}

void CameraManager::Update()
{
	_actionSterategy->DoAction();
	const int currQuest = QuestManager::GetInstance()->GetQuest();
	if (currQuest == 10)
	{
		cameraDelay++;
		if (cameraDelay >= 3)
		{
			cameraDelay = 0;
			cameraPos.y += 1;
		}
		if (cameraPos.y >= 96)
		{
			cameraPos.y = 96;

			QuestManager::GetInstance()->NextQuest();
			GameManager::GetInstance()->SetPlayerSprite(PlayerSpriteState::Init);
			GameManager::GetInstance()->SetPlayerAction(PlayerActionState::Initial);
		}
		if (Input::GetButtonDown('P'))
		{
			cameraPos.y = 96;
		}
	}
}

void CameraManager::Release()
{
	for (auto it = actions.begin(); it != actions.end(); ++it)
	{
		delete* it;
	}
	_actionSterategy = nullptr;
}

void CameraManager::Write(std::ostream& os) const
{
	os << cameraPos.x << "\t";
	os << cameraPos.y << "\t";
}

void CameraManager::Read(std::istream& is)
{
	is >> cameraPos.x
		>> cameraPos.y;
}

std::ostream& operator<<(std::ostream& os, const CameraManager& cameraManager)
{
	cameraManager.Write(os);
	return os;
}

std::istream& operator>>(std::istream& is, CameraManager& cameraManager)
{
	cameraManager.Read(is);
	return is;
}
