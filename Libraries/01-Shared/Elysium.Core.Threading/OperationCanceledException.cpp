#include "OperationCanceledException.hpp"

Elysium::Core::Threading::Tasks::OperationCanceledException::OperationCanceledException()
	: Elysium::Core::Exception(u"OperationCanceledException")
{
}
Elysium::Core::Threading::Tasks::OperationCanceledException::OperationCanceledException(const String & Message)
	: Elysium::Core::Exception(Message)
{
}
Elysium::Core::Threading::Tasks::OperationCanceledException::~OperationCanceledException()
{
}
