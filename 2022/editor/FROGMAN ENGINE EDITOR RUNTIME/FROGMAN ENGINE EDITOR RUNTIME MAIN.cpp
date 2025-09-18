// FROGMAN ENGINE EDITOR RUNTIME MAIN.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "FROGMAN ENGINE EDITOR RUNTIME.h"

#define _DEPRECATED_PARAMETER_
#define MAX_LOADSTRING 100

// http://developer.download.nvidia.com/devzone/devcenter/gamegraphics/files/OptimusRenderingPolicies.pdf
// The following line is to favor the high performance NVIDIA GPU if there are multiple GPUs
// Has to be .exe module to be correctly detected.
extern "C" { _declspec( dllexport ) DWORD NvOptimusEnablement = 0x00000001; }

// And the AMD equivalent
// Also has to be .exe module to be correctly detected.
extern "C" { _declspec( dllexport ) DWORD AmdPowerXpressRequestHighPerformance = 0x00000001; }

// 전역 변수:
HINSTANCE g_hInst;                                // 현재 인스턴스입니다.
WCHAR g_szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR g_szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.


// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance_p,
                      _In_opt_ _DEPRECATED_PARAMETER_ HINSTANCE h_prev_instance_p,
                      _In_ LPWSTR lpCmdLine_p, _In_ int nCmdShow_p
                     )
{

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance_p, IDS_APP_TITLE, /* edit project title name here */ g_szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance_p, IDC_FROGMANENGINEEDITORRUNTIME, g_szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance_p);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance_p, nCmdShow_p))
    {
        return FALSE;
    }

    // load shortcut key list
    HACCEL l_hAccelTable = LoadAccelerators(hInstance_p, MAKEINTRESOURCE(IDC_FROGMANENGINEEDITORRUNTIME));

    MSG l_msg;

    // 기본 메시지 루프입니다:
    // process escapes the while loop below if msg.message == WM_QUIT returns false.
    while (GetMessage(&l_msg, nullptr, 0, 0))
    {
        // is one of the keys in the list pressed?
        if (!TranslateAccelerator(l_msg.hwnd, l_hAccelTable, &l_msg))
        {
            TranslateMessage(&l_msg);
            DispatchMessage(&l_msg);
        }
    }

    return (int) l_msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW l_wcex;

    l_wcex.cbSize = sizeof(WNDCLASSEX);

    l_wcex.style          = CS_HREDRAW | CS_VREDRAW;
    l_wcex.lpfnWndProc    = WndProc;
    l_wcex.cbClsExtra     = 0;
    l_wcex.cbWndExtra     = 0;
    l_wcex.hInstance      = hInstance;
    l_wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FROGMANENGINEEDITORRUNTIME));
    l_wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    l_wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    l_wcex.lpszMenuName   = nullptr; /*MAKEINTRESOURCEW(IDC_FROGMANENGINEEDITORRUNTIME); */// it excludes menu-bar if nullptr is assigned
    l_wcex.lpszClassName  = g_szWindowClass;
    l_wcex.hIconSm        = LoadIcon(l_wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&l_wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance_p, int nCmdShow_p)
{
   g_hInst = hInstance_p; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND l_hWnd = CreateWindowW(g_szWindowClass, /* edit project title name here */ g_szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance_p, nullptr);

   if (!l_hWnd)
   {
      return FALSE;
   }

   ShowWindow(l_hWnd, nCmdShow_p);
   UpdateWindow(l_hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd_p, UINT message_p, WPARAM wParam_p, LPARAM lParam_p)
{
    switch (message_p)
    {
    case WM_COMMAND:
        {
            int l_wmId = LOWORD(wParam_p);
            // 메뉴 선택을 구문 분석합니다:
            switch (l_wmId)
            {
            case IDM_ABOUT:
                DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd_p, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd_p);
                break;
            default:
                return DefWindowProc(hWnd_p, message_p, wParam_p, lParam_p);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT l_ps;
            HDC l_hdc = BeginPaint(hWnd_p, &l_ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd_p, &l_ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd_p, message_p, wParam_p, lParam_p);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlgl_p, UINT message_p, WPARAM wParam_p, LPARAM lParam_p)
{
    UNREFERENCED_PARAMETER(lParam_p);
    switch (message_p)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam_p) == IDOK || LOWORD(wParam_p) == IDCANCEL)
        {
            EndDialog(hDlgl_p, LOWORD(wParam_p));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
