#include "TileObj.h"
#include "../Component/SpriteRenderer.h"

#include "../Util/AboutTile.h"
#include "../Manager/GameManager.h"

void TileObj::Init()
{
}

void TileObj::Render(HDC hdc)
{
	POINTFLOAT* cameraPos = GameManager::GetInstance()->GetCameraPos();
	if (this->GetPosition().x >= TILE_SIZE * (cameraPos->x-1)  && this->GetPosition().x < TILE_SIZE * MAP_SIZE_X + TILE_SIZE * cameraPos->x)
	{
		if (this->GetPosition().y >= TILE_SIZE * (cameraPos->y-1) && this->GetPosition().y < TILE_SIZE * MAP_SIZE_Y + TILE_SIZE * cameraPos->y)
		{
			GameObject::Render(hdc);
		}
	}
}
