#define UNICODE
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "organic.h"

#define MYEDIT 310

static void oncreate(Window* w)
{
	unsigned int s = WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL |
		ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL;
	CreateWindowEx(0, L"Edit", "", s, 
		0, 0, 0, 0, w->hwnd, (HMENU)MYEDIT, GetModuleHandle(NULL), NULL);
}

static void onresize(Window* w, int h, int v)
{
	SetWindowPos(GetDlgItem(w->hwnd, MYEDIT), Nil, 0, 0, h, v, SWP_NOZORDER);
}

int oinit(HINSTANCE inst, wchar_t* args) 
{
	Window* w = newwin(0, Nil, &oncreate);
	winlabel(w, L"Hello!");
	w->resize = &onresize;
	winexstyle(w, WS_EX_CLIENTEDGE);
	winstyle(w, WS_OVERLAPPEDWINDOW);
	winshow(w);
}