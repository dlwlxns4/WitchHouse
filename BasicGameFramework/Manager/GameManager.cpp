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
	cameraPosData[4][3] = { 0,0 };
	cameraPosData[4][5] = { 0,0 };
	cameraPosData[5][6] = { -32, 0};
	cameraPosData[6][5] = { -32, 0 };
	cameraPosData[6][7] = { -32, 0 };
	cameraPosData[6][8] = { -32, 0 };
	cameraPosData[7][6] = { 0, -128 };
	cameraPosData[8][6] = { -32, 0 };
	cameraPosData[5][9] = { 0,0 };
	cameraPosData[9][5] = { -32,0 };
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
	playerPosData[4][3] = { 8,7 };
	playerPosData[4][5] = { 8,4 };
	playerPosData[5][6] = {6,9};
	playerPosData[6][5] = { 13,5 };
	playerPosData[6][7] = { 4,6 };
	playerPosData[6][8] = { 4,6 };
	playerPosData[7][6] = { 8,1 };
	playerPosData[8][6] = { 8,9 };
	playerPosData[5][9] = { 9,9 };
	playerPosData[9][5] = { 3,5 };

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

void GameManager::Write(std::ostream& os) const
{
	os << currScene << "\t";
	os << player->GetPosition().x << "\t";
	os << player->GetPosition().y << "\t";
}

void GameManager::Read(std::istream& is)
{
	is >> currScene;
	is >> playerPos.x;
	is >> playerPos.y;
}



POINT GameManager::GetPlayerData(int prevScene, int mapNum)
{

	POINT tmp = playerPosData[prevScene][mapNum];


	return POINT({ tmp.x, tmp.y });
}

std::ostream& operator<<(std::ostream& os, const GameManager& gameManager)
{
	gameManager.Write(os);
	return os;
}

std::istream& operator>>(std::istream& is, GameManager& gameManager)
{
	gameManager.Read(is);
	return is;
}
