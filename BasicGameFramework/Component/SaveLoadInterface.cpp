#include "SaveLoadInterface.h"
#include "../Manager/ImageManager.h"
#include "../Manager/GameManager.h"
#include "../Manager/QuestManager.h"
#include "../Manager/ItemManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/CameraManager.h"
#include "../Manager/SoundManager.h"

#include "../Scene/MainScene.h"

#include "../Util/Sprite.h"
#include "../Util/Input.h"
#include "../Component/UserInfoComponent.h"
#include "../Component/Player/PlayerAction.h"

#include "../Object/GameObject.h"
#include "../Scene/Layer.h"
#include "../Util/Timer.h"

#include <d2d1.h>
#include <dwrite.h>
void SaveLoadInterface::SetSprite(const wchar_t* infoName, const wchar_t* PanelName)
{
	saveLoadInfo = ImageManager::GetInstance()->FindSprite(infoName);
	for (int i = 0; i < 4; ++i)
	{
		saveLoadPanel[i] = ImageManager::GetInstance()->FindSprite(PanelName);
	}
	selectPanel = ImageManager::GetInstance()->FindSprite(L"Image/UI/SelectPanel_04.png");
	portrait = ImageManager::GetInstance()->FindSprite(L"Image/UI/SaveLoadPortrait.png");
}

