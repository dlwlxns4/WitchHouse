#include "GameOverComp.h"
#include "../Util/Input.h"
#include "../Manager/SceneManager.h"
#include "../Manager/CameraManager.h"
#include "../Manager/QuestManager.h"
#include "../Manager/ItemManager.h"

void GameOverComp::Update()
{
	if (Input::GetButtonDown('Z'))
	{
		SceneManager::GetInstance()->SetNextScene(L"Title");
	}
}
