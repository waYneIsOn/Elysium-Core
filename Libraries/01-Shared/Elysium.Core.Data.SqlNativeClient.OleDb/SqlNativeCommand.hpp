/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVECOMMAND
#define ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVECOMMAND

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_COMMON_DBCOMMAND
#include "../Elysium.Core.Data/DbCommand.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVECONNECTION
#include "SqlNativeConnection.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVETRANSACTION
#include "SqlNativeTransaction.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEDATAREADER
#include "SqlNativeDataReader.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEPARAMETERCOLLECTION
#include "SqlNativeParameterCollection.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVESEQUENTIALSTREAM
#include "SqlNativeSequentialStream.hpp"
#endif

namespace Elysium::Core::Data::SqlNativeClient::OleDb
{
	class ELYSIUM_CORE_DATA_SQLNATIVECLIENT_API SqlNativeCommand final : public Common::DbCommand
	{
		friend class SqlNativeConnection;
		friend class SqlNativeTransaction;
	public:
		~SqlNativeCommand();

		virtual const SqlNativeConnection& GetConnection() const override;
		virtual const SqlNativeTransaction* GetTransaction() const override;
		virtual SqlNativeParameterCollection& GetParameters() const override;

		virtual std::unique_ptr<IDataParameter> CreateParameter() override;
		virtual size_t ExecuteNonQuery() override;
		virtual std::unique_ptr<IDataReader> ExecuteReader() override;
		virtual void Prepare() override;
	private:
		SqlNativeCommand(SqlNativeConnection& Connection, IDBCreateCommand* NativeCommandFactory);
		SqlNativeCommand(SqlNativeTransaction* Transaction, IDBCreateCommand* NativeCommandFactory);

		IDBCreateCommand* _NativeCommandFactory;
		SqlNativeParameterCollection _Parameters = SqlNativeParameterCollection();

		const Text::Encoding& _Utf16 = Text::Encoding::UTF16BE();

		void PrepareParameters(ICommandText* NativeCommandText, DBPARAMS* CommandParameters, std::vector<ISequentialStream*>* Streams, std::vector<byte>* ParameterDataBuffer);
	};
}
#endif
