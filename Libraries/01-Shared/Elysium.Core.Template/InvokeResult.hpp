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

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
	template <class T>
	struct NotInvokableResult
	{
		using IsInvokable = IntegralConstant<bool, false>;
	};

	template <class FunctionOrMethod, class ...Args>
	struct InvokableResult
	{
		using IsInvokable = IntegralConstant<bool, true>;

		//using Type = decltype(FunctionOrMethod(Args...));
	};



	template <class FunctionOrMethod, class ...Args>
	struct InvokeResult
	{
		using IsInvokable = IntegralConstant<bool, true>;

		//using Type = decltype(FunctionOrMethod(Args...));
	};

	template <class T>
	struct InvokeResult<T>
	{
		using IsInvokable = IntegralConstant<bool, false>;
	};
	/*
	template <class FunctionOrMethod, class ...Args>
	using InvokeResultType = typename InvokeResult<FunctionOrMethod, Args...>::Type;
	*/
}
#endif
