#include "ChatRenderer.h"

#include "../Manager/ImageManager.h"
#include "../Manager/GameManager.h"
#include "../Manager/TalkManager.h"

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
			isOpen = true;
			isTalk = true;
		}
	}

	if (isOpen && Input::GetButtonDown('Z') || isClose)
	{
		slatePos -= 8;
		isTalk = false;
		isClose = true;
		if (slatePos <= 0)
		{
			isOpen = false;
			isClose = false;
			chatEffect.clear();
			slatePos = 0;
			vecIndex = 0;
			strIndex = 0;
			GameManager::GetInstance()->SetState(State::None);
		}
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
		vector<wstring> data = TalkManager::GetInstance()->GetVecTalkData();
		if (data.empty() == false)
		{
			if (data[vecIndex] != chatEffect)
			{
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
}

void ChatRenderer::SetSprite(const wchar_t* fileName)
{
	sprite = ImageManager::GetInstance()->FindSprite(fileName);
}

void ChatRenderer::SetSlatePos(int pos)
{
	slatePos = pos;
}

int ChatRenderer::GetSlatePos(int pos)
{
	return 0;
}

