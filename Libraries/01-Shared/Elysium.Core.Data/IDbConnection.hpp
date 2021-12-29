/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_IDBCONNECTION
#define ELYSIUM_CORE_DATA_IDBCONNECTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_CONNECTIONSTATE
#include "ConnectionState.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_IDBCOMMAND
#include "IDbCommand.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_IDBTRANSACTION
#include "IDbTransaction.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_UNIQUEPOINTER
#include "../Elysium.Core.Template/UniquePointer.hpp"
#endif

namespace Elysium::Core::Data
{
	class ELYSIUM_CORE_DATA_API IDbConnection
	{
	public:
		virtual ~IDbConnection() {}
	public:
		virtual const Elysium::Core::Utf8String& GetConnectionString() const = 0;

		virtual const Elysium::Core::uint32_t& GetConnectionTimeout() const = 0;

		virtual const Elysium::Core::Utf8String& GetDatabase() const = 0;

		virtual const ConnectionState& GetState() const = 0;
	public:
		virtual void SetConnectionString(const Elysium::Core::Utf8String& ConnectionString) = 0;
	public:
		virtual void Open() = 0;

		virtual void Close() = 0;

		virtual Elysium::Core::Template::Memory::UniquePointer<IDbTransaction> BeginTransaction() = 0;

		virtual Elysium::Core::Template::Memory::UniquePointer<IDbTransaction> BeginTransaction(IsolationLevel IsolationLevel) = 0;

		virtual Elysium::Core::Template::Memory::UniquePointer<IDbCommand> CreateCommand() = 0;

		virtual void ChangeDatabase(const Elysium::Core::Utf8String& DatabaseName) = 0;
	};
}
#endif
