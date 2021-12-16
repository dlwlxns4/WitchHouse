#pragma once

#include <Windows.h>
#include <string>

#include "../Util/Singleton.h"
#include "../IBehaviour.h"

#include <iostream>
class CameraManager : public Singleton<CameraManager>, IBehaviour
{
private:
	POINTFLOAT cameraPos = {};
	int maxPosX = 0;
	int maxPosY = 0;
	int minPosX = 1000;
	int minPosY = 1000;

public:
	POINTFLOAT* GetCameraPos() { return &cameraPos; }
	void SetCameraMinX(int x);
	void SetCameraMinY(int y);
	void SetCameraMaxX(int x);
	void SetCameraMaxY(int y);

	bool CheckOutOfTile(float x, float y);
};