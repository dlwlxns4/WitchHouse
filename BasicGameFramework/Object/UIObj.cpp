#include "UIObj.h"
#include "../Component/ChatRenderer.h"
#include "../Component/UserInfoComponent.h"
#include "../Component/InvenComponent.h"

#include "../Util/Input.h"
#include "../Manager/GameManager.h"

#define START_PANEL_POS_x 0
#define START_PANEL_POS_Y 32*11

void UIObj::Init()
{
	this->SetPosition({ 0 ,START_PANEL_POS_Y });

	ChatRenderer* sprite = new ChatRenderer(this, 1);
	sprite->SetSprite(L"Image/UI/ChatPanel.png", L"Image/UI/SelectPanel_03.png");

	UserInfoComponent* userInfo = new UserInfoComponent(this, 3);
	userInfo->SetSprite(L"Image/UI/UserInfo_1.png", L"Image/UI/UserInfo_2.png");

	InvenComponent* inven = new InvenComponent(this, 2);
	inven->SetActive(false);
	inven->SetSprite(L"Image/UI/InventoryPanel.png", L"Image/UI/ItemInfoPanel.png", L"Image/UI/SelectPanel_02.png");
}

