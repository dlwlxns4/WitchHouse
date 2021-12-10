#include "PlayerSpriteRenderer.h"
#include "../../Image.h"

#include "../../Manager/ImageManager.h"

#include "../../Object/GameObject.h"


void PlayerSpriteRenderer::Render(HDC hdc)
{


	img->Render(hdc,
		_owner->GetRenderPos().x,
		_owner->GetRenderPos().y,
		0,
		(int)dir
		);
}

void PlayerSpriteRenderer::SetImage(const wchar_t* filePath)
{
	this->img = ImageManager::GetInstance()->FindImage(filePath);
}

void PlayerSpriteRenderer::SetDirection(int dir)
{
	this->dir = (Direction)dir; 
}
