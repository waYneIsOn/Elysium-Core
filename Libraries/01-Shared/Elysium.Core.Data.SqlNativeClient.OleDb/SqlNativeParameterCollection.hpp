/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEPARAMETERCOLLECTION
#define ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEPARAMETERCOLLECTION

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_COMMON_DBPARAMETERCOLLECTION
#include "../Elysium.Core.Data/DbParameterCollection.hpp"
#endif

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
					class SqlNativeCommand;

					class ELYSIUM_CORE_DATA_SQLNATIVECLIENT_API SqlNativeParameterCollection final : public Common::DbParameterCollection
					{
						friend class SqlNativeCommand;
					public:
						~SqlNativeParameterCollection();
					private:
						SqlNativeParameterCollection();
					};
				}
			}
		}
	}
}
#endif
