#include "TileSelectComponent.h"

#include "../Manager/ImageManager.h"
#include "../stdafx.h"

#include "../Util/Sprite.h"

#include "../Util/AboutTile.h"

#include "../Scene/Layer.h"


#include <iostream>

#include "SpriteRenderer.h"

#include <d2d1.h>


#include "TextComponent.h"


#include "../Component/ParallaxSpriteRenderer.h"
#include "../Manager/GameManager.h"
#include "../Manager/PhysicsManager.h"
#include "../Manager/CameraManager.h"

#include <fstream>
#include <istream>

#include "../Object/GameObject.h"
#include "../Object/ParallaxObj.h"
#include "../Object/Player.h"
#include "../Object/Text.h"
#include "../Object/UIObj.h"
#include "../Object/PortalObj.h"
#include "../Object/TileObj.h"
#include "../Object/TwinkleObj.h"
#include "../Object/AkariObj.h"
#include "../Object/QuestObj.h"
#include "../Object/TriggerObj.h"

TileSelectComponent::~TileSelectComponent()
{
	Release();
}


void TileSelectComponent::Update()
{
	if (Input::GetButtonDown('1'))
	{
		if (sampleIndex > 0)
		{
			sampleIndex--;
			sprite = ImageManager::GetInstance()->FindSprite(ImageManager::GetInstance()->GetSpriteName(sampleIndex).c_str());

			SetRect(&spriteRect,
				WIN_SIZE_X - sprite->GetWidth(),
				0,
				WIN_SIZE_X,
				sprite->GetHeight()
			);
		}
	}
	else if (Input::GetButtonDown('2'))
	{
		if (sampleIndex < ImageManager::GetInstance()->GetSpritesNameVecSize() - 1)
		{
			sampleIndex++;
			sprite = ImageManager::GetInstance()->FindSprite(ImageManager::GetInstance()->GetSpriteName(sampleIndex).c_str());

			SetRect(&spriteRect,
				WIN_SIZE_X - sprite->GetWidth(),
				0,
				WIN_SIZE_X,
				sprite->GetHeight()
			);
		}
	}

	if (Input::GetButtonDown('3'))
	{
		if ((int)tileType > 0)
		{
			int curType = (int)tileType;
			tileType = TileType(--curType);
			wstring txt = {};
			if ((int)tileType == 0)
			{
				txt = L"TileType : TileObj";
			}
			else if ((int)tileType == 1)
			{
				txt = L"TileType : PlayerObj";
			}
			else if ((int)tileType == 2)
			{
				txt = L"TileType : ParallaxObj";
			}
			else if ((int)tileType == 3)
			{
				txt = L"TileType : Collider";
			}
			else if ((int)tileType == 4)
			{
				txt = L"TileType : Trigger";
			}
			else if ((int)tileType == 5)
			{
				txt = L"TileType : Portal";
			}
			else if ((int)tileType == 6)
			{
				txt = L"TileType : Item";
			}
			else if ((int)tileType == 7)
			{
				txt = L"TileType : Twinkle";
			}
			else if ((int)tileType == 8)
			{
				txt = L"TileType : Akari";
			}
			else if ((int)tileType == 9)
			{
				txt = L"TileType : Quest";
			}
			else if ((int)tileType == 1)
			{
				txt = L"TileType : Door";
			}
			tileTypeTxt->GetComponent<TextComponent>()->SetText(txt);
		}
	}
	else if (Input::GetButtonDown('4'))
	{
		if ((int)tileType < 10)
		{
			int curType = (int)tileType;
			tileType = TileType(++curType);
			wstring txt = {};
			if ((int)tileType == 0)
			{
				txt = L"TileType : TileObj";
			}
			else if ((int)tileType == 1)
			{
				txt = L"TileType : PlayerObj";
			}
			else if ((int)tileType == 2)
			{
				txt = L"TileType : ParallaxObj";
			}
			else if ((int)tileType == 3)
			{
				txt = L"TileType : Collider";
			}
			else if ((int)tileType == 4)
			{
				txt = L"TileType : Trigger";
			}
			else if ((int)tileType == 5)
			{
				txt = L"TileType : Portal";
			}
			else if ((int)tileType == 6)
			{
				txt = L"TileType : Item";
			}
			else if ((int)tileType == 7)
			{
				txt = L"TileType : Twinkle";
			}
			else if ((int)tileType == 8)
			{
				txt = L"TileType : Akari";
			}
			else if ((int)tileType == 9)
			{
				txt = L"TileType : Quest";
			}
			else if ((int)tileType == 10)
			{
				txt = L"TileType : Door";
			}
			tileTypeTxt->GetComponent< TextComponent>()->SetText(txt);
		}
	}

	if (Input::GetButtonDown('E'))
	{
		if (currLayer > 1)
		{
			currLayer--;
			wstring txt = L"CurrLayer : " + to_wstring(currLayer) + L" MaxLayer : " + to_wstring(mapData.size());
			currLayerTxt->GetComponent< TextComponent>()->SetText(txt);

		}
	}
	else if (Input::GetButtonDown('R'))
	{
		if (currLayer < mapData.size())
		{
			currLayer++;
			wstring txt = L"CurrLayer : " + to_wstring(currLayer) + L" MaxLayer : " + to_wstring(mapData.size());
			currLayerTxt->GetComponent< TextComponent>()->SetText(txt);

		}
	}

	//-------------SampleImage
	mousePos = Input::GetMousePosition();
	if (PtInRect(&spriteRect, mousePos))
	{
		int mouseIndexX = (mousePos.x - spriteRect.left) / 32;
		int mouseIndexY = mousePos.y / 32;
		if (Input::GetButtonDown(VK_LBUTTON))
		{
			downPos = { (mousePos.x - spriteRect.left) / 32, mousePos.y / 32 };
		}
		if (Input::GetButtonUp(VK_LBUTTON))
		{
			upPos = { (mousePos.x - spriteRect.left) / 32, mousePos.y / 32 };

		}
	}
	//-----------------------------

	//--------------MainImage
	if (Input::GetButtonDown(VK_TAB))
	{
		currLayer = 1;
		wstring txt = L"CurrLayer : " + to_wstring(currLayer) + L" MaxLayer : " + to_wstring(mapData.size() + 1);
		currLayerTxt->GetComponent< TextComponent>()->SetText(txt);
		mapData.push_back(new Layer(L"layer" + to_wstring((int)mapData.size()), (int)mapData.size()));
	}

	POINT* cameraPos = CameraManager::GetInstance()->GetCameraPos();

	RECT mainArea = { 0,0,TILE_SIZE * MAP_SIZE_X, TILE_SIZE * MAP_SIZE_Y };
	if (PtInRect(&mainArea, mousePos))
	{
		int mouseIndexX = (mousePos.x - mainArea.left) / 32 + cameraPos->x / 32;
		int mouseIndexY = mousePos.y / 32 + cameraPos->y / 32;

		if (Input::GetButtonDown(VK_LBUTTON))
		{
			SetObject(mouseIndexX, mouseIndexY);

		}
		else if (Input::GetButton(VK_RBUTTON))
		{
			if (tileType == TileType::tileObj)
			{
				mapData[currLayer - 1]->RemoveObject(POINT{ mouseIndexX * TILE_SIZE, mouseIndexY * TILE_SIZE });
			}
			else if (tileType == TileType::Trigger)
			{
				PhysicsManager::GetInstance()->RemoveChat(mouseIndexX, mouseIndexY);
			}
			else if (tileType == TileType::Collider)
			{
				PhysicsManager::GetInstance()->RemoveCollider(mouseIndexX, mouseIndexY);
			}
		}
	}


	//MoveCamera
	if (Input::GetButton('W'))
	{
		cameraPos->y -= 32;
	}
	else if (Input::GetButton('S'))
	{
		cameraPos->y += 32;

	}
	else if (Input::GetButton('A'))
	{
		cameraPos->x -= 32;
	}
	else if (Input::GetButton('D'))
	{
		cameraPos->x += 32;
	}


	//Show Collider
	if (Input::GetButtonDown(VK_SPACE))
	{
		isShowCollider = isShowCollider == false ? true : false;
	}

	//맵 데이터 업데이트
	for (auto map : mapData)
	{
		map->Update();
	}


	//select TriggerTile
	if (Input::GetButtonDown('F'))
	{
		int mouseIndexX = (mousePos.x - mainArea.left) / 32 + cameraPos->x / 32;
		int mouseIndexY = mousePos.y / 32 + cameraPos->y / 32;
		PhysicsManager::GetInstance()->addId_1(mouseIndexX, mouseIndexY);
	}
	else if (Input::GetButtonDown('G'))
	{
		int mouseIndexX = (mousePos.x - mainArea.left) / 32 + cameraPos->x / 32;
		int mouseIndexY = mousePos.y / 32 + cameraPos->y / 32;
		PhysicsManager::GetInstance()->addId_10(mouseIndexX, mouseIndexY);
	}
	else if (Input::GetButtonDown('V'))
	{
		int mouseIndexX = (mousePos.x - mainArea.left) / 32 + cameraPos->x / 32;
		int mouseIndexY = mousePos.y / 32 + cameraPos->y / 32;
		PhysicsManager::GetInstance()->addId_100(mouseIndexX, mouseIndexY);
	}
	else if (Input::GetButtonDown('B'))
	{
		int mouseIndexX = (mousePos.x - mainArea.left) / 32 + cameraPos->x / 32;
		int mouseIndexY = mousePos.y / 32 + cameraPos->y / 32;
		PhysicsManager::GetInstance()->addId_1000(mouseIndexX, mouseIndexY);
	}

	if (Input::GetButtonDown('U'))
	{
		UIObj* chatPanel = new UIObj(mapData[mapData.size() - 1], L"UI");
		chatPanel->Init();
	}

	if (Input::GetButtonDown('K'))
	{
		Save();
	}
	if (Input::GetButtonDown('L'))
	{
		Load(num);
	}

	if (Input::GetButtonDown('Q'))
	{
		int mouseIndexX = (mousePos.x - mainArea.left) / 32 + cameraPos->x / 32;
		int mouseIndexY = mousePos.y / 32 + cameraPos->y / 32;
		PhysicsManager::GetInstance()->addPortalNum(mouseIndexX, mouseIndexY);
	}

	if (Input::GetButtonDown(VK_LSHIFT))
	{
		int mouseIndexX = (mousePos.x - mainArea.left) / 32 + cameraPos->x / 32;
		int mouseIndexY = mousePos.y / 32 + cameraPos->y / 32;
		QuestManager::GetInstance()->AddQuestId(mouseIndexX, mouseIndexY);
	}
}

