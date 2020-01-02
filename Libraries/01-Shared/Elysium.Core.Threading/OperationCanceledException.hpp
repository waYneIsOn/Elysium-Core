/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_THREADING_TASKS_OPERATIONCANCELEDEXCEPTION
#define ELYSIUM_CORE_THREADING_TASKS_OPERATIONCANCELEDEXCEPTION

#ifndef ELYSIUM_CORE_EXCEPTION
#include "../Elysium.Core/Exception.hpp"
#endif

namespace Elysium::Core::Threading::Tasks
{
	class ELYSIUM_CORE_API OperationCanceledException : public Exception
	{
	public:
		OperationCanceledException();
		OperationCanceledException(const String& Message);
		~OperationCanceledException();
	};
}
#endif
