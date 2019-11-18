#include "FengYeWallpaper.h"
#include "VLCPlayer.h"
#include <vlc/vlc.h>

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK EnumWindowProcFindDesktopWindow(HWND hTop, LPARAM lparam);

VLC::Player VLCplayer;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine,  _In_ int  nCmdShow)
{
	//注册窗口类
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"DX9 Px", NULL };
	::RegisterClassEx(&wc);

	//创建窗口
	HWND hwnd = ::CreateWindow(wc.lpszClassName, L"D3DX9", WS_OVERLAPPEDWINDOW | WS_POPUP | WS_EX_LAYERED, 0, 0, 0, 0, NULL, NULL, wc.hInstance, NULL);

	//设置窗口无边框
	DWORD dwNewStyle = WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	SetWindowLong(hwnd, GWL_STYLE, dwNewStyle);//设置成新的样式   
	DWORD dwNewExStyle = WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR;
	SetWindowLong(hwnd, GWL_EXSTYLE, dwNewExStyle);//设置新的扩展样式   
	SetWindowPos(hwnd,0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);//窗口位置和大小保持原来不变！  

	//获取桌面窗口句柄
	HWND Hwnd = FindWindow(L"Progman",L"Program Manager");

	//发送分屏消息
	DWORD_PTR lpdwResult = 0;
	SendMessageTimeout(Hwnd, 0x052C, NULL, NULL, SMTO_NORMAL, 1000, &lpdwResult);

	//关闭多出来的work窗口
	EnumWindows(EnumWindowProcFindDesktopWindow,0);

	//嵌入桌面
	SetParent(hwnd,Hwnd);

	//设置窗口最大化
	SendMessage(hwnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);

	//显示窗口
	ShowWindow(hwnd,SW_SHOW);

	//初始化播放器
	VLCplayer.InitPlayer();

	//开始播放
	VLCplayer.StartPlayer(hwnd);


	MSG msg;
	ZeroMemory(&msg,sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
			continue;
		}
	}
}


LRESULT CALLBACK    WndProc(HWND hwnd, UINT msg, WPARAM wParam , LPARAM lParam)
{
switch (msg)
	{
	case  WM_DESTROY:
		::PostQuitMessage(0);
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		// TODO: 在此处添加使用 hdc 的任何绘图代码...
		EndPaint(hwnd, &ps);
	}
	break;
	}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}


BOOL CALLBACK EnumWindowProcFindDesktopWindow(HWND hTop, LPARAM lparam)
{
	HWND DeskTopHwnd;

	if (FindWindowEx(hTop, NULL, L"SHELLDLL_DefView", NULL)!=NULL)
	{
		DeskTopHwnd = ::FindWindowEx(NULL, hTop, L"WorkerW", NULL);
		SendMessage(DeskTopHwnd, WM_CLOSE, 0, 0);
	}
	return true;
}