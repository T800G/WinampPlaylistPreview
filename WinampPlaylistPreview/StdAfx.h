#ifndef _STDAFX_711CA45E_94AF_45F7_945C_E12D15C89487_
#define _STDAFX_711CA45E_94AF_45F7_945C_E12D15C89487_
#pragma once

#define STRICT
#define WIN32_LEAN_AND_MEAN

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif

#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
#include <atlapp.h>
#if (_WTL_VER < 0x0800)
#error This project requires Windows Template Library version 8.0 or higher
#endif
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>


#endif//_STDAFX_711CA45E_94AF_45F7_945C_E12D15C89487_
