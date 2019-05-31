/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVETRANSACTION
#define ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVETRANSACTION

#ifndef ELYSIUM_CORE_DATA_COMMON_DBTRANSACTION
#include "../Elysium.Core.Data/DbTransaction.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVECONNECTION
#include "SqlNativeConnection.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Data
		{
			namespace SqlNativeClient
			{
				namespace OleDb
				{
					class SqlNativeCommand;

					class EXPORT SqlNativeTransaction final : public Common::DbTransaction
					{
						friend class SqlNativeConnection;
						friend class SqlNativeCommand;
					public:
						~SqlNativeTransaction();

						virtual std::unique_ptr<IDbCommand> CreateCommand() override;

						virtual void Commit() override;
						virtual void Rollback() override;
					private:
						SqlNativeTransaction(SqlNativeConnection* Connection, IsolationLevel IsolationLevel, IDBCreateCommand* NativeCommandFactory, ITransactionLocal* NativeTransaction, unsigned long TransactionLevel);

						IDBCreateCommand* _NativeCommandFactory;
						ITransactionLocal* _NativeTransaction;
						unsigned long _TransactionLevel;
					};
				}
			}
		}
	}
}
#endif
