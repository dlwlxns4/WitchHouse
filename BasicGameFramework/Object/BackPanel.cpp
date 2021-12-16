#include "BackPanel.h"

#include "../Util/Sprite.h"

#include "../Manager/ImageManager.h"
#include "../Manager/CameraManager.h"
#include <iostream> //
void BackPanel::Init()
{
	backPanel = ImageManager::GetInstance()->FindSprite(L"Image/UI/OpacityPanel.png");
}

void BackPanel::Update()
{
	if (isActive)
	{
		if (isBright)
		{
			if (isFirst)
			{
				POINT* cameraPos = CameraManager::GetInstance()->GetCameraPos();
				if (cameraPos->y >= -32)
				{
					panelOpacity -= 0.002;
				}
				if (panelOpacity <= 0)
				{
					isBright = false;
					isActive = false;
				}
			}
		}
	}
}

void BackPanel::Render(HDC hdc)
{
	if (isActive)
	{
		if (isBright)
		{
			backPanel->SizeRender(0, 0, 32 * 17, 32 * 13, panelOpacity);
		}
	}
}

