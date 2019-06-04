#include "COMException.hpp"

#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
Elysium::Core::Runtime::InteropServices::COMException::COMException()
	: ExternalException(L"COMException")
{
}
Elysium::Core::Runtime::InteropServices::COMException::COMException(const String & Message)
	: ExternalException(Message)
{
}
Elysium::Core::Runtime::InteropServices::COMException::COMException(const String & Message, const int ErrorCode)
	: ExternalException(Message, ErrorCode)
{
}
Elysium::Core::Runtime::InteropServices::COMException::~COMException()
{
}
#endif
