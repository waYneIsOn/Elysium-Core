/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_SQLNATIVEDBTYPE
#define ELYSIUM_CORE_DATA_SQLNATIVECLIENT_SQLNATIVEDBTYPE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Data::SqlNativeClient::OleDb
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class SqlNativeDbType : uint32_t
#elif defined(__ANDROID__)
	enum class SqlNativeDbType
#else
#error "undefined os"
#endif
	{
		// A 64-bit signed integer.
		BigInt = 0,

		// Array of type Byte. A fixed-length stream of binary data ranging between 1 and 8.000 bytes.
		Binary = 1,

		// Boolean. An unsigned numeric value that can be 0, 1, or null
		Bit = 2,

		// String. A fixed-length stream of non-Unicode characters ranging between 1 and 8,000 characters.
		Char = 3,

		// DateTjime. Date and time data ranging in value from January 1, 1753 to December 31, 9999 to an accuracy of 3.33 milliseconds.
		DateTime = 4,

		// Decimal. A fixed precision and scale numeric value between -10^38 - 1 and 10^38 - 1.
		Decimal = 5,

		// 
		Float = 6,

		// 
		Image = 7,

		// 
		Int = 8,

		// 
		Money = 9,

		// 
		NChar = 10,

		// 
		NText = 11,

		// 
		NVarChar = 12,

		// 
		Real = 13,

		// 
		UniqueIdentifier = 14,

		// 
		SmallDateTime = 15,

		// 
		SmallInt = 16,

		// 
		SmallMoney = 17,

		// 
		Text = 18,

		// 
		Timestamp = 19,

		// 
		TinyInt = 20,

		// 
		VarBinary = 21,

		// 
		VarChar = 22,

		// 
		Variant = 23,

		// 
		Xml = 25,

		// 
		Udt = 29,

		// 
		Structured = 30,

		// 
		Date = 31,

		// 
		Time = 32,

		// 
		DateTime2 = 33,

		// 
		DateTimeOffset = 34,
	};
}
#endif
