#pragma once

#include "../Util/Singleton.h"
#include <Windows.h>
#include "../stdafx.h"

class Image;
class Sprite;
class IWICImagingFactory;
class ID2D1HwndRenderTarget;
class ID2D1SolidColorBrush;
class IDWriteTextFormat;
class ImageManager : public Singleton<ImageManager>
{
private:
	unordered_map<wstring, Image*> mapImages = {};
	unordered_map<wstring, Sprite*> sprites = {};

	vector<wstring> spritesName = {};
	
	HWND		_hWnd = {};
	HINSTANCE	_hInstance = {};
	IWICImagingFactory* pImagingFactory = nullptr;
	ID2D1HwndRenderTarget* pRenderTarget = nullptr;
	ID2D1SolidColorBrush* pBrush = nullptr;
	IDWriteTextFormat* pTextFormat = nullptr;
public:
	ImageManager() noexcept = default;
	~ImageManager() noexcept;

	void Init(HWND hWnd, HINSTANCE hInstance, IWICImagingFactory* pImagingFactory, ID2D1HwndRenderTarget* pRenderTarget, ID2D1SolidColorBrush* pBrush, IDWriteTextFormat* pTextFormat);
	void Release();

	Sprite* AddSprite(const wchar_t* fileName);
	Sprite* FindSprite(const wchar_t* fileName);

	Image* AddImage(const wchar_t* fileName, int width, int height,
		bool isTrans = false, COLORREF transColor = NULL);	// 사용할 이미지를 등록하는 기능

	Image* AddImage(const wchar_t* fileName, int width, int height,
		int maxFrameX, int maxFrameY,
		bool isTrans = false, COLORREF transColor = NULL);

	Image* FindImage(const wchar_t* fileName);	// 등록된 이미지 중에 필요한 이미지를 찾는 기능

	HWND GethWnd() { return _hWnd; }
	HINSTANCE GethInstance() { return _hInstance; }
	void DeleteImage(const char* fileName);	// 사용이 종료된 이미지를 등록 해제하는 기능
	IWICImagingFactory* GetImageingFactory() { return pImagingFactory; }
	ID2D1HwndRenderTarget* GetRenderTarget() { return pRenderTarget; }
	ID2D1SolidColorBrush* GetBrush() { return pBrush; }
	IDWriteTextFormat* GetTextFormat() { return pTextFormat; }
	
	wstring GetSpriteName(int index) { return spritesName[index]; }
	int GetSpritesNameVecSize() { return spritesName.size(); }
	void DrawColliderRect(int posX, int posY);
};

