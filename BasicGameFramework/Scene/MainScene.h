#pragma once

#include "Scene.h"
#include "../Util/Singleton.h"

class BackPanel;
class MainScene : public Scene, Singleton<MainScene>
{
public:
	using					Scene::Scene;
	virtual					~MainScene() noexcept = default;

	virtual void			Init() override;
	virtual void			Update() override;
	virtual void			Render(HDC hdc) override;

	void					DoTrap();
	void					TransMap(int mapNum);

	void					Save(int saveIndex = 0);
	void					Load(int loadIndex = 0);


	void					Debug();
private:
	std::vector<Layer*>*	_layers;
	int						num = 0;
	bool					isShowRect = false;

	int						nextSceneNum = 0;
	bool					loadFlag = false;
	bool					isFirst = true;

	BackPanel*				backPanel = nullptr;
};