#include "NotImplementedException.hpp"

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

Elysium::Core::NotImplementedException::NotImplementedException()
	: Elysium::Core::Exception(u8"NotImplementedException")
{ }
Elysium::Core::NotImplementedException::NotImplementedException(const char * Message)
	: Elysium::Core::Exception(Message)
{ }
Elysium::Core::NotImplementedException::NotImplementedException(String && Message)
	: Elysium::Core::Exception(std::move(Message))
{ }
Elysium::Core::NotImplementedException::~NotImplementedException()
{ }
