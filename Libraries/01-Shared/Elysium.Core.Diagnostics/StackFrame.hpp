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
		friend class StackTrace;
	private:
		StackFrame(void* Address, const char8_t* FileName, const Elysium::Core::uint32_t LineNumber, const Elysium::Core::uint32_t ColumnNumber);
	public:
		StackFrame(const StackFrame& Source);

		StackFrame(StackFrame&& Right) noexcept;

		~StackFrame() noexcept;
	public:
		StackFrame& operator=(const StackFrame& Source);

		StackFrame& operator=(StackFrame&& Right) noexcept;
	public:
		bool operator==(const StackFrame& Other) const;
	public:
		const Elysium::Core::Utf8String& GetFileName() const;

		const Elysium::Core::uint32_t GetLineNumber() const;

		const Elysium::Core::uint32_t GetColumnNumber() const;
	private:
		void* _Address;
		Elysium::Core::Utf8String _FileName;
		Elysium::Core::uint32_t _LineNumber;
		Elysium::Core::uint32_t _ColumnNumber;
	};
}
#endif
