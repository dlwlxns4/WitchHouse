#include "stdafx.h"
#include "Game.h"

#include "Util/Timer.h"
#include "Manager/SceneManager.h"
#include "Manager/ImageManager.h"


//--------------------------d2d

#include <d2d1.h>
// imaingFactory 생성을 위한 include
#include <wincodec.h>

// 전처리문

#pragma comment(lib, "D2D1.lib")

#include "Util/Sprite.h"


ID2D1SolidColorBrush* pBrush = nullptr;
ID2D1Factory* pFactory = nullptr;
ID2D1Bitmap* pBitmap = nullptr;
//-------------------------------------------------d2


LRESULT Game::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}

Game::~Game() noexcept
{
	DeleteObject(_backBitmap);
	DeleteDC(_backDC);
	ReleaseDC(_hWnd, _hDC);
}

bool Game::Init(HINSTANCE hInst)
{
	LoadStringW(hInst, IDS_APP_TITLE, _title, MAX_LOADSTRING);
	LoadStringW(hInst, IDC_BASICGAMEFRAMEWORK, _windowName, MAX_LOADSTRING);

	_hInst = hInst;

	if (0 == registerClass())
	{
		return false;
	}

	_hWnd = CreateWindowW(_windowName, _title, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInst, nullptr);

	if (_hWnd == NULL)
	{
		return false;
	}


	RECT cr = { 0, 0, _res.Width, _res.Height };
	AdjustWindowRect(&cr, WS_OVERLAPPEDWINDOW, FALSE);
	SetWindowPos(_hWnd, HWND_TOPMOST, 100, 100, cr.right - cr.left, cr.bottom - cr.top, SWP_NOMOVE | SWP_NOZORDER);

	ShowWindow(_hWnd, SW_SHOW);
	UpdateWindow(_hWnd);

	_hDC = GetDC(_hWnd);
	_backDC = CreateCompatibleDC(_hDC);
	_backBitmap = CreateCompatibleBitmap(_hDC, _res.Width, _res.Height);
	SelectObject(_backDC, _backBitmap);


	//-------------------------d2d
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);

	pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(_hWnd, D2D1::SizeU(cr.right - cr.left, cr.bottom - cr.top)),
		&pRenderTarget
	);

	CoInitialize(nullptr);
	CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pImagingFactory));



	//--------------------------d2d


	Input::Init(_hWnd);

	ImageManager::GetInstance()->Init(_hWnd, _hInst, pImagingFactory, pRenderTarget);
	SceneManager::GetInstance()->Init();

	return true;
}

INT32 Game::Run()
{
	Timer::Init();

	MSG msg;

	while (TRUE)
	{
		if (PeekMessage(&msg, nullptr, NULL, NULL, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (SceneManager::GetInstance()->IsSetNextScene())
			{
				SceneManager::GetInstance()->ChangeScene();
			}

			if (Timer::CanUpdate())
			{
				processInput();
				update();
				render();
			}
		}
	}

	return static_cast<INT32>(msg.wParam);
}

ATOM Game::registerClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = _hInst;
	wcex.hIcon = LoadIcon(_hInst, MAKEINTRESOURCE(IDI_BASICGAMEFRAMEWORK));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = _windowName;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

void Game::processInput()
{
	Input::Update();
}

void Game::update()
{
	SceneManager::GetInstance()->Update();
}


void Game::render()
{


	//PatBlt(_backDC, 0, 0, _res.Width, _res.Height, WHITENESS);
	//pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(100, 100, 0, 1), &pBrush);

	SceneManager::GetInstance()->Render(_backDC);


	//BitBlt(_hDC, 0, 0, _res.Width, _res.Height,
	//	_backDC, 0, 0, SRCCOPY);
	//

	////---------------d2d
	//pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(100, 100, 0, 1), &pBrush);
	//pRenderTarget->BeginDraw();

	//pRenderTarget->DrawRectangle(D2D1::RectF(100, 100, 200, 200), pBrush, 10);


	//if (pBitmap)
	//{
	//	D2D1_SIZE_F imageSize = pBitmap->GetSize();
	//	int frameX = 3;
	//	int frameY = 4;
	//	D2D1_SIZE_F imageOneFrameSize = D2D1::SizeF(imageSize.width / frameX, imageSize.height / frameY);
	//	static int curFrameX = 0;
	//	++curFrameX;

	//	if (curFrameX >= frameX) { curFrameX = 0; }
	//	
	//	int curFrameY = 0;


	//	pRenderTarget->DrawBitmap(pBitmap,
	//		D2D1::RectF(50, 50, 50+imageOneFrameSize.width,  50+imageOneFrameSize.height), 1,
	//		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
	//		D2D1::RectF(curFrameX * imageOneFrameSize.width, curFrameY * imageOneFrameSize.height,
	//			(curFrameX + 1) * imageOneFrameSize.width, (curFrameY + 1) * imageOneFrameSize.height));


	//	//---------------d2d

	//}
	//pRenderTarget->EndDraw();

}