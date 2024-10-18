#pragma once

typedef double(__cdecl* sqrtfunc_ptr)(double);

#if defined(_runtime) and _runtime

#include <windows.h>

sqrtfunc_ptr loadlib(const char* name)
{
	HINSTANCE hinstlib = LoadLibraryA(name);

	if (hinstlib == nullptr) return nullptr;

	sqrtfunc_ptr result = reinterpret_cast<sqrtfunc_ptr>(GetProcAddress(hinstlib, "my_sqrt"));

	return result;
}
#else
extern "C" double __cdecl my_sqrt(double);
#endif