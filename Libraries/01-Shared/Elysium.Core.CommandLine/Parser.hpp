/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_COMMANDLINE_PARSER
#define ELYSIUM_CORE_COMMANDLINE_PARSER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_COMMANDLINE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

namespace Elysium::Core::CommandLine
{
	class ELYSIUM_CORE_COMMANDLINE_API Parser
	{
	public:
		constexpr Parser() = default;

		constexpr Parser(const Parser& Source) = delete;

		constexpr Parser(Parser&& Right) noexcept = delete;

		constexpr ~Parser() = default;
	public:
		constexpr Parser& operator=(const Parser& Source) = delete;

		constexpr Parser& operator=(Parser&& Right) noexcept = delete;
	public:
		//void Parse(const Elysium::Core::Template::System::int32_t ArgumentCount, char** ArgumentVector);

		//void Parse(const Elysium::Core::Template::System::int32_t ArgumentCount, char* ArgumentVector[]);
	private:
	};
}
#endif
