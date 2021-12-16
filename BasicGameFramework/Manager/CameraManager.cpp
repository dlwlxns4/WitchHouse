#include "CameraManager.h"
#include "../Util/AboutTile.h"

void CameraManager::SetCameraMinX(int x)
{
	if (x < minPosX)
	{
		minPosX = x;
	}
}

void CameraManager::SetCameraMinY(int y)
{
	if (y < minPosY)
	{
		minPosY = y;
	}
}

void CameraManager::SetCameraMaxX(int x)
{
	if (x > maxPosX)
	{
		maxPosX = x;
	}
}

void CameraManager::SetCameraMaxY(int y)
{
	if (y > maxPosY)
	{
		maxPosY = y;
	}
}

bool CameraManager::CheckOutOfTile(float x, float y)
{
	if (x < minPosX || x > maxPosX-1-MAP_SIZE_X)
		return true;
	if (y < minPosY || y > maxPosY+1-MAP_SIZE_Y)
		return true;

	return false;
}
