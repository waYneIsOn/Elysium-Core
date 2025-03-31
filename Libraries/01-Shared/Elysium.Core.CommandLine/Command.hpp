/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_COMMANDLINE_COMMAND
#define ELYSIUM_CORE_COMMANDLINE_COMMAND

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_COMMANDLINE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_COMMANDLINE_ARGUMENT
#include "Argument.hpp"
#endif

#ifndef ELYSIUM_CORE_COMMANDLINE_OPTION
#include "Option.hpp"
#endif

#ifndef ELYSIUM_CORE_COMMANDLINE_SYMBOL
#include "Symbol.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

namespace Elysium::Core::CommandLine
{
	/// <summary>
	/// 
	/// </summary>
	class ELYSIUM_CORE_COMMANDLINE_API Command
		: public Symbol
	{
	public:
		constexpr Command() = delete;
	protected:
		Command(const char8_t* Name, const char8_t* Description);
	public:
		constexpr Command(const Command& Source) = delete;

		constexpr Command(Command&& Right) noexcept = delete;
		
		constexpr virtual ~Command() = default;
	public:
		constexpr Command& operator=(const Command& Source) = delete;

		constexpr Command& operator=(Command&& Right) noexcept = delete;
	public:
		void AddAlias(const char8_t* Alias);
	public:
		Command& AddSubCommand(const char8_t* Name, const char8_t* Description = nullptr) noexcept;
		/*
		template <class T>
		Argument<T>& AddArgument();

		template <class T>
		Option<T>& AddOption();
		*/
	public:
		void Add(const Command& SubCommand);

		template <class T>
		void Add(const Argument<T>& Argument);

		template <class T>
		void Add(const Option<T>& Option);
	private:

	};

	template<class T>
	inline void Command::Add(const Argument<T>& Argument)
	{
		// @ToDo
	}

	template<class T>
	inline void Command::Add(const Option<T>& Option)
	{
		// @ToDo
	}
}
#endif
