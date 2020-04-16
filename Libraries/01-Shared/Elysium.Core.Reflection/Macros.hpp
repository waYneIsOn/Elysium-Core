/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_REFLECTION_MACROS
#define ELYSIUM_CORE_REFLECTION_MACROS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_REFLECTION_TYPE
#include "Type.hpp"
#endif

// Concatenate preprocessor tokens A and B without expanding macro definitions (however, if invoked from a macro, macro arguments are expanded).
#define CONCATENATE(A, B) A ## B

// Concatenate preprocessor tokens A and B after macro-expanding them.
#define PREPROCESSINGCONCATENATE(A, B) CONCATENATE(A, B)

#define REFLECT																						\
static void RegisterReflectionData();																\
namespace 																							\
{																									\
    struct RegisterReflectionDataCaller																\
    {																								\
        RegisterReflectionDataCaller()																\
        {																							\
            RegisterReflectionData();																\
        }																							\
    };																								\
}																									\
static const RegisterReflectionDataCaller PREPROCESSINGCONCATENATE(auto_register__, __LINE__);      \
static void RegisterReflectionData()
/*
template<class T>
Elysium::Core::Reflection::Type typeof(T& Type)
{
	return SomeTypeMap[typeid(T).hash_code()];
}
*/
#endif
