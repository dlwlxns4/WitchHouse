#include "GameOverScene.h"
#include "Layer.h"
#include "../Object/GameOverObj.h"

void GameOverScene::Init()
{
	Layer* main = new Layer(this, L"Main", 100);

	GameOverObj* gameOverObj = new GameOverObj(this, main, L"GameOver");
	
	Scene::Init();
}
