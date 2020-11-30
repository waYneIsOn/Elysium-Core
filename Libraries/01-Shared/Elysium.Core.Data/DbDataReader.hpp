/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_COMMON_DBDATAREADER
#define ELYSIUM_CORE_DATA_COMMON_DBDATAREADER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_DATA_IDATAREADER
#include "IDataReader.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_IDBCONNECTION
#include "IDbConnection.hpp"
#endif

namespace Elysium::Core::Data::Common
{
	class ELYSIUM_CORE_DATA_API DbDataReader : public IDataReader
	{
	public:
		/// <summary>
		/// Destroy the object using the virtual destructor
		/// </summary>
		virtual ~DbDataReader() {}

		virtual const size_t GetDepth() const override;
		virtual const size_t GetFieldCount() const;

		virtual const size_t GetRecordsAffected() const override;

		virtual const bool GetBoolean(const Elysium::Core::uint32_t Index) = 0;
		virtual const Elysium::Core::byte GetByte(const Elysium::Core::uint32_t Index) = 0;
		virtual const Elysium::Core::uint64_t GetBytes(const Elysium::Core::uint32_t Index, const size_t FieldOffset, byte* Value, const size_t Length) = 0;
		virtual const char8_t GetChar(const Elysium::Core::uint32_t Index) = 0;
		virtual const Elysium::Core::uint64_t GetChars(const Elysium::Core::uint32_t Index, const size_t FieldOffset, char8_t* Value, const size_t Length) = 0;
		virtual const Elysium::Core::DateTime GetDateTime(const Elysium::Core::uint32_t Index) = 0;
		virtual const Elysium::Core::DateTimeOffset GetDateTimeOffset(const Elysium::Core::uint32_t Index) = 0;	// ToDo: think about whether we actually want that method for every reader (some dmbs do not support this type)
		virtual const Elysium::Core::Decimal GetDecimal(const Elysium::Core::uint32_t Index) = 0;
		virtual const double GetDouble(const Elysium::Core::uint32_t Index) = 0;
		virtual const float GetFloat(const Elysium::Core::uint32_t Index) = 0;
		virtual const Elysium::Core::Guid GetGuid(const Elysium::Core::uint32_t Index) = 0;
		virtual const Elysium::Core::int16_t GetInt16(const Elysium::Core::uint32_t Index) = 0;
		virtual const Elysium::Core::int32_t GetInt32(const Elysium::Core::uint32_t Index) = 0;
		virtual const Elysium::Core::int64_t GetInt64(const Elysium::Core::uint32_t Index) = 0;
		virtual const Elysium::Core::String GetString(const Elysium::Core::uint32_t Index) = 0;
		virtual const Elysium::Core::TimeSpan GetTimeSpan(const Elysium::Core::uint32_t Index) = 0;

		virtual const Elysium::Core::String GetDataTypeName(const Elysium::Core::uint32_t Index) = 0;
		virtual const Elysium::Core::String GetName(const Elysium::Core::uint32_t Index) = 0;
		virtual const Elysium::Core::uint64_t GetOrdinal(const Elysium::Core::String& Name) = 0;

		virtual const bool IsDBNull(const Elysium::Core::uint32_t Index) = 0;
	protected:
		DbDataReader(const size_t NumberOfRows, const size_t FieldCount, const size_t RecordsAffected);
		DbDataReader();

		size_t _NumberOfRows;
		size_t _FieldCount;
		size_t _RecordsAffected;
	};
}
#endif
