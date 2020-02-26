#include "OperationCanceledException.hpp"

Elysium::Core::Threading::Tasks::OperationCanceledException::OperationCanceledException()
	: Elysium::Core::Exception(u"OperationCanceledException")
{ }
Elysium::Core::Threading::Tasks::OperationCanceledException::OperationCanceledException(String && Message)
	: Elysium::Core::Exception(std::move(Message))
{ }
Elysium::Core::Threading::Tasks::OperationCanceledException::~OperationCanceledException()
{ }
