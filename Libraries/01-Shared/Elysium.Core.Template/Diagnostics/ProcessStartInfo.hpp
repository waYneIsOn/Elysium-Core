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
#include "String.hpp"
#endif

namespace Elysium::Core::Template::Diagnostics
{
	class ProcessStartInfo final
	{
	public:
		ProcessStartInfo(const char8_t* FileName = nullptr, const char8_t* Arguments = nullptr) noexcept;

		ProcessStartInfo(const ProcessStartInfo& Source) = delete;

		ProcessStartInfo(ProcessStartInfo&& Right) noexcept = delete;

		~ProcessStartInfo() noexcept;
	public:
		ProcessStartInfo& operator=(const ProcessStartInfo& Source) = delete;

		ProcessStartInfo& operator=(ProcessStartInfo&& Right) noexcept = delete;
	public:
		const Text::String<char8_t>& GetArguments() const;

		const Text::String<char8_t>& GetFileName() const;

		const ProcessWindowStyle GetWindowStyle() const;
	public:
		void SetArguments(const Text::String<char8_t>& Value);

		void SetFileName(const Text::String<char8_t>& Value);

		void SetWindowStyle(const ProcessWindowStyle Value);
	private:
		Text::String<char8_t> _FileName;
		Text::String<char8_t> _Arguments;
		ProcessWindowStyle _WindowStyle;
	};

	inline ProcessStartInfo::ProcessStartInfo(const char8_t* FileName, const char8_t* Arguments) noexcept
		: _FileName(FileName), _Arguments(Arguments), _WindowStyle(ProcessWindowStyle::Normal)
	{ }

	inline ProcessStartInfo::~ProcessStartInfo() noexcept
	{ }

	inline const Text::String<char8_t>& Elysium::Core::Template::Diagnostics::ProcessStartInfo::GetArguments() const
	{
		return _Arguments;
	}

	inline const Text::String<char8_t>& Elysium::Core::Template::Diagnostics::ProcessStartInfo::GetFileName() const
	{
		return _FileName;
	}

	inline const ProcessWindowStyle Elysium::Core::Template::Diagnostics::ProcessStartInfo::GetWindowStyle() const
	{
		return _WindowStyle;
	}

	inline void Elysium::Core::Template::Diagnostics::ProcessStartInfo::SetArguments(const Text::String<char8_t>& Value)
	{
		_Arguments = Value;
	}

	inline void Elysium::Core::Template::Diagnostics::ProcessStartInfo::SetFileName(const Text::String<char8_t>& Value)
	{
		_FileName = Value;
	}

	inline void Elysium::Core::Template::Diagnostics::ProcessStartInfo::SetWindowStyle(const ProcessWindowStyle Value)
	{
		_WindowStyle = Value;
	}
}
#endif
