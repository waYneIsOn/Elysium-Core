#include "ErrorEventArgs.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::IO::ErrorEventArgs::ErrorEventArgs(Elysium::Core::Template::Exceptions::IO::InternalBufferOverflowException&& Exception)
	: _Exception(Elysium::Core::Template::Functional::Move(Exception))
{ }

const Elysium::Core::Template::Exceptions::IO::InternalBufferOverflowException& Elysium::Core::IO::ErrorEventArgs::GetException() const
{
	return _Exception;
}