void SaveLoadInterface::Update()
{
	delay += Timer::GetDeltaTime();
	if (delay >= 50.0f)
	{
		if (Input::GetButtonDown('X'))
		{
			if (isSave)
			{
				this->SetActive(false);
				GameManager::GetInstance()->SetState(State::None);
				GameManager::GetInstance()->GetPlayer()->GetComponent<PlayerMovement>()->SetActive(true);
				GameManager::GetInstance()->GetPlayer()->GetComponent<PlayerAction>()->SetActive(true);
			}
			else
			{
				this->SetActive(false);
				isSave = true;
				_owner->GetComponent<UserInfoComponent>()->SetActive(true);
			}

			SoundManager::GetInstance()->startInfSound(L"Click");
			delay = 0;
		}

		if (Input::GetButtonDown('Z'))
		{
			if (isSave)
			{
				Save(currSelect);
			}
			else
			{
				Load(currSelect);
			}
			SoundManager::GetInstance()->startInfSound(L"Save");
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

		if (Input::GetButtonDown(VK_UP))
		{
			if (currSelect > 0)
				currSelect--;

			SoundManager::GetInstance()->startInfSound(L"Cursor");
		}
		else if (Input::GetButtonDown(VK_DOWN))
		{
			if (currSelect < 3)
				currSelect++;

			SoundManager::GetInstance()->startInfSound(L"Cursor");
		}
	}
}

void SaveLoadInterface::Render(HDC hdc)
{
	saveLoadInfo->Render(0, 0, 1);
	for (int i = 0; i < 4; ++i)
	{
		saveLoadPanel[i]->Render(0, 60 + (30 * 3) * i, 1);
		wstring str = L"파일" + to_wstring(i + 1);
		ImageManager::GetInstance()->GetRenderTarget()->DrawTextW(
			str.c_str(), str.size(),
			ImageManager::GetInstance()->GetTextFormat(),
			D2D1::RectF(20, 85 + 22 + (30 * 3) * i, 544, 85 + (30 * 3) * i),
			ImageManager::GetInstance()->GetBrushWhite()
		);
	}

	if (isSave == false)
	{
		wstring str = L"로드할 파일을 선택해주세요.";
		ImageManager::GetInstance()->GetRenderTarget()->DrawTextW(
			str.c_str(), str.size(),
			ImageManager::GetInstance()->GetTextFormat(),
			D2D1::RectF(20, 22, 544, 64),
			ImageManager::GetInstance()->GetBrushWhite()
		);
	}
	else
	{
		wstring str = L"세이브할 파일을 선택해주세요.";
		ImageManager::GetInstance()->GetRenderTarget()->DrawTextW(
			str.c_str(), str.size(),
			ImageManager::GetInstance()->GetTextFormat(),
			D2D1::RectF(20, 22, 544, 64),
			ImageManager::GetInstance()->GetBrushWhite()
		);
	}


	for (int i = 0; i < 4; ++i)
	{
		string path = "Save/Data/" + to_string(i + 1) + "/info.txt";
		ifstream read;
		read.open(path);
		int currScene;
		read >> currScene;

		wstring currSceneName;
		switch (currScene)
		{
		case 0:
			currSceneName = L"마녀의 숲";
			break;
		case 2:
			currSceneName = L"마녀의 정원";
		}
		if (read)
		{
			portrait->Render(120, 69 + (30 * 3) * i, 1.0f);
			ImageManager::GetInstance()->GetRenderTarget()->DrawTextW(
				currSceneName.c_str(), currSceneName.size(),
				ImageManager::GetInstance()->GetTextFormat(),
				D2D1::RectF(400, 80 + (30 * 3) * i, 544, 80 + (30 * 3) * i),
				ImageManager::GetInstance()->GetBrushWhite()
			);
		}

	}

	selectPanel->Render(18, 77 + (30 * 3) * currSelect, selectPanelOpacity);
}

void SaveLoadInterface::Save(int currSelect)
{
	string filePath = "Map/MapData" + to_string(GameManager::GetInstance()->GetCurrScene()) + ".txt";

	ofstream writeFile2(filePath.data());

	vector<Layer*> mapData = *((MainScene*)(SceneManager::GetInstance()->GetCurrentScene()))->GetMapData();

	if (writeFile2.is_open())
	{
		writeFile2 << mapData.size() << endl;
		for (size_t i = 0; i < mapData.size(); ++i)
		{
			writeFile2 << *(mapData[i]) << endl;
			writeFile2 << -1 << endl;
		}
		writeFile2 << *PhysicsManager::GetInstance();
	}


	cout << "세이브 완료" << endl;
	writeFile2.close();


	for (int i = 0; i <= 9; ++i)
	{
		wstring loadPath = L"Map/MapData" + to_wstring(i) + L".txt";
		wstring savePath = L"Save/Data/" + to_wstring(currSelect + 1) + L"/MapData" + to_wstring(i) + L".txt";
		CopyFile(
			loadPath.c_str(),
			savePath.c_str(),
			false);
	}

	filePath = "Save/Data/" + to_string(currSelect + 1) + "/info.txt";

	ofstream writeFile(filePath.data());

	if (writeFile.is_open())
	{
		writeFile << *GameManager::GetInstance();
		writeFile << *QuestManager::GetInstance();
		writeFile << *CameraManager::GetInstance();
		writeFile << *ItemManager::GetInstance();
	}


	cout << "세이브 완료" << endl;
	writeFile.close();
}


void SaveLoadInterface::Load(int currSelect)
{
	ItemManager::GetInstance()->Clear();
	ItemManager::GetInstance()->LoadInit();
	for (int i = 0; i <= 9; ++i)
	{
		wstring loadPath = L"Save/Data/" + to_wstring(currSelect + 1) + L"/MapData" + to_wstring(i) + L".txt";
		wstring savePath = L"Map/MapData" + to_wstring(i) + L".txt";
		CopyFile(
			loadPath.c_str(),
			savePath.c_str(),
			false);
	}

	string filePath = "Save/Data/" + to_string(currSelect + 1) + "/info.txt";

	ifstream readFile(filePath.data());

	if (readFile.is_open())
	{
		readFile >> *GameManager::GetInstance();
		readFile >> *QuestManager::GetInstance();
		readFile >> *CameraManager::GetInstance();
		readFile >> *ItemManager::GetInstance();
	}

	MainScene* scene = ((MainScene*)(SceneManager::GetInstance()->GetCurrentScene()));

	GameManager::GetInstance()->SetState(State::None);
	scene->DataLoad(GameManager::GetInstance()->GetCurrScene());
	cout << "로드 완료" << endl;
	readFile.close();
}