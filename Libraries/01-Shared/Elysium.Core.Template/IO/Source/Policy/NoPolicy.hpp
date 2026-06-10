/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_SOURCE_POLICY_NOPOLICY
#define ELYSIUM_CORE_TEMPLATE_IO_SOURCE_POLICY_NOPOLICY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_READRESULT
#include "../../ReadResult.hpp"
#endif

namespace Elysium::Core::Template::IO::Source::Policy
{
	template <class Device>
	class NoPolicy
	{
	public:
		Elysium::Core::Template::IO::ReadResult OnWouldBlock(Device& SourceDevice)
		{
			return Elysium::Core::Template::IO::ReadResult::WouldBlock;
		}
	};
}
#endif
