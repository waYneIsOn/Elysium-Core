/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_BOOLEAN
#define ELYSIUM_CORE_BOOLEAN

namespace Elysium
{
	namespace Core
	{
		namespace Boolean
		{
#if UNICODE
			constexpr const wchar_t* TrueLiteral = L"True";
			constexpr const wchar_t* FalseLiteral = L"False";
#else
			constexpr const char* TrueLiteral = "True";
			constexpr const char* FalseLiteral = "False";
#endif
		}
	}
}
#endif
