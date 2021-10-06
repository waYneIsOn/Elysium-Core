/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1IDENTIFIER
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1IDENTIFIER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1TAGCLASS
#include "Asn1TagClass.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1UNIVERSALTAG
#include "Asn1UniversalTag.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Encoding::Asn1
{
	/// <summary>
	/// 
	/// </summary>
	class ELYSIUM_CORE_SECURITY_API Asn1Identifier final
	{
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="TagClass"></param>
		/// <param name="IsConstructed"></param>
		/// <param name="TagNumber"></param>
		/// <param name="EncodedLength"></param>
		Asn1Identifier(const Asn1TagClass TagClass, const bool IsConstructed, const Asn1UniversalTag UniversalTag, const Elysium::Core::int32_t EncodedLength);
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="Source"></param>
		Asn1Identifier(const Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Identifier& Source);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Right"></param>
		/// <returns></returns>
		Asn1Identifier(Asn1Identifier&& Right) noexcept;

		/// <summary>
		/// Destroys this instance.
		/// </summary>
		~Asn1Identifier();

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Source"></param>
		/// <returns></returns>
		Asn1Identifier& operator=(const Asn1Identifier& Source);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Right"></param>
		/// <returns></returns>
		Asn1Identifier& operator=(Asn1Identifier&& Right) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const Asn1TagClass GetTagClass() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const bool GetIsConstructed() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const Asn1UniversalTag GetUniversalTag() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const Elysium::Core::int32_t GetEncodedLength() const;
	private:
		Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1TagClass _TagClass;
		bool _IsConstructed;
		Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1UniversalTag _UniversalTag;
		Elysium::Core::int32_t _EncodedLength;
	};
}
#endif
