#include "SqlNativeDataReader.hpp"

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEEXCEPTION
#include "SqlNativeException.hpp"
#endif

#ifndef ELYSIUM_CORE_INDEXOUTOFRANGEEXCEPTION
#include "../Elysium.Core/IndexOutOfRangeException.hpp"
#endif

#ifndef ELYSIUM_CORE_INVALIDCASTEXCEPTION
#include "../Elysium.Core/InvalidCastException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

#define MSSQL_BLOB_SIZE 4069

Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::~SqlNativeDataReader()
{
	Close();
}

bool Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::Read()
{
	HRESULT HResult;

	// clear the buffers
	memset(_RowDataBuffer, 0, _RowsetByteLength);

	// release the previous row (if we've obtained one)
	if (_NumberOfRowsObtained > 0)
	{
		HResult = _NativeRowset->ReleaseRows(_NumberOfRowsObtained, _RowHandles, NULL, NULL, NULL);
	}

	// obtain the desired number of rows (fixed at one for the moment)
	HROW* RowHandlesPointer = &_RowHandles[0];
	if (FAILED(HResult = _NativeRowset->GetNextRows(DB_NULL_HCHAPTER, 0, 1, &_NumberOfRowsObtained, &RowHandlesPointer)))
	{
		throw SqlNativeException(L"Failed to get next row.\r\n", HResult, _NativeRowset);
	}

	// get the row's data if we've received at least one row
	if (_NumberOfRowsObtained > 0)
	{
		for (unsigned long i = 0; i < _NumberOfBuffers; i++)
		{
			if (FAILED(HResult = _NativeRowset->GetData(_RowHandles[0], _NativeRowAccessorHandles[i], _RowDataBuffer)))
			{
				throw SqlNativeException(L"Failed to get row data.\r\n", HResult, _NativeRowset);
			}

			if (_NumberOfNonBlobFields == 0 || i > 0)
			{
				ISequentialStream* SequentialStream = *((ISequentialStream**)(_RowDataBuffer + _NativeDatabaseBindings[i][0].obValue));
				if (SequentialStream != nullptr)
				{
					HResult = SequentialStream->Release();
				}
			}
		}
	}

	// if we've obtained any rows at all, we can try to read again
	return _NumberOfRowsObtained > 0;
}
void Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::Close()
{
	if (_NativeRowAccessor != nullptr)
	{
		for (unsigned long i = 0; i < _NumberOfBuffers; i++)
		{
			_NativeRowAccessor->ReleaseAccessor(_NativeRowAccessorHandles[i], NULL);
		}
		_NativeRowAccessor->Release();
		_NativeRowAccessor = nullptr;
	}

	if (_RowDataBuffer != nullptr)
	{
		delete[] _RowDataBuffer;
		_RowDataBuffer = nullptr;
	}

	if (_ColumnInfo != nullptr)
	{
		//delete[] _ColumnInfo;
		//delete[] _ColumnNames;
	}

	if (_NativeRowset != nullptr)
	{
		_NativeRowset->Release();
		_NativeRowset = nullptr;
	}
}

void Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetBoolean(uint32_t Index, bool * Value)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(L"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_BOOL:
		*Value = static_cast<bool>(*static_cast<unsigned short*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue])));
		break;
	default:
		throw InvalidCastException();
	}
}
void Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetByte(unsigned int Index, BYTE * Value)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(L"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_BYTES:
		memcpy(Value, &_RowDataBuffer[_IndexBindingMap[Index]->obValue], sizeof(BYTE));
		break;
	default:
		throw InvalidCastException();
	}
}
__int64 Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetBytes(unsigned int Index, size_t FieldOffset, BYTE * Value, size_t BufferOffset, size_t Length)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(L"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_VARIANT:
		if (Value == nullptr)
		{
			return (__int64)_RowDataBuffer[_IndexBindingMap[Index]->cbMaxLen];
		}
		else
		{
			memcpy(&Value[BufferOffset], &_RowDataBuffer[_IndexBindingMap[Index]->obValue + FieldOffset], Length);
			return Length;
		}
	case DBTYPE_IUNKNOWN:
	{
		if (_NumberOfRowsObtained == 0)
		{	// ToDo: throw specific exception
			throw Exception(L"InvalidOperationException? Elysium::Core::Data::SqlNativeClient::SqlNativeDataReader::GetBytes");
		}

		HRESULT HResult;
		int BufferIndex = _IndexBufferMap[Index];
		if (FAILED(HResult = _NativeRowset->GetData(_RowHandles[0], _NativeRowAccessorHandles[BufferIndex], _RowDataBuffer)))
		{
			throw SqlNativeException(L"Failed to get row data.\r\n", HResult, _NativeRowset);
		}

		ULONG BLOCK_SIZE = 32;
		ULONG cbRead;
		ISequentialStream* SequentialStream = *((ISequentialStream**)(_RowDataBuffer + _IndexBindingMap[Index]->obValue));
		__int64 AvailableBytes = 0;
		if (Value == nullptr)
		{
			BYTE* IntermediateValue = new BYTE[BLOCK_SIZE];
			do
			{
				if (SUCCEEDED(HResult = SequentialStream->Read(&IntermediateValue[0], BLOCK_SIZE, &cbRead)))
				{
					AvailableBytes += cbRead;
				}
			} while (SUCCEEDED(HResult) && cbRead >= BLOCK_SIZE);
			delete[] IntermediateValue;
		}
		else
		{
			do
			{
				if (SUCCEEDED(HResult = SequentialStream->Read(Value, BLOCK_SIZE, &cbRead)))
				{
					Value += cbRead;
				}
			} while (SUCCEEDED(HResult) && cbRead >= BLOCK_SIZE);
		}
		HResult = SequentialStream->Release();
		return AvailableBytes;
	}
	case DBTYPE_BYTES:
		if (Value == nullptr)
		{
			return (__int64)_RowDataBuffer[_IndexBindingMap[Index]->cbMaxLen];
		}
		else
		{
			memcpy(&Value[BufferOffset], &_RowDataBuffer[_IndexBindingMap[Index]->obValue + FieldOffset], Length);
			return Length;
		}
		break;
	case DBTYPE_UDT:
		// hierarchyid, ...
		if (Value == nullptr)
		{
			return (__int64)_RowDataBuffer[_IndexBindingMap[Index]->cbMaxLen];
		}
		else
		{
			memcpy(&Value[BufferOffset], &_RowDataBuffer[_IndexBindingMap[Index]->obValue + FieldOffset], Length);
			return Length;
		}
		break;
	default:
		throw InvalidCastException();
	}
}
void Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetChar(unsigned int Index, char * Value)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(L"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_STR:
		memcpy(Value, &_RowDataBuffer[_IndexBindingMap[Index]->obValue], sizeof(char));
		break;
	case DBTYPE_XML:
	{
		throw NotImplementedException(L"Elysium::Core::Data::SqlNativeClient::SqlNativeDataReader::GetChar");
	}
	default:
		throw InvalidCastException();
	}
}
__int64 Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetChars(unsigned int Index, size_t FieldOffset, char * Value, size_t BufferOffset, size_t Length)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(L"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_IUNKNOWN:
	{
		if (_NumberOfRowsObtained == 0)
		{	// ToDo: throw specific exception
			throw Exception(L"InvalidOperationException? Elysium::Core::Data::SqlNativeClient::SqlNativeDataReader::GetBytes");
		}

		HRESULT HResult;
		int BufferIndex = _IndexBufferMap[Index];
		if (FAILED(HResult = _NativeRowset->GetData(_RowHandles[0], _NativeRowAccessorHandles[BufferIndex], _RowDataBuffer)))
		{
			throw SqlNativeException(L"Failed to get row data.\r\n", HResult, _NativeRowset);
		}

		ULONG BLOCK_SIZE = 32;
		ULONG cbRead;
		ISequentialStream* SequentialStream = *((ISequentialStream**)(_RowDataBuffer + _IndexBindingMap[Index]->obValue));
		__int64 AvailableBytes = 0;
		if (Value == nullptr)
		{
			BYTE* IntermediateValue = new BYTE[BLOCK_SIZE];
			do
			{
				if (SUCCEEDED(HResult = SequentialStream->Read(&IntermediateValue[0], BLOCK_SIZE, &cbRead)))
				{
					AvailableBytes += cbRead;
				}
			} while (SUCCEEDED(HResult) && cbRead >= BLOCK_SIZE);
			delete[] IntermediateValue;
		}
		else
		{
			do
			{
				if (SUCCEEDED(HResult = SequentialStream->Read(Value, BLOCK_SIZE, &cbRead)))
				{
					Value += cbRead;
				}
			} while (SUCCEEDED(HResult) && cbRead >= BLOCK_SIZE);
		}
		HResult = SequentialStream->Release();
		return AvailableBytes;
	}
	case DBTYPE_STR:
		if (Value == nullptr)
		{
			return (__int64)_IndexBindingMap[Index]->cbMaxLen;
		}
		else
		{
			memcpy(&Value[BufferOffset], &_RowDataBuffer[_IndexBindingMap[Index]->obValue + FieldOffset], Length);
			return Length;
		}
	case DBTYPE_XML:
	{
		throw NotImplementedException(L"Elysium::Core::Data::SqlNativeClient::SqlNativeDataReader::GetChars");
	}
	default:
		throw InvalidCastException();
	}
}
void Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetDateTime(uint32_t Index, DateTime * Value)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(L"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_DATE:
		throw NotImplementedException(L"Elysium::Core::Data::SqlNativeClient::SqlNativeDataReader::GetDateTime");
	case DBTYPE_DBDATE:
	{	// date
		tagDBDATE* Date = static_cast<tagDBDATE*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]));
		*Value = DateTime(Date->year, Date->month, Date->day);
		break;
	}
	case DBTYPE_DBTIME:
		throw NotImplementedException(L"Elysium::Core::Data::SqlNativeClient::SqlNativeDataReader::GetDateTime");
	case DBTYPE_DBTIMESTAMP:
	{	// datetime and datetime2
		tagDBTIMESTAMP* TimeStamp = static_cast<tagDBTIMESTAMP*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]));
		*Value = DateTime(TimeStamp->year, TimeStamp->month, TimeStamp->day, TimeStamp->hour, TimeStamp->minute, TimeStamp->second, TimeStamp->fraction);
		break;
	}
	case DBTYPE_DBTIME2:
	{	// time - ToDo: it probably would make more sense to represent this by a TimeSpan
		tagDBTIME2* Time = static_cast<tagDBTIME2*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]));
		*Value = DateTime(1, 1, 1, Time->hour, Time->minute, Time->second, Time->fraction);
		break;
	}
	default:
		throw InvalidCastException();
	}
}
void Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetDateTimeOffset(uint32_t Index, DateTimeOffset * Value)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(L"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_DBTIMESTAMPOFFSET:
	{	// datetimeoffset
		tagDBTIMESTAMPOFFSET* TimeStampOffset = static_cast<tagDBTIMESTAMPOFFSET*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]));
		*Value = DateTimeOffset(DateTime(TimeStampOffset->year, TimeStampOffset->month, TimeStampOffset->day, TimeStampOffset->hour, TimeStampOffset->minute, TimeStampOffset->second, TimeStampOffset->fraction), TimeSpan(TimeStampOffset->timezone_hour, TimeStampOffset->timezone_minute, 0));
		break;
	}
	default:
		throw InvalidCastException();
	}
}
void Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetDecimal(uint32_t Index, Decimal * Value)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(L"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_NUMERIC:
	{	// decimal
		tagDB_NUMERIC* IntermediateValue = static_cast<tagDB_NUMERIC*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]));
		memcpy(Value, &IntermediateValue->val[0], sizeof(IntermediateValue->val));
		break;
	}
	default:
		throw InvalidCastException();
	}
}
void Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetDouble(uint32_t Index, double * Value)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(L"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_R4:
		*Value = static_cast<double>(*static_cast<float*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue])));
		break;
	case DBTYPE_R8:
		*Value = *static_cast<double*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]));
		break;
	case DBTYPE_CY:
		if (_IndexBindingMap[Index]->cbMaxLen == 4)
		{	// smallmoney(4 byte)
			*Value = static_cast<double>(*static_cast<__int32*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]))) / 10000.0f;
		}
		else if (_IndexBindingMap[Index]->cbMaxLen == 8)
		{	// money (8 byte)
			*Value = static_cast<double>(*static_cast<__int64*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]))) / 10000.0;
		}
		break;
	case DBTYPE_NUMERIC:
	{	// decimal
		tagDB_NUMERIC* IntermediateValue = static_cast<tagDB_NUMERIC*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]));
		memcpy(Value, IntermediateValue->val, sizeof(IntermediateValue->val));
		break;
	}
	default:
		throw InvalidCastException();
	}
}
void Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetFloat(uint32_t Index, float * Value)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(L"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_R4:
		*Value = *static_cast<float*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]));
		break;
	case DBTYPE_R8:
		*Value = static_cast<float>(*static_cast<double*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue])));
		break;
	case DBTYPE_CY:
		if (_IndexBindingMap[Index]->cbMaxLen == 4)
		{	// smallmoney(4 byte)
			*Value = static_cast<float>(*static_cast<__int32*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]))) / 10000.0f;
		}
		else if (_IndexBindingMap[Index]->cbMaxLen == 8)
		{	// money (8 byte)
			*Value = static_cast<float>(static_cast<double>(*static_cast<__int64*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]))) / 10000.0);
		}
		break;
	default:
		throw InvalidCastException();
	}
}
void Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetGuid(uint32_t Index, Guid * Value)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(L"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_GUID:
	{
		*Value = *static_cast<Guid*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]));
		break;
	}
	default:
		throw InvalidCastException();
	}
}
void Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetInt16(uint32_t Index, int16_t * Value)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(L"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_I2:
		*Value = *static_cast<int16_t*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]));
		break;
		/*
		case DBTYPE_I4:
			throw NotImplementedException("Elysium::Core::Data::SqlNativeClient::SqlNativeDataReader::GetInt16");
		*/
	case DBTYPE_UI1:
		// tinyint (ToDo: this is an 8-bit unsigned integer. int16_t can hold each value but is this cast problematic?)
		*Value = *static_cast<int16_t*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]));
		break;
	case DBTYPE_I8:
		throw NotImplementedException(L"Elysium::Core::Data::SqlNativeClient::SqlNativeDataReader::GetInt16");
	default:
		throw InvalidCastException();
	}
}
void Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetInt32(uint32_t Index, int32_t * Value)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(L"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_I4:
		*Value = *static_cast<int32_t*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]));
		break;
		/*
		case DBTYPE_I8:
			throw NotImplementedException("Elysium::Core::Data::SqlNativeClient::SqlNativeDataReader::GetInt32");
		*/
	default:
		throw InvalidCastException();
	}
}
void Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetInt64(uint32_t Index, int64_t * Value)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(L"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_I8:
		*Value = *static_cast<int64_t*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]));
		break;
	case DBTYPE_BYTES:
		*Value = *static_cast<int64_t*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]));
		break;
	default:
		throw InvalidCastException();
	}
}
void Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetString(uint32_t Index, std::string* Value)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(L"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_BSTR:
		throw NotImplementedException(L"Elysium::Core::Data::SqlNativeClient::SqlNativeDataReader::GetString");
	case DBTYPE_STR:
	{
		size_t ResultLength = strlen((char*)&_RowDataBuffer[_IndexBindingMap[Index]->obValue]);
		Value->assign(&_RowDataBuffer[_IndexBindingMap[Index]->obValue], &_RowDataBuffer[_IndexBindingMap[Index]->obValue] + ResultLength);
		break;
	}
	/*
	case DBTYPE_WSTR:
		throw NotImplementedException("Elysium::Core::Data::SqlNativeClient::SqlNativeDataReader::GetString");
	case DBTYPE_XML:
		throw NotImplementedException("Elysium::Core::Data::SqlNativeClient::SqlNativeDataReader::GetString");
	*/
	default:
		throw InvalidCastException();
	}
}
void Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetTimeSpan(uint32_t Index, TimeSpan * Value)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(L"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_DBTIME2:
	{	// time - ToDo: it probably would make more sense to represent this by a TimeSpan
		tagDBTIME2* Time = static_cast<tagDBTIME2*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]));
		*Value = TimeSpan(Time->hour, Time->minute, Time->second, Time->fraction);
		break;
	}
	default:
		throw InvalidCastException();
	}
}
void Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetWChar(unsigned int Index, wchar_t * Value)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(L"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_WSTR:
		*Value = *static_cast<wchar_t*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]));
		break;
	case DBTYPE_XML:
		throw NotImplementedException(L"Elysium::Core::Data::SqlNativeClient::SqlNativeDataReader::GetWChar");
	default:
		throw InvalidCastException();
	}
}
__int64 Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetWChars(unsigned int Index, size_t FieldOffset, wchar_t * Value, size_t BufferOffset, size_t Length)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(L"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_IUNKNOWN:
	{
		if (_NumberOfRowsObtained == 0)
		{	// ToDo: throw specific exception
			throw Exception(L"InvalidOperationException? Elysium::Core::Data::SqlNativeClient::SqlNativeDataReader::GetBytes");
		}

		HRESULT HResult;
		int BufferIndex = _IndexBufferMap[Index];
		if (FAILED(HResult = _NativeRowset->GetData(_RowHandles[0], _NativeRowAccessorHandles[BufferIndex], _RowDataBuffer)))
		{
			throw SqlNativeException(L"Failed to get row data.\r\n", HResult, _NativeRowset);
		}

		ULONG BLOCK_SIZE = 32;
		ULONG cbRead;
		ISequentialStream* SequentialStream = *((ISequentialStream**)(_RowDataBuffer + _IndexBindingMap[Index]->obValue));
		__int64 AvailableBytes = 0;
		if (Value == nullptr)
		{
			BYTE* IntermediateValue = new BYTE[BLOCK_SIZE];
			do
			{
				if (SUCCEEDED(HResult = SequentialStream->Read(&IntermediateValue[0], BLOCK_SIZE, &cbRead)))
				{
					AvailableBytes += cbRead;
				}
			} while (SUCCEEDED(HResult) && cbRead >= BLOCK_SIZE);
			delete[] IntermediateValue;
		}
		else
		{
			do
			{
				if (SUCCEEDED(HResult = SequentialStream->Read(Value, BLOCK_SIZE, &cbRead)))
				{
					Value += cbRead;
				}
			} while (SUCCEEDED(HResult) && cbRead >= BLOCK_SIZE);
		}
		HResult = SequentialStream->Release();
		return AvailableBytes;
	}
	case DBTYPE_WSTR:
		// hierarchyid.ToString(), nchar, ...
		if (Value == nullptr)
		{
			return (__int64)_IndexBindingMap[Index]->cbMaxLen;
		}
		else
		{
			memcpy(&Value[BufferOffset], &_RowDataBuffer[_IndexBindingMap[Index]->obValue + FieldOffset], Length);
			return Length;
		}
	case DBTYPE_XML:
	{
		throw NotImplementedException(L"Elysium::Core::Data::SqlNativeClient::SqlNativeDataReader::GetChars");
	}
	default:
		throw InvalidCastException();
	}
}

void Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetDataTypeName(uint32_t Index, std::wstring * Value)
{
	switch (_ColumnInfo[Index].wType)
	{
	case DBTYPE_EMPTY:
		*Value = L"DBTYPE_EMPTY";
		break;
	case DBTYPE_NULL:
		*Value = L"DBTYPE_NULL";
		break;
	case DBTYPE_I2:
		*Value = L"DBTYPE_I2";
		break;
	case DBTYPE_I4:
		*Value = L"DBTYPE_I4";
		break;
	case DBTYPE_R4:
		*Value = L"DBTYPE_R4";
		break;
	case DBTYPE_R8:
		*Value = L"DBTYPE_R8";
		break;
	case DBTYPE_CY:
		*Value = L"DBTYPE_CY";
		break;
	case DBTYPE_DATE:
		*Value = L"DBTYPE_DATE";
		break;
	case DBTYPE_BSTR:
		*Value = L"DBTYPE_BSTR";
		break;
	case DBTYPE_IDISPATCH:
		*Value = L"DBTYPE_IDISPATCH";
		break;
	case DBTYPE_ERROR:
		*Value = L"DBTYPE_ERROR";
		break;
	case DBTYPE_BOOL:
		*Value = L"DBTYPE_BOOL";
		break;
	case DBTYPE_VARIANT:
		*Value = L"DBTYPE_VARIANT";
		break;
	case DBTYPE_IUNKNOWN:
		*Value = L"DBTYPE_IUNKNOWN";
		break;
	case DBTYPE_DECIMAL:
		*Value = L"DBTYPE_DECIMAL";
		break;
	case DBTYPE_UI1:
		*Value = L"DBTYPE_UI1";
		break;
	case DBTYPE_ARRAY:
		*Value = L"DBTYPE_ARRAY";
		break;
	case DBTYPE_BYREF:
		*Value = L"DBTYPE_BYREF";
		break;
	case DBTYPE_I1:
		*Value = L"DBTYPE_I1";
		break;
	case DBTYPE_UI2:
		*Value = L"DBTYPE_UI2";
		break;
	case DBTYPE_UI4:
		*Value = L"DBTYPE_UI4";
		break;
	case DBTYPE_I8:
		*Value = L"DBTYPE_I8";
		break;
	case DBTYPE_UI8:
		*Value = L"DBTYPE_UI8";
		break;
	case DBTYPE_GUID:
		*Value = L"DBTYPE_GUID";
		break;
	case DBTYPE_VECTOR:
		*Value = L"DBTYPE_VECTOR";
		break;
	case DBTYPE_RESERVED:
		*Value = L"DBTYPE_RESERVED";
		break;
	case DBTYPE_BYTES:
		*Value = L"DBTYPE_BYTES";
		break;
	case DBTYPE_STR:
		*Value = L"DBTYPE_STR";
		break;
	case DBTYPE_WSTR:
		*Value = L"DBTYPE_WSTR";
		break;
	case DBTYPE_NUMERIC:
		*Value = L"DBTYPE_NUMERIC";
		break;
	case DBTYPE_UDT:
		*Value = L"DBTYPE_UDT";
		break;
	case DBTYPE_DBDATE:
		*Value = L"DBTYPE_DBDATE";
		break;
	case DBTYPE_DBTIME:
		*Value = L"DBTYPE_DBTIME";
		break;
	case DBTYPE_DBTIMESTAMP:
		*Value = L"DBTYPE_DBTIMESTAMP";
		break;
	default:
		throw NotImplementedException(L"unhandled datatype in Elysium::Core::Data::SqlNativeClient::SqlNativeDataReader::GetDataTypeName");
	}
}
void Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetName(uint32_t Index, std::wstring * Value)
{
	*Value = _ColumnInfo[Index].pwszName;
}
void Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetOrdinal(wchar_t * Name, unsigned __int64 * Value)
{
	for (unsigned long i = 0; i < _FieldCount; i++)
	{
		if (wcscmp(_ColumnInfo[i].pwszName, Name) == 0)
		{
			*Value = _ColumnInfo[i].iOrdinal - 1;
			return;
		}
	}

	//ToDo: use the given column name - throw IndexOutOfRangeException(Name);
	throw IndexOutOfRangeException();
}

