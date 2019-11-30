#include "SqlNativeCommand.hpp"

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEPARAMETER
#include "SqlNativeParameter.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_FORMATCONVERTER
#include "FormatConverter.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "../Elysium.Core/Stream.hpp"
#endif

#ifndef ELYSIUM_CORE_OS_WINDOWS_CONVERT
#include "../Elysium.Core.OS.Windows/Convert.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEEXCEPTION
#include "SqlNativeException.hpp"
#endif

#ifndef ELYSIUM_CORE_RUNTIME_INTEROPSERVICES_COMEXCEPTION
#include "../Elysium.Core/COMException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeCommand::~SqlNativeCommand()
{
	if (_Transaction == nullptr)
	{
		_NativeCommandFactory->Release();
	}
}

const Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeConnection * Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeCommand::GetConnection() const
{
	return (const SqlNativeConnection*)_Connection;
}
const Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeTransaction * Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeCommand::GetTransaction() const
{
	return (const SqlNativeTransaction*)_Transaction;
}
Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeParameterCollection * Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeCommand::GetParameters() const
{
	return (SqlNativeParameterCollection*)&_Parameters;
}

std::unique_ptr<Elysium::Core::Data::IDataParameter> Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeCommand::CreateParameter()
{
	return std::unique_ptr<IDataParameter>(new SqlNativeParameter(this));
}
size_t Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeCommand::ExecuteNonQuery()
{
	HRESULT HResult;

	// create a new commandtext object
	ICommandText* NativeCommandText;
	if (FAILED(HResult = _NativeCommandFactory->CreateCommand(NULL, IID_ICommandText, (IUnknown**)&NativeCommandText)))
	{
		throw SqlNativeException(u"Failed to obtain ICommandText interface.\r\n", HResult, _NativeCommandFactory);
	}

	// set the command text
	if (FAILED(HResult = NativeCommandText->SetCommandText(DBGUID_DBSQL, Elysium::Core::OS::Windows::Convert::ToWString(_Text).c_str())))
	{
		SqlNativeException Exception = SqlNativeException(u"Failed to set command text.\r\n", HResult, NativeCommandText);
		NativeCommandText->Release();
		throw Exception;
	}

	// prepare command parameters if required
	DBPARAMS CommandParameters;
	std::vector<ISequentialStream*> ParameterStreams = std::vector<ISequentialStream*>();
	std::vector<byte> ParameterDataBuffer = std::vector<byte>();
	PrepareParameters(NativeCommandText, &CommandParameters, &ParameterStreams, &ParameterDataBuffer);

	// execute the statement
	DBROWCOUNT RowsAffected;
	if (FAILED(HResult = NativeCommandText->Execute(NULL, IID_NULL, &CommandParameters, &RowsAffected, NULL)))
	{
		SqlNativeException Exception = SqlNativeException(u"Failed to execute non-query.\r\n", HResult, NativeCommandText);
		for (size_t i = 0; i < ParameterStreams.size(); i++)
		{
			SqlNativeSequentialStream* CurrentParameterStream = static_cast<SqlNativeSequentialStream*>(ParameterStreams[i]);
			if (CurrentParameterStream != nullptr)
			{
				CurrentParameterStream->Release();
			}
		}
		NativeCommandText->Release();
		throw Exception;
	}

	// clean up
	for (size_t i = 0; i < ParameterStreams.size(); i++)
	{
		SqlNativeSequentialStream* CurrentParameterStream = static_cast<SqlNativeSequentialStream*>(ParameterStreams[i]);
		if (CurrentParameterStream != nullptr)
		{
			CurrentParameterStream->Release();
		}
	}
	NativeCommandText->Release();

	return RowsAffected;
}
std::unique_ptr<Elysium::Core::Data::IDataReader> Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeCommand::ExecuteReader()
{
	HRESULT HResult;

	// create a new commandtext object
	ICommandText* NativeCommandText;
	if (FAILED(HResult = _NativeCommandFactory->CreateCommand(NULL, IID_ICommandText, (IUnknown**)&NativeCommandText)))
	{
		throw SqlNativeException(u"Failed to obtain ICommandText interface.\r\n", HResult, _NativeCommandFactory);
	}

	// set the command text
	if (FAILED(HResult = NativeCommandText->SetCommandText(DBGUID_DBSQL, Elysium::Core::OS::Windows::Convert::ToWString(_Text).c_str())))
	{
		SqlNativeException Exception = SqlNativeException(u"Failed to set command text.\r\n", HResult, NativeCommandText);
		NativeCommandText->Release();
		throw Exception;
	}

	// prepare command parameters if required
	DBPARAMS CommandParameters;
	std::vector<ISequentialStream*> ParameterStreams = std::vector<ISequentialStream*>();
	std::vector<byte> ParameterDataBuffer = std::vector<byte>();
	PrepareParameters(NativeCommandText, &CommandParameters, &ParameterStreams, &ParameterDataBuffer);

	// execute the statement
	DBROWCOUNT RowsAffected;
	IRowset* NativeRowset;
	if (FAILED(HResult = NativeCommandText->Execute(NULL, IID_IRowset, &CommandParameters, &RowsAffected, (IUnknown**)&NativeRowset)))
	{
		SqlNativeException Exception = SqlNativeException(u"Failed to execute the reader.\r\n", HResult, NativeCommandText);
		for (size_t i = 0; i < ParameterStreams.size(); i++)
		{
			SqlNativeSequentialStream* CurrentParameterStream = static_cast<SqlNativeSequentialStream*>(ParameterStreams[i]);
			if (CurrentParameterStream != nullptr)
			{
				CurrentParameterStream->Release();
			}
		}
		NativeCommandText->Release();
		throw Exception;
	}

	// get the description of the rowset for use in binding structure creation
	IColumnsInfo* NativeColumnsInfo;
	if (FAILED(HResult = NativeRowset->QueryInterface(IID_IColumnsInfo, (void**)&NativeColumnsInfo)))
	{
		SqlNativeException Exception = SqlNativeException(u"Failed to obtain IColumnsInfo interface.\r\n", HResult, NativeRowset);
		for (size_t i = 0; i < ParameterStreams.size(); i++)
		{
			SqlNativeSequentialStream* CurrentParameterStream = static_cast<SqlNativeSequentialStream*>(ParameterStreams[i]);
			if (CurrentParameterStream != nullptr)
			{
				CurrentParameterStream->Release();
			}
		}
		NativeCommandText->Release();
		NativeRowset->Release();
		throw Exception;
	}
	DBORDINAL FieldCount;
	DBCOLUMNINFO* ColumnInfo;
	wchar_t* ColumnNames;
	if (FAILED(HResult = NativeColumnsInfo->GetColumnInfo(&FieldCount, &ColumnInfo, &ColumnNames)))
	{
		SqlNativeException Exception = SqlNativeException(u"Failed to get column info.\r\n", HResult, NativeColumnsInfo);
		for (size_t i = 0; i < ParameterStreams.size(); i++)
		{
			SqlNativeSequentialStream* CurrentParameterStream = static_cast<SqlNativeSequentialStream*>(ParameterStreams[i]);
			if (CurrentParameterStream != nullptr)
			{
				CurrentParameterStream->Release();
			}
		}
		NativeColumnsInfo->Release();
		NativeCommandText->Release();
		NativeRowset->Release();
		throw Exception;
	}
	NativeColumnsInfo->Release();

	// create the reader
	std::unique_ptr<SqlNativeDataReader> Reader = std::unique_ptr<SqlNativeDataReader>(new SqlNativeDataReader(NativeRowset, RowsAffected, FieldCount, ColumnInfo, ColumnNames));

	// clean up
	for (size_t i = 0; i < ParameterStreams.size(); i++)
	{
		ISequentialStream* CurrentParameterStream = ParameterStreams[i];
		if (CurrentParameterStream != nullptr)
		{
			CurrentParameterStream->Release();
		}
	}
	NativeCommandText->Release();

	return Reader;
}
void Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeCommand::Prepare()
{
	HRESULT HResult;
	ICommandPrepare* NativeCommandPrepare;
	if (FAILED(HResult = _NativeCommandFactory->QueryInterface(IID_ICommandPrepare, (void**)&NativeCommandPrepare)))
		//if (FAILED(HResult = NativeCommandText->QueryInterface(IID_ICommandPrepare, (void**)&NativeCommandPrepare)))
	{
		throw SqlNativeException(u"Failed to obtain ICommandPrepare interface.\r\n", HResult, _NativeCommandFactory);
	}
	if (FAILED(HResult = NativeCommandPrepare->Prepare(0)))
	{
		// prepare the exception
		SqlNativeException Exception = SqlNativeException(u"Failed to prepare command.\r\n", HResult, NativeCommandPrepare);

		// clean-up and throw the exception
		NativeCommandPrepare->Release();
		throw Exception;
	}
	NativeCommandPrepare->Release();
}

Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeCommand::SqlNativeCommand(SqlNativeConnection * Connection, IDBCreateCommand* NativeCommandFactory)
	: Elysium::Core::Data::Common::DbCommand(Connection),
	_NativeCommandFactory(NativeCommandFactory)
{
}
Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeCommand::SqlNativeCommand(SqlNativeTransaction * Transaction, IDBCreateCommand* NativeCommandFactory)
	: Elysium::Core::Data::Common::DbCommand(Transaction),
	_NativeCommandFactory(NativeCommandFactory)
{
}

void Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeCommand::PrepareParameters(ICommandText* NativeCommandText, DBPARAMS * CommandParameters, std::vector<ISequentialStream*>* Streams, std::vector<byte>* ParameterDataBuffer)
{
	HRESULT HResult;
	size_t ParameterCount = _Parameters.GetCount();
	if (ParameterCount > 0)
	{
		// get the number of blob-fields
		size_t NumberOfBlobFields = 0;
		for (unsigned long i = 0; i < ParameterCount; i++)
		{
			if (_Parameters[i].GetDbType() == DbType::Binary)
			{
				NumberOfBlobFields++;
			}
		}
		size_t NumberOfNonBlobFields = ParameterCount - NumberOfBlobFields;

		// resize the stream-collection accordingly
		Streams->resize(NumberOfBlobFields);

		// create a command with parameters
		ICommandWithParameters* NativeCommandWithParameters;
		if (FAILED(HResult = NativeCommandText->QueryInterface(IID_ICommandWithParameters, (void**)&NativeCommandWithParameters)))
		{
			SqlNativeException Exception = SqlNativeException(u"Failed to obtain ICommandWithParameters interface.\r\n", HResult, NativeCommandText);
			NativeCommandText->Release();
			throw Exception;
		}

		// code I left in because it might come in handy at some point
		{
			/*
			// describe the parameters
			std::vector<DB_UPARAMS> ParameterOrdinals = std::vector<DB_UPARAMS>();
			std::vector<DBPARAMBINDINFO> NativeParameterBindingInfos = std::vector<DBPARAMBINDINFO>();
			for (unsigned long i = 0; i < ParameterCount; i++)
			{
				DB_UPARAMS ParameterOrdinal = i + 1;
				ParameterOrdinals.push_back(ParameterOrdinal);

				DBPARAMBINDINFO NativeParameterBindingInfo = DBPARAMBINDINFO();
				NativeParameterBindingInfo.pwszDataSourceType = SysAllocString(L"DBTYPE_I4");
				NativeParameterBindingInfo.pwszName = SysAllocString(L"@ParamName1");
				NativeParameterBindingInfo.ulParamSize = sizeof(int32_t);
				NativeParameterBindingInfo.dwFlags = DBPARAMFLAGS_ISINPUT;
				//NativeParameterBindingInfo.dwFlags = FormatConverter::Translate()
				NativeParameterBindingInfos.push_back(NativeParameterBindingInfo);
			}
			if (FAILED(HResult = NativeCommandWithParameters->SetParameterInfo(ParameterCount, ParameterOrdinals.data(), NativeParameterBindingInfos.data())))
			{
				NativeCommandWithParameters->Release();
				NativeCommandText->Release();
				throw SqlNativeException("Failed to set parameter info.\r\n", HResult, NativeCommandWithParameters);
			}
			*/
		}

		// Define the binding information
		DBLENGTH RowsetByteLength = 0;
		unsigned long StreamCounter = 0;
		std::vector<DBBINDING> ParameterBindings = std::vector<DBBINDING>(ParameterCount);
		std::vector<DBBINDSTATUS> ParameterBindingsStatus = std::vector<DBBINDSTATUS>(ParameterCount, DBACCESSOR_PARAMETERDATA);
		for (unsigned long i = 0; i < ParameterCount; i++)
		{
			ParameterBindings[i].iOrdinal = i + 1;
			ParameterBindings[i].wType = FormatConverter::Translate(_Parameters[i].GetDbType());
			ParameterBindings[i].eParamIO = FormatConverter::Translate(_Parameters[i].GetDirection());
			ParameterBindings[i].cbMaxLen = _Parameters[i].GetSize();
			switch (ParameterBindings[i].wType)
			{
			case DBTYPE_NUMERIC:
				ParameterBindings[i].cbMaxLen = sizeof(tagDB_NUMERIC);
				break;
			case DBTYPE_DBDATE:
				ParameterBindings[i].cbMaxLen = sizeof(tagDBDATE);
				break;
			case DBTYPE_DBTIMESTAMP:
				ParameterBindings[i].cbMaxLen = sizeof(tagDBTIMESTAMP);
				break;
			case DBTYPE_DBTIME2:
				ParameterBindings[i].cbMaxLen = sizeof(tagDBTIME2);
				break;
			case DBTYPE_DBTIMESTAMPOFFSET:
				ParameterBindings[i].cbMaxLen = sizeof(tagDBTIMESTAMPOFFSET);
				break;
			default:
				ParameterBindings[i].cbMaxLen = _Parameters[i].GetSize();
				break;
			}
			ParameterBindings[i].dwFlags = 0;
			ParameterBindings[i].pObject = NULL;
			ParameterBindings[i].pBindExt = NULL;
			ParameterBindings[i].pTypeInfo = NULL;
			ParameterBindings[i].dwMemOwner = DBMEMOWNER_CLIENTOWNED;
			ParameterBindings[i].dwPart = DBPART_LENGTH | DBPART_STATUS | DBPART_VALUE;
			ParameterBindings[i].obLength = RowsetByteLength;
			ParameterBindings[i].obStatus = ParameterBindings[i].obLength + sizeof(DBLENGTH);
			ParameterBindings[i].obValue = ParameterBindings[i].obStatus + sizeof(DBSTATUS);
			//ParameterBindings[i].bPrecision = 10;	// not required?
			//ParameterBindings[i].bScale = 0; // not required?

			// change ParameterBindings[i] accordingly
			if (ParameterBindings[i].wType == DBTYPE_IUNKNOWN)
			{
				DBOBJECT dbobject = DBOBJECT();
				dbobject.dwFlags = STGM_WRITE; // STGM_READ - STGM_WRITE
				dbobject.iid = IID_ISequentialStream;
				ParameterBindings[i].pObject = &dbobject;

				// populate the stream (if possible)
				if (!_Parameters[i].GetIsDBNull())
				{
					const BYTE* Value = _Parameters[i].GetValue();
					Elysium::Core::IO::Stream* SourceStream;
					memcpy(&SourceStream, &Value[0], sizeof(Elysium::Core::IO::Stream*));	// need to memcpy, not just cast since the bytes are stored in reverse order
					if (SourceStream != nullptr && (void*)SourceStream != Elysium::Core::Data::DBNull::Value())
					{
						SqlNativeSequentialStream* CurrentStream = new SqlNativeSequentialStream();
						CurrentStream->AddRef();	// very important or the object will be deleted too early
						Streams->at(StreamCounter) = CurrentStream;

						size_t BytesRead = 0;
						byte Buffer[4096];
						SourceStream->SetPosition(0);
						while ((BytesRead = SourceStream->Read(&Buffer[0], 4096)) > 0)
						{
							if (FAILED(HResult = CurrentStream->Write(&Buffer[0], (unsigned long)BytesRead, nullptr)))
							{
								SqlNativeException Exception = SqlNativeException(u"Failed to obtain IAccessor interface.\r\n", HResult, CurrentStream);
								NativeCommandWithParameters->Release();
								NativeCommandText->Release();
								throw Exception;
							}
						}
						CurrentStream->Seek(0);	// very important to reset the position so the mssql server can read the data correctly
						StreamCounter++;
					}
				}
			}

			RowsetByteLength += ParameterBindings[i].cbMaxLen + sizeof(DBLENGTH) + sizeof(DBSTATUS);
		}

		// resize and populate the buffer
		ParameterDataBuffer->resize(RowsetByteLength);
		unsigned __int64 ByteOffset = 0;
		StreamCounter = 0;
		for (unsigned long i = 0; i < ParameterCount; i++)
		{
			// length
			DBLENGTH Length = ParameterBindings[i].cbMaxLen;
			if (ParameterBindings[i].wType == DBTYPE_IUNKNOWN && Length > 0)
			{
				SqlNativeSequentialStream* CurrentStream = static_cast<SqlNativeSequentialStream*>(Streams->at(StreamCounter));
				Length = CurrentStream->Length();	// DBLENGTH is used to tell the provider how many bytes to expect from the stream
			}
			memcpy(&ParameterDataBuffer->data()[ByteOffset], &Length, sizeof(DBLENGTH));
			ByteOffset += sizeof(DBLENGTH);

			// status
			DBSTATUS Status = DBSTATUS_S_OK;
			//if (_Parameters[i].GetIsDBNull())
			if (Length == 0)
			{
				Status = DBSTATUS_S_ISNULL;
			}
			memcpy(&ParameterDataBuffer->data()[ByteOffset], &Status, sizeof(DBSTATUS));
			ByteOffset += sizeof(DBSTATUS);

			// value
			switch (ParameterBindings[i].wType)
			{
			case DBTYPE_IUNKNOWN:
			{
				SqlNativeSequentialStream* CurrentStream = static_cast<SqlNativeSequentialStream*>(Streams->at(StreamCounter++));
				memcpy(&ParameterDataBuffer->data()[ByteOffset], &CurrentStream, sizeof(IUnknown*));
				ByteOffset += sizeof(IUnknown*);
				break;
			}
			case DBTYPE_NUMERIC:
			{
				const Decimal* DecimalValue = static_cast<const Decimal*>(static_cast<const void*>(_Parameters[i].GetValue()));
				tagDB_NUMERIC Numeric;
				memcpy(&Numeric.val[0], _Parameters[i].GetValue(), sizeof(Numeric.val));
				memcpy(&ParameterDataBuffer->data()[ByteOffset], &Numeric, Length);
				ByteOffset += Length;
				break;
			}
			case DBTYPE_DBDATE:
			{
				const DateTime* DateTime = static_cast<const Elysium::Core::DateTime*>(static_cast<const void*>(_Parameters[i].GetValue()));
				tagDBDATE DBDate;
				DBDate.year = (short)DateTime->GetYear();
				DBDate.month = (short)DateTime->GetMonth();
				DBDate.day = (short)DateTime->GetDay();
				memcpy(&ParameterDataBuffer->data()[ByteOffset], &DBDate, Length);
				ByteOffset += Length;
				break;
			}
			case DBTYPE_DBTIMESTAMP:
			{
				const DateTime* DateTime = static_cast<const Elysium::Core::DateTime*>(static_cast<const void*>(_Parameters[i].GetValue()));
				tagDBTIMESTAMP DBTimestamp;
				DBTimestamp.year = (short)DateTime->GetYear();
				DBTimestamp.month = (short)DateTime->GetMonth();
				DBTimestamp.day = (short)DateTime->GetDay();
				DBTimestamp.hour = (short)DateTime->GetHour();
				DBTimestamp.minute = (short)DateTime->GetMinute();
				DBTimestamp.second = (short)DateTime->GetSecond();
				DBTimestamp.fraction = (short)DateTime->GetMillisecond();
				memcpy(&ParameterDataBuffer->data()[ByteOffset], &DBTimestamp, Length);
				ByteOffset += Length;
				break;
			}
			case DBTYPE_DBTIME2:
			{
				const TimeSpan* TimeSpan = static_cast<const Elysium::Core::TimeSpan*>(static_cast<const void*>(_Parameters[i].GetValue()));
				tagDBTIME2 DBTime;
				DBTime.hour = (unsigned short)TimeSpan->GetHours();
				DBTime.minute = (unsigned short)TimeSpan->GetMinutes();
				DBTime.second = (unsigned short)TimeSpan->GetSeconds();
				DBTime.fraction = (unsigned short)TimeSpan->GetMilliseconds();
				memcpy(&ParameterDataBuffer->data()[ByteOffset], &DBTime, Length);
				ByteOffset += Length;
				break;
			}
			case DBTYPE_DBTIMESTAMPOFFSET:
			{
				const DateTimeOffset* DateTimeOffset = static_cast<const Elysium::Core::DateTimeOffset*>(static_cast<const void*>(_Parameters[i].GetValue()));
				tagDBTIMESTAMPOFFSET DBTimestampOffset;
				DBTimestampOffset.year = (short)DateTimeOffset->GetDateTime().GetYear();
				DBTimestampOffset.month = (short)DateTimeOffset->GetDateTime().GetMonth();
				DBTimestampOffset.day = (short)DateTimeOffset->GetDateTime().GetDay();
				DBTimestampOffset.hour = (short)DateTimeOffset->GetDateTime().GetHour();
				DBTimestampOffset.minute = (short)DateTimeOffset->GetDateTime().GetMinute();
				DBTimestampOffset.second = (short)DateTimeOffset->GetDateTime().GetSecond();
				DBTimestampOffset.fraction = (short)DateTimeOffset->GetDateTime().GetMillisecond();
				DBTimestampOffset.timezone_hour = (short)DateTimeOffset->GetOffset().GetHours();
				DBTimestampOffset.timezone_minute = (short)DateTimeOffset->GetOffset().GetMinutes();
				memcpy(&ParameterDataBuffer->data()[ByteOffset], &DBTimestampOffset, Length);
				ByteOffset += Length;
				break;
			}
			default:
			{
				const BYTE* Value = _Parameters[i].GetValue();
				memcpy(&ParameterDataBuffer->data()[ByteOffset], Value, Length);
				ByteOffset += Length;
				break;
			}
			}
		}

		// create accessor and accessor handle
		IAccessor* NativeParameterAccessor;
		HResult = NativeCommandText->QueryInterface(IID_IAccessor, (void**)&NativeParameterAccessor);
		if (FAILED(HResult))
		{
			SqlNativeException Exception = SqlNativeException(u"Failed to obtain IAccessor interface.\r\n", HResult, NativeCommandText);
			NativeCommandWithParameters->Release();
			NativeCommandText->Release();
			throw Exception;
		}
		HACCESSOR NativeParameterAccessorHandle;
		HResult = NativeParameterAccessor->CreateAccessor(DBACCESSOR_PARAMETERDATA, ParameterCount, ParameterBindings.data(), RowsetByteLength, &NativeParameterAccessorHandle, ParameterBindingsStatus.data());
		if (FAILED(HResult))
		{
			SqlNativeException Exception = SqlNativeException(u"Failed to create accessor.\r\n", HResult, NativeParameterAccessor);
			NativeParameterAccessor->Release();
			NativeCommandWithParameters->Release();
			NativeCommandText->Release();
			throw Exception;
		}

		NativeParameterAccessor->Release();
		NativeCommandWithParameters->Release();

		// populate the command parameters
		CommandParameters->cParamSets = 1;
		CommandParameters->hAccessor = NativeParameterAccessorHandle;
		CommandParameters->pData = &ParameterDataBuffer->data()[0];
	}
}
