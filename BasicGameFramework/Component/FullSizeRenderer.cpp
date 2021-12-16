#include "FullSizeRenderer.h"
#include "../Util/Sprite.h"
#include "../Object/GameObject.h"


#include "../Manager/ImageManager.h"
void FullSizeRenderer::Render(HDC hdc)
{
	sprite->Render(_owner->GetRenderPos().x
				,_owner->GetPosition().y
		, 1);
}

void FullSizeRenderer::SetSprite(const wchar_t* fileName)
{
	sprite = ImageManager::GetInstance()->FindSprite(fileName);
}
