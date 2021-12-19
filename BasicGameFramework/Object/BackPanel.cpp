#include "BackPanel.h"

#include "../Util/Sprite.h"

#include "../Manager/ImageManager.h"
#include "../Manager/CameraManager.h"
#include "../Manager/QuestManager.h"

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
			if (QuestManager::GetInstance()->GetQuest() == 10)
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
			else
			{
				panelOpacity -= 0.05;
				if (panelOpacity <= 0)
				{
					isBright = false;
					isActive = false;
				}
			}
		}
		else
		{
			panelOpacity += 0.05;
			if (panelOpacity >= 1)
			{

				isBright = true;
				isActive = false;
			}
		}
	}

	if (isItemEffect)
	{
		if (isBright == false)
		{
			panelOpacity += 0.1;
			if (panelOpacity >= 1)
			{
				rotationDelay++;
				if (rotationDelay >= 50)
				{
					panelOpacity = 1.0f;
					isBright = true;
				}
			}
		}
		else
		{
			panelOpacity -= 0.1;
			if (panelOpacity <= 0)
			{
				isItemEffect = false;
				isBright = true;
				isActive = false;
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

	if (isItemEffect)
	{
		backPanel->SizeRender(0, 0, 32 * 17, 32 * 13, panelOpacity);
	}
}

