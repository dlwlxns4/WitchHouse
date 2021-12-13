#include "ChatPanel.h"
#include "../Component/SlateRenderer.h"
#include "../Component/UserInfoComponent.h"

#include "../Util/Input.h"
#include "../Manager/GameManager.h"

#define START_PANEL_POS_x 0
#define START_PANEL_POS_Y 32*11

void ChatPanel::Init()
{
	this->SetPosition({ 0 ,START_PANEL_POS_Y });

	SlateRenderer* sprite = new SlateRenderer(this, 1);
	sprite->SetSprite(L"Image/UI/ChatPanel.png");

	UserInfoComponent* userInfo = new UserInfoComponent(this, 2);
	userInfo->SetSprite(L"Image/UI/UserInfo_1.png", L"Image/UI/UserInfo_2.png");
}

