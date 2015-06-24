// TestWebBrowser.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "TestWebBrowser.h"
#include "KeepAlive.h"
#include "Window.h"
#include "Manager.h"
#include "WindowDescription.h"
#include "WindowManager.h"
#include "Geometry.h"
#include "PushButton.h"
 #include "WebBrowser.h"
#include "ximage/ximage.h"
using namespace wui;

#define MAX_LOADSTRING 100

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

Window* pWin;
Manager* pMgr;
WindowManager* pWinmgr;
TopLevelDescription* pDesc;
PushButton *pBtn;
wui::WebBrowser *pWeb;
CxImage imgBack;
CxImage imgBtn;



RECT rect,rcClient;
Rect rc;


// �˴���ģ���а����ĺ�����ǰ������:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void OnRender(XGraphics &graphic, const Rect &rcDraw);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TESTWEBBROWSER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTWEBBROWSER));

	// ����Ϣѭ��:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			bool bTrans = false;
			if (pWeb)
			{
				bTrans = pWeb->OnTranslateAccelerator(msg);
				if (bTrans)
					OutputDebugString("dd");
			}	
			if (!bTrans)
				DispatchMessage(&msg);
			KeepAlive::Process();
		}
	}

	return (int) msg.wParam;
}



//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
//  ע��:
//
//    ����ϣ��
//    �˴�������ӵ� Windows 95 �еġ�RegisterClassEx��
//    ����֮ǰ�� Win32 ϵͳ����ʱ������Ҫ�˺��������÷������ô˺���ʮ����Ҫ��
//    ����Ӧ�ó���Ϳ��Ի�ù�����
//    ����ʽ��ȷ�ġ�Сͼ�ꡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TESTWEBBROWSER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TESTWEBBROWSER);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
		{
			::CoInitialize(NULL);

			pMgr = new Manager();
			pWinmgr = new WindowManager();
			pMgr->SetWindowManager(pWinmgr);
			GetClientRect(hWnd,	&rcClient);
			pDesc = new TopLevelDescription();
			pDesc->SetOwnerHandle(hWnd);
			pDesc->SetChildWindow(true);
			pDesc->SetPosition(Rect(rcClient.left+10, rcClient.top+ 10, rcClient.right-rcClient.left-20,rcClient.bottom-rcClient.top-20),true);
			pWin = new Window(pMgr, *pDesc);
			Rect rect = Rect(rcClient.left, rcClient.top, rcClient.right-rcClient.left,rcClient.bottom-rcClient.top);
			pWin->SetWindowGeometry(Rect(rcClient.left+10, rcClient.top+10, rcClient.right-rcClient.left-20,rcClient.bottom-rcClient.top-20));
			imgBack.LoadResource(FindResource(NULL,MAKEINTRESOURCE(IDB_BACK),_T("PNG")),CXIMAGE_FORMAT_PNG);
			pWin->sigRender().connect(&OnRender);
			pBtn = new PushButton(pWin);
			pBtn->SetText("ffdafdsaf");
			imgBtn.LoadResource(FindResource(NULL,MAKEINTRESOURCE(IDB_BTN),_T("PNG")),CXIMAGE_FORMAT_PNG);
			pBtn->SetBkImage(&imgBtn, PushButton::BTN_IMAGE_4STATE);
			pBtn->SetVisible();
			Rect rcBtn = pBtn->GetGeometry();
			rcBtn.Offset(100,0);
			pBtn->SetGeometry(rcBtn);
// 
 			pWeb = new wui::WebBrowser(pWin);
 			pWeb->SetGeometry(Rect(100,100,800,600));
 			pWeb->SetVisible();
 			pWeb->Navigate2("http://statics.qipai007.com/ad/226001.html?subsiteId=0");
 

			// 			pItemwindow = new ItemsDisplayWindow(pWin,rect);
		}
		break;	
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: �ڴ���������ͼ����...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		::CoUninitialize();
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void OnRender(XGraphics &graphic, const Rect &rcDraw)
{
	graphic.DrawImage(&imgBack,0,0,imgBack.GetWidth(),imgBack.GetHeight(),&rcDraw.GetRectStruct());
}