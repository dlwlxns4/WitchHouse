#pragma once
#include "../Manager/ImageManager.h"

#include "Component.h"
class TileSelectComponent : public Component
{
public:

private:

	using Component::Component;
	virtual ~TileSelectComponent() noexcept = default;

	class Sprite* sprite = ImageManager::GetInstance()->FindSprite(ImageManager::GetInstance()->GetSpriteName(0).c_str());
	int sampleIndex = 0;

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

};