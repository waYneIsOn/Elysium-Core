/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_REFLECTION_TYPEATTRIBUTES
#define ELYSIUM_CORE_REFLECTION_TYPEATTRIBUTES

namespace Elysium
{
	namespace Core
	{
		namespace Reflection
		{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
			enum class TypeAttributes : long
#elif defined(__ANDROID__)
			enum class TypeAttributes
#else
#error "undefined os"
#endif
			{
				//Abstract = 128,
				//AnsiClass = 0,
				//AutoClass = 131072,
				//AutoLayout = 0,
				//BeforeFieldInit = 1048576,
				Class = 0,
				ClassSemanticsMask = 32,
				//CustomFormatClass = 196608,
				//CustomFormatMask = 12582912,
				//ExplicitLayout = 16,
				//HasSecurity = 262144,
				//Import = 4096,
				Interface = 32,
				//LayoutMask = 24,
				//NestedAssembly = 5,
				//NestedFamANDAssem = 6,
				//NestedFamily = 4,
				//NestedFamORAssem = 7,
				NestedPrivate = 3,
				NestedPublic = 2,
				//NotPublic = 0,
				Public = 1,
				//ReservedMask = 264192,
				//RTSpecialName = 2048,
				Sealed = 256,
				//SequentialLayout = 8,
				//Serializable = 8192,
				//SpecialName = 1024,
				//StringFormatMask = 196608,
				//UnicodeClass = 65536,
				//VisibilityMask = 7,
				//WindowsRuntime = 16384
			};

			inline TypeAttributes operator|(TypeAttributes lhs, TypeAttributes rhs)
			{
				return static_cast<TypeAttributes>(static_cast<int>(lhs) | static_cast<int>(rhs));
			}
			inline TypeAttributes operator&(TypeAttributes lhs, TypeAttributes rhs)
			{
				return static_cast<TypeAttributes>(static_cast<int>(lhs) & static_cast<int>(rhs));
			}
		}
	}
}
#endif
