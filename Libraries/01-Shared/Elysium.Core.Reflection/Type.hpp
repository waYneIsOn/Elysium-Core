/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_REFLECTION_TYPE
#define ELYSIUM_CORE_REFLECTION_TYPE

#ifndef ELYSIUM_CORE_REFLECTION_MEMBERINFO
#include "MemberInfo.hpp"
#endif

#ifndef ELYSIUM_CORE_REFLECTION_ASSEMBLY
#include "Assembly.hpp"
#endif

namespace Elysium::Core::Reflection
{
	class ELYSIUM_CORE_API Type : public MemberInfo
	{
		//friend class Elysium::Core::Collections::Generic::List<Type>;
	public:
		virtual ~Type();

		const bool GetIsArray() const;
		const bool GetIsEnum() const;
		const bool GetIsClass() const;

		const StringView& GetFullName() const;
		//const StringView& GetNamespace() const;

		bool operator==(const Type& Other) const;
		bool operator!=(const Type& Other) const;
		bool operator<(const Type& Other) const;
		bool operator>(const Type& Other) const;
		bool operator<=(const Type& Other) const;
		bool operator>=(const Type& Other) const;
	protected:
		Type();

		size_t _HashCode;
		bool _IsArray;
		bool _IsEnum;
		bool _IsClass;

		//std::map<const size_t, const Elysium::Core::Reflection::Type _TypeHashTypeMap;
		//std::map<const size_t, const Elysium::Core::Reflection::Assembly&> _TypeHashAssemblyMap;
	};
}
#endif
