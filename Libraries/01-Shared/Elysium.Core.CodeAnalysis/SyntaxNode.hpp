/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_CODEANALYSIS_SYNTAXNODE
#define ELYSIUM_CORE_CODEANALYSIS_SYNTAXNODE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_CODEANALYSIS_API
#include "API.hpp"
#endif

namespace Elysium::Core::CommandLine
{
	class ELYSIUM_CORE_CODEANALYSIS_API SyntaxNode
	{
	protected:
		constexpr SyntaxNode() = default;
	public:
		constexpr SyntaxNode(const SyntaxNode& Source) = delete;

		constexpr SyntaxNode(SyntaxNode&& Right) noexcept = delete;

		virtual ~SyntaxNode() noexcept;
	public:
		constexpr SyntaxNode& operator=(const SyntaxNode& Source) = delete;

		constexpr SyntaxNode& operator=(SyntaxNode&& Right) noexcept = delete;
	private:

	};
}
#endif
