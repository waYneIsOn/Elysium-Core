/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEDATAREADER
#define ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEDATAREADER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_COMMON_DBDATAREADER
#include "../Elysium.Core.Data/DbDataReader.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
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

namespace Elysium::Core::Data::SqlNativeClient::OleDb
{
	class ELYSIUM_CORE_DATA_SQLNATIVECLIENT_API SqlNativeDataReader final : public Common::DbDataReader
	{
		friend class SqlNativeCommand;
	public:
		~SqlNativeDataReader();

		virtual const bool GetIsClosed() const override;

		virtual void Close() override;
		virtual const bool NextResult() override;
		virtual const bool Read() override;

		virtual const bool GetBoolean(const Elysium::Core::uint32_t Index) override;
		virtual const Elysium::Core::byte GetByte(const Elysium::Core::uint32_t Index) override;
		virtual const Elysium::Core::uint64_t GetBytes(const Elysium::Core::uint32_t Index, const Elysium::Core::size FieldOffset, byte* Value, const Elysium::Core::size Length) override;
		virtual const char8_t GetChar(const Elysium::Core::uint32_t Index) override;
		virtual const Elysium::Core::uint64_t GetChars(const Elysium::Core::uint32_t Index, const Elysium::Core::size FieldOffset, char8_t* Value, const Elysium::Core::size Length) override;
		virtual const Elysium::Core::DateTime GetDateTime(const Elysium::Core::uint32_t Index) override;
		virtual const Elysium::Core::DateTimeOffset GetDateTimeOffset(const Elysium::Core::uint32_t Index) override;
		virtual const Elysium::Core::Decimal GetDecimal(const Elysium::Core::uint32_t Index) override;
		virtual const double GetDouble(const Elysium::Core::uint32_t Index) override;
		virtual const float GetFloat(const Elysium::Core::uint32_t Index) override;
		virtual const Elysium::Core::Guid GetGuid(const Elysium::Core::uint32_t Index) override;
		virtual const Elysium::Core::int16_t GetInt16(const Elysium::Core::uint32_t Index) override;
		virtual const Elysium::Core::int32_t GetInt32(const Elysium::Core::uint32_t Index) override;
		virtual const Elysium::Core::int64_t GetInt64(const Elysium::Core::uint32_t Index) override;
		virtual const Elysium::Core::String GetString(const Elysium::Core::uint32_t Index) override;
		virtual const Elysium::Core::TimeSpan GetTimeSpan(const Elysium::Core::uint32_t Index) override;

		virtual const Elysium::Core::String GetDataTypeName(const Elysium::Core::uint32_t Index) override;
		virtual const Elysium::Core::String GetName(const Elysium::Core::uint32_t Index) override;
		virtual const Elysium::Core::uint64_t GetOrdinal(const Elysium::Core::String& Name) override;

		virtual const bool IsDBNull(const uint32_t Index) override;
	private:
		SqlNativeDataReader(IRowset* NativeRowset, const Elysium::Core::size RowsAffected, const Elysium::Core::size FieldCount, const DBCOLUMNINFO* ColumnInfo, const wchar_t* ColumnNames);

		const Text::Encoding& _WindowsEncoding = Text::Encoding::UTF16LE();

		IRowset* _NativeRowset;
		const DBCOLUMNINFO* _ColumnInfo = nullptr;
		const wchar_t* _ColumnNames = nullptr;

		Elysium::Core::size _NumberOfNonBlobFields;
		Elysium::Core::size _NumberOfBuffers;
		std::vector<std::vector<DBBINDING>> _NativeDatabaseBindings;
		std::vector<std::vector<DBBINDSTATUS>> _NativeDatabaseBindStatus;
		std::map<Elysium::Core::size, DBBINDING*> _IndexBindingMap;
		std::map<int, int> _IndexBufferMap;

		DBROWOFFSET _RowsetByteLength = 0;
		BYTE* _RowDataBuffer = nullptr;

		IAccessor* _NativeRowAccessor = nullptr;
		std::vector<HACCESSOR> _NativeRowAccessorHandles;

		DBCOUNTITEM _NumberOfRowsObtained = 0;
		HROW _RowHandles[1];
	};
}
#endif
