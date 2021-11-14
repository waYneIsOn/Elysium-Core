/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_COMMON_DBCONNECTIONSTRINGBUILDER
#define ELYSIUM_CORE_DATA_COMMON_DBCONNECTIONSTRINGBUILDER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_HASHTABLE
#include "../Elysium.Core.Template/HashTable.hpp"
#endif

namespace Elysium::Core::Data::Common
{
	class ELYSIUM_CORE_DATA_API DbConnectionStringBuilder
	{
	public:
		DbConnectionStringBuilder();

		DbConnectionStringBuilder(const DbConnectionStringBuilder& Source) = delete;

		DbConnectionStringBuilder(DbConnectionStringBuilder&& Right) noexcept = delete;

		virtual ~DbConnectionStringBuilder();
	public:
		DbConnectionStringBuilder& operator=(const DbConnectionStringBuilder& Source) = delete;

		DbConnectionStringBuilder& operator=(DbConnectionStringBuilder&& Right) noexcept = delete;
	public:
		void SetConnectionString(const Elysium::Core::String& ConnectionString);
	private:
		Elysium::Core::Template::Container::HashTable<Elysium::Core::String, Elysium::Core::String> _KeyValueMap;
	};
}
#endif
