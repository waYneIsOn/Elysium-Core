/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVESEQUENTIALSTREAM
#define ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVESEQUENTIALSTREAM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_API
#include "API.hpp"
#endif

#ifndef __sqlncli_h__
#define _SQLNCLI_OLEDB_IGNORE_DEPRECATION_WARNING_
#define _SQLNCLI_OLEDB_
#include "C:/Program Files (x86)/Microsoft SQL Server/110/SDK/Include/sqlncli.h"
#endif

#ifndef _VECTOR_
#include <vector>
#endif

#pragma warning(disable : 4251)	// std::vector<BYTE> _Buffer;

namespace Elysium::Core::Data::SqlNativeClient::OleDb
{
	class ELYSIUM_CORE_DATA_SQLNATIVECLIENT_API SqlNativeSequentialStream : public ISequentialStream
	{
	public:
		SqlNativeSequentialStream();
		virtual ~SqlNativeSequentialStream();

		virtual int Seek(unsigned long Position);
		virtual int Clear();
		virtual int CompareData(void* Buffer);
		virtual size_t Length();

		virtual operator void* const();

		STDMETHODIMP_(unsigned long) AddRef(void);
		STDMETHODIMP_(unsigned long) Release(void);
		STDMETHODIMP QueryInterface(REFIID Guid, LPVOID* Object);

		STDMETHODIMP Read(
			/* [out] */ void __RPC_FAR* Buffer,
			/* [in]  */ unsigned long Count,
			/* [out] */ unsigned long __RPC_FAR* BytesRead);

		STDMETHODIMP Write(
			/* [in] */ const void __RPC_FAR* Buffer,
			/* [in] */ unsigned long Count,
			/* [out]*/ unsigned long __RPC_FAR* BytesWritten);
	private:
		unsigned long _ReferenceCounter = 0;
		std::vector<BYTE> _Buffer;
		size_t _CurrentPosition = 0;
	};
}
#endif
