#include "TitleScene.h"


#include "../Util/Input.h"

#include "../Manager/SceneManager.h"

#include "../Object/TitleObj.h"

#include "../Scene/Layer.h"
void TitleScene::Init()
{
	Layer* main = new Layer(this, L"Main", 1);

	TitleObj* titleObj = new TitleObj(this, main, L"Title");
	titleObj->SetPosition(0, 0);


	Scene::Init();
}

void TitleScene::Update()
{
	Scene::Update();

	if (Input::GetButtonDown(VK_SPACE))
	{
		SceneManager::GetInstance()->SetNextScene(L"Temp");
	}
}
