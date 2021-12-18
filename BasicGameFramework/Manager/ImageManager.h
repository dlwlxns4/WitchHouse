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

	vector<wstring>			spritesName = {};
	vector<wstring>			parallaxName = {};

	HWND					_hWnd = {};
	HINSTANCE				_hInstance = {};
	IWICImagingFactory*		pImagingFactory = nullptr;
	ID2D1HwndRenderTarget*	pRenderTarget = nullptr;
	ID2D1SolidColorBrush*	pBrush = nullptr;
	ID2D1SolidColorBrush*	pBrushRed = nullptr;
	ID2D1SolidColorBrush*	pBrushWhite = nullptr;
	ID2D1SolidColorBrush*	pBrushBlue = nullptr;
	ID2D1SolidColorBrush*	pBrushOrange = nullptr;

	IDWriteTextFormat*		pTextFormat = nullptr;
public:
	ImageManager() noexcept = default;
	~ImageManager() noexcept;

	void Init(HWND hWnd, HINSTANCE hInstance, IWICImagingFactory* pImagingFactory, ID2D1HwndRenderTarget* pRenderTarget, ID2D1SolidColorBrush* pBrush, IDWriteTextFormat* pTextFormat);
	void Release();

	Sprite* AddSprite(const wchar_t* fileName);
	Sprite* FindSprite(const wchar_t* fileName);



	HWND GethWnd() { return _hWnd; }
	HINSTANCE GethInstance() { return _hInstance; }
	IWICImagingFactory* GetImageingFactory() { return pImagingFactory; }
	ID2D1HwndRenderTarget* GetRenderTarget() { return pRenderTarget; }
	ID2D1SolidColorBrush* GetBrush() { return pBrush; }
	ID2D1SolidColorBrush* GetBrushWhite() { return pBrushWhite; }
	ID2D1SolidColorBrush* GetBrushBlue() { return pBrushBlue; }
	ID2D1SolidColorBrush* GetBrushOrange() { return pBrushOrange; }
	IDWriteTextFormat* GetTextFormat() { return pTextFormat; }
	
	wstring GetSpriteName(int index) { return spritesName[index]; }
	int GetSpritesNameVecSize() { return spritesName.size(); }
	void DrawColliderRect(int posX, int posY);
	void DrawColliderRectRed(int posX, int posY, int id);
	void DrawColliderRectBlue(int posX, int posY, int num);
	void DrawColliderRectOrange(int posX, int posY, int id);
};

