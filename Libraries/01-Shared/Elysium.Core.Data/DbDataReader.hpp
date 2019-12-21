/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATA_COMMON_DBDATAREADER
#define ELYSIUM_CORE_DATA_COMMON_DBDATAREADER

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

		virtual size_t GetDepth() const override;
		virtual size_t GetFieldCount() const override;

		virtual size_t GetRecordsAffected() const override;
	protected:
		DbDataReader(size_t NumberOfRows, size_t FieldCount, size_t RecordsAffected);
		DbDataReader();

		size_t _NumberOfRows;
		size_t _FieldCount;
		size_t _RecordsAffected;
	};
}
#endif
