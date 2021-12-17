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
	cameraDatas.push_back({ 0, -128, 96 });
	cameraDatas.push_back({ 1, 32, -96 });
}

POINT GameManager::GetCameraData(int mapNum)
{
	cameraData tmp = cameraDatas[mapNum];
	int x = tmp.cameraPosX;
	int y = tmp.cameraPosY;

	return POINT({ x,y });
}


void GameManager::GeneratePlayerData()
{
	playerDatas.push_back({ 0, 4, 14 });
	playerDatas.push_back({ 1, 9, -2 });
}

POINT GameManager::GetPlayerData(int mapNum)
{
	playerData tmp = playerDatas[mapNum];
	int x = tmp.characterPosX;
	int y = tmp.characterPosY;

	return POINT({ x,y });
}
