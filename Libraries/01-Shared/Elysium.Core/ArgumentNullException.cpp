#include "ArgumentNullException.hpp"

Elysium::Core::ArgumentNullException::ArgumentNullException()
	: Elysium::Core::Exception(u"ArgumentNullException")
{ }
Elysium::Core::ArgumentNullException::ArgumentNullException(String && Message)
	: Elysium::Core::Exception(std::move(Message))
{ }
Elysium::Core::ArgumentNullException::~ArgumentNullException()
{ }
