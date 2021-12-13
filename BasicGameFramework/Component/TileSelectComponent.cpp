#include "TileSelectComponent.h"

#include "../Manager/ImageManager.h"
#include "../stdafx.h"

#include "../Util/Sprite.h"
#include "../Object/GameObject.h"

#include "../Util/AboutTile.h"

#include "../Scene/Layer.h"


#include <iostream>

#include "../Object/TileObj.h"
#include "SpriteRenderer.h"

#include <d2d1.h>


#include "../Object/Text.h"
#include "TextComponent.h"

#include "../Object/Player.h"

#include "../Manager/GameManager.h"
#include "../Component/ParallaxSpriteRenderer.h"
#include "../Object/ParallaxObj.h"
#include "../Manager/PhysicsManager.h"


#include "../Object/ChatPanel.h"

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
			tileTypeTxt->GetComponent<TextComponent>()->SetText(txt);
		}
	}
	else if (Input::GetButtonDown('4'))
	{
		if ((int)tileType < 4)
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

	POINTFLOAT* cameraPos = GameManager::GetInstance()->GetCameraPos();

	RECT mainArea = { 0,0,TILE_SIZE * MAP_SIZE_X, TILE_SIZE * MAP_SIZE_Y };
	if (PtInRect(&mainArea, mousePos))
	{
		int mouseIndexX = (mousePos.x - mainArea.left) / 32 + (int)cameraPos->x;
		int mouseIndexY = mousePos.y / 32 + (int)cameraPos->y;

		if (Input::GetButtonDown(VK_LBUTTON))
		{
			SetObject(mouseIndexX, mouseIndexY);

		}
		else if (Input::GetButton(VK_RBUTTON))
		{
			if (tileType == TileType::Trigger)
			{
				PhysicsManager::GetInstance()->RemoveTrigger(mouseIndexX, mouseIndexY);
			}
		}
	}


	//MoveCamera
	if (Input::GetButton('W'))
	{
		cameraPos->y--;
	}
	else if (Input::GetButton('S'))
	{
		cameraPos->y++;

	}
	else if (Input::GetButton('A'))
	{
		cameraPos->x--;
	}
	else if (Input::GetButton('D'))
	{
		cameraPos->x++;
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
		int mouseIndexX = (mousePos.x - mainArea.left) / 32 + (int)cameraPos->x;
		int mouseIndexY = mousePos.y / 32 + (int)cameraPos->y;
		PhysicsManager::GetInstance()->addId_1(mouseIndexX, mouseIndexY);
	}
	else if (Input::GetButtonDown('G'))
	{
		int mouseIndexX = (mousePos.x - mainArea.left) / 32 + (int)cameraPos->x;
		int mouseIndexY = mousePos.y / 32 + (int)cameraPos->y;
		PhysicsManager::GetInstance()->addId_10(mouseIndexX, mouseIndexY);
	}
	else if (Input::GetButtonDown('V'))
	{
		int mouseIndexX = (mousePos.x - mainArea.left) / 32 + (int)cameraPos->x;
		int mouseIndexY = mousePos.y / 32 + (int)cameraPos->y;
		PhysicsManager::GetInstance()->addId_100(mouseIndexX, mouseIndexY);
	}
	else if (Input::GetButtonDown('B'))
	{
		int mouseIndexX = (mousePos.x - mainArea.left) / 32 + (int)cameraPos->x;
		int mouseIndexY = mousePos.y / 32 + (int)cameraPos->y;
		PhysicsManager::GetInstance()->addId_1000(mouseIndexX, mouseIndexY);
	}

	if (Input::GetButtonDown('U'))
	{
		ChatPanel* chatPanel = new ChatPanel(mapData[mapData.size()-1], L"UI");
		chatPanel->Init();
	}
}

void TileSelectComponent::Init()
{
	const wstring str = L"titleText";


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
		true
	);

	sprite->Render(
		0,
		WIN_SIZE_Y - 96,
		downPos.first,
		downPos.second,
		upPos.first - downPos.first,
		upPos.second - downPos.second
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
		unordered_map<int, unordered_map<int, int>>* trigger = PhysicsManager::GetInstance()->GetTriggerObj();
		for (auto it : *trigger)
		{
			for (auto itt : it.second)
			{	
				ImageManager::GetInstance()->DrawColliderRectRed(it.first, itt.first, itt.second);
			}
		}

	}

	tileTypeTxt->Render(hdc);
	currLayerTxt->Render(hdc);
	triggerPosTxt->Render(hdc);
}

void TileSelectComponent::SetObject(int mouseIndexX, int mouseIndexY)
{
	POINTFLOAT* camera = (GameManager::GetInstance()->GetCameraPos());


	if (tileType == TileType::tileObj)
	{
		if (mapData.size() != 0)
		{
			for (int i = downPos.first + camera->x; i <= upPos.first + camera->x; ++i)
			{
				for (int j = downPos.second + camera->y; j <= upPos.second + camera->y; ++j)
				{
					TileObj* tileObj = new TileObj(mapData[currLayer - 1], L"Tile");
					SpriteRenderer* spriteRenderer = new SpriteRenderer(tileObj, 1);
					spriteRenderer->SetSprite(ImageManager::GetInstance()->GetSpriteName(sampleIndex).c_str(), i - camera->x, j - camera->y);
					tileObj->SetPosition(
						(mouseIndexX + (i - downPos.first - camera->x)) * TILE_SIZE,
						(mouseIndexY + (j - downPos.second - camera->y)) * TILE_SIZE
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
		PhysicsManager::GetInstance()->SetTrigger(mouseIndexX, mouseIndexY);
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
