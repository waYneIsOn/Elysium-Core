#include "SqlNativeConnection.hpp"

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVETRANSACTION
#include "SqlNativeTransaction.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVECOMMAND
#include "SqlNativeCommand.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEEXCEPTION
#include "SqlNativeException.hpp"
#endif

#ifndef ELYSIUM_CORE_RUNTIME_INTEROPSERVICES_COMEXCEPTION
#include "../Elysium.Core/COMException.hpp"
#endif

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#include "../Elysium.Core/InvalidOperationException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

using namespace Elysium::Core::Runtime::InteropServices;

Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeConnection::SqlNativeConnection()
	: DbConnection()
{
	/*
	// initialize the COM library
	HRESULT HResult;
	//if (FAILED(HResult = CoInitializeEx(NULL, COINIT_MULTITHREADED)))	// RPC_E_CHANGED_MODE;
	if (FAILED(HResult = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)))
	{
		throw Exception("failed to initialize sql native client.\r\n");
	}
	*/
}
Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeConnection::~SqlNativeConnection()
{
	Close();
	/*
	// uninitialize the COM library if required
	CoUninitialize();
	*/
}

const std::wstring & Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeConnection::GetConnectionString() const
{
	return DbConnection::GetConnectionString();
}
const int & Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeConnection::GetConnectionTimeout() const
{
	return DbConnection::GetConnectionTimeout();
}
const std::wstring & Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeConnection::GetDatabase() const
{
	return DbConnection::GetDatabase();
}
const Elysium::Core::Data::ConnectionState & Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeConnection::GetState() const
{
	return DbConnection::GetState();
}

void Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeConnection::SetConnectionString(std::wstring ConnectionString)
{
	DbConnection::SetConnectionString(ConnectionString);
}

void Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeConnection::Open()
{
	if (_ConnectionState == ConnectionState::Closed)
	{
		HRESULT HResult;

		// obtain access to the SQL server native client OLE DB provider
		if (FAILED(HResult = CoCreateInstance(CLSID_SQLNCLI11, NULL, CLSCTX_INPROC_SERVER, IID_IDBInitialize, (void **)&_NativeDataSource)))
			//if (FAILED(HResult = CoCreateInstance({ 0x397C2819L,0x8272,0x4532,{0xAD,0x3A,0xFB,0x5E,0x43,0xBE,0xAA,0x38} }, NULL, CLSCTX_INPROC_SERVER, IID_IDBInitialize, (void **)&_NativeDataSource)))
		{
			throw COMException("Failed to CoCreateInstance\r\n", HResult);
		}

		// Set initialization properties.
		IDBProperties* DataBaseProperties;
		if (FAILED(HResult = _NativeDataSource->QueryInterface(IID_IDBProperties, (void **)&DataBaseProperties)))
		{
			// prepare the exception
			SqlNativeException Exception = SqlNativeException("Failed to obtain IDBProperties interface.\r\n", HResult, _NativeDataSource);

			// clean-up and throw the exception
			_NativeDataSource->Release();
			throw Exception;
		}

		// initialize the properties and populate their values
		const ULONG ConnectionPropertiesCount = 1;
		DBPROP ConnectionProperties[ConnectionPropertiesCount];
		VariantInit(&ConnectionProperties[1].vValue);
		ConnectionProperties[0].dwPropertyID = DBPROP_INIT_PROVIDERSTRING;
		ConnectionProperties[0].vValue.vt = VT_BSTR;
		ConnectionProperties[0].vValue.bstrVal = SysAllocString(_ConnectionString.c_str());
		ConnectionProperties[0].dwOptions = DBPROPOPTIONS_REQUIRED;
		ConnectionProperties[0].colid = DB_NULLID;

		// create the propertyset
		const ULONG ConnectionPropertySetsCount = 1;
		DBPROPSET ConnectionPropertySet[ConnectionPropertySetsCount];
		ConnectionPropertySet[0].guidPropertySet = DBPROPSET_DBINIT;
		ConnectionPropertySet[0].cProperties = ConnectionPropertiesCount;
		ConnectionPropertySet[0].rgProperties = ConnectionProperties;

		// set the connection properties using the propertyset
		HResult = DataBaseProperties->SetProperties(ConnectionPropertySetsCount, ConnectionPropertySet);
		SysFreeString(ConnectionProperties[0].vValue.bstrVal);
		VariantClear(&ConnectionProperties[1].vValue);
		if (FAILED(HResult))
		{
			// prepare the exception
			SqlNativeException Exception = SqlNativeException("Failed to set initialization properties.\r\n", HResult, DataBaseProperties);

			// clean-up and throw the exception
			DataBaseProperties->Release();
			_NativeDataSource->Release();
			throw Exception;
		}

		// Now establish a connection to the data source.
		_ConnectionState = ConnectionState::Connecting;
		if (FAILED(HResult = _NativeDataSource->Initialize()))
		{
			// prepare the exception
			SqlNativeException Exception = SqlNativeException("Problem in initializing.\r\n", HResult, _NativeDataSource);

			// clean-up and throw the exception
			_NativeDataSource->Release();
			_ConnectionState = ConnectionState::Broken;
			throw Exception;
		}

		// create the session
		if (FAILED(HResult = _NativeDataSource->QueryInterface(IID_IDBCreateSession, (void**)&_NativeSession)))
		{
			// prepare the exception
			SqlNativeException Exception = SqlNativeException("Session initialization failed.\r\n", HResult, _NativeDataSource);

			// clean-up and throw the exception
			_NativeSession->Release();
			_NativeDataSource->Release();
			_ConnectionState = ConnectionState::Broken;
			throw Exception;
		}

		DataBaseProperties->Release();
		_ConnectionState = ConnectionState::Open;
	}
}
std::unique_ptr<Elysium::Core::Data::IDbTransaction> Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeConnection::BeginTransaction()
{
	return BeginTransaction(IsolationLevel::ReadCommitted);
}
std::unique_ptr<Elysium::Core::Data::IDbTransaction> Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeConnection::BeginTransaction(IsolationLevel IsolationLevel)
{
	if (_ActiveTransaction != nullptr)
	{
		throw InvalidOperationException("SqlNativeConnection doesn't support parallel transactions.\r\n");
	}

	HRESULT HResult;

	// create the transaction command factory
	IDBCreateCommand* NativeCommandFactory;
	if (FAILED(HResult = _NativeSession->CreateSession(NULL, IID_IDBCreateCommand, (IUnknown**)&NativeCommandFactory)))
	{
		throw SqlNativeException("Create transaction-command failed.\r\n", HResult, _NativeSession);
	}

	// create the transaction
	ITransactionLocal* NativeTransaction;
	if (FAILED(HResult = NativeCommandFactory->QueryInterface(IID_ITransactionLocal, (void**)&NativeTransaction)))
	{
		throw SqlNativeException("Transaction initialization failed.\r\n", HResult, NativeCommandFactory);
	}

	// begin the transaction
	unsigned long TransactionLevel;
	if (FAILED(HResult = NativeTransaction->StartTransaction((ISOLEVEL)IsolationLevel, 0, NULL, &TransactionLevel)))
	{
		throw SqlNativeException("Transaction beginning failed.\r\n", HResult, NativeTransaction);
	}

	SqlNativeTransaction* Transaction = new SqlNativeTransaction(this, IsolationLevel, NativeCommandFactory, NativeTransaction, TransactionLevel);
	_ActiveTransaction = Transaction;

	return std::unique_ptr<SqlNativeTransaction>(Transaction);
}
std::unique_ptr<Elysium::Core::Data::IDbCommand> Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeConnection::CreateCommand()
{
	HRESULT HResult;
	IDBCreateCommand* CommandFactory;
	if (FAILED(HResult = _NativeSession->CreateSession(NULL, IID_IDBCreateCommand, (IUnknown**)&CommandFactory)))
	{
		throw SqlNativeException("Create command failed.\r\n", HResult, _NativeSession);
	}

	return std::unique_ptr<SqlNativeCommand>(new SqlNativeCommand(this, CommandFactory));
}
void Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeConnection::ChangeDatabase(std::wstring DatabaseName)
{
	HRESULT HResult;

	// Set initialization properties.
	IDBProperties* DataBaseProperties;
	if (FAILED(HResult = _NativeDataSource->QueryInterface(IID_IDBProperties, (void**)&(DataBaseProperties))))
	{
		throw SqlNativeException("Properties initialization failed.\r\n", HResult, _NativeDataSource);
	}
	// initialize the properties and populate their values
	const ULONG ConnectionPropertiesCount = 1;
	DBPROP ConnectionProperties[ConnectionPropertiesCount];
	VariantInit(&ConnectionProperties[1].vValue);
	ConnectionProperties[0].dwPropertyID = DBPROP_CURRENTCATALOG;
	ConnectionProperties[0].vValue.vt = VT_BSTR;
	ConnectionProperties[0].vValue.bstrVal = SysAllocString(DatabaseName.c_str());
	ConnectionProperties[0].dwOptions = DBPROPOPTIONS_REQUIRED;
	ConnectionProperties[0].colid = DB_NULLID;
	ConnectionProperties[0].dwStatus = DBPROPSTATUS_OK;

	// create the propertyset
	const ULONG ConnectionPropertySetsCount = 1;
	DBPROPSET ConnectionPropertySet[ConnectionPropertySetsCount];
	ConnectionPropertySet[0].guidPropertySet = DBPROPSET_DATASOURCE;
	ConnectionPropertySet[0].cProperties = ConnectionPropertySetsCount;
	ConnectionPropertySet[0].rgProperties = ConnectionProperties;

	// set the connection properties using the propertyset
	HResult = DataBaseProperties->SetProperties(ConnectionPropertySetsCount, ConnectionPropertySet);
	SysFreeString(ConnectionProperties[0].vValue.bstrVal);
	VariantClear(&ConnectionProperties[1].vValue);
	if (FAILED(HResult))
	{
		// prepare the exception
		SqlNativeException Exception = SqlNativeException("Failed to set initialization properties.\r\n", HResult, DataBaseProperties);

		// clean-up and throw the exception
		DataBaseProperties->Release();
		throw Exception;
	}
	DataBaseProperties->Release();
}
void Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeConnection::Close()
{
	if (_ConnectionState != ConnectionState::Closed && _ConnectionState != ConnectionState::Broken)
	{
		HRESULT HResult;
		HResult = _NativeSession->Release();
		if (FAILED(HResult = _NativeDataSource->Uninitialize()))
		{
			// Uninitialize() is not required, but it fails if an interface (like IDBCreateCommand etc.) has not been released.
			// this code still makes sense for debugging purposes
			//throw Exception("failed to uninitialze. has the interface not been released?");
		}
		HResult = _NativeDataSource->Release();

		_ConnectionState = ConnectionState::Closed;
	}
}
