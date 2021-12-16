#pragma once

#include "Scene.h"

class MainScene : public Scene
{
public:
	using Scene::Scene;
	virtual ~MainScene() noexcept = default;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void DoTrap();
	void TransMap();

	void Save(int saveIndex = 0);
	void Load(int loadIndex = 0);

private:
	std::vector<Layer*>* _layers;

	bool isShowRect = false;
};