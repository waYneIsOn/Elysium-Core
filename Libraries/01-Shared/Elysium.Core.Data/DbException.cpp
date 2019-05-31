#include "DbException.hpp"

Elysium::Core::Data::Common::DbException::DbException()
	: Elysium::Core::Runtime::InteropServices::ExternalException()
{
}
Elysium::Core::Data::Common::DbException::DbException(const char * Message)
	: Elysium::Core::Runtime::InteropServices::ExternalException(Message)
{
}
Elysium::Core::Data::Common::DbException::DbException(const char * Message, const int ErrorCode)
	: Elysium::Core::Runtime::InteropServices::ExternalException(Message, ErrorCode)
{
}
Elysium::Core::Data::Common::DbException::~DbException()
{
}
