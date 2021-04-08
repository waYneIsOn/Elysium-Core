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
		ProcessStartInfo(const String& FileName);
		ProcessStartInfo(const String& FileName, const String& Arguments);
		ProcessStartInfo(const ProcessStartInfo& Source) = delete;
		ProcessStartInfo(ProcessStartInfo&& Right) noexcept = delete;
		~ProcessStartInfo();

		ProcessStartInfo& operator=(const ProcessStartInfo& Source) = delete;
		ProcessStartInfo& operator=(ProcessStartInfo&& Right) noexcept = delete;

		const Elysium::Core::String& GetArguments() const;
		const Elysium::Core::String& GetFileName() const;
		const ProcessWindowStyle GetWindowStyle() const;

		void SetArguments(const String& Value);
		void SetFileName(const String& Value);
		void SetWindowStyle(const ProcessWindowStyle Value);
	private:
		String _FileName;
		String _Arguments;
		ProcessWindowStyle _WindowStyle;
	};
}
#endif
