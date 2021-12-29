/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

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

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
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
	public:
		virtual const Elysium::Core::Utf8String& GetConnectionString() const override;

		virtual const Elysium::Core::uint32_t& GetConnectionTimeout() const override;

		virtual const Elysium::Core::Utf8String& GetDatabase() const override;

		virtual const ConnectionState& GetState() const override;

		virtual void SetConnectionString(const Elysium::Core::Utf8String& ConnectionString) override;
	public:
		virtual void Open() override;

		virtual Template::Memory::UniquePointer<IDbTransaction> BeginTransaction() override;

		virtual Template::Memory::UniquePointer<IDbTransaction> BeginTransaction(IsolationLevel IsolationLevel) override;

		virtual Template::Memory::UniquePointer<IDbCommand> CreateCommand() override;

		virtual void ChangeDatabase(const Elysium::Core::Utf8String& DatabaseName) override;

		virtual void Close() override;
	private:
		IDBInitialize* _NativeDataSource = nullptr;
		IDBCreateSession* _NativeSession = nullptr;

		const Text::Encoding& _WindowsEncoding = Text::Encoding::UTF16LE();

		SqlNativeTransaction* _ActiveTransaction = nullptr;
	};
}
#endif
