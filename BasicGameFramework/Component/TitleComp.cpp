#include "TitleComp.h"
#include "../Manager/ImageManager.h"
#include "../Util/Sprite.h"
#include "../Util/Input.h"
#include "../Scene/Scene.h"
#include "../Manager/SceneManager.h"
#include "../Manager/GameManager.h"
#include "../Manager/QuestManager.h"
#include "../Manager/ItemManager.h"
#include "../Manager/CameraManager.h"
#include "../Manager/SoundManager.h"

void TitleComp::Init()
{
	Component::Init();
	selectPanelOpacity = 1;
	backPanelOpacity = 0;

	isDecrease = true;

	isSelect = false;
	state = SelectState::StartOver;

	SoundManager::GetInstance()->startSound(L"Title");
	this->SetActive(true);
}

void TitleComp::Update()
{

	if (isSelect == false)
	{
		if (Input::GetButtonDown(VK_DOWN))
		{
			if ((int)state < 2)
			{
				int tmp = (int)state;
				state = (SelectState)(++tmp);
			}
			SoundManager::GetInstance()->startInfSound(L"Cursor");

		}
		else if (Input::GetButtonDown(VK_UP))
		{
			if ((int)state > 0)
			{
				int tmp = (int)state;
				state = (SelectState)(--tmp);
			}
			SoundManager::GetInstance()->startInfSound(L"Cursor");

		}

		if (Input::GetButtonDown('Z'))
		{
			isSelect = true;
			SoundManager::GetInstance()->startInfSound(L"Click");
		}


	}
	if (isDecrease == true)
	{
		selectPanelOpacity -= 0.05;
		if (selectPanelOpacity <= 0.5f)
		{
			isDecrease = false;
		}
	}
	else
	{
		selectPanelOpacity += 0.05f;
		if (selectPanelOpacity >= 1.0f)
		{
			isDecrease = true;
		}
	}

	if (isSelect)
	{
		backPanelOpacity += 0.01;

		//상태 실행 부분
		if (backPanelOpacity >= 1.1)
		{
			switch (state)
			{
			case SelectState::StartOver:
				MapCopy();
				SoundManager::GetInstance()->StopSound(L"Title");
				SceneManager::GetInstance()->SetNextScene(L"Main");
				state = SelectState::None;
				GameManager::GetInstance()->SetCurrScene(0);
				QuestManager::GetInstance()->SetQuest(10);
				ItemManager::GetInstance()->Clear();
				ItemManager::GetInstance()->Init();
				CameraManager::GetInstance()->Init();
				break;
			case SelectState::Load:

				break;
			case SelectState::Exit:
				PostQuitMessage(0);
				break;
			default:
				break;
			}
		}
	}
}

void TitleComp::Render(HDC hdc)
{
	SelectPanel->Render(230,
		293 + (int)state * 30,
		selectPanelOpacity);

	if (isSelect)
	{
		backPanel->SizeRender(0, 0, 32 * 17, 32 * 13, backPanelOpacity);
	}
}

void TitleComp::SetSprite(const wchar_t* fileName)
{
	SelectPanel = ImageManager::GetInstance()->FindSprite(fileName);
	backPanel = ImageManager::GetInstance()->FindSprite(L"Image/UI/OpacityPanel.png");
}


void TitleComp::MapCopy()
{

	for (int i = 0; i <= 9; ++i)
	{
		wstring loadPath = L"Save/MapData" + to_wstring(i) + L".txt";
		wstring savePath = L"Map/MapData" + to_wstring(i) + L".txt";
		CopyFile(
			loadPath.c_str(),
			savePath.c_str(),
			false);
	}
}
