/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_CODEANALYSIS_SYNTAXTOKEN
#define ELYSIUM_CORE_CODEANALYSIS_SYNTAXTOKEN

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_CODEANALYSIS_API
#include "API.hpp"
#endif

namespace Elysium::Core::CodeAnalysis
{
	class ELYSIUM_CORE_CODEANALYSIS_API SyntaxToken
	{
	protected:
		constexpr SyntaxToken() = default;
	public:
		constexpr SyntaxToken(const SyntaxToken& Source) = delete;

		constexpr SyntaxToken(SyntaxToken&& Right) noexcept = delete;

		virtual ~SyntaxToken() noexcept;
	public:
		constexpr SyntaxToken& operator=(const SyntaxToken& Source) = delete;

		constexpr SyntaxToken& operator=(SyntaxToken&& Right) noexcept = delete;
	private:

	};
}
#endif
