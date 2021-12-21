#pragma once

#include "Scene.h"

class GameOverScene : public Scene
{
public:
	using Scene::Scene;
	virtual ~GameOverScene() noexcept = default;

	virtual void Init() override;
};