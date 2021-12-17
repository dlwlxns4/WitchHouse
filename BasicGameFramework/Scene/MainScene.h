#pragma once

#include "Scene.h"
#include "../Util/Singleton.h"


class MainScene : public Scene, Singleton<MainScene>
{
public:
	using Scene::Scene;
	virtual ~MainScene() noexcept = default;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void DoTrap();
	void TransMap(int mapNum);

	void Save(int saveIndex = 0);
	void Load(int loadIndex = 0);

private:
	std::vector<Layer*>* _layers;
	int num = 0;
	bool isShowRect = false;

	bool flag = false;
	int nextSceneNum = 0;
};