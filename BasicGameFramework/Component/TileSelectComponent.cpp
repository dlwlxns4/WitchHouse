#include "TileSelectComponent.h"

#include "../Manager/ImageManager.h"
#include "../stdafx.h"

#include "../Util/Sprite.h"
#include "../Object/GameObject.h"

#include "../Util/AboutTile.h"

#include "../Scene/Layer.h"

#define WIN_SIZE_X 1440
#define WIN_SIZE_Y 720

#include <iostream>

#include "../Object/TileObj.h"
#include "SpriteRenderer.h"

#include <d2d1.h>


#include "../Object/Text.h"
#include "TextComponent.h"

#include "../Object/Player.h"

#include "../Manager/GameManager.h"

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
			tileTypeTxt->GetComponent<TextComponent>()->SetText(txt);
		}
	}
	else if (Input::GetButtonDown('4'))
	{
		if ((int)tileType < 1)
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
		if (currLayer < mapData.size() )
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
		mapData.push_back(new Layer(L"layer" + to_wstring(mapData.size()), mapData.size()));
	}


	RECT mainArea = { 0,0,TILE_SIZE * MAP_SIZE_X, TILE_SIZE * MAP_SIZE_Y };
	if (PtInRect(&mainArea, mousePos))
	{
		int mouseIndexX = (mousePos.x - mainArea.left) / 32;
		int mouseIndexY = mousePos.y / 32;

		if (Input::GetButtonDown(VK_LBUTTON))
		{

			SetObject(mouseIndexX, mouseIndexY);
			
		}
		else if (Input::GetButton(VK_RBUTTON))
		{
			mapData[currLayer - 1]->RemoveObject(L"Tile");
			
		}
	}
	for (auto map : mapData)
	{
		map->Update();
	}

}

void TileSelectComponent::Init()
{

	tileTypeTxt = new Text(L"tileText");
	tileTypeTxt->SetPosition(20, TILE_SIZE * MAP_SIZE_Y);
	TextComponent* txtComponent = new TextComponent(tileTypeTxt, 1);
	txtComponent->SetText(L"TileType : tileObj");
	tileTypeTxt->AddComponent(txtComponent);

	currLayerTxt = new Text(L"currLayerText");
	currLayerTxt->SetPosition(20, TILE_SIZE * (MAP_SIZE_Y + 1));
	TextComponent* txtComponent2 = new TextComponent(currLayerTxt, 1);
	txtComponent2->SetText(L"CurrLayer : -1 MaxLayer : -1");
	currLayerTxt->AddComponent(txtComponent2);
}

void TileSelectComponent::Render(HDC hdc)
{
	sprite->Render(
		WIN_SIZE_X - sprite->GetWidth() + 16,
		16,
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

	tileTypeTxt->Render(hdc);
	currLayerTxt->Render(hdc);

}

void TileSelectComponent::SetObject(int mouseIndexX, int mouseIndexY)
{
	POINTFLOAT* camera = (GameManager::GetInstance()->GetCameraPos());


	if (tileType == TileType::tileObj)
	{
		if (mapData.size() != 0)
		{
			for (int i = downPos.first+camera->x; i <= upPos.first+ camera->x; ++i)
			{
				for (int j = downPos.second+ camera->y; j <= upPos.second+ camera->y; ++j)
				{
					TileObj* tileObj = new TileObj(mapData[currLayer - 1], L"Tile");
					SpriteRenderer* spriteRenderer = new SpriteRenderer(tileObj, 1);
					spriteRenderer->SetSprite(ImageManager::GetInstance()->GetSpriteName(sampleIndex).c_str(), i, j);
					tileObj->SetPosition((mouseIndexX + (i - downPos.first)) * TILE_SIZE, (mouseIndexY + (j - downPos.second)) * TILE_SIZE);

				}
			}
		}
	}
	else if (tileType == TileType::parallaxObj)
	{
		if (mapData.size() != 0)
		{
			cout << mouseIndexX << " " << mouseIndexY << endl;
			Player* player = new Player(mapData[currLayer-1], L"Player");
			player->Init();
			player->SetPosition((mouseIndexX + camera->x) * TILE_SIZE, (mouseIndexY+ camera->y) * TILE_SIZE);
		}
	}
}
