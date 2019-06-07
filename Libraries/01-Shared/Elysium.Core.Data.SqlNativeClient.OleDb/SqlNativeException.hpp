/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEEXCEPTION
#define ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEEXCEPTION

#ifndef ELYSIUM_CORE_DATA_COMMON_DBEXCEPTION
#include "../Elysium.Core.Data/DbException.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEERRORCOLLECTION
#include "SqlNativeErrorCollection.hpp"
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
					class ELYSIUM_CORE_DATA_SQLNATIVECLIENT_API SqlNativeException final : public Elysium::Core::Data::Common::DbException
					{
					public:
						SqlNativeException(const String& Message, const int ErrorCode, IUnknown* ErrorObject);
						~SqlNativeException();

						const SqlNativeErrorCollection& GetErrors() const;
					private:
						SqlNativeErrorCollection _Errors;
					};
				}
			}
		}
	}
}
#endif
