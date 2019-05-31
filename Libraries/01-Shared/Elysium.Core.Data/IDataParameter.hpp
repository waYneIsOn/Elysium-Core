/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATA_IDATAPARAMETER
#define ELYSIUM_CORE_DATA_IDATAPARAMETER

#ifndef ELYSIUM_CORE_EXPORT
#include "../Elysium.Core/Export.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_DBTYPE
#include "DbType.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_PARAMETERDIRECTION
#include "ParameterDirection.hpp"
#endif

#ifndef _STRING_
#include <string>
#endif

#ifndef ELYSIUM_CORE_DATA_DATAROWVERSION
#include "DataRowVersion.hpp"
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

#ifndef ELYSIUM_CORE_DECIMAL
#include "../Elysium.Core/Decimal.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "../Elysium.Core.IO/Stream.hpp"
#endif

#ifndef ELYSIUM_CORE_GUID
#include "../Elysium.Core/Guid.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_DBNULL
#include "DBNull.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Data
		{
			class EXPORT IDataParameter
			{
			public:
				/// <summary>
				/// Destroy the object using the virtual destructor
				/// </summary>
				virtual ~IDataParameter() {}

				virtual DbType GetDbType() const = 0;
				virtual ParameterDirection GetDirection() const = 0;
				virtual bool GetIsNullable() const = 0;
				virtual std::string GetParameterName() const = 0;
				virtual std::string GetSourceColumn() const = 0;
				virtual DataRowVersion GetSourceVersion() const = 0;
				virtual const BYTE* GetValue() const = 0;
				virtual size_t GetSize() const = 0;
				virtual bool GetIsDBNull() const = 0;

				virtual void SetDbType(DbType Type) = 0;
				virtual void SetDirection(ParameterDirection Direction) = 0;
				virtual void SetIsNullable(bool IsNullable) = 0;
				virtual void SetParameterName(std::string ParameterName) = 0;
				virtual void SetSourceColumn(std::string SourceColumn) = 0;
				virtual void SetSourceVersion(DataRowVersion Version) = 0;
				virtual void SetValue(const DBNull* Value) = 0;
				virtual void SetValue(const bool Value) = 0;
				virtual void SetValue(const BYTE Value) = 0;
				virtual void SetValue(const BYTE* Value, const size_t BufferOffset, const size_t Length) = 0;
				virtual void SetValue(const char Value) = 0;
				virtual void SetValue(const char* Value, const size_t BufferOffset, const size_t Length) = 0;
				virtual void SetValue(const std::string* Value) = 0;
				virtual void SetValue(const DateTime* Value) = 0;
				virtual void SetValue(const DateTimeOffset* Value) = 0;
				virtual void SetValue(const TimeSpan* Value) = 0;
				virtual void SetValue(const Elysium::Core::Decimal* Value) = 0;
				virtual void SetValue(const double Value) = 0;
				virtual void SetValue(const float Value) = 0;
				virtual void SetValue(const Guid* Value) = 0;
				virtual void SetValue(const __int16 Value) = 0;
				virtual void SetValue(const __int32 Value) = 0;
				virtual void SetValue(const __int64 Value) = 0;
				virtual void SetValue(const unsigned __int16 Value) = 0;
				virtual void SetValue(const unsigned __int32 Value) = 0;
				virtual void SetValue(const unsigned __int64 Value) = 0;
				virtual void SetValue(const wchar_t Value) = 0;
				virtual void SetValue(const wchar_t* Value, const size_t BufferOffset, const size_t Length) = 0;
				virtual void SetValue(const std::wstring* Value) = 0;
				virtual void SetValue(const Elysium::Core::IO::Stream* Value) = 0;
			};
		}
	}
}
#endif
