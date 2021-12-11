#include "MapData.h"
#include <iostream>
#include "../stdafx.h"

void MapData::Update()
{
	if (Input::GetButtonDown(VK_TAB))
	{
		mapLayer.push_back(new Layer(L"layer"+mapLayer.size(), 1));
	}

	for (auto layer : mapLayer)
	{
		layer->Update();
	}
}

void MapData::Render(HDC hdc)
{
	for (auto layer : mapLayer)
	{
		layer->Render(hdc);
	}
}
