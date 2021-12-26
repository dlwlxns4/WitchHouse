#include "InteractionComp.h"

#include "../Manager/ImageManager.h"
#include "../Manager/GameManager.h"
#include "../Manager/TalkManager.h"
#include "../Manager/ItemManager.h"
#include "../Manager/QuestManager.h"
#include "../Manager/SoundManager.h"

#include "../Util/Sprite.h"
#include "../Object/GameObject.h"

#include "../stdafx.h"

#include <d2d1.h>
#include <dwrite.h>

#include <iostream>



void InteractionComp::Init()
{
	Component::Init();
	slatePos = 0;
}

void InteractionComp::Update()
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

	if (GameManager::GetInstance()->GetState() == State::Chat && isOpen)
	{
		if (TalkManager::GetInstance()->GetIsItem() == false)
		{
			if (data.size() - 1 == vecIndex)
			{
				if (isOpen && Input::GetButtonDown('Z'))
				{
					if (data[vecIndex].size() == chatEffect.size())
					{
						isTalk = false;
						isClose = true;
						int thidObjId = TalkManager::GetInstance()->GetCurrInteractId();
						QuestManager::GetInstance()->DoActivateQuestObj(thidObjId);
						SoundManager::GetInstance()->startInfSound(L"Click");
					}
				}
			}
			else
			{
				if (Input::GetButtonDown('Z'))
				{
					if (data[vecIndex].size() == chatEffect.size())
					{
						vecIndex++;
						chatEffect.clear();
						talkIndexStr.clear();
						strIndex = 0;
						SoundManager::GetInstance()->startInfSound(L"Click");

					}
				}
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
					int thidObjId = TalkManager::GetInstance()->GetCurrInteractId();
					QuestManager::GetInstance()->DoActivateQuestObj(thidObjId);
					int id = ItemManager::GetInstance()->GetCurrFindItem();
					if (ItemManager::GetInstance()->CanObtainItem(id))
					{
						SoundManager::GetInstance()->startInfSound(L"Item");
					}
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
					SoundManager::GetInstance()->startInfSound(L"Cursor");

				}
				else if (Input::GetButtonDown(VK_UP))
				{
					if (state == ApprovalState::Disagree)
					{
						state = ApprovalState::Agree;
					}
					SoundManager::GetInstance()->startInfSound(L"Cursor");

				}

				if (Input::GetButtonDown('Z'))
				{
					if (state == ApprovalState::Agree)
					{
						int id = ItemManager::GetInstance()->GetCurrFindItem();
						if (ItemManager::GetInstance()->CanObtainItem(id))
						{
							ItemManager::GetInstance()->AddItem(id);
						}
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
					SoundManager::GetInstance()->startInfSound(L"Click");

				}
			}
			else
			{
				if (isOpen && Input::GetButtonDown('Z'))
				{
					if (data[vecIndex] == talkIndexStr)
					{
						vecIndex++;
						talkIndexStr.clear();
						strIndex = 0;
						SoundManager::GetInstance()->startInfSound(L"Click");
					}

				}
			}
		}

	}
	ClosePanel();

}


void InteractionComp::Render(HDC hdc)
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

void InteractionComp::SetSprite(const wchar_t* fileName, const wchar_t* selectPanelFileName)
{
	sprite = ImageManager::GetInstance()->FindSprite(fileName);
	selectPanel = ImageManager::GetInstance()->FindSprite(selectPanelFileName);
}

void InteractionComp::SetSlatePos(int pos)
{
	slatePos = pos;
}

int InteractionComp::GetSlatePos(int pos)
{
	return 0;
}

void InteractionComp::ManageSelectPanel()
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

void InteractionComp::ClosePanel()
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

void InteractionComp::DoActivateObj(int id)
{
}

