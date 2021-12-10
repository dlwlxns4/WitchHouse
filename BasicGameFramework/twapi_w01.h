#ifndef _TWAPI_W01_H_
#define _TWAPI_W01_H_

/*
  �� ���̺귯���� Win32�� Direct2D�� ����ؼ� ���α׷��� �ϴ� 
  �����ڵ��� ���� ���ϰ� ���α׷��� ������ �� �ֵ��� ���� ���̺귯�� �Դϴ�.
  ������ ���� ������� �������̽� ���̺귯���� �����ϰ� �������
  �ȵ���̵�� ���̺귯���� TWAPI_A01�� Ŭ������ �Լ��� ����ϰ� �����Ͽ�
  Win32 ���α׷��� �ȵ���̵� �۰��� �ҽ� ������ ���ϰ� �� �� �ֵ��� �߽��ϴ�.
  �� ���̺귯���� ���� �������� �߰��ϰų� �������� �ʿ��ϴٸ� �Ʒ��� �� ���Ϸ�
  �ǰ� �����ֽðų� ��α׿� ��۷� �����ּ���.
  �̸��� : tipsware@naver.com
  ��α� : http://blog.naver.com/tipsware
  
  ���̺귯�� ���� : 2017�� 11�� 2�� ( �輺�� )
  ���̺귯�� ���� ������Ʈ : 2017�� 11�� 2�� ( �輺�� )

  �׸��� �� ���̺귯���� ����ϴ� ������� ���ϰ� ����� �� �ֵ��� 
  �ʿ��� ���̺귯���� �߰��ϴ� ��ó���� �ڵ带 ����ϴ�.

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

// Direct2D�� ����ϱ� ���� ��� ���ϰ� ���̺귯�� ������ ���Խ�Ų��.
#include <d2d1.h>
#include <Wincodec.h>     // IWICImagingFactory�� ����ϱ� ���ؼ� �߰�

// Direct2D���� ���� ����� ���� �����̽��� ������ �� �ֵ��� �����Ѵ�.
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

// Direct2D�� �����ϴ� ���� ��ü�� �����ϴ� Factory ��ü
extern ID2D1Factory *gp_factory;
// Windows 8.1 �̻��� �ü������ ����ϱ� ���� Factory ��ü
extern ID2D1Factory1 *gp_factory_ext;
// WIC(Windows Imaging Component)���� ��ü�� �����ϱ� ���� Factory ��ü
extern IWICImagingFactory *gp_wic_factory;

class TW_Wnd
{
protected:
	// �� ��ü�� ������ �������� �ڵ�
	HWND mh_wnd;
	// Direct2D���� �������� Ŭ���̾�Ʈ ������ �׸��� �׸� ��ü
	ID2D1HwndRenderTarget *mp_target;

	// Windows 8.1 �̻󿡼� ��� ������ �׸� �׸��� ��ɵ�!
	ID2D1Device *mp_device;
	ID2D1DeviceContext *mp_dc;
	ID2D1Bitmap1 *mp_dc_bitmap;
	IDXGISwapChain1 *mp_sc;
	DXGI_PRESENT_PARAMETERS m_sc_parameters;
public:
	TW_Wnd();  // ��ü ������
	virtual ~TW_Wnd();  // ��ü �ı���

    // ��ü�� �����ϴ� mh_wnd ���� ��ų� ���ο� �ڵ� ���� �����ϴ� �Լ�
	HWND GetHandle() { return mh_wnd; }
	void SetHandle(HWND ah_wnd) { mh_wnd = ah_wnd; }
	// �����츦 ������ �� ����ϴ� �Լ�
	void Create(const wchar_t *ap_title_name, int a_x = 50, int a_y = 50,
		int a_width = 500, int a_height = 300, DWORD a_style = WS_OVERLAPPEDWINDOW);
	// �����츦 �ı��� �� ����ϴ� �Լ�
	void DestoryWindow();
	// �����츦 ������ ������� �ʰ� ��� �����ϵ��� �ϴ� �Լ�
	void UpdateWindow();
	// �����츦 ȭ�鿡 ��� ��½�ų �������� �����ϴ� �Լ�
	void ShowWindow(int a_show_type = SW_SHOW);
	// �������� Ŭ���̾�Ʈ ������ �������� ������ ũ�⸦ �����ϴ� �Լ�
	void ResizeWindow(int a_width, int a_height);
	// ������ ȭ���� ��ȿȭ ���Ѽ� WM_PAINT �޽����� �߻���Ű�� �Լ�
	void Invalidate();
	// Ÿ�̸Ӹ� ����ϴ� �Լ�
	void SetTimer(UINT a_timer_id, UINT a_elapse_time);
	// Ÿ�̸Ӹ� �����ϴ� �Լ�
	void KillTimer(UINT a_timer_id);

	// WM_PAINT �޽����� �߻��� �� �۾��� �Լ�. �� �Լ��� �Ļ� Ŭ�������� ��κ� ������ ��
	virtual void OnPaint();
	// WM_CREATE �޽����� �߻��� �� �۾��� �Լ�.
	virtual int OnCreate(CREATESTRUCT *ap_create_info);
	// WM_TIMER �޽����� �߻��� �� �۾��� �Լ�.
	virtual void OnTimer(UINT a_timer_id);
	// WM_DESTROY �޽����� �߻��� �� �۾��� �Լ�.
	virtual void OnDestroy();
};

class TW_WinApp
{
protected:
	TW_Wnd *mp_wnd;    // ���� ������ ��ü�� �ּҸ� ����
	HINSTANCE mh_instance;  // WinMain�� ���޵Ǵ� ù ��° ���ڰ� ����
	wchar_t m_class_name[32]; // '������ Ŭ����' �̸��� ������ ����
	// WinMain �Լ��� ���� ��ȯ���� WM_QUIT�޽����� wParam ������ ����ϱ�
	// ���ؼ� �� ���� ������ ����
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