/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DIAGNOSTICS_STACKFRAME
#define ELYSIUM_CORE_DIAGNOSTICS_STACKFRAME

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

namespace Elysium::Core::Diagnostics
{
	class ELYSIUM_CORE_API StackFrame final
	{
	public:
		StackFrame(const String& FileName, const Elysium::Core::uint32_t LineNumber, const Elysium::Core::uint32_t ColumnNumber) = delete;

		StackFrame(const StackFrame& Source) = delete;

		StackFrame(StackFrame&& Right) noexcept = delete;

		~StackFrame() = delete;
	public:
		StackFrame& operator=(const StackFrame& Source) = delete;

		StackFrame& operator=(StackFrame&& Right) noexcept = delete;
	public:

	private:
		String _FileName;
		Elysium::Core::uint32_t _LineNumber;
		Elysium::Core::uint32_t _ColumnNumber;
	};
}
#endif