void TileSelectComponent::Init()
{
	const wstring str = L"titleText";

	POINT* cameraPos = CameraManager::GetInstance()->GetCameraPos();
	cameraPos->x = 0;
	cameraPos->y = 0;

	tileTypeTxt = new Text(str);
	tileTypeTxt->SetPosition(20, TILE_SIZE * MAP_SIZE_Y);
	TextComponent* txtComponent = new TextComponent(tileTypeTxt, 1);
	txtComponent->SetText(L"TileType : tileObj");


	currLayerTxt = new Text(L"currLayerText");
	currLayerTxt->SetPosition(20, TILE_SIZE * (MAP_SIZE_Y + 1));
	TextComponent* txtComponent2 = new TextComponent(currLayerTxt, 1);
	txtComponent2->SetText(L"CurrLayer : -1 MaxLayer : -1");

	triggerPosTxt = new Text(L"SelectTriggerTile");
	triggerPosTxt->SetPosition(20, TILE_SIZE * (MAP_SIZE_Y + 2));
	TextComponent* txtComponent3 = new TextComponent(triggerPosTxt, 1);
	txtComponent3->SetText(L"SelectTriggerTile : x: -1 y: -1");
}

void TileSelectComponent::Render(HDC hdc)
{

	sprite->Render(
		WIN_SIZE_X - sprite->GetWidth(),
		0,
		0,
		0,
		(bool)true
	);

	sprite->Render(
		0,
		WIN_SIZE_Y - 128,
		downPos.first,
		downPos.second,
		upPos.first - downPos.first,
		upPos.second - downPos.second,
		true
	);

	for (auto map : mapData)
	{
		map->Render(hdc);
	}



	if (isShowCollider)
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
				ImageManager::GetInstance()->DrawColliderRectBlue(it.first, itt.first, ((TriggerObj*)((itt.second)))->GetNextMap());
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

	}

	tileTypeTxt->Render(hdc);
	currLayerTxt->Render(hdc);
	triggerPosTxt->Render(hdc);
}


