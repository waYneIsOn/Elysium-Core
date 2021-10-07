#include "FileNotFoundException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::IO::FileNotFoundException::FileNotFoundException()
	: Elysium::Core::IO::IOException(u8"FileNotFoundException")
{ }
Elysium::Core::IO::FileNotFoundException::FileNotFoundException(const char8_t* Message)
	: Elysium::Core::IO::IOException(Message)
{ }
Elysium::Core::IO::FileNotFoundException::FileNotFoundException(String && Message)
	: Elysium::Core::IO::IOException(Elysium::Core::Template::Functional::Move(Message))
{ }
Elysium::Core::IO::FileNotFoundException::~FileNotFoundException()
{ }
