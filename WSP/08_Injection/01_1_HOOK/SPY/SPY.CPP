// SPY.h
/*
#ifdef DLL_SOURCE
	#define DLLAPI extern "C" __declspec( dllexport)

#else
	#define DLLAPI extern "C" __declspec(dllimport)
#endif

// 2���� �Լ��� export
DLLAPI void Install();
DLLAPI void Uninstall();
*/


// SPY.cpp
#include <windows.h>
#define DLL_SOURCE

#include "SPY.h"

HHOOK		g_hook;		// hook �ڵ�
HMODULE		g_hDll;		// �� �Լ��� �ִ� DLL�� �ڵ�

BOOL WINAPI DllMain( HANDLE h, DWORD, LPVOID )
{
	g_hDll = (HMODULE)h;		// DLL�� instance handle ����
	return TRUE;
}

// �� �Լ�
LRESULT  CALLBACK foo( int nCode, WPARAM wp, LPARAM lp)
{
	if( nCode == HC_ACTION )	// GetMessage()�� PeekMessage()�� �޽����� ���� ���
	{
		MSG *pMsg  = (MSG*)lp;

		if( pMsg->message	== WM_CHAR)
		{
			HWND hwnd = FindWindow(0, "UseSPY");
			PostMessage(hwnd, WM_USER+100, pMsg->wParam, pMsg->lParam);
		}
	}
	// ���� ��ü�ο��� ����
	return CallNextHookEx( g_hook, nCode, wp, lp);
}

// �� ��ġ
void Install()
{
	g_hook = SetWindowsHookEx(WH_GETMESSAGE, foo, g_hDll, 0);
}

void Uninstall()
{
	UnhookWindowsHookEx(g_hook);
}