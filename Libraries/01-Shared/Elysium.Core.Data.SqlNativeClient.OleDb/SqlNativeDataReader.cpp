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

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "../Elysium.Core.Template/CharacterTraits.hpp"
#endif

#define MSSQL_BLOB_SIZE 4069

Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::~SqlNativeDataReader()
{
	Close();
}

const bool Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetIsClosed() const
{
	return _NativeRowAccessor == nullptr;
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

const bool Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::NextResult()
{	// ToDo
	throw 1;
}

const bool Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::Read()
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
		throw SqlNativeException(HResult, _NativeRowset);
	}

	// get the row's data if we've received at least one row
	if (_NumberOfRowsObtained > 0)
	{
		for (unsigned long i = 0; i < _NumberOfBuffers; i++)
		{
			if (FAILED(HResult = _NativeRowset->GetData(_RowHandles[0], _NativeRowAccessorHandles[i], _RowDataBuffer)))
			{
				throw SqlNativeException(HResult, _NativeRowset);
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

const bool Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetBoolean(const Elysium::Core::uint32_t Index)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(u8"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_BOOL:
		return static_cast<bool>(*static_cast<unsigned short*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue])));
	default:
		throw InvalidCastException();
	}
}

const Elysium::Core::byte Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetByte(const Elysium::Core::uint32_t Index)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(u8"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_BYTES:
		return _RowDataBuffer[_IndexBindingMap[Index]->obValue];
		//memcpy(Value, &_RowDataBuffer[_IndexBindingMap[Index]->obValue], sizeof(byte));
	default:
		throw InvalidCastException();
	}
}

const Elysium::Core::uint64_t Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetBytes(const Elysium::Core::uint32_t Index, const Elysium::Core::size FieldOffset, byte * Value, const Elysium::Core::size Length)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(u8"Index");
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
			memcpy(&Value[0], &_RowDataBuffer[_IndexBindingMap[Index]->obValue + FieldOffset], Length);
			return Length;
		}
	case DBTYPE_IUNKNOWN:
	{
		if (_NumberOfRowsObtained == 0)
		{	// ToDo: throw specific exception
			throw Exception(u8"InvalidOperationException? Elysium::Core::Data::SqlNativeClient::SqlNativeDataReader::GetBytes");
		}

		HRESULT HResult;
		int BufferIndex = _IndexBufferMap[Index];
		if (FAILED(HResult = _NativeRowset->GetData(_RowHandles[0], _NativeRowAccessorHandles[BufferIndex], _RowDataBuffer)))
		{
			throw SqlNativeException(HResult, _NativeRowset);
		}

		ULONG BLOCK_SIZE = 32;
		ULONG cbRead;
		ISequentialStream* SequentialStream = *((ISequentialStream**)(_RowDataBuffer + _IndexBindingMap[Index]->obValue));
		__int64 AvailableBytes = 0;
		if (Value == nullptr)
		{
			byte* IntermediateValue = new byte[BLOCK_SIZE];
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
			//return _IndexBindingMap[Index]->obLength;
			return _RowDataBuffer[_IndexBindingMap[Index]->obLength];
		}
		else
		{
			memcpy(&Value[0], &_RowDataBuffer[_IndexBindingMap[Index]->obValue + FieldOffset], Length);
			return Length;
		}
		break;
	case DBTYPE_UDT:
		// hierarchyid, ...
		if (Value == nullptr)
		{
			return _RowDataBuffer[_IndexBindingMap[Index]->obLength];
		}
		else
		{
			memcpy(&Value[0], &_RowDataBuffer[_IndexBindingMap[Index]->obValue + FieldOffset], Length);
			return Length;
		}
		break;
	default:
		throw InvalidCastException();
	}
}

