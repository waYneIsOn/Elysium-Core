/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATA_IDBCOMMAND
#define ELYSIUM_CORE_DATA_IDBCOMMAND

#ifndef ELYSIUM_CORE_DATA_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_ISOLATIONLEVEL
#include "IsolationLevel.hpp"
#endif

#ifndef _XSTRING_
#include <xstring>
#endif

#ifndef ELYSIUM_CORE_DATA_COMMANDTYPE
#include "CommandType.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_COMMANDBEHAVIOUR
#include "CommandBehaviour.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_IDBCONNECTION
#include "IDbConnection.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_IDATAPARAMETERCOLLECTION
#include "IDataParameterCollection.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_IDBTRANSACTION
#include "IDbTransaction.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_IDATAREADER
#include "IDataReader.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Data
		{
			class ELYSIUM_CORE_DATA_API IDbCommand
			{
			public:
				/// <summary>
				/// Destroy the object using the virtual destructor
				/// </summary>
				virtual ~IDbCommand() {}

				virtual const std::wstring GetCommandText() const = 0;
				virtual const int& GetConnectionTimeout() const = 0;
				virtual const CommandType& GetCommandType() const = 0;
				virtual const IDbConnection* GetConnection() const = 0;
				virtual IDataParameterCollection* GetParameters() const = 0;
				virtual const IDbTransaction* GetTransaction() const = 0;
				//virtual const UpdateRowSource* GetUpdateRowSource() const = 0;

				virtual void SetCommandText(std::wstring CommandText) = 0;
				virtual void SetConnectionTimeout(int Timeout) = 0;
				virtual void SetCommandType(CommandType Type) = 0;
				//virtual void SetConnection(IDbConnection* Connection) = 0;
				//virtual void SetTransaction(IDbTransaction* Transaction) = 0;
				//virtual void SetUpdateRowSource(UpdateRowSource* UpdateRowSource) = 0;

				//virtual void Cancel() = 0;
				virtual std::unique_ptr<IDataParameter> CreateParameter() = 0;
				virtual int ExecuteNonQuery() = 0;
				virtual std::unique_ptr<IDataReader> ExecuteReader() = 0;
				//virtual IDataReader ExecuteReader(CommandBehaviour Behaviour) = 0;
				//virtual object ExecuteScalar() = 0;
				virtual void Prepare() = 0;
			};
		}
	}
}
#endif
