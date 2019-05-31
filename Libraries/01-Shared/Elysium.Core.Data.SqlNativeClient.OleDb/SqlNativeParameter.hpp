/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once


#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEPARAMETER
#define ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEPARAMETER

#ifndef ELYSIUM_CORE_DATA_COMMON_DBPARAMETER
#include "../Elysium.Core.Data/DbParameter.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVECOMMAND
#include "SqlNativeCommand.hpp"
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
					class EXPORT SqlNativeParameter final : public Common::DbParameter
					{
						friend class SqlNativeCommand;
					public:
						~SqlNativeParameter();
					private:
						SqlNativeParameter(const SqlNativeCommand* const Command);
					};
				}
			}
		}
	}
}
#endif
