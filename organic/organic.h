#define ORGANICH "0.0.1"

/* Size of hwnd->*Window hash-map */
#ifndef ORGANIC_WINMAPSIZ
#define ORGANIC_WINMAPSIZ 2048
#endif

/* Non-zero value enables bound-checks in window hash-map */
#ifndef ORGANIC_FOOLPROOF
#define ORGANIC_FOOLPROOF
#endif

#ifndef _WINDOWS_
#include <windows.h>
#endif

/* MACROS */

#define mnew(type) (type*)calloc(1, sizeof(type))

#define mzero(varptr) memset(varptr, 0, sizeof *varptr)

#define mtzero(type, ptr) memset(ptr, 0, sizeof (type))

#define mcero(type, ptr) mtzero(type, ptr)

#define mzap(type, ptr) dispose##type##(ptr)

/* #define mnilof(type) (type*)0 */

#define Nil NULL



/* TYPES */

typedef int Bool;

typedef struct orgmessage {
	unsigned int id;
	WPARAM wparam;
	LPARAM lparam;
} WinMessage;

typedef struct orgwindow {
	HWND hwnd;
	HWND mdihwnd;
	void (*create)(Window* w); 
	void (*close)(Window* w);
	void (*destroy)(Window* w);
	void (*paint)(Window* w, HDC dc, PAINTSTRUCT ps);
	Bool (*pass)(Window* w, WinMessage msg, int* ret);
	struct {
		unsigned mdied : 1;			/* enables next flag */
		unsigned mdichild : 1;		/* if 0 -- use DefFrameProc, if 1 -- use DefMDIChildProc */
	} flags; /* let's hope that msvc 2003 supports nested structs */
} Window;


/* HELPER FUNCTIONS */

void alert(wchar_t* label, wchar_t* message);
Bool askyesno(wchar_t* label, wchar_t* message);
unsigned long winstyle(Window* w, unsigned long style)
unsigned long winexstyle(Window* w, unsigned long style)
/*
Bool winshow(Window w);
Bool winhide(Window w);
Bool winminimize(Window w);
Bool winmaximize(Window w);
*/


/* BASIC FUNCTIONS */

/* Prototype-based windows */
Window newwin(wchar_t* label, Window* parent, ...);
Window winclone(Window* w);

/* Messaging */
WinMessage giveenvelope();
int winsend(Window w, WinMessage m);

/* Entry point */
int oinit(HINSTANCE instance, wchar_t* args, int view);

