/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATA_IDATAREADER
#define ELYSIUM_CORE_DATA_IDATAREADER

#ifndef ELYSIUM_CORE_EXPORT
#include "../Elysium.Core/Export.hpp"
#endif

#ifndef _STRING_
#include <string>
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "../Elysium.Core/Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_DATETIME
#include "../Elysium.Core/DateTime.hpp"
#endif

#ifndef ELYSIUM_CORE_DATETIMEOFFSET
#include "../Elysium.Core/DateTimeOffset.hpp"
#endif

#ifndef ELYSIUM_CORE_GUID
#include "../Elysium.Core/Guid.hpp"
#endif

#ifndef ELYSIUM_CORE_DECIMAL
#include "../Elysium.Core/Decimal.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Data
		{
			class EXPORT IDataReader
			{
			public:
				/// <summary>
				/// Destroy the object using the virtual destructor
				/// </summary>
				virtual ~IDataReader() {}

				virtual unsigned long GetDepth() const = 0;
				virtual unsigned long GetFieldCount() const = 0;

				virtual long GetRecordsAffected() const = 0;

				virtual bool Read() = 0;
				virtual void Close() = 0;

				virtual void GetBoolean(unsigned int Index, bool* Value) = 0;
				virtual void GetByte(unsigned int Index, BYTE* Value) = 0;
				virtual __int64 GetBytes(unsigned int Index, size_t FieldOffset, BYTE* Value, size_t BufferOffset, size_t Length) = 0;
				virtual void GetChar(unsigned int Index, char* Value) = 0;
				virtual __int64 GetChars(unsigned int Index, size_t FieldOffset, char* Value, size_t BufferOffset, size_t Length) = 0;
				virtual void GetDateTime(uint32_t Index, DateTime* Value) = 0;
				virtual void GetDateTimeOffset(uint32_t Index, DateTimeOffset* Value) = 0;	// ToDo: think about whether we actually want that method for every reader (some dmbs do not support this type)
				virtual void GetDecimal(uint32_t Index, Decimal* Value) = 0;
				virtual void GetDouble(uint32_t Index, double* Value) = 0;
				virtual void GetFloat(uint32_t Index, float* Value) = 0;
				virtual void GetGuid(uint32_t Index, Guid* Value) = 0;
				virtual void GetInt16(uint32_t Index, int16_t* Value) = 0;
				virtual void GetInt32(uint32_t Index, int32_t* Value) = 0;
				virtual void GetInt64(uint32_t Index, int64_t* Value) = 0;
				virtual void GetString(uint32_t Index, std::string* Value) = 0;
				virtual void GetTimeSpan(uint32_t Index, TimeSpan* Value) = 0;
				virtual void GetWChar(unsigned int Index, wchar_t* Value) = 0;
				virtual __int64 GetWChars(unsigned int Index, size_t FieldOffset, wchar_t* Value, size_t BufferOffset, size_t Length) = 0;

				virtual void GetDataTypeName(uint32_t Index, std::wstring* Value) = 0;
				virtual void GetName(uint32_t Index, std::wstring* Value) = 0;
				virtual void GetOrdinal(wchar_t* Name, unsigned __int64* Value) = 0;

				virtual bool IsDBNull(uint32_t Index) = 0;
			};
		}
	}
}
#endif
