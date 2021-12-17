#pragma once

#include <Windows.h>
#include <string>
#include <unordered_map>

#include "../Util/Singleton.h"
#include "../Component/Player/PlayerMovement.h"
#include "../Component/Player/PlayerSpriteRenderer.h"
class Player;
enum class State
{
	None = 0,
	Move = 1,
	Chat = 2,
	UserInfo = 3
};

struct mapData
{
	int sceneNum;
	int charaterPosX;
	int characterPosY;
};

class GameManager : public Singleton<GameManager>
{
public:
	State GetState() { return state; };
	
	void SetState(State st) { state = st; }
	
	void Init();
	
	int GetCurrScene() { return currScene; }
	POINT GetPlayerPos() { return playerPos; }
	void SetPlayer(Player* player);
	void SetPlayerAction(PlayerActionState actionState);
	void SetPlayerSprite(PlayerSpriteState spriteState);

	void GenerateMapData();

private:
	State state = State::None;

	int currScene = 0;
	POINT playerPos = { 9*32,9*32 };
	Player* player = nullptr;
	vector<mapData> mapDatas;

};


