/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_IDBTRANSACTION
#define ELYSIUM_CORE_DATA_IDBTRANSACTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_DATA_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_ISOLATIONLEVEL
#include "IsolationLevel.hpp"
#endif

#ifndef _MEMORY_
#include <memory>
#endif

namespace Elysium::Core::Data
{
	class IDbConnection;
	class IDbCommand;

	class ELYSIUM_CORE_DATA_API IDbTransaction
	{
	public:
		/// <summary>
		/// Destroy the object using the virtual destructor
		/// </summary>
		virtual ~IDbTransaction() {}

		virtual const IDbConnection& GetConnection() const = 0;
		virtual const IsolationLevel GetIsolationLevel() const = 0;

		virtual std::unique_ptr<IDbCommand> CreateCommand() = 0;

		virtual void Commit() = 0;
		virtual void Rollback() = 0;
	};
}
#endif
