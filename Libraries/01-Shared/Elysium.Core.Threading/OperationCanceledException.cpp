#include "OperationCanceledException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::Threading::Tasks::OperationCanceledException::OperationCanceledException()
	: Elysium::Core::Exception(u8"OperationCanceledException")
{ }
Elysium::Core::Threading::Tasks::OperationCanceledException::OperationCanceledException(String && Message)
	: Elysium::Core::Exception(std::move(Message))
{ }
Elysium::Core::Threading::Tasks::OperationCanceledException::~OperationCanceledException()
{ }
