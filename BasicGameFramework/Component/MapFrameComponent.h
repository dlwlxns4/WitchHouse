#pragma once

#include "Component.h"

class MapFrameComponent : public Component
{
public:
	using Component::Component;
	virtual ~MapFrameComponent() noexcept = default;

	virtual void Render(HDC hdc) override;

};