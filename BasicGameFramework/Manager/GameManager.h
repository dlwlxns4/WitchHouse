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

struct playerData
{
	int sceneNum;
	int characterPosX;
	int characterPosY;
};

struct cameraData
{
	int sceneNum;
	int cameraPosX;
	int cameraPosY;
};

class GameManager : public Singleton<GameManager>
{
public:
	GameManager() = default;
	~GameManager() = default;

	State GetState() { return state; };
	
	void SetState(State st) { state = st; }
	
	void Init();
	
	POINT GetPlayerPos() { return playerPos; }
	int GetCurrScene() { return currScene; }
	void SetPlayer(Player* player);
	void SetPlayerAction(PlayerActionState actionState);
	void SetPlayerSprite(PlayerSpriteState spriteState);
	void SetPlayerPos(POINT pos);

	void GeneratePlayerData();
	void GenerateCameraData();
	POINT GetCameraData(int mapNum);
	POINT GetPlayerData(int mapNum);
	GameObject* GetPlayer() { return player; };

private:
	State state = State::None;

	int currScene = 0;
	POINT playerPos = { 9*32,9*32 };
	GameObject* player = nullptr;


	vector<playerData> playerDatas;
	vector<cameraData> cameraDatas;

};


