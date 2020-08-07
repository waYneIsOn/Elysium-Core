#include "DbException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::Data::Common::DbException::DbException()
	: Elysium::Core::Runtime::InteropServices::ExternalException(u8"DbException")
{ }
Elysium::Core::Data::Common::DbException::DbException(String && Message)
	: Elysium::Core::Runtime::InteropServices::ExternalException(std::move(Message))
{ }
Elysium::Core::Data::Common::DbException::DbException(String && Message, const int ErrorCode)
	: Elysium::Core::Runtime::InteropServices::ExternalException(std::move(Message), ErrorCode)
{ }
Elysium::Core::Data::Common::DbException::~DbException()
{ }
