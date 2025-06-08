/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_CODEANALYSIS_PYTHON_SYNTAXKIND
#define ELYSIUM_CORE_CODEANALYSIS_PYTHON_SYNTAXKIND

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_CODEANALYSIS_PYTHON_API
#include "../API.hpp"
#endif

namespace Elysium::Core::CodeAnalysis::Python
{
	class ELYSIUM_CORE_CODEANALYSIS_PYTHON_API SyntaxFactory
	{
	public:
		constexpr SyntaxFactory() = delete;

		constexpr SyntaxFactory(const SyntaxFactory& Source) = delete;

		constexpr SyntaxFactory(SyntaxFactory&& Right) noexcept = delete;

		~SyntaxFactory() = delete;
	public:
		constexpr SyntaxFactory& operator=(const SyntaxFactory& Source) = delete;

		constexpr SyntaxFactory& operator=(SyntaxFactory&& Right) noexcept = delete;
	public:
		//static IdentifierNameSyntax IdentifierName(const char8_t* Name);
	};
}
#endif
