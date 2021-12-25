#include "ImageManager.h"


//D2D
#include <d2d1.h>			
#include <wincodec.h>

#include <dwrite.h>

#include "../Util/Sprite.h"

#include "../Util/AboutTile.h"

#include "GameManager.h"

#include "../Manager/CameraManager.h"
#define PLAYER_SIZE_X 32
#define PLAYER_SIZE_Y 48



ImageManager::~ImageManager() noexcept
{
	Release();
}

void ImageManager::Init(HWND hWnd, HINSTANCE hInstance, IWICImagingFactory* pImagingFactory, ID2D1HwndRenderTarget* pRenderTarget, ID2D1SolidColorBrush* pBrush, IDWriteTextFormat* pTextFormat)
{	
	this->_hWnd = hWnd;
	this->_hInstance = hInstance;
	this->pImagingFactory = pImagingFactory;
	this->pRenderTarget = pRenderTarget;
	this->pTextFormat = pTextFormat;

	this->pBrush = pBrush;

	pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(220, 0, 0, 1), &pBrushRed);
	pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(255, 255, 255, 1), &pBrushWhite);
	pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(132/255.0f, 272/255.0f, 255/255.0f, 1), &pBrushBlue);
	pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(255 / 255.0f, 165 / 255.0f, 0 / 255.0f, 1), &pBrushOrange);
	pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(139 / 255.0f, 0 / 255.0f, 255 / 255.0f, 1), &pBrushPurple);
	pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(155 / 255.0f, 103 / 255.0f, 60 / 255.0f, 1), &pBrushBrown);

	//-------------Character
	AddSprite(L"Image/Character/$vivi.png");
	
	

	//-------------SampleImageTile
	AddSprite(L"Image/Tile/TileA1.png"); 
	AddSprite(L"Image/Tile/TileA2.png");
	AddSprite(L"Image/Tile/TileA3.png");
	AddSprite(L"Image/Tile/TileA4.png");
	AddSprite(L"Image/Tile/TileA5.png");
	AddSprite(L"Image/Tile/TileB.png");
	AddSprite(L"Image/Tile/TileC.png");
	AddSprite(L"Image/Tile/TileD.png");
	AddSprite(L"Image/Tile/TileE.png");
	AddSprite(L"Image/Tile/tileHouse.png");
	AddSprite(L"Image/Tile/yukab034d.png");
	AddSprite(L"Image/Tile/!$object11.png");
	AddSprite(L"Image/Tile/!$object12.png");
	AddSprite(L"Image/Tile/!$wall_eye.png");
	AddSprite(L"Image/Tile/!$wall2.png");
	AddSprite(L"Image/Tile/!$wall3.png");
	AddSprite(L"Image/Tile/!$wall4L.png");
	AddSprite(L"Image/Tile/!$wall4L2.png");
	AddSprite(L"Image/Tile/!$wall5.png");
	AddSprite(L"Image/Tile/TileEdge.png");
	AddSprite(L"Image/Tile/TileEdge2.png");
	AddSprite(L"Image/Tile/DeskTile.png");

	spritesName.push_back(L"Image/Tile/TileA1.png");
	spritesName.push_back(L"Image/Tile/TileA2.png");
	spritesName.push_back(L"Image/Tile/TileA3.png");
	spritesName.push_back(L"Image/Tile/TileA4.png");
	spritesName.push_back(L"Image/Tile/TileA5.png");
	spritesName.push_back(L"Image/Tile/TileB.png");
	spritesName.push_back(L"Image/Tile/TileC.png");
	spritesName.push_back(L"Image/Tile/TileD.png");
	spritesName.push_back(L"Image/Tile/TileE.png");
	spritesName.push_back(L"Image/Tile/yukab034d.png");
	spritesName.push_back(L"Image/Tile/tileHouse.png");
	spritesName.push_back(L"Image/Tile/!$object11.png");
	spritesName.push_back(L"Image/Tile/!$object12.png");
	spritesName.push_back(L"Image/Tile/!$wall_eye.png");
	spritesName.push_back(L"Image/Tile/!$wall2.png");
	spritesName.push_back(L"Image/Tile/!$wall3.png");
	spritesName.push_back(L"Image/Tile/!$wall4L.png");
	spritesName.push_back(L"Image/Tile/!$wall4L2.png");
	spritesName.push_back(L"Image/Tile/!$wall5.png");
	spritesName.push_back(L"Image/Tile/TileEdge.png");
	spritesName.push_back(L"Image/Tile/TileEdge2.png");


	
	//-------------------Parallax
	AddSprite(L"Image/Parallax/001-Fog01.png");

	parallaxName.push_back(L"Image/Parallax/001-Fog01.png");

	//------------------UI
	AddSprite(L"Image/UI/ChatPanel.png");
	AddSprite(L"Image/UI/UserInfo_1.png");
	AddSprite(L"Image/UI/UserInfo_2.png");
	AddSprite(L"Image/UI/InventoryPanel.png");
	AddSprite(L"Image/UI/ItemInfoPanel.png");
	AddSprite(L"Image/UI/HealthBar.png");
	AddSprite(L"Image/UI/viviface.png");
	AddSprite(L"Image/UI/OpacityPanel.png");
	AddSprite(L"Image/UI/SelectPanel_01.png");
	AddSprite(L"Image/UI/SelectPanel_02.png");
	AddSprite(L"Image/UI/SelectPanel_03.png");
	AddSprite(L"Image/UI/SelectPanel_04.png");
	AddSprite(L"Image/UI/title.jpg");
	AddSprite(L"Image/UI/GameOver.png");
	AddSprite(L"Image/UI/SaveLoadInfo.png");
	AddSprite(L"Image/UI/SaveLoadPanel.png");
	AddSprite(L"Image/UI/SaveLoadPortrait.png");

	//-----------Obj
	AddSprite(L"Image/Graphics/Obj/HouseDoor.png");
	AddSprite(L"Image/Graphics/Obj/Twinkle.png");
	AddSprite(L"Image/Graphics/Obj/Akari.png");
	AddSprite(L"Image/Graphics/Obj/Message.png");
	AddSprite(L"Image/Graphics/Obj/Boxes.png");
	AddSprite(L"Image/Graphics/Obj/FootPrint.png");
	AddSprite(L"Image/Graphics/Obj/TeddyBucket.png");
	AddSprite(L"Image/Graphics/Obj/AstarTeddy.png");
	AddSprite(L"Image/Graphics/Obj/AstarTeddy_Find.png");
	AddSprite(L"Image/Graphics/Obj/Cat.png");


	spritesName.push_back(L"Image/Graphics/Obj/HouseDoor.png");
	spritesName.push_back(L"Image/Graphics/Obj/Message.png");
	spritesName.push_back(L"Image/Graphics/Obj/Boxes.png");
	spritesName.push_back(L"Image/Tile/DeskTile.png");
	spritesName.push_back(L"Image/Graphics/Obj/FootPrint.png");
	spritesName.push_back(L"Image/Graphics/Obj/TeddyBucket.png");
	spritesName.push_back(L"Image/Graphics/Obj/Cat.png");


}

