#include "InvenComponent.h"

#include "../Manager/ItemManager.h"
#include "../Manager/ImageManager.h"
#include "../Manager/GameManager.h"
#include "../Util/Sprite.h"
#include "../Util/AboutTile.h"

#include "../Object/GameObject.h"
#include "../Component/UserInfoComponent.h"

#include <d2d1.h>
#include <dwrite.h>

void InvenComponent::Update()
{
	if (Input::GetButtonDown('X'))
	{
		SetActive(false);
		_owner->GetComponent<UserInfoComponent>()->SetActive(true);
		panelOpacity = 0;
	}
	else if (Input::GetButtonDown('Z'))
	{
		ItemManager::GetInstance()->UseItem(selectInvenItem);
	}

	if (panelOpacity <= 1)
	{
		panelOpacity += 0.1f;
	}

	if (Input::GetButtonDown(VK_LEFT))
	{
		if (selectInvenItem  > 0)
		{
			selectInvenItem--;
		}
	}
	else if (Input::GetButtonDown(VK_RIGHT))
	{
		if (selectInvenItem < ItemManager::GetInstance()->GetInventorySize()-1)
		{
			selectInvenItem++;
		}
	}
	else if (Input::GetButtonDown(VK_UP))
	{
		if (selectInvenItem - 2 > 0)
		{
			selectInvenItem -= 2;
		}
	}
	else if (Input::GetButtonDown(VK_DOWN))
	{
		if (selectInvenItem + 2 < ItemManager::GetInstance()->GetInventorySize()-1)
		{
			selectInvenItem += 2;
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

void InvenComponent::Render(HDC hdc)
{

	upPanel->Render(_owner->GetPosition().x,
		_owner->GetPosition().y - TILE_SIZE * 2 - TILE_SIZE * 9, panelOpacity);

	downPanel->Render(_owner->GetPosition().x,
		_owner->GetPosition().y - TILE_SIZE * 2, panelOpacity);

	selectPanel->Render(
		_owner->GetPosition().x + TILE_SIZE / 2 + (selectInvenItem%2) * TILE_SIZE*8, 
		_owner->GetPosition().y - TILE_SIZE * 1.5 +(selectInvenItem/2) * TILE_SIZE, 
		selectPanelOpacity);

	PrintString();
}

void InvenComponent::SetSprite(const wchar_t* downFileName, const wchar_t* upFileName, const wchar_t* selectPanelFileName)
{
	upPanel = ImageManager::GetInstance()->FindSprite(upFileName);
	downPanel = ImageManager::GetInstance()->FindSprite(downFileName);
	selectPanel = ImageManager::GetInstance()->FindSprite(selectPanelFileName);
}

void InvenComponent::SetIsShow(bool isShow)
{
	this->isShow = isShow;
}

void InvenComponent::PrintString()
{
	wstring printStr = L"";
	for (int i = 0; i < ItemManager::GetInstance()->GetInventorySize(); ++i)
	{
		printStr = ItemManager::GetInstance()->GetItemName(i);
		ImageManager::GetInstance()->GetRenderTarget()->DrawTextW(
			printStr.c_str(), printStr.size(),
			ImageManager::GetInstance()->GetTextFormat(),
			D2D1::RectF(_owner->GetPosition().x + TILE_SIZE / 2 + 6 + (i % 2) * TILE_SIZE * 8,
				_owner->GetPosition().y - TILE_SIZE * 1.5 + 6 + (i / 2) * TILE_SIZE,
				_owner->GetPosition().x + TILE_SIZE / 2 + TILE_SIZE * 6 + (i % 2) * TILE_SIZE * 8,
				_owner->GetPosition().y - TILE_SIZE * 1.5 + TILE_SIZE + (i / 2) * TILE_SIZE
			),
			ImageManager::GetInstance()->GetBrushWhite()
		);

		printStr = L": " + to_wstring(ItemManager::GetInstance()->GetItemCount(i));
		ImageManager::GetInstance()->GetRenderTarget()->DrawTextW(
			printStr.c_str(), printStr.size(),
			ImageManager::GetInstance()->GetTextFormat(),
			D2D1::RectF(_owner->GetPosition().x + TILE_SIZE / 2 + TILE_SIZE*10 + (i%2)*TILE_SIZE*8,
				_owner->GetPosition().y - TILE_SIZE * 1.5 + 6 + (i/2)*TILE_SIZE,
				_owner->GetPosition().x + TILE_SIZE / 2 + TILE_SIZE*6 + (i % 2) * TILE_SIZE * 8,
				_owner->GetPosition().y - TILE_SIZE * 1.5 + TILE_SIZE + (i / 2) * TILE_SIZE
			),
			ImageManager::GetInstance()->GetBrushWhite()
		);

	}

	printStr = ItemManager::GetInstance()->GetitemInfo(selectInvenItem);
	ImageManager::GetInstance()->GetRenderTarget()->DrawTextW(
		printStr.c_str(), printStr.size(),
		ImageManager::GetInstance()->GetTextFormat(),
		D2D1::RectF(_owner->GetPosition().x + TILE_SIZE/2,
			_owner->GetPosition().y - TILE_SIZE * 2 - TILE_SIZE * 8.5 + 8,
			_owner->GetPosition().x + TILE_SIZE / 2 + TILE_SIZE*MAP_SIZE_X,
			_owner->GetPosition().y - TILE_SIZE * 1.5 + TILE_SIZE
		),
		ImageManager::GetInstance()->GetBrushWhite()
	);
}