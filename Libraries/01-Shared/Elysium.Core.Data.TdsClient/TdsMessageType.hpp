/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_TDSCLIENT_TDSMESSAGETYPE
#define ELYSIUM_CORE_DATA_TDSCLIENT_TDSMESSAGETYPE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

namespace Elysium::Core::Data::TdsClient
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class TdsMessageType : Elysium::Core::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class TdsMessageType
#else
#error "undefined os"
#endif
	{
		SqlBatch = 0x01,

		PreLoginOld = 0x02,

		RemoteProcedureCall = 0x03,

		FeatureExtAck = 0x04,

		PreLoginResponse = 0x04,

		LoginResponse = 0x04,

		FederatedAuthenticationInformation = 0x04,

		RowData = 0x04,

		ReturnStatus = 0x04,

		ReturnParameters = 0x04,

		ResponseCompletion = 0x04,

		SesstionSTate = 0x04,

		ErrorAndInfo = 0x04,

		AttentionAcknowledgement = 0x04,

		Attention = 0x06,

		BulkLoad = 0x07,

		FederatedAuthenticationToken = 0x08,

		Login = 0x10,

		LoginIntegratedAuthentication = 0x11,

		PreLoginNew = 0x12
	};
}
#endif
