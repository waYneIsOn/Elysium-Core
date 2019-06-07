/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEDATAREADER
#define ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEDATAREADER

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_COMMON_DBDATAREADER
#include "../Elysium.Core.Data/DbDataReader.hpp"
#endif

#ifndef __sqlncli_h__
#define _SQLNCLI_OLEDB_IGNORE_DEPRECATION_WARNING_
#define _SQLNCLI_OLEDB_
#include "C:/Program Files (x86)/Microsoft SQL Server/110/SDK/Include/sqlncli.h"
#endif

#ifndef _MAP_
#include <map>
#endif

#ifndef _VECTOR_
#include <vector>
#endif

#pragma warning(disable : 4251)	// disable warning about str::map<...> and std:vector<...>

namespace Elysium
{
	namespace Core
	{
		namespace Data
		{
			namespace SqlNativeClient
			{
				namespace OleDb
				{
					class ELYSIUM_CORE_DATA_SQLNATIVECLIENT_API SqlNativeDataReader final : public Common::DbDataReader
					{
						friend class SqlNativeCommand;
					public:
						~SqlNativeDataReader();

						virtual bool Read() override;
						virtual void Close() override;

						virtual void GetBoolean(uint32_t Index, bool* Value) override;
						virtual void GetByte(unsigned int Index, BYTE* Value) override;
						virtual __int64 GetBytes(unsigned int Index, size_t FieldOffset, BYTE* Value, size_t BufferOffset, size_t Length) override;
						virtual void GetChar(unsigned int Index, char* Value) override;
						virtual __int64 GetChars(unsigned int Index, size_t FieldOffset, char* Value, size_t BufferOffset, size_t Length) override;
						virtual void GetDateTime(uint32_t Index, DateTime* Value) override;
						virtual void GetDateTimeOffset(uint32_t Index, DateTimeOffset* Value) override;
						virtual void GetDecimal(uint32_t Index, Decimal* Value) override;
						virtual void GetDouble(uint32_t Index, double* Value) override;
						virtual void GetFloat(uint32_t Index, float* Value) override;
						virtual void GetGuid(uint32_t Index, Guid* Value) override;
						virtual void GetInt16(uint32_t Index, int16_t* Value) override;
						virtual void GetInt32(uint32_t Index, int32_t* Value) override;
						virtual void GetInt64(uint32_t Index, int64_t* Value) override;
						virtual void GetString(uint32_t Index, std::string* Value) override;
						virtual void GetTimeSpan(uint32_t Index, TimeSpan* Value) override;
						virtual void GetWChar(unsigned int Index, wchar_t* Value) override;
						virtual __int64 GetWChars(unsigned int Index, size_t FieldOffset, wchar_t* Value, size_t BufferOffset, size_t Length) override;

						virtual void GetDataTypeName(uint32_t Index, std::wstring* Value) override;
						virtual void GetName(uint32_t Index, std::wstring* Value) override;
						virtual void GetOrdinal(wchar_t* Name, unsigned __int64* Value) override;

						virtual bool IsDBNull(uint32_t Index) override;
					private:
						SqlNativeDataReader(IRowset* NativeRowset, long RowsAffected, unsigned long FieldCount, DBCOLUMNINFO* ColumnInfo, wchar_t* ColumnNames);

						IRowset* _NativeRowset;
						DBCOLUMNINFO* _ColumnInfo = nullptr;
						wchar_t* _ColumnNames = nullptr;

						unsigned long _NumberOfNonBlobFields;
						unsigned long _NumberOfBuffers;
						std::vector<std::vector<DBBINDING>> _NativeDatabaseBindings;
						std::vector<std::vector<DBBINDSTATUS>> _NativeDatabaseBindStatus;
						std::map<int, DBBINDING*> _IndexBindingMap;
						std::map<int, int> _IndexBufferMap;

						DBROWOFFSET _RowsetByteLength;
						BYTE* _RowDataBuffer;

						IAccessor* _NativeRowAccessor = nullptr;
						std::vector<HACCESSOR> _NativeRowAccessorHandles;

						DBCOUNTITEM _NumberOfRowsObtained = 0;
						HROW _RowHandles[1];
					};
				}
			}
		}
	}
}
#endif