void ImageManager::Release()
{
	for (auto& elem : sprites)
	{
		SAFE_RELEASE(elem.second);
	}

	mapImages.clear();
}

Sprite* ImageManager::AddSprite(const wchar_t* fileName)
{
	Sprite* sprite = new Sprite;
	sprite->Init(fileName);
	if (FindSprite(fileName) != nullptr)
	{
		return nullptr;
	}

	sprites.emplace(fileName, sprite);

	return sprite;
}



Sprite* ImageManager::FindSprite(const wchar_t* fileName)
{
	auto it = sprites.find(fileName);
	if (it == sprites.end())
	{
		return nullptr;
	}
	return it->second;
}

void ImageManager::DrawColliderRect(int posX, int posY)
{
	POINT* camera = CameraManager::GetInstance()->GetCameraPos();

	int left = posX * TILE_SIZE - TILE_SIZE * (camera->x / TILE_SIZE);
	int right = (posX+1) * TILE_SIZE - TILE_SIZE * (camera->x / TILE_SIZE);
	int top = posY * TILE_SIZE - TILE_SIZE * (camera->y / TILE_SIZE);
	int bottom = (posY+1) * TILE_SIZE - TILE_SIZE * (camera->y / TILE_SIZE);
	
	if ( left >= 0 && right <= TILE_SIZE * MAP_SIZE_X)
	{
		if (top >=0 && bottom<=TILE_SIZE * MAP_SIZE_Y)
		{
			ImageManager::GetInstance()->GetRenderTarget()->DrawRectangle(
				D2D1::RectF(
					left,
					top,
					right,
					bottom
				),
				pBrush, 10.0f
			);
		}
	}
}

void ImageManager::DrawColliderRectPurple(int posX, int posY, int id)
{
	POINT* camera = CameraManager::GetInstance()->GetCameraPos();

	int left = posX * TILE_SIZE - camera->x + 2;
	int right = (posX + 1) * TILE_SIZE - camera->x - 2;
	int top = posY * TILE_SIZE - camera->y + 2;
	int bottom = (posY + 1) * TILE_SIZE - camera->y - 2;

	if (left >= 0 && right <= TILE_SIZE * MAP_SIZE_X)
	{
		if (top >= 0 && bottom <= TILE_SIZE * MAP_SIZE_Y)
		{
			ImageManager::GetInstance()->GetRenderTarget()->DrawRectangle(
				D2D1::RectF(
					left,
					top,
					right,
					bottom
				),
				pBrushPurple, 10.0f
			);

			ImageManager::GetInstance()->GetRenderTarget()->DrawTextW(
				to_wstring(id).c_str(),
				to_wstring(id).size(),
				ImageManager::GetInstance()->GetTextFormat(),
				D2D1::RectF(
					left,
					top,
					right,
					bottom
				),
				ImageManager::GetInstance()->GetBrush()
			);
		}
	}
}

