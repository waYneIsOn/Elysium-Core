#include "OperationCanceledException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Threading::Tasks::OperationCanceledException::OperationCanceledException()
	: Elysium::Core::Exception(u8"OperationCanceledException")
{ }

Elysium::Core::Threading::Tasks::OperationCanceledException::OperationCanceledException(Elysium::Core::Utf8String&& Message)
	: Elysium::Core::Exception(Elysium::Core::Template::Functional::Move(Message))
{ }

Elysium::Core::Threading::Tasks::OperationCanceledException::~OperationCanceledException()
{ }
