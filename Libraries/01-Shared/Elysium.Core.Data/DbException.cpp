#include "DbException.hpp"

Elysium::Core::Data::Common::DbException::DbException()
	: Elysium::Core::Runtime::InteropServices::ExternalException(L"DbException")
{
}
Elysium::Core::Data::Common::DbException::DbException(const String & Message)
	: Elysium::Core::Runtime::InteropServices::ExternalException(Message)
{
}
Elysium::Core::Data::Common::DbException::DbException(const String & Message, const int ErrorCode)
	: Elysium::Core::Runtime::InteropServices::ExternalException(Message, ErrorCode)
{
}
Elysium::Core::Data::Common::DbException::~DbException()
{
}
