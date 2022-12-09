/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_CONTAINER_DELEGATEOFVOIDCONSTIASYNCRESULTPOINTER
#define ELYSIUM_CORE_CONTAINER_DELEGATEOFVOIDCONSTIASYNCRESULTPOINTER

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

namespace Elysium::Core::Container
{
	template class ELYSIUM_CORE_API Elysium::Core::Template::Container::Delegate<void, const Elysium::Core::IAsyncResult*>;

	using DelegateOfVoidConstIASyncResultPointer = Elysium::Core::Template::Container::Delegate<void, const Elysium::Core::IAsyncResult*>;
}
#endif