const char8_t Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetChar(const Elysium::Core::uint32_t Index)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(u8"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_STR:
		return _RowDataBuffer[_IndexBindingMap[Index]->obValue];
		//memcpy(Value, &_RowDataBuffer[_IndexBindingMap[Index]->obValue], sizeof(char));
	case DBTYPE_WSTR:
	{
		wchar_t Utf16LEChar = (wchar_t)_RowDataBuffer[_IndexBindingMap[Index]->obValue];

		// ToDo: Encoding::GetChar?
		Elysium::Core::String String = _WindowsEncoding.GetString((Elysium::Core::byte*)&Utf16LEChar, sizeof(wchar_t));

		return String[0];
	}
	case DBTYPE_XML:
	{
		throw NotImplementedException(u8"Elysium::Core::Data::SqlNativeClient::SqlNativeDataReader::GetChar");
	}
	default:
		throw InvalidCastException();
	}
}

const Elysium::Core::uint64_t Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetChars(const Elysium::Core::uint32_t Index, const Elysium::Core::size FieldOffset, char8_t * Value, const Elysium::Core::size Length)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(u8"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_IUNKNOWN:
	{
		if (_NumberOfRowsObtained == 0)
		{	// ToDo: throw specific exception
			throw Exception(u8"InvalidOperationException? Elysium::Core::Data::SqlNativeClient::SqlNativeDataReader::GetBytes");
		}

		HRESULT HResult;
		int BufferIndex = _IndexBufferMap[Index];
		if (FAILED(HResult = _NativeRowset->GetData(_RowHandles[0], _NativeRowAccessorHandles[BufferIndex], _RowDataBuffer)))
		{
			throw SqlNativeException(HResult, _NativeRowset);
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
			memcpy(&Value[0], &_RowDataBuffer[_IndexBindingMap[Index]->obValue + FieldOffset], Length);
			return Length;
		}
	case DBTYPE_WSTR:
		if (Value == nullptr)
		{
			return _RowDataBuffer[_IndexBindingMap[Index]->obLength] / sizeof(wchar_t);
		}
		else
		{
			wchar_t* Utf16LEChars = (wchar_t*)&_RowDataBuffer[_IndexBindingMap[Index]->obValue + FieldOffset];
			Elysium::Core::String String = _WindowsEncoding.GetString((Elysium::Core::byte*)Utf16LEChars, Length * sizeof(wchar_t));
			
			memcpy(&Value[0], &String[0], String.GetLength() + sizeof(char8_t));
			return Length;
		}
	case DBTYPE_XML:
	{
		throw NotImplementedException(u8"Elysium::Core::Data::SqlNativeClient::SqlNativeDataReader::GetChars");
	}
	default:
		throw InvalidCastException();
	}
}

const Elysium::Core::DateTime Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetDateTime(const Elysium::Core::uint32_t Index)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(u8"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_DATE:
		throw NotImplementedException(u8"Elysium::Core::Data::SqlNativeClient::SqlNativeDataReader::GetDateTime");
	case DBTYPE_DBDATE:
	{	// date
		tagDBDATE* Date = static_cast<tagDBDATE*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]));
		return DateTime(Date->year, Date->month, Date->day);
	}
	case DBTYPE_DBTIME:
		throw NotImplementedException(u8"Elysium::Core::Data::SqlNativeClient::SqlNativeDataReader::GetDateTime");
	case DBTYPE_DBTIMESTAMP:
	{	// datetime and datetime2
		tagDBTIMESTAMP* TimeStamp = static_cast<tagDBTIMESTAMP*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]));
		return DateTime(TimeStamp->year, TimeStamp->month, TimeStamp->day, TimeStamp->hour, TimeStamp->minute, TimeStamp->second, TimeStamp->fraction);
	}
	case DBTYPE_DBTIME2:
	{	// time - ToDo: it probably would make more sense to represent this by a TimeSpan
		tagDBTIME2* Time = static_cast<tagDBTIME2*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]));
		return DateTime(1, 1, 1, Time->hour, Time->minute, Time->second, Time->fraction);
	}
	default:
		throw InvalidCastException();
	}
}

