#include "TitleScene.h"


#include "../Util/Input.h"

#include "../Manager/SceneManager.h"

#include "../Object/TitleObj.h"

#include "../Scene/Layer.h"
#include "../Util/Timer.h"
void TitleScene::Init()
{
	delay = 0;
	Layer* main = new Layer(this, L"Main", 1);

	TitleObj* titleObj = new TitleObj(this, main, L"Title");
	titleObj->SetPosition(0, 0);


	Scene::Init();
}

void TitleScene::Update()
{
	delay += Timer::GetDeltaTime();
	if (delay >= 1000.0f)
	{
		Scene::Update();
	}
}
