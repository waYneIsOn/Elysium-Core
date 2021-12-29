/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_TDSCLIENT_TDSCONNECTIONSTRINGBUILDER
#define ELYSIUM_CORE_DATA_TDSCLIENT_TDSCONNECTIONSTRINGBUILDER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_DATA_COMMON_DBCONNECTIONSTRINGBUILDER
#include "../Elysium.Core.Data/DbConnectionStringBuilder.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_TDSCLIENT_API
#include "API.hpp"
#endif

namespace Elysium::Core::Data::TdsClient
{
	class ELYSIUM_CORE_DATA_TDSCLIENT_API TdsConnectionStringBuilder final : public Common::DbConnectionStringBuilder
	{
	public:
		TdsConnectionStringBuilder();

		TdsConnectionStringBuilder(const TdsConnectionStringBuilder& Source) = delete;

		TdsConnectionStringBuilder(TdsConnectionStringBuilder&& Right) noexcept = delete;

		virtual ~TdsConnectionStringBuilder();
	public:
		TdsConnectionStringBuilder& operator=(const TdsConnectionStringBuilder& Source) = delete;

		TdsConnectionStringBuilder& operator=(TdsConnectionStringBuilder&& Right) noexcept = delete;
	public:
		const Elysium::Core::Utf8String& GetServer() const;

		const Elysium::Core::Utf8String& GetDatabase() const;

		const bool GetIsTrustedConnection() const;
	public:
		void SetServer(const Elysium::Core::Utf8String& Value);

		void SetDatabase(const Elysium::Core::Utf8String& Value);

		void SetIsTrustedConnection(const bool Value);
	};
}
#endif
