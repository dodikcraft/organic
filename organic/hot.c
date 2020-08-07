#ifndef ORGANICH#include "organic.h"#endif#include <stddef.h>static WinTmpl defclass;static (Window*) winmap[ORGANIC_WINMAPSIZ];/* remaining capacity of winmap */static size_t mapcap;static size_t maphash(size_t n) {	return n % ORGANIC_WINMAPSIZ;}static Window* winset(HWND h, Window* w) {	size_t k;#if ORGANIC_FOOLPROOF != 0	if (mapcap >= ORGANIC_WINMAPSIZ)		return Nil;#endif	k = maphash(h);	/* awful, i know */	if (w == Nil)		return winrm(k);again:	if (winmap[k] == Nil)		winmap[k] = w;	else {		k = (k + 1) % ORGANIC_WINMAPSIZ;		goto again;	}#if ORGANIC_FOOLPROOF != 0	if (w == Nil)		mapcap--;	else		mapcap++;#endif	return w;}static Window* winget(HWND h) {	Window* w;	size_t k = maphash(h);	w = winmap[k];	if (w == Nil) {		return Nil; 	}	while (w->hwnd != h) {		k = (k + 1) % ORGANIC_WINMAPSIZ;		w = winmap[k];	}	return w;}static Window* winrm(size_t k) {	Window* w = winmap[k];	winmap[k] = Nil;	do {		k = (k + 1) % ORGANIC_WINMAPSIZ;		winmap[k-1] = winmap[k];	} while (winmap[k] != Nil);	return w;}/*this hashmap won't work in general, but for our purposes it will be enough*/LRESULT CALLBACK LiterallyEveryWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam){	Window* w = winget(hwnd);	switch (msg)	{	case WM_CREATE:		w->create(w);		return 0;	case WM_CLOSE: 		w->close(w);		return 0;	case WM_DESTROY:		w->destroy(w);		PostQuitMessage(0);		return 0;	case WM_PAINT:		{			PAINTSTRUCT ps;			HDC hdc = BeginPaint(hwnd, &ps);			w->paint(w, hdc, ps);			/*FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));*/			EndPaint(hwnd, &ps);		}		return 0;	default:		{			int ret;			WinMessage pack;			pack.id = msg;			pack.wparam = wparam;			pack.lparam = lparam;			if (w->pass(w, pack, &ret) != 0)				return ret;			else if (w->flags.mdied) {				if (w->flags.mdichild) 					return DefMDIChildProc(hwnd, msg, wParam, lParam);				else					return DefFrameProc(hwnd, w->mdihwnd, msg, wparam, lparam);			}		}	}}int WINAPI wWinMain(appl_t instance, appl_t previnst, wchar_t* cmdline, int cmdshow) {	HWND hwnd;	HWND textfield;	MSG msg;	WNDCLASSEX cls;	INITCOMMONCONTROLSEX iccx;	wchar_t* clsname = L"Organic";	mzero(cls);	mzero(msg);	cls.cbSize = sizeof cls;	cls.style = CS_HREDRAW | CS_VREDRAW;	cls.lpfnWndProc = &WndProc;	cls.hbrBackground = COLOR_BACKGROUND + 1;	cls.hInstance = instance;	cls.lpszClassName = clsname;	RegisterClassEx(&cls);	iccx.dwSize = sizeof iccx;	iccx.dwICC = 0x0000FFFF;	InitCommonControlsEx(&iccx);	LoadLibrary(L"Msftedit.dll");	hwnd = CreateWindowEx(		0,                              // Optional window styles.		clsname,						// Window class		L"Learn to Program Windows",    // Window text		WS_OVERLAPPEDWINDOW,            // Window style		// Size and position		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,		NULL,       // Parent window    		NULL,       // Menu		instance,	// Instance handle		NULL        // Additional application data		);	textfield = CreateWindowEx(0, L"Edit", "text...", ES_MULTILINE | WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP, 		0, 16, -1, -1, hwnd, 1, instance, 0);	if (hwnd == NULL)	{		return 0;	}	ShowWindow(hwnd, cmdshow);	while (GetMessage(&msg, NULL, 0, 0))	{		TranslateMessage(&msg);		DispatchMessage(&msg);	}	return 0;}