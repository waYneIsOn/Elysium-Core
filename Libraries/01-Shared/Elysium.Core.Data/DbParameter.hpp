/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_COMMON_DBPARAMETER
#define ELYSIUM_CORE_DATA_COMMON_DBPARAMETER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_DATA_IDATAPARAMETER
#include "IDataParameter.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_COMMON_DBCOMMAND
#include "DbCommand.hpp"
#endif

#ifndef _VECTOR_
#include <vector>
#endif

#pragma warning(disable : 4251)

namespace Elysium::Core::Data::Common
{
	class ELYSIUM_CORE_DATA_API DbParameter : public IDataParameter
	{
	public:
		/// <summary>
		/// Destroy the object using the virtual destructor
		/// </summary>
		virtual ~DbParameter() {}

		virtual const DbType GetDbType() const override;
		virtual const ParameterDirection GetDirection() const override;
		virtual const bool GetIsNullable() const override;
		virtual const Elysium::Core::String GetParameterName() const override;
		virtual const Elysium::Core::String GetSourceColumn() const override;
		virtual const DataRowVersion GetSourceVersion() const override;
		virtual const byte* GetValue() const override;
		virtual const Elysium::Core::size GetSize() const override;
		virtual const bool GetIsDBNull() const override;

		virtual void SetDbType(const DbType Type) override;
		virtual void SetDirection(const ParameterDirection Direction) override;
		virtual void SetIsNullable(const bool IsNullable) override;
		virtual void SetParameterName(const Elysium::Core::String& ParameterName) override;
		virtual void SetSourceColumn(const Elysium::Core::String& SourceColumn) override;
		virtual void SetSourceVersion(DataRowVersion Version) override;

		virtual void SetValue(const DBNull& Value) override;
		virtual void SetValue(const bool Value) override;
		virtual void SetValue(const byte Value) override;
		virtual void SetValue(const byte* Value, const  Elysium::Core::size Length) override;
		virtual void SetValue(const char8_t Value) override;
		virtual void SetValue(const char8_t* Value, const Elysium::Core::size Length) override;
		virtual void SetValue(const Elysium::Core::String& Value) override;
		virtual void SetValue(const DateTime& Value) override;
		virtual void SetValue(const DateTimeOffset& Value) override;
		virtual void SetValue(const TimeSpan& Value) override;
		virtual void SetValue(const Decimal& Value) override;
		virtual void SetValue(const double Value) override;
		virtual void SetValue(const float Value) override;
		virtual void SetValue(const Guid& Value) override;
		virtual void SetValue(const Elysium::Core::int16_t Value) override;
		virtual void SetValue(const Elysium::Core::int32_t Value) override;
		virtual void SetValue(const Elysium::Core::int64_t Value) override;
		virtual void SetValue(const Elysium::Core::uint16_t Value) override;
		virtual void SetValue(const Elysium::Core::uint32_t Value) override;
		virtual void SetValue(const Elysium::Core::uint64_t Value) override;
		virtual void SetValue(const Elysium::Core::IO::Stream& Value) override;
	protected:
		DbParameter(const DbCommand* Command);

		const DbCommand* _Command;

		DbType _DbType;
		ParameterDirection _Direction = ParameterDirection::Input;
		bool _IsNullable = true;
		Elysium::Core::String _ParameterName;
		Elysium::Core::String _SourceColumn;
		DataRowVersion _SourceVersion;
		std::vector<byte> _Data;
		const DBNull* _DBNullPointer;
	};
}
#endif
