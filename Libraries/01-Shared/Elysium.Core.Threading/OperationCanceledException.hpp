/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_TASKS_OPERATIONCANCELEDEXCEPTION
#define ELYSIUM_CORE_THREADING_TASKS_OPERATIONCANCELEDEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "../Elysium.Core/Exception.hpp"
#endif

namespace Elysium::Core::Threading::Tasks
{
	class ELYSIUM_CORE_API OperationCanceledException : public Exception
	{
	public:
		OperationCanceledException();

		OperationCanceledException(Elysium::Core::Utf8String&& Message);

		~OperationCanceledException();
	};
}
#endif