void ImageManager::DrawColliderRectBrown(int posX, int posY, int id)
{
	POINT* camera = CameraManager::GetInstance()->GetCameraPos();

	int left = posX * TILE_SIZE - camera->x + 2;
	int right = (posX + 1) * TILE_SIZE - camera->x - 2;
	int top = posY * TILE_SIZE - camera->y + 2;
	int bottom = (posY + 1) * TILE_SIZE - camera->y - 2;

	if (left >= 0 && right <= TILE_SIZE * MAP_SIZE_X)
	{
		if (top >= 0 && bottom <= TILE_SIZE * MAP_SIZE_Y)
		{
			ImageManager::GetInstance()->GetRenderTarget()->DrawRectangle(
				D2D1::RectF(
					left,
					top,
					right,
					bottom
				),
				pBrushBrown, 10.0f
			);

			ImageManager::GetInstance()->GetRenderTarget()->DrawTextW(
				to_wstring(id).c_str(),
				to_wstring(id).size(),
				ImageManager::GetInstance()->GetTextFormat(),
				D2D1::RectF(
					left,
					top,
					right,
					bottom
				),
				ImageManager::GetInstance()->GetBrush()
			);
		}
	}
}

void ImageManager::DrawColliderRectRed(int posX, int posY, int id)
{
	POINT* camera = CameraManager::GetInstance()->GetCameraPos();

	int left = posX * TILE_SIZE - camera->x +2;
	int right = (posX + 1) * TILE_SIZE -  camera->x -2;
	int top = posY * TILE_SIZE -  camera->y +2;
	int bottom = (posY + 1) * TILE_SIZE -  camera->y -2;

	if (left >= 0 && right <= TILE_SIZE * MAP_SIZE_X)
	{
		if (top >= 0 && bottom <= TILE_SIZE * MAP_SIZE_Y)
		{
			ImageManager::GetInstance()->GetRenderTarget()->DrawRectangle(
				D2D1::RectF(
					left,
					top,
					right,
					bottom
				),
				pBrushRed, 10.0f
			);

			ImageManager::GetInstance()->GetRenderTarget()->DrawTextW(
				to_wstring(id).c_str(),
				to_wstring(id).size(),
				ImageManager::GetInstance()->GetTextFormat(),
				D2D1::RectF(
					left,
					top,
					right,
					bottom
				), 
				ImageManager::GetInstance()->GetBrush()
			);
		}
	}
}

void ImageManager::DrawColliderRectBlue(int posX, int posY, int num)
{
	POINT* camera = CameraManager::GetInstance()->GetCameraPos();

	int left = posX * TILE_SIZE - camera->x + 2;
	int right = (posX + 1) * TILE_SIZE - camera->x - 2;
	int top = posY * TILE_SIZE - camera->y + 2;
	int bottom = (posY + 1) * TILE_SIZE - camera->y - 2;

	if (left >= 0 && right <= TILE_SIZE * MAP_SIZE_X)
	{
		if (top >= 0 && bottom <= TILE_SIZE * MAP_SIZE_Y)
		{
			ImageManager::GetInstance()->GetRenderTarget()->DrawRectangle(
				D2D1::RectF(
					left,
					top,
					right,
					bottom
				),
				pBrushBlue, 10.0f
			);

			ImageManager::GetInstance()->GetRenderTarget()->DrawTextW(
				to_wstring(num).c_str(),
				to_wstring(num).size(),
				ImageManager::GetInstance()->GetTextFormat(),
				D2D1::RectF(
					left,
					top,
					right,
					bottom
				),
				ImageManager::GetInstance()->GetBrush()
			);
		}
	}
}

void ImageManager::DrawColliderRectOrange(int posX, int posY, int id)
{
	POINT* camera = CameraManager::GetInstance()->GetCameraPos();

	int left = posX * TILE_SIZE - camera->x + 2;
	int right = (posX + 1) * TILE_SIZE - camera->x - 2;
	int top = posY * TILE_SIZE - camera->y + 2;
	int bottom = (posY + 1) * TILE_SIZE - camera->y - 2;

	if (left >= 0 && right <= TILE_SIZE * MAP_SIZE_X)
	{
		if (top >= 0 && bottom <= TILE_SIZE * MAP_SIZE_Y)
		{
			ImageManager::GetInstance()->GetRenderTarget()->DrawRectangle(
				D2D1::RectF(
					left,
					top,
					right,
					bottom
				),
				pBrushOrange, 10.0f
			);

			ImageManager::GetInstance()->GetRenderTarget()->DrawTextW(
				to_wstring(id).c_str(),
				to_wstring(id).size(),
				ImageManager::GetInstance()->GetTextFormat(),
				D2D1::RectF(
					left,
					top,
					right,
					bottom
				),
				ImageManager::GetInstance()->GetBrush()
			);
		}
	}
}
