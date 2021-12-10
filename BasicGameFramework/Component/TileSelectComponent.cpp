#include "TileSelectComponent.h"

#include "../Manager/ImageManager.h"
#include "../stdafx.h"

#include "../Util/Sprite.h"
#include "../Object/GameObject.h"
void TileSelectComponent::Update()
{
	if (Input::GetButtonDown('1'))
	{
		if (sampleIndex > 0)
		{
			sampleIndex--;
		}
		sprite=ImageManager::GetInstance()->FindSprite(ImageManager::GetInstance()->GetSpriteName(sampleIndex).c_str());
	}
	else if (Input::GetButtonDown('2'))
	{
		sampleIndex++;
		sprite=ImageManager::GetInstance()->FindSprite(ImageManager::GetInstance()->GetSpriteName(sampleIndex).c_str());

	}
}

void TileSelectComponent::Render(HDC hdc)
{
	sprite->Render(
		_owner->GetPosition().x,
		_owner->GetPosition().y
	);
}
