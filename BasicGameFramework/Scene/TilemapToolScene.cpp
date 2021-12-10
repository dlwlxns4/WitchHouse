#include "TilemapToolScene.h"

#include "Layer.h"
#include "../Object/SampleSprite.h"

void TilemapToolScene::Init()
{
	Layer* mainLayer = new Layer(this, L"main", 1);

	SampleSprite* sampleSprite = new SampleSprite(this, mainLayer, L"sampleImage");
	sampleSprite->SetPosition(0,0);

	Scene::Init();
}
