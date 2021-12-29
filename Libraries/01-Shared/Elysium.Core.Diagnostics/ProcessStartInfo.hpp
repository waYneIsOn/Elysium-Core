/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DIAGNOSTICS_PROCESSSTARTINFO
#define ELYSIUM_CORE_DIAGNOSTICS_PROCESSSTARTINFO

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_DIAGNOSTICS_PROCESSWINDOWSTYLE
#include "ProcessWindowStyle.hpp"
#endif

namespace Elysium::Core::Diagnostics
{
	class ELYSIUM_CORE_API ProcessStartInfo final
	{
	public:
		ProcessStartInfo();

		ProcessStartInfo(const Elysium::Core::Utf8String& FileName);

		ProcessStartInfo(const Elysium::Core::Utf8String& FileName, const Elysium::Core::Utf8String& Arguments);

		ProcessStartInfo(const ProcessStartInfo& Source) = delete;

		ProcessStartInfo(ProcessStartInfo&& Right) noexcept = delete;

		~ProcessStartInfo();
	public:
		ProcessStartInfo& operator=(const ProcessStartInfo& Source) = delete;

		ProcessStartInfo& operator=(ProcessStartInfo&& Right) noexcept = delete;
	public:
		const Elysium::Core::Utf8String& GetArguments() const;

		const Elysium::Core::Utf8String& GetFileName() const;

		const ProcessWindowStyle GetWindowStyle() const;

		void SetArguments(const Elysium::Core::Utf8String& Value);

		void SetFileName(const Elysium::Core::Utf8String& Value);

		void SetWindowStyle(const ProcessWindowStyle Value);
	private:
		Elysium::Core::Utf8String _FileName;
		Elysium::Core::Utf8String _Arguments;
		ProcessWindowStyle _WindowStyle;
	};
}
#endif
