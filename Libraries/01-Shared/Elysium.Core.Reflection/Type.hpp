/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_REFLECTION_TYPE
#define ELYSIUM_CORE_REFLECCTION_TYPE

#ifndef ELYSIUM_CORE_REFLECTION_MEMBERINFO
#include "MemberInfo.hpp"
#endif

#ifndef ELYSIUM_CORE_REFLECTION_ASSEMBLY
#include "Assembly.hpp"
#endif

// https://github.com/rttrorg/rttr/blob/c6782594802074bf7f5ca89e7e17ab5b5340c1da/src/rttr/detail/registration/registration_impl.h
// https://github.com/rttrorg/rttr/blob/master/src/examples/json_serialization/main.cpp
#define TEST_REGISTRATION	\
static void Bla();			\
namespace					\
{							\
	struct xyz				\
	{						\
		xyz()				\
		{					\
			Bla();			\
		}					\
	};						\
}							\
static void Bla()			

TEST_REGISTRATION
{
	/*
	rttr::registration::class_<shape>("shape")
		.property("visible", &shape::get_visible, &shape::set_visible)
		.property("color", &shape::color_)
		.property("name", &shape::name)
		.property("position", &shape::position)
		.property("dictionary", &shape::dictionary)
	;
	*/
}

namespace Elysium
{
	namespace Core
	{
		namespace Reflection
		{
			class ELYSIUM_CORE_API Type : public MemberInfo
			{
			public:
				virtual ~Type();

				bool GetIsArray();
				bool GetIsEnum();
				bool GetIsClass();

				const StringView& GetFullName() const;
				//const StringView& GetNamespace() const;
			protected:
				Type();
				
				bool _IsArray;
				bool _IsEnum;
				bool _IsClass;
			};
		}
	}
}
#endif
