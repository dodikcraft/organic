#ifndef ORG_DEFAULTH
#include "defaults.h"
#endif

#ifndef ORGANICH
#include "organic.h"
#endif

void odefcreate(Window* w) 
{
	return;
}

void odefclose(Window* w)
{
	w->destroy(w);
}

void odefdestroy(Window* w) 
{
	PostQuitMessage(0);
}

void odefpaint(Window* w, HDC dc, PAINTSTRUCT ps)
{
	FillRect(dc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
}

Bool odefpass(Window* w, WinMessage msg, int* ret)
{
	return 0;	
}

void odefmove(Window* w, int x, int y)
{
	return;
}

void odefresize(Window* w, int h, int v)
{
	return;
}