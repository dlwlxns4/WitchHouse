#include "TilemapToolScene.h"

#include "Layer.h"
#include "../Object/SampleSprite.h"
#include "../Object/MapFrame.h"
#include "../Object/MapData.h"

void TilemapToolScene::Init()
{
	Layer* mainLayer = new Layer(this, L"main", 1);

	SampleSprite* sampleSprite = new SampleSprite(this, mainLayer, L"sampleImage");
	sampleSprite->SetPosition(0,0);

	MapFrame* mapFrame = new MapFrame(this, mainLayer, L"mapFrame");
	

	Scene::Init();
}
