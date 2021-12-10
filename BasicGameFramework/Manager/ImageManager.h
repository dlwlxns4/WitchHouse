#pragma once

#include "../Util/Singleton.h"
#include <Windows.h>
#include "../stdafx.h"

class Image;
class ImageManager : public Singleton<ImageManager>
{
private:
	unordered_map<wstring, Image*> mapImages;


	HWND		_hWnd = {};
	HINSTANCE	_hInstance = {};
	struct IWICImagingFactory* pImagingFactory = nullptr;
	struct ID2D1HwndRenderTarget* pRenderTarget = nullptr;

public:
	ImageManager() noexcept = default;
	~ImageManager() noexcept;

	void Init(HWND hWnd, HINSTANCE hInstance, IWICImagingFactory* pImagingFactory, ID2D1HwndRenderTarget* pRenderTarget);
	void Release();



	Image* AddImage(const wchar_t* fileName, int width, int height,
		bool isTrans = false, COLORREF transColor = NULL);	// ����� �̹����� ����ϴ� ���

	Image* AddImage(const wchar_t* fileName, int width, int height,
		int maxFrameX, int maxFrameY,
		bool isTrans = false, COLORREF transColor = NULL);

	Image* FindImage(const wchar_t* fileName);	// ��ϵ� �̹��� �߿� �ʿ��� �̹����� ã�� ���

	HWND GethWnd() { return _hWnd; }
	HINSTANCE GethInstance() { return _hInstance; }
	void DeleteImage(const char* fileName);	// ����� ����� �̹����� ��� �����ϴ� ���
};

