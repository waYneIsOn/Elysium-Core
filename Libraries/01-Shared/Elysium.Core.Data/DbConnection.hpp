/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_COMMON_DBCONNECTION
#define ELYSIUM_CORE_DATA_COMMON_DBCONNECTION

#ifdef _MSC_VER
#pragma once
#endif

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

namespace Elysium::Core::Data::Common
{
	class ELYSIUM_CORE_DATA_API DbConnection : public IDbConnection
	{
	protected:
		DbConnection(const String& ConnectionString, const Elysium::Core::uint32_t ConnectionTimeout);
	public:
		virtual ~DbConnection();
	public:
		virtual const Elysium::Core::String& GetConnectionString() const override;

		virtual const Elysium::Core::uint32_t& GetConnectionTimeout() const override;

		virtual const Elysium::Core::String& GetDatabase() const override;

		virtual const ConnectionState& GetState() const override;
	public:
		virtual void SetConnectionString(const String& ConnectionString) override;
	protected:
		String _ConnectionString;
		Elysium::Core::uint32_t _ConnectionTimeout;
		String _Database;
		ConnectionState _ConnectionState;
	};
}
#endif
