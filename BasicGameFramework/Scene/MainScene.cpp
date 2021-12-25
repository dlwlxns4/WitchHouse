#include "MainScene.h"
#include "../stdafx.h"
#include "Layer.h"
#include "../Manager/PhysicsManager.h"
#include "../Manager/GameManager.h"
#include "../Manager/ImageManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/CameraManager.h"
#include "../Manager/QuestManager.h"
#include "../Manager/ItemManager.h"
#include "../Object/Player.h"
#include "../Object/UIObj.h"
#include "../Object/BackPanel.h"
#include "../Object/QuestObj.h"
#include "../Object/MovableObj.h"
#include "../Util/Timer.h"
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
		for (auto layer : *_layers)
		{
			delete layer;
		}

		(*_layers).clear();
		SceneManager::GetInstance()->SetNextScene(L"TilemapTool");
		PhysicsManager::GetInstance()->AllClear();
	}
	if (Input::GetButtonDown('A'))
	{
		Load(num++);
	}
	if (Input::GetButtonDown('S'))
	{
		Load(num--);
	}


	if (loadFlag == true)
	{
		loadFlag = false;
		GameObject* obj = PhysicsManager::GetInstance()->GetTriggerObj(nextSceneNum);
		PhysicsManager::GetInstance()->RemoveCollider(obj->GetPosition().x / 32, obj->GetPosition().y / 32);
		PhysicsManager::GetInstance()->RemoveCollider(obj->GetPosition().x / 32, obj->GetPosition().y / 32+1);
		Save(GameManager::GetInstance()->GetCurrScene());
		
		Load(nextSceneNum);
	}

	if (backPaenlActiveFlag == true)
	{
		backPanel->SetIsBright(false);
		backPanel->SetIsItemEffect(true);
		backPanel->SetOpaicty(0);
		backPaenlActiveFlag = false;
	}

}

void MainScene::Render(HDC hdc)
{
	Scene::Render(hdc);
	Debug();

}



void MainScene::DoTrap(int id)
{
	switch (id)
	{
	case 0:
	{
		GameObject* player = GameManager::GetInstance()->GetPlayer();
		player->GetComponent<PlayerMovement>()->SetActionStartegy(PlayerActionState::Null);
		QuestManager::GetInstance()->SetTrapAction(0);
		QuestManager::GetInstance()->SetTrapAction(1);
		break;
	}
	case 1:
		if (QuestManager::GetInstance()->GetQuest() == 14)
		{
			GameObject* player = GameManager::GetInstance()->GetPlayer();
			player->GetComponent<PlayerMovement>()->SetActionStartegy(PlayerActionState::Null);
			QuestManager::GetInstance()->SetTrapAction(2);
			QuestManager::GetInstance()->NextQuest();
		}
		break;
	case 2:
		if (QuestManager::GetInstance()->GetQuest() == 16)
		{
			GameObject* player = GameManager::GetInstance()->GetPlayer();
			player->GetComponent<PlayerMovement>()->SetActionStartegy(PlayerActionState::Null);
			QuestManager::GetInstance()->SetTrapAction(3);
			QuestManager::GetInstance()->NextQuest();
		}
		break;
	case 3:
		if (QuestManager::GetInstance()->GetQuest() == 18)
		{
			AstarTeddy* teddy = new AstarTeddy(this, (*_layers)[0], L"AStar");
			teddy->SetPosition(32 * 3, 32 * 5);
			teddy->Init();
			QuestManager::GetInstance()->NextQuest();
		}
		break;
	}
}

void MainScene::TransMap(int mapNum)
{
	loadFlag = true;
	nextSceneNum = mapNum;
	backPanel->SetActive(true);
}

void MainScene::Save(int saveIndex)
{
	string filePath = "Map/MapData" + to_string(saveIndex) + ".txt";

	ofstream writeFile(filePath.data());
	POINT pos = GameManager::GetInstance()->GetPlayer()->GetPosition();
	PhysicsManager::GetInstance()->RemoveCollider(pos.x / 32, pos.y / 32);

	if (writeFile.is_open())
	{
		writeFile << (*_layers).size() << endl;
		for (size_t i = 0; i < (*_layers).size(); ++i)
		{
			writeFile << (*((*_layers)[i])) << endl;
			writeFile << -1 << endl;
		}
		writeFile << *PhysicsManager::GetInstance();
	}


	cout << "세이브 완료" << endl;
	writeFile.close();
}

