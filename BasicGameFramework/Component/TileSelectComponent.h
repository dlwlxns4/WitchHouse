#pragma once
#include "../Manager/ImageManager.h"

#include "../Object/Text.h"

#include "Component.h"
#include <vector>

class Layer;
class Text;
class ChatPanel;
class TileSelectComponent : public Component
{

private:
	enum class TileType
	{
		tileObj = 0,
		PlayerObj = 1,
		parallaxObj = 2,
		Collider = 3,
		Trigger = 4,
		Portal = 5
	};

	using Component::Component;
	virtual ~TileSelectComponent();

	class Sprite* sprite = ImageManager::GetInstance()->FindSprite(ImageManager::GetInstance()->GetSpriteName(0).c_str());
	RECT spriteRect = {};
	int sampleIndex = 0;
	
	pair<int, int> downPos;
	pair<int, int> upPos;

	POINT mousePos = {};
	
	vector<Layer*> mapData;

	TileType tileType = TileType::tileObj;

	Text* tileTypeTxt = nullptr;
	Text* currLayerTxt = nullptr;
	Text* triggerPosTxt= nullptr;

	int currLayer = -1;

	bool isShowCollider = false;

public:

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void SetObject(int mouseIndexX, int mouseIndexY);

	void Save(int saveIndex=0);
	void Load(int loadIndex=0);
};