#include "ArgumentNullException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::ArgumentNullException::ArgumentNullException()
	: Elysium::Core::Exception(u"ArgumentNullException")
{ }
Elysium::Core::ArgumentNullException::ArgumentNullException(const char16_t * Message)
	: Elysium::Core::Exception(Message)
{ }
Elysium::Core::ArgumentNullException::ArgumentNullException(String && Message)
	: Elysium::Core::Exception(std::move(Message))
{ }
Elysium::Core::ArgumentNullException::~ArgumentNullException()
{ }
