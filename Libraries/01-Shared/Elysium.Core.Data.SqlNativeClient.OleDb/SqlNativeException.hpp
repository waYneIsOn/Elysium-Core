/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEEXCEPTION
#define ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_DATA_COMMON_DBEXCEPTION
#include "../Elysium.Core.Data/DbException.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEERRORCOLLECTION
#include "SqlNativeErrorCollection.hpp"
#endif

namespace Elysium::Core::Data::SqlNativeClient::OleDb
{
	class ELYSIUM_CORE_DATA_SQLNATIVECLIENT_API SqlNativeException final : public Elysium::Core::Data::Common::DbException
	{
	public:
		SqlNativeException(String&& Message, const int ErrorCode, IUnknown* ErrorObject);
		~SqlNativeException();

		const SqlNativeErrorCollection& GetErrors() const;
	private:
		SqlNativeErrorCollection _Errors;
	};
}
#endif
