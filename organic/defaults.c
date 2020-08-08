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
	return;
}

void odefdestroy(Window* w) 
{
	return;
}

void odefpaint(Window* w, HDC dc, PAINTSTRUCT ps)
{
	FillRect(dc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
}

Bool odefpass(Window* w, WinMessage msg, int* ret)
{
	return 0;	
}
