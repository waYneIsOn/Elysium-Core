/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_COMMON_DBTRANSACTION
#define ELYSIUM_CORE_DATA_COMMON_DBTRANSACTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_DATA_IDBTRANSACTION
#include "IDbTransaction.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_IDBCONNECTION
#include "IDbConnection.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_ISOLATIONLEVEL
#include "IsolationLevel.hpp"
#endif

namespace Elysium::Core::Data::Common
{
	class ELYSIUM_CORE_DATA_API DbTransaction : public IDbTransaction
	{
	public:
		/// <summary>
		/// Destroy the object using the virtual destructor
		/// </summary>
		virtual ~DbTransaction() {}

		virtual const IDbConnection& GetConnection() const override;
		virtual const IsolationLevel GetIsolationLevel() const override;
	protected:
		DbTransaction(IDbConnection& Connection, IsolationLevel _IsolationLevel);

		const IDbConnection& _Connection;
		IsolationLevel _IsolationLevel;
	};
}
#endif
