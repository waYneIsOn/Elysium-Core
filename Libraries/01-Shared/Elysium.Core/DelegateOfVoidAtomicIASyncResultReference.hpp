/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_CONTAINER_DELEGATEOFVOIDATOMICIASYNCRESULTREFERENCE
#define ELYSIUM_CORE_CONTAINER_DELEGATEOFVOIDATOMICIASYNCRESULTREFERENCE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_IASYNCRESULT
#include "IAsyncResult.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DELEGATE
#include "../Elysium.Core.Template/Delegate.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMIC
#include "../Elysium.Core.Template/Atomic.hpp"
#endif

namespace Elysium::Core::Container
{
	template class ELYSIUM_CORE_API Elysium::Core::Template::Container::Delegate<void,
		Elysium::Core::Template::Threading::Atomic<Elysium::Core::IAsyncResult*>&>;

	using DelegateOfVoidAtomicIASyncResultReference = Elysium::Core::Template::Container::Delegate<void,
		Elysium::Core::Template::Threading::Atomic<Elysium::Core::IAsyncResult*>&>;
}
#endif
