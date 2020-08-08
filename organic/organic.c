#define UNICODE

#ifndef _WINDOWS_
#include <windows.h>
#endif

#ifndef ORGANICH
#include "organic.h"
#endif

/* alert displays alert message with ok button */
void alert(wchar_t* label, wchar_t* message)
{
	MessageBox(0, message, label, MB_ICONWARNING | MB_OK);
}

/* askyesno displays yes/no dialog and returns 1 on yes */
Bool askyesno(wchar_t* label, wchar_t* message)
{
	return MessageBox(0, message, label, MB_ICONWARNING | MB_YESNO) == IDYES;
}

/* winstyle sets window's style */
unsigned long winstyle(Window* w, unsigned long style)
{
	return SetWindowLong(w->hwnd, GWL_STYLE, style);
}

/* winexstyle sets window's extended style */
unsigned long winexstyle(Window* w, unsigned long style)
{
	return SetWindowLong(w->hwnd, GWL_EXSTYLE, style);
}

/* wintoggle sets the window visibility

please note that 

wintoggle(w, 3 [maximized], 0 [false])

will hide the window

active				inactive
normal		SW_SHOWNORMAL		SW_SHOWNOACTIVATE
current		SW_SHOW				SW_SHOWNA
minimized	SW_SHOWMINIMIZED	SW_SHOWMINNOACTIVE
maximized	SW_MAXIMIZE			SW_HIDE

you can look up ShowWindow on msdn to get meaning of constants
*/
void wintoggle(Window* w, int mode, int focus) 
{
	static const int _wintoggle[4][2] = {
		{SW_SHOWNORMAL, SW_SHOWNOACTIVATE},
		{SW_SHOW, SW_SHOWNA},
		{SW_SHOWMINIMIZED, SW_SHOWMINNOACTIVE},
		{SW_MAXIMIZE, SW_HIDE},
	};
	ShowWindow(w->hwnd, _wintoggle[mode][focus]);
}

/* winminimize minimizes the window */
void winminimize(Window* w)
{
	ShowWindow(w->hwnd, SW_MINIMIZE);
}

/* winrestore restores and focuses on minimized window */
void winrestore(Window* w)
{
	ShowWindow(w->hwnd, SW_RESTORE);
}

/* winshow is the equivalent of wintoggle(w, 2, 1) (show and focus on window) */
void winshow(Window* w) 
{
	wintoggle(w, 2, 1);
}
