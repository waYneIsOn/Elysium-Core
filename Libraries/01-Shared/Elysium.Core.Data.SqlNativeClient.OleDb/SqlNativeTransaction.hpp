/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVETRANSACTION
#define ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVETRANSACTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_DATA_COMMON_DBTRANSACTION
#include "../Elysium.Core.Data/DbTransaction.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVECONNECTION
#include "SqlNativeConnection.hpp"
#endif

namespace Elysium::Core::Data::SqlNativeClient::OleDb
{
	class SqlNativeCommand;

	class ELYSIUM_CORE_DATA_SQLNATIVECLIENT_API SqlNativeTransaction final : public Common::DbTransaction
	{
		friend class SqlNativeConnection;
		friend class SqlNativeCommand;
	public:
		~SqlNativeTransaction();

		virtual Template::Memory::UniquePointer<IDbCommand> CreateCommand() override;

		virtual void Commit() override;
		virtual void Rollback() override;
	private:
		SqlNativeTransaction(SqlNativeConnection& Connection, IsolationLevel IsolationLevel, IDBCreateCommand* NativeCommandFactory, ITransactionLocal* NativeTransaction, unsigned long TransactionLevel);

		IDBCreateCommand* _NativeCommandFactory;
		ITransactionLocal* _NativeTransaction;
		unsigned long _TransactionLevel;
	};
}
#endif
