#include "InvalidCastException.hpp"

Elysium::Core::InvalidCastException::InvalidCastException()
	: Elysium::Core::Exception(u"The specified cast is not valid")
{ }
Elysium::Core::InvalidCastException::InvalidCastException(String && Message)
	: Elysium::Core::Exception(std::move(Message))
{ }
Elysium::Core::InvalidCastException::~InvalidCastException()
{ }
