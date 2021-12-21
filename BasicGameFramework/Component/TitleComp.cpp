#include "TitleComp.h"
#include "../Manager/ImageManager.h"
#include "../Util/Sprite.h"
#include "../Util/Input.h"
#include "../Manager/SceneManager.h"

void TitleComp::Init()
{
	Component::Init();
	selectPanelOpacity = 1;
	backPanelOpacity = 0;

	isDecrease = true;

	isSelect = false;
	state = SelectState::StartOver;
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
		}
		else if (Input::GetButtonDown(VK_UP))
		{
			if ((int)state > 0)
			{
				int tmp = (int)state;
				state = (SelectState)(--tmp);
			}
		}

		if (Input::GetButtonDown('Z'))
		{
			isSelect = true;
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
				SceneManager::GetInstance()->SetNextScene(L"Main");
				isSelect = false;
				break;
			case SelectState::Load:

				break;
			case SelectState::Exit:
				PostQuitMessage(0);
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
