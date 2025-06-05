/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_CODEANALYSIS_SYNTAXTREE
#define ELYSIUM_CORE_CODEANALYSIS_SYNTAXTREE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_CODEANALYSIS_API
#include "API.hpp"
#endif

namespace Elysium::Core::CommandLine
{
	class ELYSIUM_CORE_CODEANALYSIS_API SyntaxTree
	{
	protected:
		constexpr SyntaxTree() = default;
	public:
		constexpr SyntaxTree(const SyntaxTree& Source) = delete;

		constexpr SyntaxTree(SyntaxTree&& Right) noexcept = delete;

		virtual ~SyntaxTree() noexcept;
	public:
		constexpr SyntaxTree& operator=(const SyntaxTree& Source) = delete;

		constexpr SyntaxTree& operator=(SyntaxTree&& Right) noexcept = delete;
	private:

	};
}
#endif
