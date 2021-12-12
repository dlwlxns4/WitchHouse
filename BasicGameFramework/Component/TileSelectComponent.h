#pragma once
#include "../Manager/ImageManager.h"

#include "../Object/Text.h"

#include "Component.h"
#include <vector>

class Layer;
class Text;
class TileSelectComponent : public Component
{

private:
	enum class TileType
	{
		tileObj=0,
		PlayerObj=1,
		parallaxObj=2
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

	Text* tileTypeTxt;
	Text* currLayerTxt;
	int currLayer = -1;

public:

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void SetObject(int mouseIndexX, int mouseIndexY);

};