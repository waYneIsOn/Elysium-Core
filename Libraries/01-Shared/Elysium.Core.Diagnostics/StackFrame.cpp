#include "StackFrame.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Diagnostics::StackFrame::StackFrame(void* Address, const char8_t* FileName, const Elysium::Core::uint32_t LineNumber, const Elysium::Core::uint32_t ColumnNumber)
	: _Address(Address), _FileName(FileName), _LineNumber(LineNumber), _ColumnNumber(ColumnNumber)
{ }

Elysium::Core::Diagnostics::StackFrame::StackFrame(const StackFrame & Source)
	: _Address(Source._Address), _FileName(Source._FileName), _LineNumber(Source._LineNumber), _ColumnNumber(Source._ColumnNumber)
{ }

Elysium::Core::Diagnostics::StackFrame::StackFrame(StackFrame&& Right) noexcept
	: _Address(nullptr), _FileName(), _LineNumber(0), _ColumnNumber(0)
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}

Elysium::Core::Diagnostics::StackFrame::~StackFrame() noexcept
{ }

Elysium::Core::Diagnostics::StackFrame& Elysium::Core::Diagnostics::StackFrame::operator=(const StackFrame& Source)
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

Elysium::Core::Diagnostics::StackFrame& Elysium::Core::Diagnostics::StackFrame::operator=(StackFrame&& Right) noexcept
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

bool Elysium::Core::Diagnostics::StackFrame::operator==(const StackFrame& Other) const
{
	return _Address == Other._Address;
}

const Elysium::Core::Utf8String& Elysium::Core::Diagnostics::StackFrame::GetFileName() const
{
	return _FileName;
}

const Elysium::Core::uint32_t Elysium::Core::Diagnostics::StackFrame::GetLineNumber() const
{
	return _LineNumber;
}

const Elysium::Core::uint32_t Elysium::Core::Diagnostics::StackFrame::GetColumnNumber() const
{
	return _ColumnNumber;
}