void TileSelectComponent::SetObject(int mouseIndexX, int mouseIndexY)
{
	POINT* camera = (CameraManager::GetInstance()->GetCameraPos());


	if (tileType == TileType::tileObj)
	{
		if (mapData.size() != 0)
		{
			for (int i = downPos.first + (camera->x / TILE_SIZE); i <= upPos.first + (camera->x / TILE_SIZE); ++i)
			{
				for (int j = downPos.second + (camera->y / TILE_SIZE); j <= upPos.second + (camera->y / TILE_SIZE); ++j)
				{
					TileObj* tileObj = new TileObj(mapData[currLayer - 1], L"Tile");
					SpriteRenderer* spriteRenderer = new SpriteRenderer(tileObj, 1);
					spriteRenderer->SetSprite(sampleIndex, i - camera->x / 32, j - camera->y / 32);

					tileObj->SetPosition(
						(mouseIndexX + (i - downPos.first - camera->x / TILE_SIZE)) * TILE_SIZE,
						(mouseIndexY + (j - downPos.second - camera->y / TILE_SIZE)) * TILE_SIZE
					);
				}
			}
		}
	}
	else if (tileType == TileType::PlayerObj)
	{
		if (mapData.size() != 0)
		{
			Player* player = new Player(mapData[currLayer - 1], L"Player");
			player->Init();
			player->SetPosition(
				(mouseIndexX)*TILE_SIZE,
				(mouseIndexY)*TILE_SIZE
			);
			PhysicsManager::GetInstance()->SetCollision(mouseIndexX, mouseIndexY);
		}
	}
	else if (tileType == TileType::parallaxObj)
	{
		if (mapData.size() != 0)
		{
			ParallaxObj* parallaxObj = new ParallaxObj(mapData[currLayer - 1], L"Parallax");
			ParallaxSpriteRenderer* paralaxSpriteRenderer = new ParallaxSpriteRenderer(parallaxObj, 1);
			paralaxSpriteRenderer->SetSprite(L"Image/Parallax/001-Fog01.png");
		}
	}
	else if (tileType == TileType::Collider)
	{
		PhysicsManager::GetInstance()->SetCollision(mouseIndexX, mouseIndexY);
	}
	else if (tileType == TileType::Trigger)
	{
		PhysicsManager::GetInstance()->SetChat(mouseIndexX, mouseIndexY);
	}
	else if (tileType == TileType::Portal)
	{
		cout << "protal" << endl;
		PortalObj* portal = new PortalObj(mapData[mapData.size() - 1], L"Portal");
		PhysicsManager::GetInstance()->SetTriggerObj(mouseIndexX, mouseIndexY, portal);
	}
	else if (tileType == TileType::Item)
	{
		PhysicsManager::GetInstance()->SetItem(mouseIndexX, mouseIndexY);
	}
	else if (tileType == TileType::Twinkle)
	{
		TwinkleObj* twinkle = new TwinkleObj(mapData[currLayer - 1], L"Twinkle");
		twinkle->Init();
		twinkle->SetPosition((mouseIndexX)*TILE_SIZE, (mouseIndexY)*TILE_SIZE);
	}
	else if (tileType == TileType::Akari)
	{
		AkariObj* akari = new AkariObj(mapData[currLayer - 1], L"Akari");
		akari->Init();
		akari->SetPosition(mouseIndexX * TILE_SIZE, mouseIndexY * TILE_SIZE);
	}
	else if (tileType == TileType::Quest)
	{
		if (mapData.size() != 0)
		{
			for (int i = downPos.first + (camera->x / TILE_SIZE); i <= upPos.first + (camera->x / TILE_SIZE); ++i)
			{
				for (int j = downPos.second + (camera->y / TILE_SIZE); j <= upPos.second + (camera->y / TILE_SIZE); ++j)
				{
					QuestObj* quest = new QuestObj(mapData[currLayer - 1], L"Quest");
					quest->Init();
					quest->SetSprite(sampleIndex, i - camera->x / 32, j - camera->y / 32);

					int posX = (mouseIndexX + (i - downPos.first - camera->x / TILE_SIZE)) * TILE_SIZE;
					int posY = (mouseIndexY + (j - downPos.second - camera->y / TILE_SIZE)) * TILE_SIZE;

					quest->SetPosition(
						posX,
						posY
					);
				
					QuestManager::GetInstance()->SetQuestObj(posX/32, posY/32, quest);
				}
			}
		}
	}
	else if (tileType == TileType::Door)
	{
		DoorObj* door = new DoorObj(mapData[currLayer - 1], L"Door");
		door->Init();
		door->SetSpriteIndex(sampleIndex);
		door->SetPosition(mouseIndexX * TILE_SIZE, mouseIndexY * TILE_SIZE);
		
	}
}

