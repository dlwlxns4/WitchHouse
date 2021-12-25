#pragma once

#include "Scene.h"
#include "../Util/Singleton.h"
#include <vector>

using namespace std;

class BackPanel;
class MainScene : public Scene, Singleton<MainScene>
{
public:
	using					Scene::Scene;
	virtual					~MainScene() noexcept = default;

	virtual void			Init() override;
	virtual void			Update() override;
	virtual void			Render(HDC hdc) override;

	void					DoTrap(int id);
	void					TransMap(int mapNum);
	void					DataLoad(int mapNum);

	void					Save(int saveIndex = 0);
	void					Load(int loadIndex = 0);


	void					Debug();
	void					SetActiveBackPanelFlag(bool isActive);
	vector<Layer*>*			GetMapData() { return _layers; }
	void					SetEffect(int id);
private:
	vector<Layer*>*	_layers;
	vector<Layer*>*	_CopyLayer;
	int						num = 0;
	bool					isShowRect = false;
	bool					isShowCollider = false;

	int						nextSceneNum = 0;
	bool					loadFlag = false;
	bool					dataLoadFlag = false;
	bool					isDataLoad = false;
	bool					isFirst = true;
	bool					backPaenlActiveFlag = false;

	bool					QuestDebug = false;
	BackPanel*				backPanel = nullptr;

};