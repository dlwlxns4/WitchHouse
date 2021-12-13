#include "InvenComponent.h"


#include "../Manager/ImageManager.h"
#include "../Manager/GameManager.h"
#include "../Util/Sprite.h"
#include "../Object/GameObject.h"

#include "../Util/AboutTile.h"


void InvenComponent::Update()
{
	if (Input::GetButtonDown('X'))
	{
		if (GameManager::GetInstance()->GetState() == State::None)
		{
			GameManager::GetInstance()->SetState(State::UserInfo);
		}
		else if (GameManager::GetInstance()->GetState() == State::UserInfo)
		{
			GameManager::GetInstance()->SetState(State::None);
			panelOpacity = 0;
		}

	}
	if (GameManager::GetInstance()->GetState() == State::UserInfo && isShow)
	{
		panelOpacity += 0.1f;
	}
}

void InvenComponent::Render(HDC hdc)
{
	if (GameManager::GetInstance()->GetState() == State::UserInfo && isShow)
	{
		upPanel->Render(_owner->GetPosition().x,
			_owner->GetPosition().y - TILE_SIZE * 2, panelOpacity);

		downPanel->Render(_owner->GetPosition().x + TILE_SIZE * 5 + TILE_SIZE / 2,
			_owner->GetPosition().y - TILE_SIZE * 2, panelOpacity);
	}
}

void InvenComponent::SetSprite(const wchar_t* leftfileName, const wchar_t* rightFileName)
{
	upPanel = ImageManager::GetInstance()->FindSprite(leftfileName);
	downPanel = ImageManager::GetInstance()->FindSprite(rightFileName);
}

void InvenComponent::SetIsShow(bool isShow)
{
	this->isShow = isShow;
}
