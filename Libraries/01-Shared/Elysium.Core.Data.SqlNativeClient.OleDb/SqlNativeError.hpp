/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEERROR
#define ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEERROR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "../Elysium.Core/Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_MEMORY_DEFAULTALLOCATOROFSTRING
#include "../Elysium.Core/DefaultAllocatorOfString.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Elysium.Core.Template/Vector.hpp"
#endif

#ifndef _XSTRING_
#include <xstring>
#endif

#ifndef GUID_DEFINED
#include <guiddef.h>
#endif

#pragma warning(disable : 4251)

namespace Elysium::Core::Data::SqlNativeClient::OleDb
{
	class ELYSIUM_CORE_DATA_SQLNATIVECLIENT_API SqlNativeError final
	{
		friend class Elysium::Core::Template::Container::Vector<SqlNativeError>;
	private:
		SqlNativeError();
	public:
		SqlNativeError(long ErrorSpecificErrorCode, unsigned long ProviderSpecificErrorCode, GUID ClassId, GUID InterfaceId, long DisplayId,
			wchar_t* Description, GUID GUID, unsigned long HelpContext, wchar_t* HelpFile, wchar_t* Source,
			wchar_t* SqlState, long ErrorCode, wchar_t* SSError, wchar_t* Server, wchar_t* Procedure, long Number, byte State, byte ErrorSeverity, unsigned short LineNumber);

		SqlNativeError(const SqlNativeError& Source);

		SqlNativeError(SqlNativeError&& Right) noexcept;

		~SqlNativeError();
	public:
		SqlNativeError& operator=(const SqlNativeError& Source);

		SqlNativeError& operator=(SqlNativeError&& Right) noexcept;
	public:
		bool operator==(const SqlNativeError& Other) const;

		bool operator!=(const SqlNativeError& Other) const;
	public:
		const long& GetErrorSpecificErrorCode() const;
		const unsigned long& GetProviderSpecificErrorCode() const;
		const GUID& GetClassId() const;
		const GUID& GetInterfaceId() const;
		const long& GetDisplayId() const;

		const std::wstring& GetDescription() const;
		const GUID& GetGUID() const;
		const unsigned long& GetHelpContext() const;
		const std::wstring& GetHelpFile() const;
		const std::wstring& GetSource() const;

		const std::wstring& GetSqlState() const;
		const long& GetErrorCode() const;
		const std::wstring& GetSSError() const;
		const std::wstring& GetServer() const;
		const std::wstring& GetProcedure() const;
		const long& GetNumber() const;
		const byte& GetState() const;
		const byte& GetErrorSeverity() const;
		const unsigned short& GetLineNumber() const;
	private:
		// basic error information using ERRORINFO NativeErrorInfo
		long _ErrorSpecificErrorCode;
		unsigned long _ProviderSpecificErrorCode;
		GUID _ClassId;
		GUID _InterfaceId;
		long _DisplayId;

		// most of the basic error information using IErrorInfo* NativeIErrorInfoRecord
		std::wstring _Description;	// Message
		GUID _GUID;
		unsigned long _HelpContext;
		std::wstring _HelpFile;
		std::wstring _Source;

		// sql specific error information using ISQLErrorInfo* NativeSQLErrorInfo
		std::wstring _SqlState;
		long _ErrorCode;

		std::wstring _SSError;
		std::wstring _Server;
		std::wstring _Procedure;
		long _Number;
		byte _State;
		byte _ErrorSeverity;
		unsigned short _LineNumber;
	};
}
#endif
