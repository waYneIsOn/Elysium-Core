#include "Exception.hpp"

Elysium::Core::Exception::Exception()
#ifdef UNICODE
	: _Message(L"Exception"), _InnerException(nullptr)
#else
	: _Message("Exception"), _InnerException(nullptr)
#endif 
{
}
Elysium::Core::Exception::Exception(const String & Message)
	: _Message(Message), _InnerException(nullptr)
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

const Elysium::Core::Exception * Elysium::Core::Exception::GetInnerException() const
{
	return _InnerException;
}

const Elysium::Core::String & Elysium::Core::Exception::GetExceptionMessage() const
{
	return _Message;
}
