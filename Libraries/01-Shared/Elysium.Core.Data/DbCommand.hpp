/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_COMMON_DBCOMMAND
#define ELYSIUM_CORE_DATA_COMMON_DBCOMMAND

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_DATA_IDBCOMMAND
#include "IDbCommand.hpp"
#endif

#pragma warning(disable : 4251)

namespace Elysium::Core::Data::Common
{
	class ELYSIUM_CORE_DATA_API DbCommand : public IDbCommand
	{
	public:
		/// <summary>
		/// Destroy the object using the virtual destructor
		/// </summary>
		virtual ~DbCommand() {}

		virtual const String& GetCommandText() const override;
		virtual const int& GetConnectionTimeout() const override;
		virtual const CommandType& GetCommandType() const override;
		//virtual const UpdateRowSource& GetUpdateRowSource() const override;

		virtual void SetCommandText(const char* CommandText) override;
		virtual void SetCommandText(const String& CommandText) override;
		virtual void SetConnectionTimeout(int Timeout) override;
		virtual void SetCommandType(CommandType Type) override;
		//virtual void SetConnection(IDbConnection Connection) override;
		//virtual void SetTransaction(IDbTransaction Transaction) override;
		//virtual void SetUpdateRowSource(UpdateRowSource UpdateRowSource) override;
	protected:
		DbCommand(IDbConnection* Connection);
		DbCommand(IDbTransaction* Transaction);

		const IDbConnection* _Connection;
		const IDbTransaction* _Transaction;

		String _Text = "";
		int _Timeout = 30;
		CommandType _Type = CommandType::Text;
	};
}
#endif
