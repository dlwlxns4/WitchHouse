#include "MainScene.h"
#include "../stdafx.h"
#include "Layer.h"
#include "../Manager/PhysicsManager.h"
#include "../Manager/GameManager.h"
#include "../Manager/ImageManager.h"
#include "../Object/Player.h"
#include "../Object/UIObj.h"
#include "../Object/BackPanel.h"
void MainScene::Init()
{
	
	_layers = this->GetLayer();
	Load(GameManager::GetInstance()->GetCurrScene());

	BackPanel* backPanel = new BackPanel(this, (*_layers)[(*_layers).size()-1], L"BackPanel");
	backPanel->Init();
}

void MainScene::Update()
{
	Scene::Update();
	if (Input::GetButtonDown(VK_SPACE))
	{
		isShowRect = isShowRect == false ? true : false;
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
		unordered_map<int, unordered_map<int, int>>* trigger = PhysicsManager::GetInstance()->GetTriggerObj();
		for (auto it : *trigger)
		{
			for (auto itt : it.second)
			{
				ImageManager::GetInstance()->DrawColliderRectRed(it.first, itt.first, itt.second);
			}
		}

	}
}

void MainScene::Save(int saveIndex)
{
}

void MainScene::Load(int loadIndex)
{
	string filePath = "Save/MapData" + to_string(loadIndex) + ".txt";

	ifstream openFile(filePath.data());

	int maxLayer = 0;
	if (openFile.is_open())
	{
		openFile >> maxLayer;

		for (auto layer : *_layers)
		{
			delete layer;
		}

		(*_layers).clear();
		(*_layers).clear();
		(*_layers).reserve(maxLayer);


		for (int i = 0; i < maxLayer; ++i)
		{
			(*_layers).push_back(new Layer(L"layer" + to_wstring((int)(*_layers).size()), (int)(*_layers).size()));

			//플레이어 생성
			if (i == 2)
			{
				Player* player = new Player(this, (*_layers)[i], L"Player");
				player->Init();
				GameManager::GetInstance()->SetPlayer(player);

				POINT playerPos = GameManager::GetInstance()->GetPlayerPos();
				player->SetPosition(playerPos);
			}
			openFile >> *((*_layers)[i]);
		}
		UIObj* ui = new UIObj(this,(*_layers)[(*_layers).size() - 1], L"UI");
		ui->Init();
	}
	openFile >> *PhysicsManager::GetInstance();


	cout << "Load완료" << endl;
	openFile.close();
}
