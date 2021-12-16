#include "GameManager.h"

#include "../Object/Player.h"

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
