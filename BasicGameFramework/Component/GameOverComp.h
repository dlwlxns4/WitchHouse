#pragma once

#include "Component.h"

class GameOverComp : public Component
{
public:
	using Component::Component;
	virtual ~GameOverComp() = default;

	virtual void Update() override;
};