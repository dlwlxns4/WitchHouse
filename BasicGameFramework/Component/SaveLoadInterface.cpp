#include "SaveLoadInterface.h"
#include "../Manager/ImageManager.h"
#include "../Util/Sprite.h"
#include "../Util/Input.h"
#include "../Component/UserInfoComponent.h"
#include "../Object/GameObject.h"

#include <d2d1.h>
#include <dwrite.h>
void SaveLoadInterface::SetSprite(const wchar_t* infoName, const wchar_t* PanelName)
{
	saveLoadInfo = ImageManager::GetInstance()->FindSprite(infoName);
	for (int i = 0; i < 4; ++i)
	{
		saveLoadPanel[i] = ImageManager::GetInstance()->FindSprite(PanelName);
	}
}

void SaveLoadInterface::Update()
{
	if (Input::GetButtonDown('X'))
	{
		this->SetActive(false);
		isSave = true;
		_owner->GetComponent<UserInfoComponent>()->SetActive(true);
	}

	if (Input::GetButtonDown('Z'))
	{
		if (isSave)
		{

		}
	}
}

void SaveLoadInterface::Render(HDC hdc)
{
	saveLoadInfo->Render(0, 0, 1);
	for (int i = 0; i < 4; ++i)
	{
		saveLoadPanel[i]->Render(0, 64 + (32 * 3) * i, 1);
	}

	if (isSave==false)
	{
		wstring str = L"로드할 파일을 선택해주세요.";
		ImageManager::GetInstance()->GetRenderTarget()->DrawTextW(
			str.c_str(), str.size(),
			ImageManager::GetInstance()->GetTextFormat(),
			D2D1::RectF(20,22,544, 64),
			ImageManager::GetInstance()->GetBrushWhite()
		);
	}
	else
	{
		wstring str = L"세이브할 파일을 선택해주세요.";
		ImageManager::GetInstance()->GetRenderTarget()->DrawTextW(
			str.c_str(), str.size(),
			ImageManager::GetInstance()->GetTextFormat(),
			D2D1::RectF(20, 22, 544, 64),
			ImageManager::GetInstance()->GetBrushWhite()
		);
	}
}
