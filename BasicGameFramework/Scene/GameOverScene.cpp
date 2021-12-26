#include "GameOverScene.h"
#include "Layer.h"
#include "../Object/GameOverObj.h"
#include "../Manager/SoundManager.h"

void GameOverScene::Init()
{
	Layer* main = new Layer(this, L"Main", 100);

	GameOverObj* gameOverObj = new GameOverObj(this, main, L"GameOver");
	

	SoundManager::GetInstance()->StopSound(L"House");

	Scene::Init();
}
