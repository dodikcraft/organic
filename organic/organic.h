#define ORGANICH "0.0.1"

#ifndef _WINDOWS_
#include <windows.h>
#endif

/* MACROS */

#define mnew(type) (type*)calloc(1, sizeof(type))

#define mzero(varptr) memset(varptr, 0, sizeof *varptr)

#define mtzero(type, ptr) memset(ptr, 0, sizeof (type))

#define mcero(type, ptr) mtzero(type, ptr)

#define mzap(type, ptr) _dispose_##type##(ptr)

/* #define mnilof(type) (type*)0 */

#define Nil (void*)0



/* TYPES */

typedef int Bool;

typedef struct orgmessage {
	unsigned int id;
	WPARAM wparam;
	LPARAM lparam;
} WinMessage;

typedef struct orgwindow {
	HWND hwnd;
	void (*create)(Window* w); 
	void (*close)(Window* w);
	void (*destroy)(Window* w);
	void (*paint)(Window* w, WinDevice dc);
	int (*unknown)(Window* w, WinMessage msg, int* ret);
} Window;


/* HELPER FUNCTIONS */

void alert(wchar_t* label, wchar_t* message);
Bool askyesno(wchar_t* label, wchar_t* message);
Bool winshow(Window w);
Bool winhide(Window w);
Bool winminimize(Window w);
Bool winmaximize(Window w);



/* BASIC FUNCTIONS */

/* Template-based windows */
WinTmpl givetemplate();
int regtemplate();
Window winmaterialize(WinTmpl* t, wchar_t* label, Window* parent);
Window winm8ze(WinTmpl* t, wchar_t* label, Window* parent);

/* Prototype-based windows */
Window newwin(wchar_t* label, Window* parent);
Window winclone(Window w);

/* Messaging */
WinMessage giveenvelope();
int winsend(Window w, WinMessage m);

/* Entry point */
int omain(WinArgs args);

