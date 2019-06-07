/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATA_IDBCONNECTION
#define ELYSIUM_CORE_DATA_IDBCONNECTION

#ifndef ELYSIUM_CORE_DATA_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_CONNECTIONSTATE
#include "ConnectionState.hpp"
#endif

#ifndef _XSTRING_
#include <xstring>
#endif

#ifndef ELYSIUM_CORE_DATA_IDBTRANSACTION
#include "IDbTransaction.hpp"
#endif

#ifndef _MEMORY_
#include <memory>
#endif

#ifndef ELYSIUM_CORE_DATA_IDBCOMMAND
#include "IDbCommand.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Data
		{
			class ELYSIUM_CORE_DATA_API IDbConnection
			{
			public:
				/// <summary>
				/// Destroy the object using the virtual destructor
				/// </summary>
				virtual ~IDbConnection() {}

				virtual const std::wstring& GetConnectionString() const = 0;
				virtual const int& GetConnectionTimeout() const = 0;
				virtual const std::wstring& GetDatabase() const = 0;
				virtual const ConnectionState& GetState() const = 0;

				virtual void SetConnectionString(std::wstring ConnectionString) = 0;

				virtual void Open() = 0;
				virtual std::unique_ptr<IDbTransaction> BeginTransaction() = 0;
				virtual std::unique_ptr<IDbTransaction> BeginTransaction(IsolationLevel IsolationLevel) = 0;
				virtual std::unique_ptr<IDbCommand> CreateCommand() = 0;
				virtual void ChangeDatabase(std::wstring DatabaseName) = 0;
				virtual void Close() = 0;
			};
		}
	}
}
#endif
