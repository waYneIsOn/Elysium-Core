/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_CODEANALYSIS_PYTHON_CSHARPSYNTAXNODE
#define ELYSIUM_CORE_CODEANALYSIS_PYTHON_CSHARPSYNTAXNODE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_CODEANALYSIS_PYTHON_API
#include "../API.hpp"
#endif

#ifndef ELYSIUM_CORE_CODEANALYSIS_SYNTAXNODE
#include "../../Elysium.Core.CodeAnalysis/SyntaxNode.hpp"
#endif

namespace Elysium::Core::CodeAnalysis::Python
{
	class ELYSIUM_CORE_CODEANALYSIS_PYTHON_API PythonSyntaxNode
		: public Elysium::Core::CodeAnalysis::SyntaxNode
	{
	protected:
		constexpr PythonSyntaxNode();
	public:
		constexpr PythonSyntaxNode(const PythonSyntaxNode& Source) = delete;

		constexpr PythonSyntaxNode(PythonSyntaxNode&& Right) noexcept = delete;

		virtual ~PythonSyntaxNode() noexcept;
	public:
		constexpr PythonSyntaxNode& operator=(const PythonSyntaxNode& Source) = delete;

		constexpr PythonSyntaxNode& operator=(PythonSyntaxNode&& Right) noexcept = delete;
	private:

	};
}
#endif
