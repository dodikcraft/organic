#ifndef ORGANICH
#include "organic.h"
#endif

#ifndef ORG_DEFAULTH
#include "defaults.h"
#endif

#include <stddef.h>
#include <stdarg.h>

LRESULT CALLBACK LiterallyEveryWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

static WNDCLASSEX defclass;
static HINSTANCE instance;

static Window* winmap[ORGANIC_WINMAPSIZ];

static size_t maphash(HWND n) 
{
	return ((size_t)n % ORGANIC_WINMAPSIZ);
}

static Window* winrm(size_t k) 
{
	Window* w = winmap[k];
	winmap[k] = Nil;

	do {
		k = (k + 1) % ORGANIC_WINMAPSIZ;
		winmap[k-1] = winmap[k];
	} while (winmap[k] != Nil);

	return w;
}

static Window* winset(HWND h, Window* w) 
{
	size_t k;

	k = maphash(h);

	/* awful, i know */
	if (w == Nil)
		return winrm(k);

again:
	if (winmap[k] == Nil || winmap[k]->hwnd == h)
		winmap[k] = w;
	else {
		k = (k + 1) % ORGANIC_WINMAPSIZ;
		goto again;
	}

	return w;
}

static Window* winget(HWND h) 
{
	Window* w;
	size_t k = maphash(h);

	w = winmap[k];
	if (w == Nil) {
		return Nil; 
	}

	while (w->hwnd != h) {
		k = (k + 1) % ORGANIC_WINMAPSIZ;
		w = winmap[k];
	}

	return w;
}

/* newwin creates and initializes a new window */
Window* newwin(unsigned int id, Window* parent, void (*oncreate)(Window* w))
{
	Window* w = mnew(Window);
	HWND paren = Nil;

	if (parent != Nil)
		paren = parent->hwnd;

	LiterallyEveryWndProc(Nil, WM_ORGANIC_NEWWIN, 0, (LPARAM) w);
	LiterallyEveryWndProc(Nil, WM_ORGANIC_ONCREATESET, 0, (LPARAM) oncreate);

	w->close = &odefclose;
	w->destroy = &odefdestroy;
	w->paint = &odefpaint;
	w->pass = &odefpass;
	w->resize = &odefresize;
	w->move = &odefmove;

	w->flags.mdied = 0;
	w->flags.mdichild = 0;

	w->mdihwnd = Nil;

	w->hwnd = CreateWindowEx(0, L"Organic", Nil, 0, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		paren, (HMENU) id, instance, NULL);

	return w;
}

/* winclone creates a new window from existing */
Window* winclone(Window* w)
{
	wchar_t buf[512];
	Window* v = mnew(Window);
	memcpy(v, w, sizeof(Window));
	GetWindowText(w->hwnd, buf, 512);
	v->hwnd = CreateWindowEx(0, L"Organic", buf, 0, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		GetParent(w->hwnd), NULL, instance, NULL);
	return v;
}

/* begin windows-specific shitcode */
LRESULT CALLBACK LiterallyEveryWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	static Bool addnexthwnd;
	static Window* w;
	static void (*oncreate)(Window*);

	if (msg == WM_ORGANIC_NEWWIN) {
		w = (Window*) lparam;
		addnexthwnd = 1;
		return 0;
	}

	if (msg == WM_ORGANIC_ONCREATESET) {
		oncreate = (void (*)(Window*)) lparam;
		return 0;
	}

	if (w != Nil && addnexthwnd) {
		w = winset(hwnd, w);
		w->hwnd = hwnd;
		addnexthwnd = 0;
	}
	else
		w = winget(hwnd);

	switch (msg)
	{
	case WM_MOVE:
		{
			int x0 = LOWORD(lparam);
			int y0 = HIWORD(lparam);
			w->move(w, x0, y0);
		}
		return 0;

	case WM_SIZE:
		{
			int width = LOWORD(lparam);
			int height = HIWORD(lparam);
			w->resize(w, width, height);
		}
		return 0;

	case WM_CREATE:
		oncreate(w);
		return 0;

	case WM_CLOSE: 
		w->close(w);
		return 0;

	case WM_DESTROY:
		w->destroy(w);
		winset(hwnd, Nil);
		free(w);
		return 0;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			w->paint(w, hdc, ps);
			EndPaint(hwnd, &ps);
		}
		return 0;

	default:
		{
			int ret;
			WinMessage pack;

			pack.id = msg;
			pack.wparam = wparam;
			pack.lparam = lparam;

			if (w->pass(w, pack, &ret) != 0)
				return ret;
			else if (w->flags.mdied) {
				if (w->flags.mdichild) 
					return DefMDIChildProc(hwnd, msg, wparam, lparam);
				else
					return DefFrameProc(hwnd, w->mdihwnd, msg, wparam, lparam);
			}
			else
				return DefWindowProc(hwnd, msg, wparam, lparam);
		}
	}
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE unused, wchar_t* cmdline, int cmdshow) 
{
	MSG msg;

	mzero(msg);

	defclass.cbSize = sizeof defclass;
	defclass.style = CS_HREDRAW | CS_VREDRAW;
	defclass.lpfnWndProc = &LiterallyEveryWndProc;
	defclass.hbrBackground = COLOR_BACKGROUND + 1;
	defclass.hInstance = instance;
	defclass.lpszClassName = L"Organic";

	RegisterClassEx(&defclass);

	/* your code goes here */
	oinit(instance, cmdline);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
