#include "Exception.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Exception::Exception()
	: Elysium::Core::Exception::Exception(u8"Exception")
{ }

Elysium::Core::Exception::Exception(Elysium::Core::Utf8String::ConstCharacterPointer Message)
	: Elysium::Core::Exception::Exception(Elysium::Core::Utf8String(Message))
{ }

Elysium::Core::Exception::Exception(Elysium::Core::Utf8String&& Message)
	: _Message(Elysium::Core::Template::Functional::Move(Message)),
	_InnerException(nullptr)
{ }

Elysium::Core::Exception::~Exception()
{
	if (_InnerException != nullptr)
	{
		delete(_InnerException);
		_InnerException = nullptr;
	}
}

const Elysium::Core::Exception * Elysium::Core::Exception::GetInnerException() const
{
	return _InnerException;
}

const Elysium::Core::Utf8String& Elysium::Core::Exception::GetExceptionMessage() const
{
	return _Message;
}
