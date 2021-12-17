#include "MainScene.h"
#include "../stdafx.h"
#include "Layer.h"
#include "../Manager/PhysicsManager.h"
#include "../Manager/GameManager.h"
#include "../Manager/ImageManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/CameraManager.h"
#include "../Object/Player.h"
#include "../Object/UIObj.h"
#include "../Object/BackPanel.h"
#define MAP1_CAMERA_X -96
#define MAP1_CAMERA_Y 96


void MainScene::Init()
{

	_layers = this->GetLayer();
	Load(GameManager::GetInstance()->GetCurrScene());

	BackPanel* backPanel = new BackPanel(this, (*_layers)[(*_layers).size() - 1], L"BackPanel");
	backPanel->Init();
}

void MainScene::Update()
{
	Scene::Update();
	if (Input::GetButtonDown(VK_SPACE))
	{
		isShowRect = isShowRect == false ? true : false;
	}

	if (Input::GetButtonDown('O'))
	{
		SceneManager::GetInstance()->SetNextScene(L"TilemapTool");
	}
	if (Input::GetButtonDown('A'))
	{
		Load(num++);
	}



		if (loadFlag == true)
		{
			loadFlag = false;
			Load(nextSceneNum);
		}
	
}

void MainScene::Render(HDC hdc)
{
	Scene::Render(hdc);

	if (isShowRect)
	{
		unordered_set<pair<int, int>, pair_hash>* collision = PhysicsManager::GetInstance()->GetCollisionObj();
		for (auto pos : *collision)
		{
			ImageManager::GetInstance()->DrawColliderRect(pos.first, pos.second);
		}
		unordered_map<int, unordered_map<int, int>>* chat = PhysicsManager::GetInstance()->GetChatObjs();
		for (auto it : *chat)
		{
			for (auto itt : it.second)
			{
				ImageManager::GetInstance()->DrawColliderRectRed(it.first, itt.first, itt.second);
			}
		}
		unordered_map<int, unordered_map<int, GameObject*>>* trigger = PhysicsManager::GetInstance()->GetTriggerObjs();
		for (auto it : *trigger)
		{
			for (auto itt : it.second)
			{
				ImageManager::GetInstance()->DrawColliderRectBlue(it.first, itt.first, ((PortalObj*)((itt.second)))->GetNextMap());
			}
		}

	}
}



void MainScene::TransMap(int mapNum)
{
	//Load(mapNum);
	loadFlag = true;
	nextSceneNum = mapNum;
	backPanel->SetActive(true);
}

void MainScene::Save(int saveIndex)
{
}

void MainScene::Load(int loadIndex)
{
	string filePath = "Save/MapData" + to_string(loadIndex) + ".txt";

	cout << filePath << endl;


	ifstream openFile(filePath.data());

	int maxLayer = 0;
	if (openFile.is_open())
	{
		PhysicsManager::GetInstance()->AllClear();
		CameraManager::GetInstance()->Clear();
		cout << " 열림" << endl;
		openFile >> maxLayer;


		for (auto layer : *_layers)
		{
			delete layer;
		}

		(*_layers).clear();
		(*_layers).reserve(maxLayer);


		for (int i = 0; i < maxLayer; ++i)
		{
			(*_layers).push_back(new Layer(L"layer" + to_wstring((int)(*_layers).size()), (int)(*_layers).size()));

			//플레이어 생성
			if (i == 2)
			{
				Player* player = new Player(this, (*_layers)[2], L"Player");
				player->Init();
				GameManager::GetInstance()->SetPlayer(player);

				if (QuestManager::GetInstance()->GetQuest() == 0)
				{
					player->GetComponent<PlayerMovement>()->SetActionStartegy(PlayerActionState::Null);
					player->GetComponent<PlayerSpriteRenderer>()->SetState(PlayerSpriteState::Init);
				}
				else
				{
					player->GetComponent<PlayerMovement>()->SetActionStartegy(PlayerActionState::Input);
					player->GetComponent<PlayerSpriteRenderer>()->SetState(PlayerSpriteState::Move);
				}

				POINT playerPos = GameManager::GetInstance()->GetPlayerPos();
				player->SetPosition(playerPos);
			}

			openFile >> *((*_layers)[i]);
		}

		//UI
		UIObj* ui = new UIObj(this, (*_layers)[(*_layers).size() - 1], L"UI");
		ui->Init();

		//OpaityBackPanel
		backPanel = new BackPanel(this, (*_layers)[(*_layers).size() - 1], L"BackPanel");
		backPanel->Init();

		//콜라이더, 트리거, 포탈 재정의
		openFile >> *PhysicsManager::GetInstance(); 
	}



	


	if (isFirst && QuestManager::GetInstance()->GetQuest() == 0)
	{
		isFirst = false;
		GameManager::GetInstance()->SetPlayerPos({ 9 * 32, 9 * 32 });
	}
	else
	{
		POINT nextPlayerPos = GameManager::GetInstance()->GetPlayerData(loadIndex);
		POINT nextCameraPos = GameManager::GetInstance()->GetCameraData(loadIndex);
		CameraManager::GetInstance()->SetCameraPos({ nextCameraPos.x, nextCameraPos.y });
		GameManager::GetInstance()->SetPlayerPos({ nextPlayerPos.x * 32, nextPlayerPos.y * 32 });
	}

	openFile.close();

}
