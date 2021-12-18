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
	cameraPosData[1][0] = { -128,96 };
	cameraPosData[0][1] = { 32,-96 };
	cameraPosData[0][2] = { 0,96 };
	cameraPosData[2][0] = { 0,0 };
}

POINT GameManager::GetCameraData(int prevScene, int mapNum)
{
	POINT tmp = cameraPosData[prevScene][mapNum];


	return POINT({ tmp.x, tmp.y });
}


void GameManager::GeneratePlayerData()
{
	playerPosData[1][0] = { 4,14 };
	playerPosData[0][1] = { 9,-2 };
	playerPosData[0][2] = { 8,14 };
	playerPosData[2][0] = { 9,1 };
}

POINT GameManager::GetPlayerData(int prevScene, int mapNum)
{

	POINT tmp = playerPosData[prevScene][mapNum];


	return POINT({ tmp.x, tmp.y });
}
