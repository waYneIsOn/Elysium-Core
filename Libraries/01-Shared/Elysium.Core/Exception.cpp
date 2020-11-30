#include "Exception.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::Exception::Exception()
	: Elysium::Core::Exception::Exception(u8"Exception")
	//: _Message(&String(u8"Exception")), _InnerException(nullptr)
{ }
Elysium::Core::Exception::Exception(const char8_t* Message)
	: Elysium::Core::Exception::Exception(Elysium::Core::String(Message))
	//: _Message(&String(Message)), _InnerException(nullptr)
{ }
Elysium::Core::Exception::Exception(Elysium::Core::String && Message)
	//: _Message(std::move(Message)), _InnerException(nullptr)
	: _Message(Message), _InnerException(nullptr)
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
