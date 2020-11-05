#include "DbException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::Data::Common::DbException::DbException()
	: Elysium::Core::Runtime::InteropServices::ExternalException()
{ }
Elysium::Core::Data::Common::DbException::DbException(const Elysium::Core::int32_t ErrorCode)
	: Elysium::Core::Runtime::InteropServices::ExternalException(ErrorCode)
{ }
Elysium::Core::Data::Common::DbException::~DbException()
{ }
