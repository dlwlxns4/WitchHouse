#ifndef _TWAPI_W01_H_
#define _TWAPI_W01_H_

/*
  이 라이브러리는 Win32와 Direct2D를 사용해서 프로그램을 하는 
  개발자들이 좀더 편하게 프로그램을 개발할 수 있도록 만든 라이브러리 입니다.
  기존에 제가 만들었던 인터페이스 라이브러리와 유사하게 만들었고
  안드로이드용 라이브러리인 TWAPI_A01과 클래스나 함수를 비슷하게 유지하여
  Win32 프로그램과 안드로이드 앱간에 소스 공유를 편하게 할 수 있도록 했습니다.
  이 라이브러리에 대한 문제점을 발견하거나 개선점이 필요하다면 아래의 이 메일로
  의견 남겨주시거나 블로그에 댓글로 남겨주세요.
  이메일 : tipsware@naver.com
  블로그 : http://blog.naver.com/tipsware
  
  라이브러리 생성 : 2017년 11월 2일 ( 김성엽 )
  라이브러리 최종 업데이트 : 2017년 11월 2일 ( 김성엽 )

  그리고 이 라이브러리를 사용하는 사람들이 편하게 사용할 수 있도록 
  필요한 라이브러리를 추가하는 전처리기 코드를 남깁니다.

  #pragma comment(lib, "D2D1.lib")
  #pragma comment(lib, "D3D11.lib")
  #pragma comment(lib, "DXGI.lib")
  #pragma comment(lib, "dxguid.lib")

  #ifdef _DEBUG
      #pragma comment(lib, "DSH_TWAPI_W01.lib")
  #else
      #pragma comment(lib, "RST_TWAPI_W01.lib")
  #endif
*/

#include <Windows.h>

#include <wrl.h>
#include <d3d11.h>
#include <dxgi.h>
#include <DXGI1_2.h>
#include <d2d1effectauthor.h>

using namespace Microsoft::WRL;

// Direct2D를 사용하기 위한 헤더 파일과 라이브러리 파일을 포함시킨다.
#include <d2d1.h>
#include <Wincodec.h>     // IWICImagingFactory를 사용하기 위해서 추가

// Direct2D에서 자주 사용할 네임 스페이스를 생략할 수 있도록 설정한다.
using namespace D2D1;

#define TW_SetIRect(x, l, t, r, b){ x.left = l; x.top = t; x.right = r; x.bottom = b; }
#define TW_SetFRect(x, l, t, r, b){ x.left = (float)(l); x.top = (float)(t); x.right = (float)(r); x.bottom = (float)(b); }
#define TW_PosInRect(pos, l, t, r, b) (l <= pos.x && t <= pos.y && r >= pos.x && b >= pos.y) 

#define TW_SetFPos(pt, x_pos, y_pos){ pt.x = (FLOAT)x_pos; pt.y = (FLOAT)y_pos; }
#define TW_SetFSize(size, x_pos, y_pos){ size.width = (FLOAT)x_pos; size.height = (FLOAT)y_pos; }

#define TW_COLOR(color) (color/256.0f)
#define TW_RGB(color, red, green, blue) { color.r = (FLOAT)(red/255.0); color.g = (FLOAT)(green/255.0); color.b = (FLOAT)(blue/255.0); color.a = 1.0f; }
#define TW_FRGB(color, red, green, blue) { color.r = (FLOAT)red; color.g = (FLOAT)green; color.b = (FLOAT)blue; color.a = 1.0f; }

#define TW_Release(x) { if(x != NULL){ x->Release(); x = NULL; }}

template<class Interface>
inline void TW_IRelease(Interface **ap_interface_object)
{
	if (*ap_interface_object != NULL) {
		(*ap_interface_object)->Release();
		(*ap_interface_object) = NULL;
	}
}

// Direct2D를 구성하는 각종 객체를 생성하는 Factory 객체
extern ID2D1Factory *gp_factory;
// Windows 8.1 이상의 운영체제에서 사용하기 위한 Factory 객체
extern ID2D1Factory1 *gp_factory_ext;
// WIC(Windows Imaging Component)관련 객체를 생성하기 위한 Factory 객체
extern IWICImagingFactory *gp_wic_factory;

class TW_Wnd
{
protected:
	// 이 객체가 관리할 윈도우의 핸들
	HWND mh_wnd;
	// Direct2D에서 윈도우의 클라이언트 영역에 그림을 그릴 객체
	ID2D1HwndRenderTarget *mp_target;

