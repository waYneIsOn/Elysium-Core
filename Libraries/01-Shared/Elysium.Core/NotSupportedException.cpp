#include "NotSupportedException.hpp"

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

Elysium::Core::NotSupportedException::NotSupportedException()
	: Elysium::Core::Exception(u"NotSupportedException")
{ }
Elysium::Core::NotSupportedException::NotSupportedException(const char16_t * Message)
	: Elysium::Core::Exception(Message)
{ }
Elysium::Core::NotSupportedException::NotSupportedException(String && Message)
	: Elysium::Core::Exception(std::move(Message))
{ }
Elysium::Core::NotSupportedException::~NotSupportedException()
{ }
