#include "UserInfoComponent.h"

#include "../Manager/ImageManager.h"
#include "../Manager/GameManager.h"
#include "../Util/Sprite.h"
#include "../Util/AboutTile.h"

#include "../Component/InvenComponent.h"
#include "../Component/SaveLoadInterface.h"

#include "../Object/GameObject.h"


#include <d2d1.h>
#include <dwrite.h>

#define PORTRAIT_SIZE 96

#define PORTRAIT_START_POSX 188
#define PORTRAIT_START_POSY 304
#define STR_HEALTH_POSX 380
#define STR_HEALTH_POSY 346  

#define STR_NAME_POSX 280
#define STR_NAME_POSY 322  

#define STR_INVENTORY_POSX 40
#define STR_INVENTORY_POSY 324
#define STR_LOAD_POSY 356

#define STR_AGE_POSX 280
#define STR_AGE_13_POSX 324
#define STR_AGE_POSY 358	

#define STR_HEALTH_POSX 380
#define STR_HEALTH_POSY 346  
#define HELTHBAR_POSY 370

#define STR_HP_POSX 454
#define STR_HP_POSY 346

#define HELTHBAR_POSX 384
#define HELTHBAR_POSY 375
void UserInfoComponent::Update()
{
	if (Input::GetButtonDown('X'))
	{
		if (GameManager::GetInstance()->GetState() == State::None)
		{
			isShow = true;
			GameManager::GetInstance()->SetState(State::UserInfo);
		}
		else if (GameManager::GetInstance()->GetState() == State::UserInfo && isShow)
		{
			GameManager::GetInstance()->SetState(State::None);
			isShow = false;
			panelOpacity = 0;
		}

	}
	if (GameManager::GetInstance()->GetState() == State::UserInfo && panelOpacity<1.0f && isShow)
	{
		panelOpacity += 0.1f;
	}

	if(GameManager::GetInstance()->GetState() == State::UserInfo && isShow)
	{
		if (Input::GetButtonDown(VK_DOWN))
		{
			if (selectState == SelectUI::Inven)
			{
				selectState = SelectUI::Load;
			}
		}
		if (Input::GetButtonDown(VK_UP))
		{
			if (selectState == SelectUI::Load)
			{
				selectState = SelectUI::Inven;
			}
		}

		if (Input::GetButtonDown('Z'))
		{
			if (selectState == SelectUI::Inven)
			{
				_owner->GetComponent<InvenComponent>()->SetActive(true);
				this->SetActive(false);
			}
			else if (selectState == SelectUI::Load)
			{
				_owner->GetComponent<SaveLoadInterface>()->SetActive(true);
				_owner->GetComponent<SaveLoadInterface>()->SetIsSave(false);
				this->SetActive(false);
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
	}
}

void UserInfoComponent::Render(HDC hdc)
{
	if (GameManager::GetInstance()->GetState() == State::UserInfo && isShow)
	{
		opacityPanel->LoopRender(0, 0, 0, 0.1f);

		leftPanel->Render(_owner->GetPosition().x,
			_owner->GetPosition().y - TILE_SIZE * 2, panelOpacity);

		rightPanel->Render(_owner->GetPosition().x + TILE_SIZE*5 +TILE_SIZE/2,
			_owner->GetPosition().y-TILE_SIZE*2, panelOpacity);

		portrait->Render(PORTRAIT_START_POSX, PORTRAIT_START_POSY, panelOpacity,0,0,4,2);

		healthBar->Render(HELTHBAR_POSX, HELTHBAR_POSY, panelOpacity);

		selectPanel->Render(38, 319 + (int)selectState * 32, selectPanelOpacity);

		PrintText();
	}
}

void UserInfoComponent::SetSprite(const wchar_t* leftfileName, const wchar_t* rightFileName)
{
	leftPanel = ImageManager::GetInstance()->FindSprite(leftfileName);
	rightPanel = ImageManager::GetInstance()->FindSprite(rightFileName);
	portrait = ImageManager::GetInstance()->FindSprite(L"Image/UI/viviface.png");
	healthBar = ImageManager::GetInstance()->FindSprite(L"Image/UI/HealthBar.png");
	opacityPanel = ImageManager::GetInstance()->FindSprite(L"Image/UI/OpacityPanel.png");
	selectPanel = ImageManager::GetInstance()->FindSprite(L"Image/UI/SelectPanel_01.png");
}

void UserInfoComponent::SetIsShow(bool isShow)
{
	this->isShow = isShow;

}


void UserInfoComponent::PrintText()
{
	wstring printStr = L"소지품";
	ImageManager::GetInstance()->GetRenderTarget()->DrawTextW(
		printStr.c_str(), printStr.size(),
		ImageManager::GetInstance()->GetTextFormat(),
		D2D1::RectF(STR_INVENTORY_POSX, STR_INVENTORY_POSY, STR_INVENTORY_POSX+100, STR_INVENTORY_POSY+TILE_SIZE),
		ImageManager::GetInstance()->GetBrushWhite()
	);

	printStr = L"로드";
	ImageManager::GetInstance()->GetRenderTarget()->DrawTextW(
		printStr.c_str(), printStr.size(),
		ImageManager::GetInstance()->GetTextFormat(),
		D2D1::RectF(STR_INVENTORY_POSX, STR_LOAD_POSY, STR_INVENTORY_POSX + 100, STR_LOAD_POSY + TILE_SIZE),
		ImageManager::GetInstance()->GetBrushWhite()
	);

	printStr = L"비올라";
	ImageManager::GetInstance()->GetRenderTarget()->DrawTextW(
		printStr.c_str(), printStr.size(),
		ImageManager::GetInstance()->GetTextFormat(),
		D2D1::RectF(STR_NAME_POSX+10, STR_INVENTORY_POSY, STR_NAME_POSX + 100, STR_INVENTORY_POSY + TILE_SIZE),
		ImageManager::GetInstance()->GetBrushWhite()
	);

	printStr = L"나이";
	ImageManager::GetInstance()->GetRenderTarget()->DrawTextW(
		printStr.c_str(), printStr.size(),
		ImageManager::GetInstance()->GetTextFormat(),
		D2D1::RectF(STR_NAME_POSX+10, STR_LOAD_POSY, STR_NAME_POSX + 100, STR_LOAD_POSY + TILE_SIZE),
		ImageManager::GetInstance()->GetBrushBlue()
	);

	printStr = L"13";
	ImageManager::GetInstance()->GetRenderTarget()->DrawTextW(
		printStr.c_str(), printStr.size(),
		ImageManager::GetInstance()->GetTextFormat(),
		D2D1::RectF(STR_NAME_POSX + 50, STR_LOAD_POSY, STR_NAME_POSX + 100, STR_LOAD_POSY + TILE_SIZE),
		ImageManager::GetInstance()->GetBrushWhite()
	);

	printStr = L"체력";
	ImageManager::GetInstance()->GetRenderTarget()->DrawTextW(
		printStr.c_str(), printStr.size(),
		ImageManager::GetInstance()->GetTextFormat(),
		D2D1::RectF(STR_HEALTH_POSX, STR_LOAD_POSY, STR_HEALTH_POSX + 100, STR_LOAD_POSY + TILE_SIZE),
		ImageManager::GetInstance()->GetBrushBlue()
	);

	printStr = L"10/  10";
	ImageManager::GetInstance()->GetRenderTarget()->DrawTextW(
		printStr.c_str(), printStr.size(),
		ImageManager::GetInstance()->GetTextFormat(),
		D2D1::RectF(STR_HP_POSX, STR_LOAD_POSY, STR_HP_POSX + 100, STR_LOAD_POSY + TILE_SIZE),
		ImageManager::GetInstance()->GetBrushWhite()
	);
}