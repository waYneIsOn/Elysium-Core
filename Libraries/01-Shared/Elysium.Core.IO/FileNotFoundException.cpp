#include "FileNotFoundException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::IO::FileNotFoundException::FileNotFoundException()
	: Elysium::Core::IO::IOException(u8"FileNotFoundException")
{ }
Elysium::Core::IO::FileNotFoundException::FileNotFoundException(const char8_t* Message)
	: Elysium::Core::IO::IOException(Message)
{ }
Elysium::Core::IO::FileNotFoundException::FileNotFoundException(String && Message)
	: Elysium::Core::IO::IOException(std::move(Message))
{ }
Elysium::Core::IO::FileNotFoundException::~FileNotFoundException()
{ }
