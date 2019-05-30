#include "COMException.hpp"

Elysium::Core::Runtime::InteropServices::COMException::COMException()
	: ExternalException()
{
}
Elysium::Core::Runtime::InteropServices::COMException::COMException(const char * Message)
	: ExternalException(Message)
{
}
Elysium::Core::Runtime::InteropServices::COMException::COMException(const char * Message, const int ErrorCode)
	: ExternalException(Message, ErrorCode)
{
}
Elysium::Core::Runtime::InteropServices::COMException::~COMException()
{
}
