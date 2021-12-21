#include "GameOverComp.h"
#include "../Util/Input.h"
#include "../Manager/SceneManager.h"

void GameOverComp::Update()
{
	if (Input::GetButtonDown('Z'))
	{
		SceneManager::GetInstance()->SetNextScene(L"Title");
	}

}
