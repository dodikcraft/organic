#include <windows.h>
#include "organic.h"

static void oncreate(Window* w)
{
	/* бля не ебу че сюда писать вообще нахуй */
}

int oinit(HINSTANCE inst, wchar_t* args, int winmode) 
{
	Window w = newwin(L"Organic test", Nil);
	winstyle(&w, WS_CLIENTEDGE);
	w.create = &oncreate;
}