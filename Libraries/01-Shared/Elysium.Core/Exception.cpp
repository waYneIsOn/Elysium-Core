#include "Exception.hpp"

Elysium::Core::Exception::Exception()
	: _Message(u"Exception"), _InnerException(nullptr)
{ }
Elysium::Core::Exception::Exception(const char16_t * Message)
	: _Message(String(Message)), _InnerException(nullptr)
{ }
Elysium::Core::Exception::Exception(String && Message)
	: _Message(std::move(Message)), _InnerException(nullptr)
{ }
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
