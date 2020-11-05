#include "SqlNativeTransaction.hpp"

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_FORMATCONVERTER
#include "FormatConverter.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVECOMMAND
#include "SqlNativeCommand.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEEXCEPTION
#include "SqlNativeException.hpp"
#endif

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#include "../Elysium.Core/InvalidOperationException.hpp"
#endif

Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeTransaction::~SqlNativeTransaction()
{
	((SqlNativeConnection*)_Connection)->_ActiveTransaction = nullptr;
}

std::unique_ptr<Elysium::Core::Data::IDbCommand> Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeTransaction::CreateCommand()
{
	return std::unique_ptr<SqlNativeCommand>(new SqlNativeCommand(this, _NativeCommandFactory));
}

void Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeTransaction::Commit()
{
	if (_NativeTransaction == nullptr)
	{
		throw InvalidOperationException(u8"SqlNativeTransaction has already been committed or rolled back.\r\n");
	}

	HRESULT HResult;
	if (FAILED(HResult = _NativeTransaction->Commit(false, XACTTC_SYNC, 0)))
	{
		throw SqlNativeException(HResult, _NativeTransaction);
	}

	// the transaction cannot be reused after a commit which means we can release it right away
	_NativeTransaction->Release();
	_NativeTransaction = nullptr;
	_NativeCommandFactory->Release();
	_NativeCommandFactory = nullptr;
}
void Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeTransaction::Rollback()
{
	if (_NativeTransaction == nullptr)
	{
		throw InvalidOperationException(u8"SqlNativeTransaction has already been committed or rolled back.\r\n");
	}

	HRESULT HResult;
	if (FAILED(HResult = _NativeTransaction->Abort(NULL, false, false)))
	{
		throw SqlNativeException(HResult, _NativeTransaction);
	}

	// the transaction cannot be reused after a commit which means we can release it right away
	_NativeTransaction->Release();
	_NativeTransaction = nullptr;
	_NativeCommandFactory->Release();
	_NativeCommandFactory = nullptr;
}

Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeTransaction::SqlNativeTransaction(SqlNativeConnection * Connection, IsolationLevel IsolationLevel, IDBCreateCommand * NativeCommandFactory, ITransactionLocal * NativeTransaction, unsigned long TransactionLevel)
	: Elysium::Core::Data::Common::DbTransaction(Connection, IsolationLevel),
	_NativeCommandFactory(NativeCommandFactory),
	_NativeTransaction(NativeTransaction),
	_TransactionLevel(TransactionLevel)
{ }
