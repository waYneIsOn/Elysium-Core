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

namespace Elysium::Core::CommandLine
{
	/// <summary>
	/// 
	/// </summary>
	class ELYSIUM_CORE_COMMANDLINE_API RootCommand final
		: public Command
	{
	public:
		constexpr RootCommand() = delete;

		RootCommand(const char8_t* Description);

		constexpr RootCommand(const RootCommand& Source) = delete;

		constexpr RootCommand(RootCommand&& Right) noexcept = delete;

		constexpr virtual ~RootCommand() = default;
	public:
		constexpr RootCommand& operator=(const RootCommand& Source) = delete;

		constexpr RootCommand& operator=(RootCommand&& Right) noexcept = delete;
	private:
		static const char8_t* _ExecutableName;
	};
}
#endif
