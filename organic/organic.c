#define UNICODE

#ifndef _WINDOWS_
#include <windows.h>
#endif

#ifndef ORGANICH
#include "organic.h"
#endif

/* alert displays alert message with ok button */
void alert(wchar_t* label, wchar_t* message) {
	MessageBox(0, message, label, MB_ICONWARNING | MB_OK);
}

/* askyesno displays yes/no dialog and returns 1 on yes */
Bool askyesno(wchar_t* label, wchar_t* message) {
	return MessageBox(0, message, label, MB_ICONWARNING | MB_YESNO) == IDYES;
}

Window newwin(wchar_t* label, Window* parent) {

};

WinTmpl givetemplate() {
	struct orgtemplate tmpl;

	wchar_t* clsname = L"Organic";

	tmpl.nativeclass.cbSize = sizeof cls;
	tmpl.nativeclass.style = CS_HREDRAW | CS_VREDRAW;
	tmpl.nativeclass.lpfnWndProc = &WndProc;
	tmpl.nativeclass.hbrBackground = COLOR_BACKGROUND + 1;
	tmpl.nativeclass.hInstance = instance;
	tmpl.nativeclass.lpszClassName = clsname;

	
};