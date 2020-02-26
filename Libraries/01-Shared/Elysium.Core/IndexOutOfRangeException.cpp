#include "IndexOutOfRangeException.hpp"

Elysium::Core::IndexOutOfRangeException::IndexOutOfRangeException()
	: Elysium::Core::Exception(u"IndexOutOfRangeException")
{ }
Elysium::Core::IndexOutOfRangeException::IndexOutOfRangeException(String && Message)
	: Elysium::Core::Exception(std::move(Message))
{ }
Elysium::Core::IndexOutOfRangeException::~IndexOutOfRangeException()
{ }
