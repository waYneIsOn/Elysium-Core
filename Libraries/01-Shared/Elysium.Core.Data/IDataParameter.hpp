/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_IDATAPARAMETER
#define ELYSIUM_CORE_DATA_IDATAPARAMETER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_DATA_API
#include "API.hpp"
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

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Data
{
	class ELYSIUM_CORE_DATA_API IDataParameter
	{
	public:
		virtual ~IDataParameter() {}
	public:
		virtual const DbType GetDbType() const = 0;

		virtual const ParameterDirection GetDirection() const = 0;

		virtual const bool GetIsNullable() const = 0;

		virtual const Elysium::Core::String GetParameterName() const = 0;

		virtual const Elysium::Core::String GetSourceColumn() const = 0;

		virtual const DataRowVersion GetSourceVersion() const = 0;

		virtual const byte* GetValue() const = 0;

		virtual const Elysium::Core::size GetSize() const = 0;

		virtual const bool GetIsDBNull() const = 0;
	public:
		virtual void SetDbType(const DbType Type) = 0;

		virtual void SetDirection(const ParameterDirection Direction) = 0;

		virtual void SetIsNullable(const bool IsNullable) = 0;

		virtual void SetParameterName(const Elysium::Core::String& ParameterName) = 0;

		virtual void SetSourceColumn(const Elysium::Core::String& SourceColumn) = 0;

		virtual void SetSourceVersion(const DataRowVersion Version) = 0;

		virtual void SetValue(const DBNull& Value) = 0;

		virtual void SetValue(const bool Value) = 0;

		virtual void SetValue(const byte Value) = 0;

		virtual void SetValue(const byte* Value, const Elysium::Core::size Length) = 0;

		virtual void SetValue(const char8_t Value) = 0;

		virtual void SetValue(const char8_t* Value, const Elysium::Core::size Length) = 0;

		virtual void SetValue(const Elysium::Core::String& Value) = 0;

		virtual void SetValue(const DateTime& Value) = 0;

		virtual void SetValue(const DateTimeOffset& Value) = 0;

		virtual void SetValue(const TimeSpan& Value) = 0;

		virtual void SetValue(const Decimal& Value) = 0;

		virtual void SetValue(const double Value) = 0;

		virtual void SetValue(const float Value) = 0;

		virtual void SetValue(const Guid& Value) = 0;

		virtual void SetValue(const Elysium::Core::int16_t Value) = 0;

		virtual void SetValue(const Elysium::Core::int32_t Value) = 0;

		virtual void SetValue(const Elysium::Core::int64_t Value) = 0;

		virtual void SetValue(const Elysium::Core::uint16_t Value) = 0;

		virtual void SetValue(const Elysium::Core::uint32_t Value) = 0;

		virtual void SetValue(const Elysium::Core::uint64_t Value) = 0;

		virtual void SetValue(const Elysium::Core::IO::Stream& Value) = 0;
	};
}
#endif
