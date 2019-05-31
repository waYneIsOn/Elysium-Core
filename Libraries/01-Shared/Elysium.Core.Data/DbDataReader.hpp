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

namespace Elysium
{
	namespace Core
	{
		namespace Data
		{
			namespace Common
			{
				class EXPORT DbDataReader : public IDataReader
				{
				public:
					/// <summary>
					/// Destroy the object using the virtual destructor
					/// </summary>
					virtual ~DbDataReader() {}

					virtual unsigned long GetDepth() const override;
					virtual unsigned long GetFieldCount() const override;

					virtual long GetRecordsAffected() const override;
				protected:
					DbDataReader(unsigned long NumberOfRows, unsigned long FieldCount, long RecordsAffected);
					DbDataReader();

					unsigned long _NumberOfRows;
					unsigned long _FieldCount;
					long _RecordsAffected;
				};
			}
		}
	}
}
#endif
