#include "stdafx.h"
#include "Game.h"

#include "Util/Timer.h"
#include "Manager/SceneManager.h"
#include "Manager/ImageManager.h"
#include "Manager/TalkManager.h"
#include "Manager/CameraManager.h"
#include "Manager/GameManager.h"

//--------------------------d2d

#include <d2d1.h>
// imaingFactory 생성을 위한 include
#include <wincodec.h>
#include <dwrite.h>

// 전처리문

#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "Dwrite")

#include "Util/Sprite.h"


#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

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


	//RECT cr = { 0, 0, _res.Width, _res.Height };
	RECT cr = { 0, 0, 32*17, 32*13 };
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

	GetClientRect(_hWnd, &cr);

	pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(_hWnd, D2D1::SizeU(cr.right - cr.left, cr.bottom - cr.top)),
		&pRenderTarget
	);

	CoInitialize(nullptr);
	CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pImagingFactory));

	pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 1), &pBrush);

	HRESULT hr =DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&pDWriteFactory)
	);

	pDWriteFactory->CreateTextFormat(
		L"휴먼나무",                // Font family name.
		NULL,                       // Font collection (NULL sets it to use the system font collection).
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		15.0f,
		L"en-us",
		&pTextFormat
	);

	//--------------------------d2d
	//_CrtSetBreakAlloc(312);

	Input::Init(_hWnd);

	TalkManager::GetInstance()->Init();
	ImageManager::GetInstance()->Init(_hWnd, _hInst, pImagingFactory, pRenderTarget, pBrush, pTextFormat);
	SceneManager::GetInstance()->Init();
	CameraManager::GetInstance()->Init();
	GameManager::GetInstance()->Init();

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
	if (SceneManager::GetInstance()->IsMainScene())
	{
		CameraManager::GetInstance()->Update();
	}
}


void Game::render()
{
	SceneManager::GetInstance()->Render(_backDC);
}