	// Windows 8.1 이상에서 사용 가능한 그림 그리기 기능들!
	ID2D1Device *mp_device;
	ID2D1DeviceContext *mp_dc;
	ID2D1Bitmap1 *mp_dc_bitmap;
	IDXGISwapChain1 *mp_sc;
	DXGI_PRESENT_PARAMETERS m_sc_parameters;
public:
	TW_Wnd();  // 객체 생성자
	virtual ~TW_Wnd();  // 객체 파괴자

    // 객체가 관리하는 mh_wnd 값을 얻거나 새로운 핸들 값을 설정하는 함수
	HWND GetHandle() { return mh_wnd; }
	void SetHandle(HWND ah_wnd) { mh_wnd = ah_wnd; }
	// 윈도우를 생성할 때 사용하는 함수
	void Create(const wchar_t *ap_title_name, int a_x = 50, int a_y = 50,
		int a_width = 500, int a_height = 300, DWORD a_style = WS_OVERLAPPEDWINDOW);
	// 윈도우를 파괴할 때 사용하는 함수
	void DestoryWindow();
	// 윈도우를 갱신을 대기하지 않고 즉시 갱신하도록 하는 함수
	void UpdateWindow();
	// 윈도우를 화면에 어떻게 출력시킬 것인지를 결정하는 함수
	void ShowWindow(int a_show_type = SW_SHOW);
	// 윈도우의 클라이언트 영역을 기준으로 윈도우 크기를 변경하는 함수
	void ResizeWindow(int a_width, int a_height);
	// 윈도우 화면을 무효화 시켜서 WM_PAINT 메시지를 발생시키는 함수
	void Invalidate();
	// 타이머를 등록하는 함수
	void SetTimer(UINT a_timer_id, UINT a_elapse_time);
	// 타이머를 제거하는 함수
	void KillTimer(UINT a_timer_id);

	// WM_PAINT 메시지가 발생할 때 작업할 함수. 이 함수는 파생 클래스에서 대부분 재정의 함
	virtual void OnPaint();
	// WM_CREATE 메시지가 발생할 때 작업할 함수.
	virtual int OnCreate(CREATESTRUCT *ap_create_info);
	// WM_TIMER 메시지가 발생할 때 작업할 함수.
	virtual void OnTimer(UINT a_timer_id);
	// WM_DESTROY 메시지가 발생할 때 작업할 함수.
	virtual void OnDestroy();
};

class TW_WinApp
{
protected:
	TW_Wnd *mp_wnd;    // 메인 윈도우 객체의 주소를 저장
	HINSTANCE mh_instance;  // WinMain에 전달되는 첫 번째 인자값 저장
	wchar_t m_class_name[32]; // '윈도우 클래스' 이름을 저장할 변수
	// WinMain 함수의 최종 반환값을 WM_QUIT메시지의 wParam 값으로 사용하기
	// 위해서 이 값을 저장할 변수
	int m_exit_state;

public:
	TW_WinApp(HINSTANCE ah_instance, const wchar_t *ap_class_name, int a_use_ext_direct2d = 0);
	virtual ~TW_WinApp();

	int GetExitState() { return m_exit_state; }
	const wchar_t *GetWindowClassName() { return m_class_name; }
	TW_Wnd *GetMainWindow() { return mp_wnd; }
	HINSTANCE GetInstanceHandle() { return mh_instance; }

	virtual void InitApplication();
	virtual void InitInstance();
	virtual void Run();
	virtual void ExitInstance();
	virtual void ExitApplication();

	virtual int NormalProcess();
};

extern TW_WinApp *gp_app;

void TWAPI_CreateWIC();
int TWAPI_MakeD2D1_Bitmap(IWICBitmapFrameDecode *ap_image_frame, ID2D1DeviceContext *ap_context, ID2D1Bitmap **ap_bitmap);
int TWAPI_MakeD2D1_Bitmap(IWICBitmapFrameDecode *ap_image_frame, ID2D1HwndRenderTarget *ap_target, ID2D1Bitmap **ap_bitmap);
int TWAPI_LoadImage(ID2D1DeviceContext *ap_context, ID2D1Bitmap **ap_bitmap, const wchar_t *ap_path);
int TWAPI_LoadImage(ID2D1HwndRenderTarget *ap_target, ID2D1Bitmap **ap_bitmap, const wchar_t *ap_path);
void TWAPI_CreateExtD2D(HWND ah_wnd, ID2D1Device **ap_graphic_device, ID2D1DeviceContext **ap_device_context, ID2D1Bitmap1 **ap_render_bitmap, IDXGISwapChain1 **ap_swap_chain);

#endif