#include "UserInfoComponent.h"

#include "../Manager/ImageManager.h"
#include "../Manager/GameManager.h"
#include "../Util/Sprite.h"
#include "../Object/GameObject.h"

#include "../Util/AboutTile.h"

#define PORTRAIT_SIZE 96

#define PORTRAIT_START_POSX 188
#define PORTRAIT_START_POSY 304
#define STR_HEALTH_POSX 380
#define STR_HEALTH_POSY 346  

#define HELTHBAR_POSX 384
#define HELTHBAR_POSY 370
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
}

void UserInfoComponent::Render(HDC hdc)
{
	if (GameManager::GetInstance()->GetState() == State::UserInfo && isShow)
	{
		leftPanel->Render(_owner->GetPosition().x,
			_owner->GetPosition().y - TILE_SIZE * 2, panelOpacity);

		rightPanel->Render(_owner->GetPosition().x + TILE_SIZE*5 +TILE_SIZE/2,
			_owner->GetPosition().y-TILE_SIZE*2, panelOpacity);

		portrait->Render(PORTRAIT_START_POSX, PORTRAIT_START_POSY, panelOpacity,0,0,4,2);

		healthBar->Render(HELTHBAR_POSX, HELTHBAR_POSY, panelOpacity);
	}
}

void UserInfoComponent::SetSprite(const wchar_t* leftfileName, const wchar_t* rightFileName)
{
	leftPanel = ImageManager::GetInstance()->FindSprite(leftfileName);
	rightPanel = ImageManager::GetInstance()->FindSprite(rightFileName);
	portrait = ImageManager::GetInstance()->FindSprite(L"Image/UI/viviface.png");
	healthBar = ImageManager::GetInstance()->FindSprite(L"Image/UI/HealthBar.png");
}

void UserInfoComponent::SetIsShow(bool isShow)
{
	this->isShow = isShow;

}
