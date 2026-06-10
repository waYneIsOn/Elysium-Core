/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_SOURCE_POLICY_TIMEOUTPOLICY
#define ELYSIUM_CORE_TEMPLATE_IO_SOURCE_POLICY_TIMEOUTPOLICY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VIEW_SPAN
#include "../../../Container/View/Span.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_READRESULT
#include "../../ReadResult.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Source::Policy
{
	// @ToDo: add a concept
	template <class Device>
	class TimeoutPolicy
	{
	public:
		Elysium::Core::Template::System::size _TimeoutInMilliseconds;
	public:
		/*
		inline const Elysium::Core::Template::IO::ReadResult ReadBlock(DeviceType& Device, Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte>& DataView)
		{
			// @ToDo: method "WaitForReadableData(...)" needs to be more clearly named an structured!
			if (!SourceDevice.WaitForReadableData(_TimeoutInMilliseconds))
			{	// @ToDo: throw specific timeout-exception
				throw 1;
			}

			return _Device.ReadBlock(Span);
		}

		inline void AdvanceReadingBlock(DeviceType& Device, const Elysium::Core::Template::System::size Length)
		{
			Device.AdvanceReadingBlock(Length);
		}
		*/
	};
}
#endif
