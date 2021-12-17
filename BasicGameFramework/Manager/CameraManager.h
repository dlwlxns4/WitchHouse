#pragma once

#include <Windows.h>
#include <string>

#include "../Util/Singleton.h"
#include "../IBehaviour.h"

#include "../Manager/QuestManager.h"

#include <iostream>
class CameraManager : public Singleton<CameraManager>, IBehaviour
{
public:
	CameraManager() = default;
	~CameraManager() = default;

	void SetCameraPos(POINT pos);
	POINT* GetCameraPos() { return &cameraPos; }
	void SetCameraMinX(int x);
	void SetCameraMinY(int y);
	void SetCameraMaxX(int x);
	void SetCameraMaxY(int y);


	bool CheckOutOfTileX(int x);
	bool CheckOutOfTileY(int y);

	void Clear();

	virtual void Init() override;
	virtual void Update() override;
private:
	POINT cameraPos = {};
	int maxPosX = 0;
	int maxPosY = 0;
	int minPosX = 10000;
	int minPosY = 10000;

	int cameraDelay = 0;
};