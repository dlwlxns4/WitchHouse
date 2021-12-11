#include "MapFrameComponent.h"

#include <d2d1.h>

#include "../Util/AboutTile.h"
#include "../Manager/ImageManager.h"

void MapFrameComponent::Render(HDC hdc)
{

	for (int i = 0; i < MAP_SIZE_Y; ++i)
	{
		for (int j = 0; j < MAP_SIZE_X; ++j)
		{
			ImageManager::GetInstance()->GetRenderTarget()->DrawRectangle(
				D2D1::RectF(j*TILE_SIZE, i*TILE_SIZE, (j+1)*TILE_SIZE, (i+1)*TILE_SIZE),
				ImageManager::GetInstance()->GetBrush());
		}
	}

}
