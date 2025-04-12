/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_COMMANDLINE_SYMBOL
#define ELYSIUM_CORE_COMMANDLINE_SYMBOL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_COMMANDLINE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

namespace Elysium::Core::CommandLine
{
	/// <summary>
	/// 
	/// </summary>
	class ELYSIUM_CORE_COMMANDLINE_API Symbol
	{
	public:
		constexpr Symbol() = delete;
	protected:
		constexpr Symbol(const char8_t* Name, const char8_t* Description);
	public:
		constexpr Symbol(const Symbol& Source) = delete;

		constexpr Symbol(Symbol&& Right) noexcept = delete;

		virtual ~Symbol() noexcept;
	public:
		constexpr Symbol& operator=(const Symbol& Source) = delete;

		constexpr Symbol& operator=(Symbol&& Right) noexcept = delete;
	public:
		const Elysium::Core::Utf8String& GetName() const noexcept;

		const Elysium::Core::Utf8String& GetDescription() const noexcept;
	private:
		Elysium::Core::Utf8String _Name;
		Elysium::Core::Utf8String _Description;
	};
}
#endif
