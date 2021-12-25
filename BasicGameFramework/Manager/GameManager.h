#pragma once

#include <Windows.h>
#include <string>
#include <unordered_map>

#include "../Util/Singleton.h"
#include "../Component/Player/PlayerMovement.h"
#include "../Component/Player/PlayerSpriteRenderer.h"
class Player;
class UIObj;
enum class State
{
	None = 0,
	Move = 1,
	Chat = 2,
	UserInfo = 3
};

struct playerData
{
	int prevSceneNum;
	int sceneNum;
	int characterPosX;
	int characterPosY;
};

struct cameraData
{
	int prevSceneNum;
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
	int	 GetCurrScene() { return currScene; }
	void SetCurrScene(int scene) { currScene = scene; }
	void SetPlayer(Player* player);
	void SetPlayerAction(PlayerActionState actionState);
	void SetPlayerSprite(PlayerSpriteState spriteState);
	void SetPlayerPos(POINT pos);

	void GeneratePlayerData();
	void GenerateCameraData();

	void SetUIObj(GameObject* ui);
	GameObject* GetUIObj();

	POINT GetPlayerData(int prevScene, int mapNum);
	POINT GetCameraData(int prevScene, int mapNum);
	GameObject* GetPlayer() { return player; };


	void Write(std::ostream& os) const;
	friend std::ostream& operator<<(std::ostream& os, const GameManager& gameManager);
	void Read(std::istream& is);
	friend std::istream& operator>>(std::istream& is, GameManager& gameManager);
private:
	State state = State::None;

	int currScene = 0;
	POINT playerPos = { 9*32,9*32 };
	GameObject* player = nullptr;
	GameObject* UIObj = nullptr;

	unordered_map<int, unordered_map<int, POINT>> playerPosData;
	unordered_map<int, unordered_map<int, POINT>> cameraPosData;
};


