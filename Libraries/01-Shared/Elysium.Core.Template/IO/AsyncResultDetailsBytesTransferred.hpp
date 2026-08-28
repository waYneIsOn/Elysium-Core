/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_ASYNCRESULTDETAILSBYTESTRANSFERRED
#define ELYSIUM_CORE_TEMPLATE_IO_ASYNCRESULTDETAILSBYTESTRANSFERRED

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Device
{
	class FileDevice;
}

namespace Elysium::Core::Template::IO
{
	template <class AsyncResultDetails>
	class AsyncResult;
	
	// @ToDo: concept for Devices
	template <class Device>
	class AsyncResultDetailsBytesTransferred
	{
	public:
		friend class Elysium::Core::Template::IO::Device::FileDevice;
	public:
		constexpr AsyncResultDetailsBytesTransferred() = delete;

		inline constexpr AsyncResultDetailsBytesTransferred(Device& Device)
			: _Device(Device), _BytesTransferred{}
		{ }

		constexpr AsyncResultDetailsBytesTransferred(const AsyncResultDetailsBytesTransferred& Source) = default;

		constexpr AsyncResultDetailsBytesTransferred(AsyncResultDetailsBytesTransferred&& Right) noexcept = default;

		constexpr ~AsyncResultDetailsBytesTransferred() = default;
	public:
		constexpr AsyncResultDetailsBytesTransferred& operator=(const AsyncResultDetailsBytesTransferred& Source) = default;

		constexpr AsyncResultDetailsBytesTransferred& operator=(AsyncResultDetailsBytesTransferred&& Right) noexcept = default;
	public:
		inline Device& GetDevice() noexcept
		{
			return _Device;
		}

		inline Elysium::Core::Template::System::size GetBytesTransferred() const noexcept
		{
			return _BytesTransferred;
		}
	private:
		Device& _Device;
		Elysium::Core::Template::System::size _BytesTransferred;
	};
}
#endif
