/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DIAGNOSTICS_INTERNAL_WINDOWFINDER
#define ELYSIUM_CORE_DIAGNOSTICS_INTERNAL_WINDOWFINDER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_DIAGNOSTICS_SYSTEM
#include "System.hpp"
#endif

namespace Elysium::Core::Diagnostics::Internal
{
	class WindowFinder final
	{
	public:
		WindowFinder() = delete;
		WindowFinder(const WindowFinder& Source) = delete;
		WindowFinder(WindowFinder&& Right) noexcept = delete;
		~WindowFinder() = delete;

		WindowFinder& operator=(const WindowFinder& Source) = delete;
		WindowFinder& operator=(WindowFinder&& Right) noexcept = delete;

		static const void* GetMainWindowHandle(const Elysium::Core::uint32_t ProcessId);
	private:
		static Elysium::Core::int32_t GetMainWindowHandleCallback(HWND WindowHandle, LPARAM Parameter);
		static const bool IsMainWindow(HWND WindowHandle);

		struct WindowHandleData
		{
			Elysium::Core::uint32_t ProcessId;
			void* WindowHandle;
		};
	};
}
#endif
