#define UNICODE
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "organic.h"

static void oncreate(Window* w)
{
	/* бля не ебу че сюда писать вообще нахуй */
}

int oinit(HINSTANCE inst, wchar_t* args) 
{
	Window w = newwin(L"Organic test", Nil, &oncreate);
	winstyle(&w, WS_OVERLAPPEDWINDOW);
	winexstyle(&w, WS_EX_CLIENTEDGE);
	winshow(&w);
}