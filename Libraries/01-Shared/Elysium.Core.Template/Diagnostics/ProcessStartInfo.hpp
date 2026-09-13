/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESSSTARTINFO
#define ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESSSTARTINFO

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESSWINDOWSTYLE
#include "ProcessWindowStyle.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "../Text/String.hpp"
#endif

namespace Elysium::Core::Template::Diagnostics
{
	class ProcessStartInfo final
	{
	public:
		inline constexpr ProcessStartInfo(const char8_t* FileName = nullptr, const char8_t* Arguments = nullptr, 
			const Elysium::Core::Template::Diagnostics::ProcessWindowStyle WindowStyle = ProcessWindowStyle::Normal) noexcept
			: _FileName(FileName), _Arguments(Arguments), _WindowStyle(WindowStyle)
		{ }

		ProcessStartInfo(const ProcessStartInfo& Source) = delete;

		ProcessStartInfo(ProcessStartInfo&& Right) noexcept = delete;

		constexpr ~ProcessStartInfo() noexcept = default;
	public:
		ProcessStartInfo& operator=(const ProcessStartInfo& Source) = delete;

		ProcessStartInfo& operator=(ProcessStartInfo&& Right) noexcept = delete;
	public:
		inline const Elysium::Core::Template::Text::String<char8_t>& GetArguments() const
		{
			return _Arguments;
		}

		inline const Elysium::Core::Template::Text::String<char8_t>& GetFileName() const
		{
			return _FileName;
		}

		inline const Elysium::Core::Template::Diagnostics::ProcessWindowStyle GetWindowStyle() const
		{
			return _WindowStyle;
		}
	public:
		inline void SetArguments(const Elysium::Core::Template::Text::String<char8_t>& Value)
		{
			_Arguments = Value;
		}

		inline void SetFileName(const Elysium::Core::Template::Text::String<char8_t>& Value)
		{
			_FileName = Value;
		}

		inline void SetWindowStyle(const Elysium::Core::Template::Diagnostics::ProcessWindowStyle Value)
		{
			_WindowStyle = Value;
		}
	private:
		Elysium::Core::Template::Text::String<char8_t> _FileName;
		Elysium::Core::Template::Text::String<char8_t> _Arguments;
		Elysium::Core::Template::Diagnostics::ProcessWindowStyle _WindowStyle;
	};
}
#endif
