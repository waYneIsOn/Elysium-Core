/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_SEQUENCECONTAINER
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_SEQUENCECONTAINER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVECONSTVOLATILE
#include "RemoveConstVolatile.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISANYOF
#include "IsAnyOf.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
	/// <summary>
	/// @ToDo: check requirements instead of allowing any class
	/// https://en.cppreference.com/w/cpp/named_req/SequenceContainer
	/// </summary>
	template<class T>
	concept SequenceContainer = true;
	/*
	template<template<class> class C, class T>
	concept SequenceContainer = Elysium::Core::Template::TypeTraits::IsAnyOfValue<Functional::RemoveConstVolatileType<C<T>>,
		Elysium::Core::Template::Container::Vector<T>>;
	*/
}
#endif
