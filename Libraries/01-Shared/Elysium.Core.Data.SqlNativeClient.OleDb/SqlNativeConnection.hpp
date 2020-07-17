/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVECONNECTION
#define ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVECONNECTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_COMMON_DBCONNECTION
#include "../Elysium.Core.Data/DbConnection.hpp"
#endif

#ifndef __sqlncli_h__
#define _SQLNCLI_OLEDB_IGNORE_DEPRECATION_WARNING_
#define _SQLNCLI_OLEDB_
#include "C:/Program Files (x86)/Microsoft SQL Server/110/SDK/Include/sqlncli.h"
#endif

namespace Elysium::Core::Data::SqlNativeClient::OleDb
{
	class SqlNativeTransaction;
	class SqlNativeCommand;

	class ELYSIUM_CORE_DATA_SQLNATIVECLIENT_API SqlNativeConnection final : public Common::DbConnection
	{
		friend class SqlNativeTransaction;
		friend class SqlNativeCommand;
	public:
		SqlNativeConnection();
		~SqlNativeConnection();

		virtual const String& GetConnectionString() const override;
		virtual const int& GetConnectionTimeout() const override;
		virtual const String& GetDatabase() const override;
		virtual const ConnectionState& GetState() const override;

		virtual void SetConnectionString(const String & ConnectionString) override;

		virtual void Open() override;
		virtual std::unique_ptr<IDbTransaction> BeginTransaction() override;
		virtual std::unique_ptr<IDbTransaction> BeginTransaction(IsolationLevel IsolationLevel) override;
		virtual std::unique_ptr<IDbCommand> CreateCommand() override;
		virtual void ChangeDatabase(const String & DatabaseName) override;
		virtual void Close() override;
	private:
		IDBInitialize* _NativeDataSource = nullptr;
		IDBCreateSession* _NativeSession = nullptr;

		SqlNativeTransaction* _ActiveTransaction = nullptr;
	};
}
#endif