const Elysium::Core::DateTimeOffset Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetDateTimeOffset(const Elysium::Core::uint32_t Index)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(u8"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_DBTIMESTAMPOFFSET:
	{	// datetimeoffset
		tagDBTIMESTAMPOFFSET* TimeStampOffset = static_cast<tagDBTIMESTAMPOFFSET*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]));
		return DateTimeOffset(DateTime(TimeStampOffset->year, TimeStampOffset->month, TimeStampOffset->day, TimeStampOffset->hour, TimeStampOffset->minute, TimeStampOffset->second, TimeStampOffset->fraction), TimeSpan(TimeStampOffset->timezone_hour, TimeStampOffset->timezone_minute, 0));
	}
	default:
		throw InvalidCastException();
	}
}

const Elysium::Core::Decimal Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetDecimal(const Elysium::Core::uint32_t Index)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(u8"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_NUMERIC:
	{	// decimal
		tagDB_NUMERIC* IntermediateValue = static_cast<tagDB_NUMERIC*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]));
		assert(sizeof(IntermediateValue->val), sizeof(Elysium::Core::Decimal));
		Elysium::Core::Decimal Result = Elysium::Core::Decimal();
		memcpy((void*)&Result, &IntermediateValue->val[0], sizeof(IntermediateValue->val));
		return Result;
	}
	default:
		throw InvalidCastException();
	}
}

const double Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetDouble(const Elysium::Core::uint32_t Index)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(u8"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_R4:
		return static_cast<double>(*static_cast<float*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue])));
	case DBTYPE_R8:
		return *static_cast<double*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]));
	case DBTYPE_CY:
		if (_IndexBindingMap[Index]->cbMaxLen == 4)
		{	// smallmoney(4 byte)
			return static_cast<double>(*static_cast<__int32*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]))) / 10000.0f;
		}
		else if (_IndexBindingMap[Index]->cbMaxLen == 8)
		{	// money (8 byte)
			return static_cast<double>(*static_cast<__int64*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]))) / 10000.0;
		}
		else
		{	// ToDo
			throw 1;
		}
	case DBTYPE_NUMERIC:
	{	// decimal - ToDo
		throw 1;
		/*
		tagDB_NUMERIC* IntermediateValue = static_cast<tagDB_NUMERIC*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]));
		memcpy(Value, IntermediateValue->val, sizeof(IntermediateValue->val));
		break;
		*/
	}
	default:
		throw InvalidCastException();
	}
}

const float Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetFloat(const Elysium::Core::uint32_t Index)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(u8"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_R4:
		return *static_cast<float*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]));
	case DBTYPE_R8:
		return static_cast<float>(*static_cast<double*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue])));
	case DBTYPE_CY:
		if (_IndexBindingMap[Index]->cbMaxLen == 4)
		{	// smallmoney(4 byte)
			return static_cast<float>(*static_cast<__int32*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]))) / 10000.0f;
		}
		else if (_IndexBindingMap[Index]->cbMaxLen == 8)
		{	// money (8 byte)
			return static_cast<float>(static_cast<double>(*static_cast<__int64*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]))) / 10000.0);
		}
		else
		{	// ToDo
			throw 1;
		}
	default:
		throw InvalidCastException();
	}
}

const Elysium::Core::Guid Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetGuid(const Elysium::Core::uint32_t Index)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(u8"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_GUID:
	{
		return *static_cast<Guid*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]));
	}
	default:
		throw InvalidCastException();
	}
}

const Elysium::Core::int16_t Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetInt16(const Elysium::Core::uint32_t Index)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(u8"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_I2:
		return *static_cast<int16_t*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]));
		/*
		case DBTYPE_I4:
			throw NotImplementedException("Elysium::Core::Data::SqlNativeClient::SqlNativeDataReader::GetInt16");
		*/
	case DBTYPE_UI1:
		// tinyint (ToDo: this is an 8-bit unsigned integer. int16_t can hold each value but is this cast problematic?)
		return *static_cast<int16_t*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]));
	case DBTYPE_I8:
		throw NotImplementedException(u8"Elysium::Core::Data::SqlNativeClient::SqlNativeDataReader::GetInt16");
	default:
		throw InvalidCastException();
	}
}

