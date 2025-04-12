/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_COMMANDLINE_ROOTCOMMAND
#define ELYSIUM_CORE_COMMANDLINE_ROOTCOMMAND

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_COMMANDLINE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_COMMANDLINE_COMMAND
#include "Command.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_VERSION
#include "../Elysium.Core/Version.hpp"
#endif

#ifndef ELYSIUM_CORE_MEMORY_SCOPED_ARENA
#include "../Elysium.Core/Arena.hpp"
#endif

namespace Elysium::Core::CommandLine
{
	/// <summary>
	/// Represents the main action that the application performs.
	/// </summary>
	class ELYSIUM_CORE_COMMANDLINE_API RootCommand final
		: public Command
	{
		friend class Command;
	public:
		constexpr RootCommand() = delete;

		RootCommand(const char8_t* Description);

		constexpr RootCommand(const RootCommand& Source) = delete;

		constexpr RootCommand(RootCommand&& Right) noexcept = delete;

		virtual ~RootCommand() noexcept;
	public:
		constexpr RootCommand& operator=(const RootCommand& Source) = delete;

		constexpr RootCommand& operator=(RootCommand&& Right) noexcept = delete;
	private:
		static const char8_t* _ExecutableName;

		static const Elysium::Core::Version _Version;
	private:
		Elysium::Core::Memory::Scoped::Arena _CommandArena;
		Elysium::Core::Memory::Scoped::Arena _ArgumentArena;
		Elysium::Core::Memory::Scoped::Arena _OptionArena;
	};
}
#endif
