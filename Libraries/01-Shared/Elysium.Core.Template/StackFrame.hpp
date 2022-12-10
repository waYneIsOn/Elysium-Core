/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_STACKFRAME
#define ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_STACKFRAME

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "String.hpp"
#endif

namespace Elysium::Core::Template::Diagnostics
{
	class StackFrame final
	{
		friend class StackTrace;
	private:
		StackFrame(void* Address, const char8_t* FileName, const System::uint32_t LineNumber, const System::uint32_t ColumnNumber);
	public:
		StackFrame() = delete;

		StackFrame(const StackFrame& Source);

		StackFrame(StackFrame&& Right) noexcept;

		~StackFrame() noexcept;
	public:
		StackFrame& operator=(const StackFrame& Source);

		StackFrame& operator=(StackFrame&& Right) noexcept;
	public:
		bool operator==(const StackFrame& Other) const;
	public:
		const Text::String<char8_t>& GetFileName() const;

		const System::uint32_t GetLineNumber() const;

		const System::uint32_t GetColumnNumber() const;
	private:
		void* _Address;
		Text::String<char8_t> _FileName;
		System::uint32_t _LineNumber;
		System::uint32_t _ColumnNumber;
	};

	inline Elysium::Core::Template::Diagnostics::StackFrame::StackFrame(void* Address, const char8_t* FileName, const System::uint32_t LineNumber, const System::uint32_t ColumnNumber)
		: _Address(Address), _FileName(FileName), _LineNumber(LineNumber), _ColumnNumber(ColumnNumber)
	{ }

	inline Elysium::Core::Template::Diagnostics::StackFrame::StackFrame(const StackFrame & Source)
		: _Address(Source._Address), _FileName(Source._FileName), _LineNumber(Source._LineNumber), _ColumnNumber(Source._ColumnNumber)
	{ }

	inline Elysium::Core::Template::Diagnostics::StackFrame::StackFrame(StackFrame && Right) noexcept
		: _Address(nullptr), _FileName(), _LineNumber(0), _ColumnNumber(0)
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}

	inline Elysium::Core::Template::Diagnostics::StackFrame::~StackFrame()
	{ }

	inline Elysium::Core::Template::Diagnostics::StackFrame& Elysium::Core::Template::Diagnostics::StackFrame::operator=(const StackFrame & Source)
	{
		if (this != &Source)
		{
			_Address = Source._Address;
			_FileName = Source._FileName;
			_LineNumber = Source._LineNumber;
			_ColumnNumber = Source._ColumnNumber;
		}

		return *this;
	}

	inline Elysium::Core::Template::Diagnostics::StackFrame& Elysium::Core::Template::Diagnostics::StackFrame::operator=(StackFrame && Right) noexcept
	{
		if (this != &Right)
		{
			_Address = Elysium::Core::Template::Functional::Move(Right._Address);
			_FileName = Elysium::Core::Template::Functional::Move(Right._FileName);
			_LineNumber = Elysium::Core::Template::Functional::Move(Right._LineNumber);
			_ColumnNumber = Elysium::Core::Template::Functional::Move(Right._ColumnNumber);

			Right._Address = nullptr;
			Right._LineNumber = 0;
			Right._ColumnNumber = 0;
		}

		return *this;
	}

	inline bool Elysium::Core::Template::Diagnostics::StackFrame::operator==(const StackFrame& Other) const
	{
		return _Address == Other._Address;
	}

	inline const Text::String<char8_t>& Elysium::Core::Template::Diagnostics::StackFrame::GetFileName() const
	{
		return _FileName;
	}

	inline const System::uint32_t Elysium::Core::Template::Diagnostics::StackFrame::GetLineNumber() const
	{
		return _LineNumber;
	}

	inline const System::uint32_t Elysium::Core::Template::Diagnostics::StackFrame::GetColumnNumber() const
	{
		return _ColumnNumber;
	}
}
#endif
