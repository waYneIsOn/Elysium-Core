#include "IOException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::IO::IOException::IOException()
	: Elysium::Core::SystemException(u8"IOException")
{ }

Elysium::Core::IO::IOException::IOException(const char8_t* Message)
	: Elysium::Core::SystemException(Message)
{ }

Elysium::Core::IO::IOException::IOException(Elysium::Core::Utf8String&& Message)
	: Elysium::Core::SystemException(Elysium::Core::Template::Functional::Move(Message))
{ }

Elysium::Core::IO::IOException::IOException(const Elysium::Core::Template::System::uint32_t ErrorCode)
	: Elysium::Core::SystemException(ErrorCode)
{
}

Elysium::Core::IO::IOException::~IOException()
{ }
