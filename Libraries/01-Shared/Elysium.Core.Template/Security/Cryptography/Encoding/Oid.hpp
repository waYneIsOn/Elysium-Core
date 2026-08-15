/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_OID
#define ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_OID

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../../../Functional/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_OIDGROUP
#include "OidGroup.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "../../../Text/String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRINGVIEW
#include "../../../Text/StringView.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF16
#include "../../../Text/Unicode/Utf16.hpp"
#endif

#ifdef ELYSIUM_CORE_OS_WINDOWS
	#ifndef __WINCRYPT_H__
	#include <wincrypt.h>
	#endif
#endif

namespace Elysium::Core::Template::Security::Cryptography::Encoding
{
	class Oid
	{
	public:
		constexpr Oid() = default;

		inline constexpr Oid(const Elysium::Core::Template::Text::StringView<char8_t> Value, const Elysium::Core::Template::Text::StringView<char8_t> FriendlyName)
			: _Value(Value), _FriendlyName(FriendlyName)
		{ }

		inline constexpr Oid(const Oid& Source)
			: _Value(Source._Value), _FriendlyName(Source._FriendlyName)
		{ }

		inline constexpr Oid(Oid&& Right) noexcept
			: _Value{}, _FriendlyName{}
		{
			*this = Elysium::Core::Template::Functional::Move(Right);
		}

		constexpr ~Oid() = default;
	public:
		inline constexpr Oid& operator=(const Oid& Source)
		{
			if (this != &Source)
			{
				_Value = Source._Value;
				_FriendlyName = Source._FriendlyName;
			}
			return *this;
		}

		inline constexpr Oid& operator=(Oid&& Right) noexcept
		{
			if (this != &Right)
			{
				_Value = Elysium::Core::Template::Functional::Move(Right._Value);
				_FriendlyName = Elysium::Core::Template::Functional::Move(Right._FriendlyName);
			}
			return *this;
		}
	public:
		inline constexpr const Elysium::Core::Template::Text::String<char8_t>& GetValue() const
		{
			return _Value;
		}

		inline constexpr const Elysium::Core::Template::Text::String<char8_t>& GetFriendlyName() const
		{
			return _FriendlyName;
		}
	public:
		inline static constexpr Oid FromFriendlyName(const Elysium::Core::Template::Text::StringView<char8_t> FriendlyName, 
			const Elysium::Core::Template::Security::Cryptography::Encoding::OidGroup Group)
		{
#ifdef ELYSIUM_CORE_OS_WINDOWS
			Elysium::Core::Template::Text::String<wchar_t> Name = Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString<char8_t>(&FriendlyName[0], FriendlyName.GetLength());

			const PCCRYPT_OID_INFO NativeOid = CryptFindOIDInfo(CRYPT_OID_INFO_NAME_KEY, static_cast<void*>(&Name[0]), (Elysium::Core::Template::System::uint32_t)Group);
			if (nullptr == NativeOid)
			{
				throw;
				//throw CryptographicException(u8"The OID was not found.");
			}

			// no need to use encoding here since char "fits" into char8_t
			return Oid(reinterpret_cast<const char8_t*>(NativeOid->pszOID), reinterpret_cast<const char8_t*>(NativeOid->pwszName));
#endif
		}

		inline static constexpr Oid FromOidValue(const Elysium::Core::Template::Text::StringView<char8_t> OidValue, 
			const Elysium::Core::Template::Security::Cryptography::Encoding::OidGroup Group)
		{
#ifdef ELYSIUM_CORE_OS_WINDOWS
			const PCCRYPT_OID_INFO NativeOid = CryptFindOIDInfo(CRYPT_OID_INFO_OID_KEY, static_cast<void*>((char8_t*)&OidValue[0]), (Elysium::Core::Template::System::uint32_t)Group);
			if (nullptr == NativeOid)
			{
				throw;
				//throw CryptographicException(u8"The friendly name for the OID value was not found.");
			}

			// no need to use encoding here since char "fits" into char8_t
			return Oid(reinterpret_cast<const char8_t*>(NativeOid->pszOID), reinterpret_cast<const char8_t*>(NativeOid->pwszName));
			/*
			return Oid(
				Elysium::Core::Template::Functional::Move(Text::Encoding::ASCII().GetString((const Elysium::Core::Template::System::byte*)NativeOid->pszOID,
					Elysium::Core::Template::Text::CharacterTraits<char>::GetSize(NativeOid->pszOID))),
				Elysium::Core::Template::Functional::Move(Text::Encoding::UTF16LE().GetString((const Elysium::Core::Template::System::byte*)NativeOid->pwszName,
					Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetSize(NativeOid->pwszName)))
			);
			*/
#endif
		}
	private:
		Elysium::Core::Template::Text::String<char8_t> _Value;
		Elysium::Core::Template::Text::String<char8_t> _FriendlyName;
	};
}
#endif