bool Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::IsDBNull(uint32_t Index)
{
	return (DBSTATUSENUM)((BYTE*)_RowDataBuffer)[_IndexBindingMap[Index]->obStatus] == DBSTATUS_S_ISNULL;
}

Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::SqlNativeDataReader(IRowset* NativeRowset, long RowsAffected, unsigned long FieldCount, DBCOLUMNINFO* ColumnInfo, wchar_t* ColumnNames)
	: Elysium::Core::Data::Common::DbDataReader(0, FieldCount, RowsAffected),
	_NativeRowset(NativeRowset), _ColumnInfo(ColumnInfo), _ColumnNames(ColumnNames)
{
	HRESULT HResult;

	// get the number of blob-fields
	unsigned long NumberOfBlobFields = 0;
	for (unsigned long i = 0; i < _FieldCount; i++)
	{
		if (_ColumnInfo[i].ulColumnSize > MSSQL_BLOB_SIZE || _ColumnInfo[i].wType == DBTYPE_IUNKNOWN)
		{
			NumberOfBlobFields++;
		}
	}
	_NumberOfNonBlobFields = _FieldCount - NumberOfBlobFields;

	// create all required arrays
	_NumberOfBuffers = _NumberOfNonBlobFields == 0 ? NumberOfBlobFields : NumberOfBlobFields + 1;
	_NativeDatabaseBindings = std::vector<std::vector<DBBINDING>>(_NumberOfBuffers);
	_NativeDatabaseBindStatus = std::vector<std::vector<DBBINDSTATUS>>(_NumberOfBuffers);
	if (_NumberOfNonBlobFields > 0)
	{
		_NativeDatabaseBindings[0] = std::vector<DBBINDING>(_NumberOfNonBlobFields);
		_NativeDatabaseBindStatus[0] = std::vector<DBBINDSTATUS>(_NumberOfNonBlobFields);
		for (unsigned long i = 1; i < _NativeDatabaseBindings.size(); i++)
		{
			_NativeDatabaseBindings[i] = std::vector<DBBINDING>(1);
			_NativeDatabaseBindStatus[i] = std::vector<DBBINDSTATUS>(1);
		}
	}
	else
	{
		for (unsigned long i = 0; i < _NativeDatabaseBindings.size(); i++)
		{
			_NativeDatabaseBindings[i] = std::vector<DBBINDING>(1);
			_NativeDatabaseBindStatus[i] = std::vector<DBBINDSTATUS>(1);
		}
	}
	_NativeRowAccessorHandles = std::vector<HACCESSOR>(_NumberOfBuffers);

	// create the non-blob columns binding
	unsigned long ColumnIndex = 0;
	for (unsigned long i = 0; i < _FieldCount; i++)
	{
		if (_ColumnInfo[i].ulColumnSize <= MSSQL_BLOB_SIZE && _ColumnInfo[i].wType != DBTYPE_IUNKNOWN)
		{
			_NativeDatabaseBindings[0][ColumnIndex].iOrdinal = i + 1;	// the bookmark column holds the ordinal 0 which is why we need to add 1
			_NativeDatabaseBindings[0][ColumnIndex].obLength = _RowsetByteLength;
			_NativeDatabaseBindings[0][ColumnIndex].obStatus = _NativeDatabaseBindings[0][ColumnIndex].obLength + sizeof(DBLENGTH);
			_NativeDatabaseBindings[0][ColumnIndex].obValue = _NativeDatabaseBindings[0][ColumnIndex].obStatus + sizeof(DBSTATUS);
			_NativeDatabaseBindings[0][ColumnIndex].pTypeInfo = NULL;
			_NativeDatabaseBindings[0][ColumnIndex].pBindExt = NULL;
			_NativeDatabaseBindings[0][ColumnIndex].dwPart = DBPART_VALUE | DBPART_STATUS | DBPART_LENGTH;
			_NativeDatabaseBindings[0][ColumnIndex].dwMemOwner = DBMEMOWNER_CLIENTOWNED;
			_NativeDatabaseBindings[0][ColumnIndex].eParamIO = DBPARAMIO_NOTPARAM;
			_NativeDatabaseBindings[0][ColumnIndex].dwFlags = 0;

			_NativeDatabaseBindings[0][ColumnIndex].pObject = NULL;
			_NativeDatabaseBindings[0][ColumnIndex].wType = _ColumnInfo[i].wType;
			_NativeDatabaseBindings[0][ColumnIndex].bPrecision = _ColumnInfo[i].bPrecision;
			_NativeDatabaseBindings[0][ColumnIndex].bScale = _ColumnInfo[i].bScale;
			_NativeDatabaseBindings[0][ColumnIndex].cbMaxLen = (_ColumnInfo[i].wType == DBTYPE_WSTR) ? _ColumnInfo[i].ulColumnSize * 2 + 2 : _ColumnInfo[i].ulColumnSize;
			if (_ColumnInfo[i].wType == DBTYPE_STR)
			{
				_NativeDatabaseBindings[0][ColumnIndex].cbMaxLen++;
			}

			_IndexBindingMap[i] = &_NativeDatabaseBindings[0][ColumnIndex];
			_IndexBufferMap[i] = 0;
			_RowsetByteLength += _NativeDatabaseBindings[0][ColumnIndex].cbMaxLen + sizeof(DBLENGTH) + sizeof(DBSTATUS);
			ColumnIndex++;
		}
	}

	// create the blob columns binding
	_NumberOfNonBlobFields == 0 ? ColumnIndex = 0 : ColumnIndex = 1;	// start at one because index zero points to the non-blob columns
	for (unsigned long i = 0; i < _FieldCount; i++)
	{
		if (_ColumnInfo[i].ulColumnSize > MSSQL_BLOB_SIZE || _ColumnInfo[i].wType == DBTYPE_IUNKNOWN)
		{
			DBOBJECT dbobject = DBOBJECT();
			dbobject.dwFlags = STGM_READ;
			dbobject.iid = IID_ISequentialStream;

			_NativeDatabaseBindings[ColumnIndex][0].iOrdinal = i + 1;	// the bookmark column holds the ordinal 0 which is why we need to add 1
			_NativeDatabaseBindings[ColumnIndex][0].obLength = _RowsetByteLength;
			_NativeDatabaseBindings[ColumnIndex][0].obStatus = _NativeDatabaseBindings[ColumnIndex][0].obLength + sizeof(DBLENGTH);
			_NativeDatabaseBindings[ColumnIndex][0].obValue = _NativeDatabaseBindings[ColumnIndex][0].obStatus + sizeof(DBSTATUS);
			_NativeDatabaseBindings[ColumnIndex][0].pTypeInfo = NULL;
			_NativeDatabaseBindings[ColumnIndex][0].pBindExt = NULL;
			_NativeDatabaseBindings[ColumnIndex][0].dwPart = DBPART_VALUE | DBPART_STATUS | DBPART_LENGTH;
			_NativeDatabaseBindings[ColumnIndex][0].dwMemOwner = DBMEMOWNER_CLIENTOWNED;
			_NativeDatabaseBindings[ColumnIndex][0].eParamIO = DBPARAMIO_NOTPARAM;
			_NativeDatabaseBindings[ColumnIndex][0].dwFlags = 0;

			_NativeDatabaseBindings[ColumnIndex][0].pObject = &dbobject;
			_NativeDatabaseBindings[ColumnIndex][0].wType = DBTYPE_IUNKNOWN;
			_NativeDatabaseBindings[ColumnIndex][0].bPrecision = 0;
			_NativeDatabaseBindings[ColumnIndex][0].bScale = 0;
			_NativeDatabaseBindings[ColumnIndex][0].cbMaxLen = sizeof(ISequentialStream*);

			_IndexBindingMap[i] = &_NativeDatabaseBindings[ColumnIndex][0];
			_IndexBufferMap[i] = ColumnIndex;
			_RowsetByteLength += _NativeDatabaseBindings[ColumnIndex][0].cbMaxLen + sizeof(DBLENGTH) + sizeof(DBSTATUS);
			ColumnIndex++;
		}
	}

	// create the buffer to store row values in
	_RowDataBuffer = new BYTE[_RowsetByteLength];

	// create the row accessor
	if (FAILED(HResult = _NativeRowset->QueryInterface(IID_IAccessor, (void**)&_NativeRowAccessor)))
	{
		throw SqlNativeException(L"Failed to obtain IAccessor interface.\r\n", HResult, _NativeRowset);
	}
	if (_NumberOfNonBlobFields > 0)
	{
		if (FAILED(HResult = _NativeRowAccessor->CreateAccessor(
			DBACCESSOR_ROWDATA,					// Accessor will be used to retrieve row data.
			_NumberOfNonBlobFields,				// Number of columns being bound
			_NativeDatabaseBindings[0].data(),	// Structure containing bind info
			0,									// Not used for row accessors
			&_NativeRowAccessorHandles[0],		// Returned accessor handle
			_NativeDatabaseBindStatus[0].data()	// Information about binding validity
		)))
		{
			throw SqlNativeException(L"Failed to create accessor.\r\n", HResult, _NativeRowAccessor);
		}
	}
	if (NumberOfBlobFields > 0)
	{
		int StartIndex = 0;
		if (_NumberOfNonBlobFields > 0)
		{
			StartIndex++;
		}
		for (unsigned long i = StartIndex; i < _NumberOfBuffers; i++)
		{
			if (FAILED(HResult = _NativeRowAccessor->CreateAccessor(
				DBACCESSOR_ROWDATA,					// Accessor will be used to retrieve row data.
				1,									// Number of columns being bound
				_NativeDatabaseBindings[i].data(),	// Structure containing bind info
				0,									// Not used for row accessors
				&_NativeRowAccessorHandles[i],		// Returned accessor handle
				_NativeDatabaseBindStatus[i].data()	// Information about binding validity
			)))
			{
				throw SqlNativeException(L"Failed to create accessor.\r\n", HResult, _NativeRowAccessor);
			}
		}
	}
}
