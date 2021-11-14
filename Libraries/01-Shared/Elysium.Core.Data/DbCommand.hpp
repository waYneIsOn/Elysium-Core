/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

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

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Data::Common
{
	class ELYSIUM_CORE_DATA_API DbCommand : public IDbCommand
	{
	protected:
		DbCommand(IDbConnection& Connection);
		DbCommand(IDbTransaction* Transaction);
	public:
		virtual ~DbCommand();

		virtual const String& GetCommandText() const override;

		virtual const Elysium::Core::uint32_t& GetConnectionTimeout() const override;

		virtual const CommandType& GetCommandType() const override;

		//virtual const UpdateRowSource& GetUpdateRowSource() const override;

		virtual void SetCommandText(const char8_t* CommandText) override;

		virtual void SetCommandText(const String& CommandText) override;

		virtual void SetConnectionTimeout(const Elysium::Core::uint32_t Timeout) override;

		virtual void SetCommandType(CommandType Type) override;

		//virtual void SetConnection(IDbConnection Connection) override;
		// 
		//virtual void SetTransaction(IDbTransaction Transaction) override;
		// 
		//virtual void SetUpdateRowSource(UpdateRowSource UpdateRowSource) override;
	protected:
		const IDbConnection& _Connection;
		const IDbTransaction* _Transaction;

		String _Text = String::Empty;
		Elysium::Core::uint32_t _Timeout = 30;
		CommandType _Type = CommandType::Text;
	};
}
#endif
