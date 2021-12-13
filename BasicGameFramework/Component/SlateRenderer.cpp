#include "SlateRenderer.h"

#include "../Manager/ImageManager.h"
#include "../Manager/GameManager.h"
#include "../Util/Sprite.h"
#include "../Object/GameObject.h"

void SlateRenderer::Init()
{
	Component::Init();
	slatePos = 0;
}

void SlateRenderer::Update()
{
	if (GameManager::GetInstance()->GetState() == State::Chat && slatePos < sprite->GetHeight()/2 && isOpen==false)
	{
		slatePos+=8;
		if (slatePos >= sprite->GetHeight() / 2)
		{
			isOpen = true;
		}
	}

	if (isOpen && Input::GetButtonDown('Z') || isClose)
	{
		slatePos -= 8;
		isClose = true;
		if (slatePos <= 0)
		{
			isOpen = false;
			isClose = false;
			slatePos = 0;
			GameManager::GetInstance()->SetState(State::None);
		}
	}
}

void SlateRenderer::Render(HDC hdc)
{

	if (GameManager::GetInstance()->GetState() == State::Chat)
	{
		sprite->SlateRender(_owner->GetPosition().x, _owner->GetPosition().y, slatePos);
	}
}

void SlateRenderer::SetSprite(const wchar_t* fileName)
{
	sprite = ImageManager::GetInstance()->FindSprite(fileName);
}

void SlateRenderer::SetSlatePos(int pos)
{
	slatePos = pos;
}

int SlateRenderer::GetSlatePos(int pos)
{
	return 0;
}