void MainScene::Load(int loadIndex)
{
	string filePath = "Map/MapData" + to_string(loadIndex) + ".txt";

	cout << filePath << endl;


	ifstream openFile(filePath.data());

	int maxLayer = 0;
	if (openFile.is_open())
	{
		PhysicsManager::GetInstance()->AllClear();
		CameraManager::GetInstance()->Clear();
		QuestManager::GetInstance()->Clear();
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

				if (QuestManager::GetInstance()->GetQuest() == 10)
				{
					player->GetComponent<PlayerMovement>()->SetActionStartegy(PlayerActionState::Null);
					player->GetComponent<PlayerSpriteRenderer>()->SetState(PlayerSpriteState::Init);
				}
				else
				{
					player->GetComponent<PlayerMovement>()->SetActionStartegy(PlayerActionState::Input);
					player->GetComponent<PlayerSpriteRenderer>()->SetState(PlayerSpriteState::Move);
				}
				ItemManager::GetInstance()->SetOwner(player);

				//POINT playerPos = GameManager::GetInstance()->GetPlayerPos();
				//player->SetPosition(playerPos);
			}

			openFile >> *((*_layers)[i]);
		}

		//UI
		UIObj* ui = new UIObj(this, (*_layers)[(*_layers).size() - 1], L"UI");
		ui->Init();
		GameManager::GetInstance()->SetUIObj(ui);

		//OpaityBackPanel
		backPanel = new BackPanel(this, (*_layers)[(*_layers).size() - 1], L"BackPanel");
		backPanel->Init();

		//콜라이더, 트리거, 포탈 재정의
		openFile >> *PhysicsManager::GetInstance();
	}





	if (isFirst && QuestManager::GetInstance()->GetQuest() == 10)
	{
		isFirst = false;
		GameManager::GetInstance()->SetPlayerPos({ 9 * 32, 9 * 32 });
	}

	else
	{
		int prevScene = GameManager::GetInstance()->GetCurrScene();
		POINT nextPlayerPos = GameManager::GetInstance()->GetPlayerData(prevScene, loadIndex);
		POINT nextCameraPos = GameManager::GetInstance()->GetCameraData(prevScene, loadIndex);
		CameraManager::GetInstance()->SetCameraPos({ nextCameraPos.x, nextCameraPos.y });
		GameManager::GetInstance()->SetPlayerPos({ nextPlayerPos.x * 32, nextPlayerPos.y * 32 });
		GameManager::GetInstance()->SetCurrScene(loadIndex);
	}


	openFile.close();

}

void MainScene::Debug()
{
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
				ImageManager::GetInstance()->DrawColliderRectBlue(it.first, itt.first, ((PortalObj*)((itt.second)))->GetMainId());
			}
		}
		unordered_map<int, unordered_map<int, int>>* item = PhysicsManager::GetInstance()->GetItemObj();
		for (auto it : *item)
		{
			for (auto itt : it.second)
			{
				ImageManager::GetInstance()->DrawColliderRectOrange(it.first, itt.first, itt.second);
			}
		}
		unordered_map<int, unordered_map<int, GameObject*>>* quest = QuestManager::GetInstance()->GetQuestObjMap();
		for (auto it : *quest)
		{
			for (auto itt : it.second)
			{
				ImageManager::GetInstance()->DrawColliderRectPurple(it.first, itt.first, ((QuestObj*)((itt.second)))->GetId());
			}
		}
		unordered_map<int, unordered_map<int, GameObject*>>* trapAction = QuestManager::GetInstance()->GetQuestActionObjMap();
		for (auto it : *trapAction)
		{
			for (auto itt : it.second)
			{
				ImageManager::GetInstance()->DrawColliderRectBrown(it.first, itt.first, (((TrapActionObj*)(itt.second)))->GetId());
			}
		}

	}


	if (Input::GetButtonDown('Q'))
	{
		QuestDebug = QuestDebug == true ? false : true;
	}

	if (Input::GetButtonDown('T'))
	{
		QuestManager::GetInstance()->NextQuest();
	}
	if (Input::GetButtonDown('W'))
	{
		isShowCollider = isShowCollider == true ? false : true;
	}
	if (isShowCollider)
	{
		unordered_set<pair<int, int>, pair_hash>* collision = PhysicsManager::GetInstance()->GetCollisionObj();
		for (auto pos : *collision)
		{
			ImageManager::GetInstance()->DrawColliderRect(pos.first, pos.second);
		}
	}

	if (QuestDebug)
	{
		unordered_map<int, unordered_map<int, int>>* item = PhysicsManager::GetInstance()->GetItemObj();
		for (auto it : *item)
		{
			for (auto itt : it.second)
			{
				ImageManager::GetInstance()->DrawColliderRectOrange(it.first, itt.first, itt.second);
			}
		}
	}
}

void MainScene::SetActiveBackPanelFlag(bool isActive)
{
	backPaenlActiveFlag = isActive;
}

