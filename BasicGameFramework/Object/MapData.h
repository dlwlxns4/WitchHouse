#pragma once

#include "GameObject.h"
#include "../Scene/Layer.h"

#include <vector>

using namespace std;

class MapData : public GameObject
{
private: 
	using GameObject::GameObject;
	virtual ~MapData() noexcept = default;
	
	vector<Layer*> mapLayer;


public:
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};