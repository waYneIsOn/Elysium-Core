/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_MEMORY_DEFAULTALLOCATOROFSQLNATIVEERROR
#define ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_MEMORY_DEFAULTALLOCATOROFSQLNATIVEERROR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEERROR
#include "SqlNativeError.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTALLOCATOR
#include "../Elysium.Core.Template/DefaultAllocator.hpp"
#endif

namespace Elysium::Core::Data::SqlNativeClient::OleDb::Memory
{
	template class ELYSIUM_CORE_DATA_SQLNATIVECLIENT_API Elysium::Core::Template::Memory::DefaultAllocator<Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError>;

	using DefaultAllocatorOfSqlNativeError = Elysium::Core::Template::Memory::DefaultAllocator<Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError>;
}
#endif
