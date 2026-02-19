/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_MEMBERFUNCTIONPOINTER
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_MEMBERFUNCTIONPOINTER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISMEMBERFUNCTIONPOINTER
#include "../IsMemberFunctionPointer.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
	/*
	template<class T, class U>
	concept MemberFunctionPointer = TypeTraits::IsMemberFunctionPointerValue<T, U>;
	*/
}
#endif
