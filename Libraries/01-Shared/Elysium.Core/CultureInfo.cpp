#include "CultureInfo.hpp"

#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
#ifndef _WINDOWS_
#include <Windows.h>
#endif

#ifndef _WINNLS_
#include <WinNls.h>
#endif
#endif

Elysium::Core::CultureInfo::CultureInfo()
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	: _Culture(GetSystemDefaultLCID())
#elif defined(__ANDROID__)
	: _Culture(0)
	// ToDo: how to get the current locale id on android?
#endif
{
}
Elysium::Core::CultureInfo::CultureInfo(int Culture)
	: _Culture(Culture)
{
}
Elysium::Core::CultureInfo::~CultureInfo()
{
}

int Elysium::Core::CultureInfo::GetLCID()
{
	return _Culture;
}
