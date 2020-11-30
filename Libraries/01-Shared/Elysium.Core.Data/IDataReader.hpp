/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_IDATAREADER
#define ELYSIUM_CORE_DATA_IDATAREADER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_DATA_API
#include "API.hpp"
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

namespace Elysium::Core::Data
{
	class ELYSIUM_CORE_DATA_API IDataReader
	{
	public:
		virtual ~IDataReader() {}

		virtual const size_t GetDepth() const = 0;
		virtual const bool GetIsClosed() const = 0;
		virtual const size_t GetRecordsAffected() const = 0;

		virtual void Close() = 0;
		//virtual const Elysium::Core::Data::DataTable GetSchemaTable() = 0;
		virtual const bool NextResult() = 0;
		virtual const bool Read() = 0;
	};
}
#endif
