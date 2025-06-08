/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_CODEANALYSIS_CSHARP_CSHARPSYNTAXNODE
#define ELYSIUM_CORE_CODEANALYSIS_CSHARP_CSHARPSYNTAXNODE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_CODEANALYSIS_CSHARP_API
#include "../API.hpp"
#endif

#ifndef ELYSIUM_CORE_CODEANALYSIS_SYNTAXNODE
#include "../../Elysium.Core.CodeAnalysis/SyntaxNode.hpp"
#endif

namespace Elysium::Core::CodeAnalysis::CSharp
{
	class ELYSIUM_CORE_CODEANALYSIS_CSHARP_API CSharpSyntaxNode 
		: public Elysium::Core::CodeAnalysis::SyntaxNode
	{
	protected:
		constexpr CSharpSyntaxNode();
	public:
		constexpr CSharpSyntaxNode(const CSharpSyntaxNode& Source) = delete;

		constexpr CSharpSyntaxNode(CSharpSyntaxNode&& Right) noexcept = delete;

		virtual ~CSharpSyntaxNode() noexcept;
	public:
		constexpr CSharpSyntaxNode& operator=(const CSharpSyntaxNode& Source) = delete;

		constexpr CSharpSyntaxNode& operator=(CSharpSyntaxNode&& Right) noexcept = delete;
	private:

	};
}
#endif
