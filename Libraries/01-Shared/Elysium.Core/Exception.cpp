#include "Exception.hpp"

Elysium::Core::Exception::Exception()
	: std::exception(),
	_InnerException(nullptr)
{
}
Elysium::Core::Exception::Exception(const char* Message)
	: std::exception(Message),
	_InnerException(nullptr)
{
}
Elysium::Core::Exception::~Exception()
{
	if (_InnerException != nullptr)
	{
		delete(_InnerException);
		_InnerException = nullptr;
	}
}

Elysium::Core::Exception * Elysium::Core::Exception::GetInnerException()
{
	return _InnerException;
}
