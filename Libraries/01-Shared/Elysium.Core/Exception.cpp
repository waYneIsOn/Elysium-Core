#include "Exception.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Exception::Exception()
	: Elysium::Core::Exception::Exception(u8"Exception")
{ }

Elysium::Core::Exception::Exception(Elysium::Core::Utf8String::ConstCharacterPointer Message)
	: _Message(Message)
{ }

Elysium::Core::Exception::Exception(Elysium::Core::Utf8String && Message)
	: _Message(Elysium::Core::Template::Functional::Move(Message))
{ }

Elysium::Core::Exception::~Exception()
{ }

const Elysium::Core::Utf8String& Elysium::Core::Exception::GetExceptionMessage() const
{
	return _Message;
}
