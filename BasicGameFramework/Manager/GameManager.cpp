#include "GameManager.h"

#include "../Object/Player.h"

void GameManager::Init()
{
	GeneratePlayerData();
	GenerateCameraData();
}

void GameManager::SetPlayer(Player* player)
{
	this->player = player;
}

void GameManager::SetPlayerAction(PlayerActionState actionState)
{
	player->GetComponent<PlayerMovement>()->SetActionStartegy(actionState);
}

void GameManager::SetPlayerSprite(PlayerSpriteState spriteState)
{
	player->GetComponent<PlayerSpriteRenderer>()->SetState(spriteState);
}

void GameManager::SetPlayerPos(POINT pos)
{
	player->SetPosition(pos);
}


void GameManager::GenerateCameraData()
{
	cameraPosData[1][0] = { -128, 96 };
	cameraPosData[0][1] = { 32, -96 };
	cameraPosData[0][2] = { 0, 96 };
	cameraPosData[2][0] = { 0, 0 };
	cameraPosData[2][3] = { 0, 160 };
	cameraPosData[3][2] = { 0, -416 };
}

void GameManager::GeneratePlayerData()
{
	playerPosData[1][0] = { 4, 14 };
	playerPosData[0][1] = { 9, -2 };
	playerPosData[0][2] = { 8, 14 };
	playerPosData[2][0] = { 9, 1 };
	playerPosData[2][3] = { 8, 14 };
	playerPosData[3][2] = { 8, -6 };
	playerPosData[3][4] = { 8, 8 };
}
void GameManager::SetUIObj(GameObject* ui)
{
	UIObj = ui;
}

GameObject* GameManager::GetUIObj()
{
	return UIObj;
}

POINT GameManager::GetCameraData(int prevScene, int mapNum)
{
	POINT tmp = cameraPosData[prevScene][mapNum];


	return POINT({ tmp.x, tmp.y });
}



POINT GameManager::GetPlayerData(int prevScene, int mapNum)
{

	POINT tmp = playerPosData[prevScene][mapNum];


	return POINT({ tmp.x, tmp.y });
}
