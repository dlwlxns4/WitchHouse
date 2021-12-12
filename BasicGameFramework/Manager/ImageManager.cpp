#include "ImageManager.h"


//D2D
#include <d2d1.h>			
#include <wincodec.h>

#include <dwrite.h>

#include "../Util/Sprite.h"

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
	AddSprite(L"Image/Tile/yukab034d.png");

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


	//-------------------Parallax

	AddSprite(L"Image/Parallax/001-Fog01.png");
								 
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

//Image* ImageManager::AddImage(const wchar_t* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
//{
//	if (FindImage(fileName))
//	{
//		return nullptr;
//	}
//
//	Image* img = new Image;
//	if (FAILED(img->Init(fileName, width, height, maxFrameX,
//		maxFrameY, isTrans, transColor)))
//	{
//		SAFE_RELEASE(img);
//		return nullptr;
//	}
//
//	mapImages.insert(make_pair(fileName, img));
//	cout << fileName << "의 이미지가 추가되었습니다." << endl;
//
//	return img;
//}
//
//Image* ImageManager::FindImage(const wchar_t* fileName)
//{
//	unordered_map<wstring, Image*>::iterator it = mapImages.find(fileName);
//	if (it == mapImages.end())
//	{
//		cout << fileName << "을 찾지못하였습니다" << endl;
//		return nullptr;
//	}
//
//	return it->second;
//}
//
//void ImageManager::DeleteImage(const char* fileName)
//{
//}
