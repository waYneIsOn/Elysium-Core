/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1LENGTH
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1LENGTH

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Encoding::Asn1
{
	/// <summary>
	/// 
	/// </summary>
	class ELYSIUM_CORE_SECURITY_API Asn1Length final
	{
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="Length"></param>
		/// <param name="EncodedLength"></param>
		Asn1Length(const Elysium::Core::uint32_t Length, const Elysium::Core::uint32_t EncodedLength);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Source"></param>
		Asn1Length(const Asn1Length& Source);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Right"></param>
		/// <returns></returns>
		Asn1Length(Asn1Length&& Right) noexcept;

		/// <summary>
		/// Destroys this instance.
		/// </summary>
		~Asn1Length();

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Source"></param>
		/// <returns></returns>
		Asn1Length& operator=(const Asn1Length& Source);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Right"></param>
		/// <returns></returns>
		Asn1Length& operator=(Asn1Length&& Right) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const Elysium::Core::uint32_t GetLength() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const Elysium::Core::uint32_t GetEncodedLength() const;
	private:
		Elysium::Core::uint32_t _Length;
		Elysium::Core::uint32_t _EncodedLength;
	};
}
#endif
