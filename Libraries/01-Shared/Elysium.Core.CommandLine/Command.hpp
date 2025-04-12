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

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_UNORDEREDMAP
#include "../Elysium.Core.Template/UnorderedMap.hpp"
#endif

namespace Elysium::Core::CommandLine
{
	class RootCommand;

	/// <summary>
	/// Represents a specific action that the application performs.
	/// </summary>
	class ELYSIUM_CORE_COMMANDLINE_API Command
		: public Symbol
	{
	public:
		constexpr Command() = delete;
	protected:
		Command(RootCommand& RootCommand, const char8_t* Name, const char8_t* Description);
	public:
		constexpr Command(const Command& Source) = delete;

		constexpr Command(Command&& Right) noexcept = delete;
		
		virtual ~Command() noexcept;
	public:
		constexpr Command& operator=(const Command& Source) = delete;

		constexpr Command& operator=(Command&& Right) noexcept = delete;
	public:
		void AddAlias(const char8_t* Alias);
	public:
		Command& AddSubCommand(const char8_t* Name, const char8_t* Description = nullptr) noexcept;
		
		template <class T>
		Argument<T>& AddArgument(const char8_t* Name, const char8_t* Description = nullptr) noexcept;
		
		template <class ...T>
		Option<T...>& AddOption(const char8_t* Name, const char8_t* Description = nullptr) noexcept;
	protected:
		void CleanUpArguments();

		void CleanupOptions();

		void CleanUpSubCommands();
	private:
		void* AllocatedMemoryForArgument(const Elysium::Core::Template::System::size Size);

		void* AllocatedMemoryForOption(const Elysium::Core::Template::System::size Size);
	private:
		RootCommand& _RootCommand;

		Elysium::Core::Template::Container::UnorderedMap<Elysium::Core::Utf8String, IArgument*> _Arguments;
		Elysium::Core::Template::Container::UnorderedMap<Elysium::Core::Utf8String, IOption*> _Options;
		Elysium::Core::Template::Container::UnorderedMap<Elysium::Core::Utf8String, Command*> _SubCommands;
	};

	template<class T>
	inline Argument<T>& Command::AddArgument(const char8_t* Name, const char8_t* Description) noexcept
	{
		void* AllocatedMemory = AllocatedMemoryForArgument(sizeof(Argument<T>));
		Argument<T>* Argument = ::new (AllocatedMemory) Elysium::Core::CommandLine::Argument<T>(Name, Description);

		_Arguments.Set(Argument->GetName(), Argument);

		return *Argument;
	}

	template<class ...T>
	inline Option<T...>& Command::AddOption(const char8_t* Name, const char8_t* Description) noexcept
	{
		void* AllocatedMemory = AllocatedMemoryForOption(sizeof(Option<T...>));
		Option<T...>* Option = ::new (AllocatedMemory) Elysium::Core::CommandLine::Option<T...>(Name, Description);

		_Options.Set(Option->GetName(), Option);

		return *Option;
	}
}
#endif
