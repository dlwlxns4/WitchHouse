#pragma once

#include "Scene.h"

class TilemapToolScene : public Scene
{
public:
	using Scene::Scene;
	virtual ~TilemapToolScene() noexcept = default;

	virtual void		Init() override;
};
