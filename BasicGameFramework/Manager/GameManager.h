#pragma once

#include <Windows.h>
#include <string>
#include <unordered_map>

#include "../Util/Singleton.h"

enum class State
{
	None = 0,
	Move = 1,
	Chat = 2,
	UserInfo = 3
};

class GameManager : public Singleton<GameManager>
{
private:
	POINTFLOAT cameraPos = {};
	State state = State::None;

	int currScene = 0;
	POINT playerPos = { 9*32,9*32 };

public:
	POINTFLOAT* GetCameraPos() { return &cameraPos; }
	State GetState() { return state; };
	
	void SetState(State st) { state = st; }
	
	
	int GetCurrScene() { return currScene; }
	POINT GetPlayerPos() { return playerPos; }
};

