#define ORG_DEFAULTH
#ifndef ORGANICH
#include "organic.h"
#endif

/* names = {'create','close','destroy','paint','pass'} 
for name in pairs(names) do print('w.'..name..' = &odef'..name) end */

void odefcreate(Window* w);
void odefclose(Window* w);
void odefmove(Window* w, int x, int y);
void odefresize(Window* w, int h, int v);
void odefdestroy(Window* w);
void odefpaint(Window* w, HDC dc, PAINTSTRUCT ps);
Bool odefpass(Window* w, WinMessage msg, int* ret);
