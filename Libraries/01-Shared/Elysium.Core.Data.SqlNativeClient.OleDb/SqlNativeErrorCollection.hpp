/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEERRORCOLLECTION
#define ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEERRORCOLLECTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEERROR
#include "SqlNativeError.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Elysium.Core.Template/Vector.hpp"
#endif

#ifndef __sqlncli_h__
#define _SQLNCLI_OLEDB_IGNORE_DEPRECATION_WARNING_
#define _SQLNCLI_OLEDB_
#include "C:/Program Files (x86)/Microsoft SQL Server/110/SDK/Include/sqlncli.h"
#endif

#pragma warning(disable : 4251)

namespace Elysium::Core::Data::SqlNativeClient::OleDb
{
	class ELYSIUM_CORE_DATA_SQLNATIVECLIENT_API SqlNativeErrorCollection final
	{
	public:
		SqlNativeErrorCollection(IUnknown* ErrorObject);
		~SqlNativeErrorCollection();

		const SqlNativeError& operator [] (Elysium::Core::size i) const;

		const Elysium::Core::size GetLength() const;
		const bool GetIsReadOnly() const;

		void Add(const SqlNativeError& Item);
		void Clear();
		bool Contains(const SqlNativeError& Item) const;
		bool Remove(const SqlNativeError& Item);
	private:
		Elysium::Core::Template::Container::Vector<SqlNativeError> _Errors;
	};
}
#endif
