#include "SystemException.hpp"

Elysium::Core::SystemException::SystemException()
	: Elysium::Core::Exception(u"SystemException")
{ }
Elysium::Core::SystemException::SystemException(String && Message)
	: Elysium::Core::Exception(std::move(Message))
{ }
Elysium::Core::SystemException::~SystemException()
{ }
