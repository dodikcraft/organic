#define ORGANICH "0.0.1"

/* Size of hwnd->*Window hash-map */
#ifndef ORGANIC_WINMAPSIZ
#define ORGANIC_WINMAPSIZ 2048
#endif

/* newwin() sends it to register hwnd in winmap */
#define WM_ORGANIC_NEWWIN 0x401

/* newwin() uses in to remember oncreate() func */
#define WM_ORGANIC_ONCREATESET 0x402

/* Non-zero value enables bound-checks in window hash-map */
#ifndef ORGANIC_FOOLPROOF
#define ORGANIC_FOOLPROOF
#endif

#ifndef _WINDOWS_
#include <windows.h>
#endif

/* MACROS */

#define mnew(type) (type*)calloc(1, sizeof(type))

#define mzero(var) memset(&var, 0, sizeof var)

#define mtzero(type, ptr) memset(ptr, 0, sizeof (type))

#define mcero(type, ptr) mtzero(type, ptr)

#define mzap(type, ptr) dispose##type##(ptr)

#define mbool(m) ((m == 0) ? 0 : 1) 

#define Nil NULL



/* TYPES */

typedef int Bool;

typedef struct orgmessage {
	unsigned int id;
	WPARAM wparam;
	LPARAM lparam;
} WinMessage;

typedef struct orgwindow Window;
struct orgwindow {
	HWND hwnd;
	HWND mdihwnd;
	void (*close)(Window* w);
	void (*destroy)(Window* w);
	void (*paint)(Window* w, HDC dc, PAINTSTRUCT ps);
	Bool (*pass)(Window* w, WinMessage msg, int* ret);
	struct {
		unsigned mdied : 1;			/* enables next flag */
		unsigned mdichild : 1;		/* if 0 -- use DefFrameProc, if 1 -- use DefMDIChildProc */
	} flags; /* let's hope that msvc 2003 supports nested structs */
};


/* HELPER FUNCTIONS */

void alert(wchar_t* label, wchar_t* message);
Bool askyesno(wchar_t* label, wchar_t* message);
unsigned long winstyle(Window* w, unsigned long style);
unsigned long winexstyle(Window* w, unsigned long style);
void wintoggle(Window* w, int mode, int focus);
void winminimize(Window* w);
void winrestore(Window* w);
void winshow(Window* w);


/* BASIC FUNCTIONS */

/* Prototype-based windows */
Window* newwin(wchar_t* label, Window* parent, void (*oncreate)(Window* w));
Window winclone(Window* w);

/* Messaging */
WinMessage giveenvelope();
int winsend(Window w, WinMessage m);

/* Entry point */
int oinit(HINSTANCE instance, wchar_t* args);
