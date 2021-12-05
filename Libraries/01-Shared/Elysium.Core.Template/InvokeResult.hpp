/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INVOKERESULT
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INVOKERESULT

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::TypeTraits
{
	template <class Method, class ...Args>
	struct InvokeResult
	{
		using Type = decltype(Method(Args...));
	};

	template <class Method, class ...Args>
	using InvokeResultType = InvokeResult<Method, Args...>::Type;
}
#endif
