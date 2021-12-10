#include "ImageManager.h"
#include <filesystem>
#include "../ImageHelper.h"

//D2D
#include <d2d1.h>			
#include <wincodec.h>


#include <iostream>

#define PLAYER_SIZE_X 32
#define PLAYER_SIZE_Y 48

ImageManager::~ImageManager() noexcept
{
	Release();
}

void ImageManager::Init(HWND hWnd, HINSTANCE hInstance, IWICImagingFactory* pImagingFactory, ID2D1HwndRenderTarget* pRenderTarget)
{	
	this->_hWnd = hWnd;
	this->_hInstance = hInstance;
	this->pImagingFactory = pImagingFactory;
	this->pRenderTarget = pRenderTarget;


	wstring wCharacterPath = L"Image/Character/$vivi.bmp";
	string characterPath = "Image/Character/$vivi.bmp";
	Mat charImg = OpencvHelper::ReadImage(characterPath.c_str(), 1);
	
	
	AddImage(wCharacterPath.c_str(), charImg.cols, charImg.rows,  charImg.cols / PLAYER_SIZE_X, charImg.rows / PLAYER_SIZE_Y, true, RGB(255, 0, 255));


	//for (auto& p : filesystem::directory_iterator(dir2))
	//{
	//	string inFolder = p.path().string() + '/';
	//	for (auto& p2 : filesystem::directory_iterator(inFolder))
	//	{
	//		//mapName.push_back(p2.path().string());
	//		//cout << p2.path().string() << endl;

	//		Mat img = OpencvHelper::ReadImage(p2.path().string(), 1);
	//		vecSampleImage.push_back(ImageManager::GetSingleton()->AddImage(p2.path().string().c_str(), img.cols, img.rows, img.cols / TILE_SIZE, img.rows / TILE_SIZE, true, RGB(255, 0, 255)));
	//	}
	//}
}

void ImageManager::Release()
{
	for (auto& elem : mapImages)
	{
		SAFE_RELEASE(elem.second);
	}

	mapImages.clear();
}

Image* ImageManager::AddImage(const wchar_t* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	return nullptr;
}

Image* ImageManager::AddImage(const wchar_t* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	if (FindImage(fileName))
	{
		return nullptr;
	}

	Image* img = new Image;
	if (FAILED(img->Init(fileName, width, height, maxFrameX,
		maxFrameY, isTrans, transColor)))
	{
		SAFE_RELEASE(img);
		return nullptr;
	}

	mapImages.insert(make_pair(fileName, img));
	cout << fileName << "의 이미지가 추가되었습니다." << endl;

	return img;
}

Image* ImageManager::FindImage(const wchar_t* fileName)
{
	unordered_map<wstring, Image*>::iterator it = mapImages.find(fileName);
	if (it == mapImages.end())
	{
		cout << fileName << "을 찾지못하였습니다" << endl;
		return nullptr;
	}

	return it->second;
}

void ImageManager::DeleteImage(const char* fileName)
{
}
