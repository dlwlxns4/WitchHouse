#include "GameOverObj.h"

#include "../Component/FullSizeRenderer.h"
#include "../Component/GameOverComp.h"

void GameOverObj::Init()
{
	FullSizeRenderer* renderer = new FullSizeRenderer(this, 1);
	renderer->SetSprite(L"Image/UI/GameOver.png");

	GameOverComp* gameOverComp = new GameOverComp(this, 2);
}
