/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_CONTAINER_VECTOROFSQLNATIVEERROR
#define ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_CONTAINER_VECTOROFSQLNATIVEERROR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEERROR
#include "SqlNativeError.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_MEMORY_DEFAULTALLOCATOROFSQLNATIVEERROR
#include "../Memory/DefaultAllocatorOfSqlNativeError.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Elysium.Core.Template/Vector.hpp"
#endif

namespace Elysium::Core::Data::SqlNativeClient::OleDb::Container
{
	template class ELYSIUM_CORE_DATA_SQLNATIVECLIENT_API Elysium::Core::Template::Container::Vector<Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError>;

	using VectorOfSqlNativeError = Elysium::Core::Template::Container::Vector<Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError, Memory::DefaultAllocatorOfSqlNativeError>;
}
#endif
