/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEERRORCOLLECTION
#define ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEERRORCOLLECTION

#ifndef ELYSIUM_CORE_COLLECTIONS_ICOLLECTION
#include "../Elysium.Core/ICollection.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEERROR
#include "SqlNativeError.hpp"
#endif

#ifndef _VECTOR_
#include <vector>
#endif

#ifndef __sqlncli_h__
#define _SQLNCLI_OLEDB_IGNORE_DEPRECATION_WARNING_
#define _SQLNCLI_OLEDB_
#include "C:/Program Files (x86)/Microsoft SQL Server/110/SDK/Include/sqlncli.h"
#endif

#pragma warning(disable : 4251)

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
					class EXPORT SqlNativeErrorCollection final : public Elysium::Core::Collections::ICollection<SqlNativeError>
					{
					public:
						SqlNativeErrorCollection(IUnknown* ErrorObject);
						~SqlNativeErrorCollection();

						const SqlNativeError& operator [] (size_t i) const;

						virtual const size_t GetCount() const override;
						virtual const bool GetIsReadOnly() const override;

						virtual void Add(const SqlNativeError& Item) override;
						virtual void Add(const SqlNativeError* Item) override;
						virtual void Clear() override;
						virtual bool Contains(const SqlNativeError& Item) override;
						virtual bool Remove(const SqlNativeError& Item) override;
					private:
						std::vector<SqlNativeError> _Errors;
					};
				}
			}
		}
	}
}
#endif