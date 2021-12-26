#pragma once

#include <Windows.h>
#include <string>

#include "../Util/Singleton.h"
#include "../IBehaviour.h"

#include "../Manager/QuestManager.h"
#include "../Manager/SceneManager.h"

#include <iostream>

#include <array>

enum class CameraActionState
{
	Null,
	Shake,
};

class CameraManager : public Singleton<CameraManager>, IBehaviour
{
public:
	CameraManager() = default;
	virtual ~CameraManager();

	void SetCameraPos(POINT pos);
	POINT* GetCameraPos() { return &cameraPos; }
	void SetCameraMinX(int x);
	void SetCameraMinY(int y);
	void SetCameraMaxX(int x);
	void SetCameraMaxY(int y);


	bool CheckOutOfTileX(int x);
	bool CheckOutOfTileY(int y);

	void Clear();

	void SetActionStrategy(CameraActionState state);

	virtual void Init() override;
	virtual void Update() override;
	virtual void Release() override;

	virtual void Write(std::ostream& os) const;
	friend std::ostream& operator<<(std::ostream& os, const CameraManager& cameraManager);
	virtual void Read(std::istream& is);
	friend std::istream& operator>>(std::istream& is, CameraManager& cameraManager);
private:
	POINT cameraPos = {};
	int maxPosX = 0;
	int maxPosY = 0;
	int minPosX = 10000;
	int minPosY = 10000;

	int cameraDelay = 0;


	std::array<class ICameraAction*, 2> actions = {nullptr};
	class ICameraAction* _actionSterategy = actions[0];
};

class ICameraAction abstract
{
public:
	ICameraAction(CameraManager* camera)
		:_owner{ camera }
	{}
	virtual ~ICameraAction() = default;

	virtual void DoAction() = 0;

protected:
	CameraManager* _owner;
};

class CameraNullAction : public ICameraAction
{
public:
	ICameraAction::ICameraAction;
	virtual ~CameraNullAction() = default;

	virtual void DoAction() override
	{

	}
};

class CameraShakeAction : public ICameraAction
{
#define LEFT 0
#define RIGHT 1
#define RESET 2
#define END 3
public:
	ICameraAction::ICameraAction;
	virtual ~CameraShakeAction() = default;

	virtual void DoAction() override
	{
		POINT* pos = _owner->GetCameraPos();
		if (dir == LEFT)
		{
			moveDistance += 16;
			if (moveDistance >= 32)
			{
				moveDistance = 0;
				dir++;
			}
			pos->x += 16;
		}
		else if (dir == RIGHT)
		{
			moveDistance += 32;
			if (moveDistance >= 64)
			{
				moveDistance = 0;
				dir++;
			}
			pos->x -= 32;
		}
		else if (dir == RESET)
		{
			moveDistance += 16;
			if (moveDistance >= 32)
			{
				moveDistance = 0;
				dir++;
			}
			pos->x += 16;
		}
		else if (dir == END)
		{
			moveDistance++;
			if (moveDistance > 30)
			{
				_owner->SetActionStrategy(CameraActionState::Null);
				SceneManager::GetInstance()->SetNextScene(L"GameOver");
			}
		}
	}
private:
	int dir = 0;
	int moveDistance = 0;
};