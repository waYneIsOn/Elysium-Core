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
#include "../Functional/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "../Text/String.hpp"
#endif

namespace Elysium::Core::Template::Diagnostics
{
	class StackFrame final
	{
		friend class StackTrace;
		friend class Elysium::Core::Template::Container::Vector<StackFrame>;
	private:
		constexpr StackFrame() = default;

		inline constexpr StackFrame(void* Address, const char8_t* FileName, const Elysium::Core::Template::System::uint32_t LineNumber, 
			const Elysium::Core::Template::System::uint32_t ColumnNumber)
			: _Address(Address), _FileName(FileName), _LineNumber(LineNumber), _ColumnNumber(ColumnNumber)
		{ }
	public:
		inline constexpr StackFrame(const StackFrame& Source)
			: _Address(Source._Address), _FileName(Source._FileName), _LineNumber(Source._LineNumber), _ColumnNumber(Source._ColumnNumber)
		{ }

		inline constexpr StackFrame(StackFrame&& Right) noexcept
			: _Address(nullptr), _FileName(), _LineNumber(0), _ColumnNumber(0)
		{
			*this = Elysium::Core::Template::Functional::Move(Right);
		}

		constexpr ~StackFrame() noexcept = default;
	public:
		inline constexpr StackFrame& operator=(const StackFrame& Source)
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

		inline constexpr StackFrame& operator=(StackFrame&& Right) noexcept
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
	public:
		inline bool operator==(const StackFrame& Other) const
		{
			return _Address == Other._Address;
		}
	public:
		inline const Elysium::Core::Template::Text::String<char8_t>& GetFileName() const
		{
			return _FileName;
		}

		inline const Elysium::Core::Template::System::uint32_t GetLineNumber() const
		{
			return _LineNumber;
		}

		inline const Elysium::Core::Template::System::uint32_t GetColumnNumber() const
		{
			return _ColumnNumber;
		}
	private:
		void* _Address;
		Elysium::Core::Template::Text::String<char8_t> _FileName;
		Elysium::Core::Template::System::uint32_t _LineNumber;
		Elysium::Core::Template::System::uint32_t _ColumnNumber;
	};
}
#endif
