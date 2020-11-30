#include "IndexOutOfRangeException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::IndexOutOfRangeException::IndexOutOfRangeException()
	: Elysium::Core::Exception(u8"IndexOutOfRangeException")
{ }
Elysium::Core::IndexOutOfRangeException::IndexOutOfRangeException(const char8_t* Message)
	: Elysium::Core::Exception(Message)
{ }
Elysium::Core::IndexOutOfRangeException::IndexOutOfRangeException(Elysium::Core::String&& Message)
	: Elysium::Core::Exception(std::move(Message))
{ }
Elysium::Core::IndexOutOfRangeException::~IndexOutOfRangeException()
{ }
