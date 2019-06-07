/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATA_COMMON_DBCONNECTION
#define ELYSIUM_CORE_DATA_COMMON_DBCONNECTION

#ifndef ELYSIUM_CORE_DATA_IDBCONNECTION
#include "IDbConnection.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_IDBTRANSACTION
#include "IDbTransaction.hpp
#endif

#ifndef ELYSIUM_CORE_DATA_IDBCONNECTION
#include "IDbConnection.hpp"
#endif

#pragma warning(disable : 4251)

namespace Elysium
{
	namespace Core
	{
		namespace Data
		{
			namespace Common
			{
				class ELYSIUM_CORE_DATA_API DbConnection : public IDbConnection
				{
				public:
					/// <summary>
					/// Destroy the object using the virtual destructor
					/// </summary>
					virtual ~DbConnection() {}

					virtual const std::wstring& GetConnectionString() const override;
					virtual const int& GetConnectionTimeout() const override;
					virtual const std::wstring& GetDatabase() const override;
					virtual const ConnectionState& GetState() const override;

					virtual void SetConnectionString(std::wstring ConnectionString) override;
				protected:
					DbConnection();
					DbConnection(std::wstring ConnectionString);

					std::wstring _ConnectionString;
					int _ConnectionTimeout;
					std::wstring _Database;
					ConnectionState _ConnectionState;
				};
			}
		}
	}
}
#endif
