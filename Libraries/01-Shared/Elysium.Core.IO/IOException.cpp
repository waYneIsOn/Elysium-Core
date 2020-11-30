#include "IOException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::IO::IOException::IOException()
	: Elysium::Core::Exception(u8"IOException")
{ }
Elysium::Core::IO::IOException::IOException(const char8_t* Message)
	: Elysium::Core::Exception(Message)
{ }
Elysium::Core::IO::IOException::IOException(String && Message)
	: Elysium::Core::Exception(std::move(Message))
{ }
Elysium::Core::IO::IOException::~IOException()
{ }
