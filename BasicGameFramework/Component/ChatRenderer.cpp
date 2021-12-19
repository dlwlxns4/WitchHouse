#include "ChatRenderer.h"

#include "../Manager/ImageManager.h"
#include "../Manager/GameManager.h"
#include "../Manager/TalkManager.h"
#include "../Manager/ItemManager.h"

#include "../Util/Sprite.h"
#include "../Object/GameObject.h"

#include "../stdafx.h"

#include <d2d1.h>
#include <dwrite.h>

#include <iostream>



void ChatRenderer::Init()
{
	Component::Init();
	slatePos = 0;
}

void ChatRenderer::Update()
{
	if (GameManager::GetInstance()->GetState() == State::Chat && slatePos < sprite->GetHeight() / 2 && isOpen == false)
	{
		slatePos += 8;
		if (slatePos >= sprite->GetHeight() / 2)
		{
			data = TalkManager::GetInstance()->GetVecTalkData();
			isOpen = true;
			isTalk = true;
		}
	}

	if (GameManager::GetInstance()->GetState() == State::Chat)
	{
		if (TalkManager::GetInstance()->GetIsItem() == false)
		{
			if (isOpen && Input::GetButtonDown('Z'))
			{
				isTalk = false;
				isClose = true;
			}
		}
		else
		{
			if (data.size() - 1 == vecIndex)
			{
				if (Input::GetButtonDown('Z'))
				{
					isTalk = false;
					isClose = true;
				}
			}
			else if (data.size() - 2 == vecIndex && data[vecIndex] == talkIndexStr)
			{
				ManageSelectPanel();

				if (Input::GetButtonDown(VK_DOWN))
				{
					if (state == ApprovalState::Agree)
					{
						state = ApprovalState::Disagree;
					}
				}
				else if (Input::GetButtonDown(VK_UP))
				{
					if (state == ApprovalState::Disagree)
					{
						state = ApprovalState::Agree;
					}
				}

				if (Input::GetButtonDown('Z'))
				{
					if (state == ApprovalState::Agree)
					{
						int id = ItemManager::GetInstance()->GetCurrFindItem();
						ItemManager::GetInstance()->AddItem(id);
						vecIndex++;
						talkIndexStr.clear();
						strIndex = 0;
						chatEffect.clear();
					}
					else
					{
						isTalk = false;
						isClose = true;
					}
					isShowSelectPanel = false;
				}
			}
			else
			{
				if (isOpen && Input::GetButtonDown('Z'))
				{
					vecIndex++;
					talkIndexStr.clear();
					strIndex = 0;
				}
			}
		}
		ClosePanel();
	}
}


void ChatRenderer::Render(HDC hdc)
{

	if (GameManager::GetInstance()->GetState() == State::Chat)
	{
		sprite->SlateRender(_owner->GetPosition().x, _owner->GetPosition().y, slatePos);
	}

	if (GameManager::GetInstance()->GetState() == State::Chat && isTalk)
	{
		if (data.empty() == false)
		{
			if (data[vecIndex] != talkIndexStr)
			{
				talkIndexStr += data[vecIndex][strIndex];
				chatEffect += data[vecIndex][strIndex++];
			}
		}
		D2D1_RECT_F layoutRect = D2D1::RectF(
			10, 310, 534, 406
		);



		ImageManager::GetInstance()->GetRenderTarget()->DrawTextW(chatEffect.c_str(), chatEffect.size(),
			ImageManager::GetInstance()->GetTextFormat(),
			layoutRect,
			ImageManager::GetInstance()->GetBrushWhite());
	}

	if (isShowSelectPanel)
	{
		selectPanel->Render(
			TILE_SIZE / 2,
			TILE_SIZE * 10 + TILE_SIZE / 2 + (int)state * TILE_SIZE,
			selectPanelOpacity);
	}
}

void ChatRenderer::SetSprite(const wchar_t* fileName, const wchar_t* selectPanelFileName)
{
	sprite = ImageManager::GetInstance()->FindSprite(fileName);
	selectPanel = ImageManager::GetInstance()->FindSprite(selectPanelFileName);
}

void ChatRenderer::SetSlatePos(int pos)
{
	slatePos = pos;
}

int ChatRenderer::GetSlatePos(int pos)
{
	return 0;
}

void ChatRenderer::ManageSelectPanel()
{
	if (isShowSelectPanel == false)
	{
		isShowSelectPanel = true;
	}
	else
	{
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

void ChatRenderer::ClosePanel()
{
	if (isClose)
	{
		slatePos -= 8;
		if (slatePos <= 0)
		{
			isOpen = false;
			isClose = false;
			chatEffect.clear();
			talkIndexStr.clear();
			slatePos = 0;
			vecIndex = 0;
			strIndex = 0;
			data.clear();
			isShowSelectPanel = false;
			GameManager::GetInstance()->SetState(State::None);
		}
	}
}

