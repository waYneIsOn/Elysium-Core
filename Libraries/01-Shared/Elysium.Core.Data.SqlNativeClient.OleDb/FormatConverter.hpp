/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_FORMATCONVERTER
#define ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_FORMATCONVERTER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __sqlncli_h__
#define _SQLNCLI_OLEDB_
#define _SQLNCLI_OLEDB_IGNORE_DEPRECATION_WARNING_
#include "C:/Program Files (x86)/Microsoft SQL Server/110/SDK/Include/sqlncli.h"
#endif

#ifndef ELYSIUM_CORE_DATA_ISOLATIONLEVEL
#include "../Elysium.Core.Data/IsolationLevel.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_DBTYPE
#include "../Elysium.Core.Data/DbType.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_PARAMETERDIRECTION
#include "../Elysium.Core.Data/ParameterDirection.hpp"
#endif

namespace Elysium::Core::Data::SqlNativeClient::OleDb
{
	class FormatConverter final
	{
	public:
		//static long Translate(IsolationLevel IsolationLevel);
		static DBTYPEENUM Translate(DbType DbType);
		static DBPARAMIOENUM Translate(ParameterDirection ParameterDirection);
	private:
		FormatConverter();
		~FormatConverter();
	};
}
#endif
