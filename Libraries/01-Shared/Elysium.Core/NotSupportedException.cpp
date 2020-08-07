#include "NotSupportedException.hpp"

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

Elysium::Core::NotSupportedException::NotSupportedException()
	: Elysium::Core::Exception(u8"NotSupportedException")
{ }
Elysium::Core::NotSupportedException::NotSupportedException(const char * Message)
	: Elysium::Core::Exception(Message)
{ }
Elysium::Core::NotSupportedException::NotSupportedException(String && Message)
	: Elysium::Core::Exception(std::move(Message))
{ }
Elysium::Core::NotSupportedException::~NotSupportedException()
{ }
