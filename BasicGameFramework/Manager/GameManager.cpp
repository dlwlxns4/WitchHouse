#include "GameManager.h"

#include "../Object/Player.h"

void GameManager::Init()
{
	GenerateMapData();
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

void GameManager::GenerateMapData()
{
	mapDatas.push_back({ 0, 10, 10 });
	mapDatas.push_back({ 1, 10, 10 });
}
