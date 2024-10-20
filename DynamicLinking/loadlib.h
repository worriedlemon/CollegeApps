#pragma once

typedef double(__cdecl* sqrtfunc_ptr)(double);

#ifndef _runtime
#error _runtime should be defined as a number to use this code

#else

#if _runtime
#include <windows.h>

sqrtfunc_ptr loadlib(const char* name)
{
	HINSTANCE hinstlib = LoadLibraryA(name);

	if (hinstlib == nullptr) return nullptr;

	sqrtfunc_ptr result = reinterpret_cast<sqrtfunc_ptr>(GetProcAddress(hinstlib, "my_sqrt"));

	return result;
}

bool freelib(const char* name)
{
	HINSTANCE hinstlib = GetModuleHandleA(name);

	return FreeLibrary(hinstlib);
}
#else
extern "C" double __cdecl my_sqrt(double);
#endif // if _runtime

#endif // ifdef _runtime