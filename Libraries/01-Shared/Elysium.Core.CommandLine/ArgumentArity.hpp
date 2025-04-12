/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_COMMANDLINE_ARGUMENTARITY
#define ELYSIUM_CORE_COMMANDLINE_ARGUMENTARITY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_COMMANDLINE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

namespace Elysium::Core::CommandLine
{
	/// <summary>
	/// Defines the arity of an option or argument.
	/// </summary>
	class ELYSIUM_CORE_COMMANDLINE_API ArgumentArity
	{
	public:
		constexpr ArgumentArity() = delete;

		constexpr ArgumentArity(const Elysium::Core::Template::System::uint32_t MinimumNumberOfValues, 
			const Elysium::Core::Template::System::uint32_t MaximumNumberOfValues);

		constexpr ArgumentArity(const ArgumentArity& Source) = delete;

		constexpr ArgumentArity(ArgumentArity&& Right) noexcept = delete;

		constexpr virtual ~ArgumentArity() = default;
	public:
		constexpr ArgumentArity& operator=(const ArgumentArity& Source) = delete;

		constexpr ArgumentArity& operator=(ArgumentArity&& Right) noexcept = delete;
	public:
		Elysium::Core::Template::System::uint32_t GetMinimumNumberOfValues();

		Elysium::Core::Template::System::uint32_t GetMaximumNumberOfValues();
	public:
		void SetMinimumNumberOfValues(const Elysium::Core::Template::System::uint32_t Value);

		void SetMaximumNumberOfValues(const Elysium::Core::Template::System::uint32_t Value);
	private:
		Elysium::Core::Template::System::uint32_t _MinimumNumberOfValues;
		Elysium::Core::Template::System::uint32_t _MaximumNumberOfValues;
	};
}
#endif
