/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_JSON_JSONSERIALIZER
#define ELYSIUM_CORE_JSON_JSONSERIALIZER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_JSON_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

namespace Elysium::Core::Json
{
	class ELYSIUM_CORE_JSON_API JsonSerializer final
	{
	public:
		JsonSerializer();

		JsonSerializer(const JsonSerializer& Source) = delete;

		JsonSerializer(JsonSerializer&& Right) noexcept = delete;

		~JsonSerializer();
	public:
		JsonSerializer& operator=(const JsonSerializer& Source) = delete;

		JsonSerializer& operator=(JsonSerializer&& Right) noexcept = delete;
	public:
		template <class T>
		const Elysium::Core::Utf8String Serialize(const T& Object);

		template <class T>
		T Deserialize(const Elysium::Core::Utf8String& Json);
	};

	template<class T>
	inline const Elysium::Core::Utf8String JsonSerializer::Serialize(const T & Object)
	{
		/*
		const Elysium::Core::Reflection::Type& ObjectType = typeof(T);
		ObjectType.GetPropertyInfos();
		*/
		return Elysium::Core::Utf8String();
	}

	template<class T>
	inline T JsonSerializer::Deserialize(const Elysium::Core::Utf8String& Json)
	{
		return T();
	}
}
#endif