void TileSelectComponent::Release()
{
	delete tileTypeTxt;

	delete currLayerTxt;

	delete triggerPosTxt;

	for (auto layer : mapData)
	{
		delete layer;
	}

}

void TileSelectComponent::Save(int saveIndex)
{
	string filePath = "Save/Tilemap/MapData" + to_string(saveIndex) + ".txt";

	ofstream writeFile(filePath.data());

	if (writeFile.is_open())
	{
		writeFile << mapData.size() << endl;
		for (size_t i = 0; i < mapData.size(); ++i)
		{
			writeFile << *(mapData[i]) << endl;
			writeFile << -1 << endl;
		}
		writeFile << *PhysicsManager::GetInstance();
	}


	cout << "세이브 완료" << endl;
	writeFile.close();
}

void TileSelectComponent::Load(int loadIndex)
{
	string filePath = "Save/Tilemap/MapData" + to_string(loadIndex) + ".txt";

	ifstream openFile(filePath.data());

	int maxLayer = 0;

	if (openFile.is_open())
	{
		PhysicsManager::GetInstance()->AllClear();
		openFile >> maxLayer;

		for (auto layer : mapData)
		{
			delete layer;
		}

		mapData.clear();
		mapData.reserve(maxLayer);

		currLayer = 1;

		for (int i = 0; i < maxLayer; ++i)
		{
			mapData.push_back(new Layer(L"layer" + to_wstring((int)mapData.size()), (int)mapData.size()));

			openFile >> *(mapData[i]);
		}

		openFile >> *PhysicsManager::GetInstance();
	}

	wstring txt = L"CurrLayer : " + to_wstring(currLayer) + L" MaxLayer : " + to_wstring(mapData.size());
	currLayerTxt->GetComponent< TextComponent>()->SetText(txt);
	cout << "Load완료" << endl;
	openFile.close();
}