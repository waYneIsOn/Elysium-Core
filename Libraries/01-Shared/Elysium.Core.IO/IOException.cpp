#include "IOException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::IO::IOException::IOException()
	: Elysium::Core::SystemException(u8"IOException")
{ }
Elysium::Core::IO::IOException::IOException(const char8_t* Message)
	: Elysium::Core::SystemException(Message)
{ }
Elysium::Core::IO::IOException::IOException(String && Message)
	: Elysium::Core::SystemException(std::move(Message))
{ }
Elysium::Core::IO::IOException::~IOException()
{ }
