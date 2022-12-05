/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DIAGNOSTICS_STACKTRACE
#define ELYSIUM_CORE_DIAGNOSTICS_STACKTRACE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_DIAGNOSTICS_STACKFRAME
#include "StackFrame.hpp"
#endif

#ifndef ELYSIUM_CORE_DIAGNOSTICS_CONTAINER_VECTOROFSTACKFRAME
#include "VectorOfStackFrame.hpp"
#endif

namespace Elysium::Core::Diagnostics
{
	class ELYSIUM_CORE_API StackTrace final
	{
	public:
		StackTrace();

		StackTrace(const StackTrace& Source) = delete;

		StackTrace(StackTrace&& Right) noexcept = delete;

		~StackTrace() noexcept;
	public:
		StackTrace& operator=(const StackTrace& Source) = delete;

		StackTrace& operator=(StackTrace&& Right) noexcept = delete;
	public:
		static constexpr const Elysium::Core::size FramesToSkip = 0;

		static constexpr const Elysium::Core::size MaxFrames = 0xFFFF;

		static constexpr const Elysium::Core::size MaxFunctionNameLength = 1024;
	public:
		const Container::VectorOfStackFrame& GetFrames() const noexcept;
	public:
		//Utf8String ToUtf8String();
	private:
		Container::VectorOfStackFrame _StackFrames;
	private:
		Container::VectorOfStackFrame CaptureStackFrames();
	};
}
#endif
