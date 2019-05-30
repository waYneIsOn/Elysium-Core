#include "CultureInfo.hpp"

#ifndef _WINNLS_
//#include <WinNls.h>
#endif

Elysium::Core::CultureInfo::CultureInfo(int Culture)
	: _Culture(Culture)
{
	//GetSystemDefaultLCID();
}
Elysium::Core::CultureInfo::~CultureInfo()
{
}

int Elysium::Core::CultureInfo::GetLCID()
{
	return _Culture;
}
