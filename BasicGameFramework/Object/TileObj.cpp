#include "TileObj.h"
#include "../Component/SpriteRenderer.h"

#include "../Util/AboutTile.h"
#include "../Manager/GameManager.h"
#include "../Manager/CameraManager.h"

#include <iostream>

void TileObj::Init()
{
}

void TileObj::Render(HDC hdc)
{
	POINT* cameraPos = CameraManager::GetInstance()->GetCameraPos();
	if (this->GetPosition().x >= TILE_SIZE * (cameraPos->x / TILE_SIZE -1)  && this->GetPosition().x < TILE_SIZE * MAP_SIZE_X + TILE_SIZE * cameraPos->x / TILE_SIZE)
	{
		if (this->GetPosition().y >= TILE_SIZE * (cameraPos->y / TILE_SIZE -1) && this->GetPosition().y < TILE_SIZE * MAP_SIZE_Y + TILE_SIZE * cameraPos->y / TILE_SIZE)
		{
			GameObject::Render(hdc);
		}
	}
}

void TileObj::Write(std::ostream& os) const
{
	os << 1 << "\t";
	GameObject::Write(os);
}

void TileObj::OnTrigger()
{
}