const Elysium::Core::int32_t Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetInt32(const Elysium::Core::uint32_t Index)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(u8"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_I4:
		return *static_cast<int32_t*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]));
		/*
		case DBTYPE_I8:
			throw NotImplementedException("Elysium::Core::Data::SqlNativeClient::SqlNativeDataReader::GetInt32");
		*/
	default:
		throw InvalidCastException();
	}
}

const Elysium::Core::int64_t Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetInt64(const Elysium::Core::uint32_t Index)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(u8"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_I8:
		return *static_cast<int64_t*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]));
	case DBTYPE_BYTES:
		return *static_cast<int64_t*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]));
	default:
		throw InvalidCastException();
	}
}

const Elysium::Core::String Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetString(const Elysium::Core::uint32_t Index)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(u8"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_BSTR:
		throw NotImplementedException(u8"Elysium::Core::Data::SqlNativeClient::SqlNativeDataReader::GetString");
	case DBTYPE_STR:
	{
		Elysium::Core::size ResultLength = strlen((char*)&_RowDataBuffer[_IndexBindingMap[Index]->obValue]);
		return Elysium::Core::String((char8_t*)&_RowDataBuffer[_IndexBindingMap[Index]->obValue], ResultLength);
		//Value->assign(&_RowDataBuffer[_IndexBindingMap[Index]->obValue], &_RowDataBuffer[_IndexBindingMap[Index]->obValue] + ResultLength);
		//break;
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

const Elysium::Core::TimeSpan Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetTimeSpan(const Elysium::Core::uint32_t Index)
{
	if (Index > _FieldCount)
	{
		throw IndexOutOfRangeException(u8"Index");
	}

	switch (_IndexBindingMap[Index]->wType)
	{
	case DBTYPE_DBTIME2:
	{	// time - ToDo: it probably would make more sense to represent this by a TimeSpan
		tagDBTIME2* Time = static_cast<tagDBTIME2*>((void*)(&_RowDataBuffer[_IndexBindingMap[Index]->obValue]));
		return TimeSpan(Time->hour, Time->minute, Time->second, Time->fraction);
	}
	default:
		throw InvalidCastException();
	}
}

const Elysium::Core::String  Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetDataTypeName(uint32_t Index)
{
	switch (_ColumnInfo[Index].wType)
	{
	case DBTYPE_EMPTY:
		return u8"DBTYPE_EMPTY";
	case DBTYPE_NULL:
		return u8"DBTYPE_NULL";
	case DBTYPE_I2:
		return u8"DBTYPE_I2";
	case DBTYPE_I4:
		return u8"DBTYPE_I4";
	case DBTYPE_R4:
		return u8"DBTYPE_R4";
	case DBTYPE_R8:
		return u8"DBTYPE_R8";
	case DBTYPE_CY:
		return u8"DBTYPE_CY";
	case DBTYPE_DATE:
		return u8"DBTYPE_DATE";
	case DBTYPE_BSTR:
		return u8"DBTYPE_BSTR";
	case DBTYPE_IDISPATCH:
		return u8"DBTYPE_IDISPATCH";
	case DBTYPE_ERROR:
		return u8"DBTYPE_ERROR";
	case DBTYPE_BOOL:
		return u8"DBTYPE_BOOL";
	case DBTYPE_VARIANT:
		return u8"DBTYPE_VARIANT";
	case DBTYPE_IUNKNOWN:
		return u8"DBTYPE_IUNKNOWN";
	case DBTYPE_DECIMAL:
		return u8"DBTYPE_DECIMAL";
	case DBTYPE_UI1:
		return u8"DBTYPE_UI1";
	case DBTYPE_ARRAY:
		return u8"DBTYPE_ARRAY";
	case DBTYPE_BYREF:
		return u8"DBTYPE_BYREF";
	case DBTYPE_I1:
		return u8"DBTYPE_I1";
	case DBTYPE_UI2:
		return u8"DBTYPE_UI2";
	case DBTYPE_UI4:
		return u8"DBTYPE_UI4";
	case DBTYPE_I8:
		return u8"DBTYPE_I8";
	case DBTYPE_UI8:
		return u8"DBTYPE_UI8";
	case DBTYPE_GUID:
		return u8"DBTYPE_GUID";
	case DBTYPE_VECTOR:
		return u8"DBTYPE_VECTOR";
	case DBTYPE_RESERVED:
		return u8"DBTYPE_RESERVED";
	case DBTYPE_BYTES:
		return u8"DBTYPE_BYTES";
	case DBTYPE_STR:
		return u8"DBTYPE_STR";
	case DBTYPE_WSTR:
		return u8"DBTYPE_WSTR";
	case DBTYPE_NUMERIC:
		return u8"DBTYPE_NUMERIC";
	case DBTYPE_UDT:
		return u8"DBTYPE_UDT";
	case DBTYPE_DBDATE:
		return u8"DBTYPE_DBDATE";
	case DBTYPE_DBTIME:
		return u8"DBTYPE_DBTIME";
	case DBTYPE_DBTIMESTAMP:
		return u8"DBTYPE_DBTIMESTAMP";
	default:
		throw NotImplementedException(u8"unhandled datatype in Elysium::Core::Data::SqlNativeClient::SqlNativeDataReader::GetDataTypeName");
	}
}

const Elysium::Core::String Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetName(const Elysium::Core::uint32_t Index)
{
	wchar_t* Name = _ColumnInfo[Index].pwszName;
	return _WindowsEncoding.GetString((byte*)Name, Template::Text::CharacterTraits<wchar_t>::GetSize(Name));
}

const Elysium::Core::uint64_t Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::GetOrdinal(const Elysium::Core::String & Name)
{	
	Collections::Template::Array<byte> Bytes = _WindowsEncoding.GetBytes(&Name[0], Name.GetLength(), sizeof(wchar_t));

	for (unsigned long i = 0; i < _FieldCount; i++)
	{
		if (wcscmp(_ColumnInfo[i].pwszName, (wchar_t*)&Bytes[0]) == 0)
		{
			return _ColumnInfo[i].iOrdinal - 1;
		}
	}

	//ToDo: use the given column name - throw IndexOutOfRangeException(Name);
	throw IndexOutOfRangeException();
}

const bool Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::IsDBNull(const Elysium::Core::uint32_t Index)
{
	return (DBSTATUSENUM)((BYTE*)_RowDataBuffer)[_IndexBindingMap[Index]->obStatus] == DBSTATUS_S_ISNULL;
}

Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeDataReader::SqlNativeDataReader(IRowset* NativeRowset, const Elysium::Core::size RowsAffected, const Elysium::Core::size FieldCount,
	const DBCOLUMNINFO* ColumnInfo, const wchar_t* ColumnNames)
	: Elysium::Core::Data::Common::DbDataReader(0, FieldCount, RowsAffected),
	_NativeRowset(NativeRowset), _ColumnInfo(ColumnInfo), _ColumnNames(ColumnNames)
{
	HRESULT HResult;

	// get the number of blob-fields
	Elysium::Core::size NumberOfBlobFields = 0;
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
	for (Elysium::Core::size i = 0; i < _FieldCount; i++)
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
	for (Elysium::Core::size i = 0; i < _FieldCount; i++)
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
		throw SqlNativeException(HResult, _NativeRowset);
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
			throw SqlNativeException(HResult, _NativeRowAccessor);
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
				throw SqlNativeException(HResult, _NativeRowAccessor);
			}
		}
	}
}
