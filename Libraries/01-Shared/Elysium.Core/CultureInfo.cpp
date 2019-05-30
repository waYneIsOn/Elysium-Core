#include "CultureInfo.hpp"

#ifndef _WINDOWS_
#include <Windows.h>
#endif

#ifndef _WINNLS_
#include <WinNls.h>
#endif

Elysium::Core::CultureInfo::CultureInfo()
	: _Culture(GetSystemDefaultLCID())
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
