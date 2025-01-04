#include "SqlNativeConnection.hpp"

#ifndef ELYSIUM_CORE_EXCEPTION
#include "../Elysium.Core/Exception.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

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
	: DbConnection(u8"", 15000)
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

const Elysium::Core::Utf8String & Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeConnection::GetConnectionString() const
{
	return DbConnection::GetConnectionString();
}

const Elysium::Core::uint32_t& Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeConnection::GetConnectionTimeout() const
{
	return DbConnection::GetConnectionTimeout();
}

const Elysium::Core::Utf8String & Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeConnection::GetDatabase() const
{
	return DbConnection::GetDatabase();
}

const Elysium::Core::Data::ConnectionState & Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeConnection::GetState() const
{
	return DbConnection::GetState();
}

void Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeConnection::SetConnectionString(const Elysium::Core::Utf8String & ConnectionString)
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
			throw COMException(HResult);
		}

		// Set initialization properties.
		IDBProperties* DataBaseProperties;
		if (FAILED(HResult = _NativeDataSource->QueryInterface(IID_IDBProperties, (void **)&DataBaseProperties)))
		{
			// prepare the exception
			SqlNativeException Exception = SqlNativeException(HResult, _NativeDataSource);

			// clean-up and throw the exception
			_NativeDataSource->Release();
			throw Exception;
		}

		// initialize the properties and populate their values
		Elysium::Core::Container::VectorOfByte Bytes = _WindowsEncoding.GetBytes(&_ConnectionString[0], _ConnectionString.GetLength(), sizeof(wchar_t));
		const ULONG ConnectionPropertiesCount = 1;
		DBPROP ConnectionProperties[ConnectionPropertiesCount];
		VariantInit(&ConnectionProperties[0].vValue);
		ConnectionProperties[0].dwPropertyID = DBPROP_INIT_PROVIDERSTRING;
		ConnectionProperties[0].vValue.vt = VT_BSTR;
		ConnectionProperties[0].vValue.bstrVal = SysAllocString((wchar_t*)&Bytes[0]);
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
		VariantClear(&ConnectionProperties[0].vValue);
		if (FAILED(HResult))
		{
			// prepare the exception
			SqlNativeException Exception = SqlNativeException(HResult, DataBaseProperties);

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
			SqlNativeException Exception = SqlNativeException(HResult, _NativeDataSource);

			// clean-up and throw the exception
			DataBaseProperties->Release();
			_NativeDataSource->Release();
			_ConnectionState = ConnectionState::Broken;
			throw Exception;
		}

		// create the session
		if (FAILED(HResult = _NativeDataSource->QueryInterface(IID_IDBCreateSession, (void**)&_NativeSession)))
		{
			// prepare the exception
			SqlNativeException Exception = SqlNativeException(HResult, _NativeDataSource);

			// clean-up and throw the exception
			DataBaseProperties->Release();
			_NativeDataSource->Release();
			_ConnectionState = ConnectionState::Broken;
			throw Exception;
		}

		DataBaseProperties->Release();
		_ConnectionState = ConnectionState::Open;
	}
}

Elysium::Core::Template::Memory::UniquePointer<Elysium::Core::Data::IDbTransaction> Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeConnection::BeginTransaction()
{
	return BeginTransaction(IsolationLevel::ReadCommitted);
}

Elysium::Core::Template::Memory::UniquePointer<Elysium::Core::Data::IDbTransaction> Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeConnection::BeginTransaction(IsolationLevel IsolationLevel)
{
	if (_ActiveTransaction != nullptr)
	{
		throw InvalidOperationException(u8"SqlNativeConnection doesn't support parallel transactions.\r\n");
	}

	HRESULT HResult;

	// create the transaction command factory
	IDBCreateCommand* NativeCommandFactory;
	if (FAILED(HResult = _NativeSession->CreateSession(NULL, IID_IDBCreateCommand, (IUnknown**)&NativeCommandFactory)))
	{
		throw SqlNativeException(HResult, _NativeSession);
	}

	// create the transaction
	ITransactionLocal* NativeTransaction;
	if (FAILED(HResult = NativeCommandFactory->QueryInterface(IID_ITransactionLocal, (void**)&NativeTransaction)))
	{
		throw SqlNativeException(HResult, NativeCommandFactory);
	}

	// begin the transaction
	unsigned long TransactionLevel;
	if (FAILED(HResult = NativeTransaction->StartTransaction((ISOLEVEL)IsolationLevel, 0, NULL, &TransactionLevel)))
	{
		throw SqlNativeException(HResult, NativeTransaction);
	}

	SqlNativeTransaction* Transaction = new SqlNativeTransaction(*this, IsolationLevel, NativeCommandFactory, NativeTransaction, TransactionLevel);
	_ActiveTransaction = Transaction;

	return Template::Memory::UniquePointer<IDbTransaction>(Transaction);
}

Elysium::Core::Template::Memory::UniquePointer<Elysium::Core::Data::IDbCommand> Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeConnection::CreateCommand()
{
	HRESULT HResult;
	IDBCreateCommand* CommandFactory;
	if (FAILED(HResult = _NativeSession->CreateSession(NULL, IID_IDBCreateCommand, (IUnknown**)&CommandFactory)))
	{
		throw SqlNativeException(HResult, _NativeSession);
	}

	return Template::Memory::UniquePointer<IDbCommand>(new SqlNativeCommand(*this, CommandFactory));
}

void Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeConnection::ChangeDatabase(const Elysium::Core::Utf8String & DatabaseName)
{
	HRESULT HResult;

	// Set initialization properties.
	IDBProperties* DataBaseProperties;
	if (FAILED(HResult = _NativeDataSource->QueryInterface(IID_IDBProperties, (void**)&(DataBaseProperties))))
	{
		throw SqlNativeException(HResult, _NativeDataSource);
	}
	// initialize the properties and populate their values
	Elysium::Core::Container::VectorOfByte Bytes = _WindowsEncoding.GetBytes(&DatabaseName[0], DatabaseName.GetLength(), sizeof(wchar_t));
	const ULONG ConnectionPropertiesCount = 1;
	DBPROP ConnectionProperties[ConnectionPropertiesCount];
	VariantInit(&ConnectionProperties[0].vValue);
	ConnectionProperties[0].dwPropertyID = DBPROP_CURRENTCATALOG;
	ConnectionProperties[0].vValue.vt = VT_BSTR;
	ConnectionProperties[0].vValue.bstrVal = SysAllocString((wchar_t*)&Bytes[0]);
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
	VariantClear(&ConnectionProperties[0].vValue);
	if (FAILED(HResult))
	{
		// prepare the exception
		SqlNativeException Exception = SqlNativeException(HResult, DataBaseProperties);

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
