#include "Exception.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

Elysium::Core::Exception::Exception()
	: _Message(&Elysium::Core::String(u"Exception")), _InnerException(nullptr)
{ }
Elysium::Core::Exception::Exception(const char16_t * Message)
	: _Message(&Elysium::Core::String(Message)), _InnerException(nullptr)
{ }
Elysium::Core::Exception::Exception(Elysium::Core::String && Message)
	//: _Message(std::move(Message)), _InnerException(nullptr)
	: _Message(&Elysium::Core::String(Message)), _InnerException(nullptr)
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
	return *_Message;
}
