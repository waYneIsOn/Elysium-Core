/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATA_COMMON_DBPARAMETER
#define ELYSIUM_CORE_DATA_COMMON_DBPARAMETER

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

namespace Elysium
{
	namespace Core
	{
		namespace Data
		{
			namespace Common
			{
				class EXPORT DbParameter : public IDataParameter
				{
				public:
					/// <summary>
					/// Destroy the object using the virtual destructor
					/// </summary>
					virtual ~DbParameter() {}

					virtual DbType GetDbType() const override;
					virtual ParameterDirection GetDirection() const override;
					virtual bool GetIsNullable() const override;
					virtual std::string GetParameterName() const override;
					virtual std::string GetSourceColumn() const override;
					virtual DataRowVersion GetSourceVersion() const override;
					virtual const BYTE* GetValue() const override;
					virtual size_t GetSize() const override;
					virtual bool GetIsDBNull() const override;

					virtual void SetDbType(DbType Type) override;
					virtual void SetDirection(ParameterDirection Direction) override;
					virtual void SetIsNullable(bool IsNullable) override;
					virtual void SetParameterName(std::string ParameterName) override;
					virtual void SetSourceColumn(std::string SourceColumn) override;
					virtual void SetSourceVersion(DataRowVersion Version) override;
					virtual void SetValue(const DBNull* Value) override;
					virtual void SetValue(const bool Value) override;
					virtual void SetValue(const BYTE Value) override;
					virtual void SetValue(const BYTE* Value, const size_t BufferOffset, const  size_t Length) override;
					virtual void SetValue(const char Value) override;
					virtual void SetValue(const char* Value, const size_t BufferOffset, const size_t Length) override;
					virtual void SetValue(const std::string* Value) override;
					virtual void SetValue(const DateTime* Value) override;
					virtual void SetValue(const DateTimeOffset* Value) override;
					virtual void SetValue(const TimeSpan* Value) override;
					virtual void SetValue(const Elysium::Core::Decimal* Value) override;
					virtual void SetValue(const double Value) override;
					virtual void SetValue(const float Value) override;
					virtual void SetValue(const Guid* Value) override;
					virtual void SetValue(const __int16 Value) override;
					virtual void SetValue(const __int32 Value) override;
					virtual void SetValue(const __int64 Value) override;
					virtual void SetValue(const unsigned __int16 Value) override;
					virtual void SetValue(const unsigned __int32 Value) override;
					virtual void SetValue(const unsigned __int64 Value) override;
					virtual void SetValue(const wchar_t Value) override;
					virtual void SetValue(const wchar_t* Value, const size_t BufferOffset, const size_t Length) override;
					virtual void SetValue(const std::wstring* Value) override;
					virtual void SetValue(const Elysium::Core::IO::Stream* Value) override;
				protected:
					DbParameter(const DbCommand* Command);

					const DbCommand* _Command;

					DbType _DbType;
					ParameterDirection _Direction = ParameterDirection::Input;
					bool _IsNullable = true;
					std::string _ParameterName;
					std::string _SourceColumn;
					DataRowVersion _SourceVersion;
					std::vector<BYTE> _Data;
					const DBNull* _DBNullPointer = nullptr;
				};
			}
		}
	}
}
#endif
