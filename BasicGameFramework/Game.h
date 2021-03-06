#pragma once

#include "Util/Type.h"

class ID2D1HwndRenderTarget;
class IWICImagingFactory;
class ID2D1SolidColorBrush;
class IDWriteFactory;
class IDWriteTextFormat;
class Game
{
	enum { MAX_LOADSTRING = 100 };

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
	~Game() noexcept;

	bool				Init(HINSTANCE hInst);
	INT32				Run();

private:
	ATOM				registerClass();

	void				processInput();
	void				update();
	void				render();
private:
	HINSTANCE			_hInst = {};
	HWND				_hWnd = {};
	WCHAR				_title[MAX_LOADSTRING] = {};
	WCHAR				_windowName[MAX_LOADSTRING] = {};
	HDC					_hDC = {};
	HDC					_backDC = {};
	HBITMAP				_backBitmap = {};


	Resolution			_res = { 1440, 720 };

	ID2D1SolidColorBrush* pBrush = nullptr;
	IWICImagingFactory* pImagingFactory = nullptr;
	ID2D1HwndRenderTarget* pRenderTarget = nullptr;
	IDWriteFactory* pDWriteFactory = nullptr;
	IDWriteTextFormat* pTextFormat = nullptr;
};

