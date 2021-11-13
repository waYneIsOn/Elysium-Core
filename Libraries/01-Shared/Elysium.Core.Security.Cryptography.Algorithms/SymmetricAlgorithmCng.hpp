/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_WINDOWS_SYMMETRICALGORITHMCNG
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_WINDOWS_SYMMETRICALGORITHMCNG

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_SYMMETRICALGORITHM
#include "SymmetricAlgorithm.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINDOWS_
#include <windows.h>
#endif

#ifndef __BCRYPT_H__
#include <bcrypt.h>
#endif

#pragma comment (lib, "bcrypt.lib")

namespace Elysium::Core::Security::Cryptography::Windows
{
	class ELYSIUM_CORE_SECURITY_API SymmetricAlgorithmCng : public SymmetricAlgorithm
	{
	protected:
		SymmetricAlgorithmCng(const Elysium::Core::uint32_t BlockSize, const Elysium::Core::uint32_t KeySize, const Elysium::Core::uint32_t FeedbackSize,
			const CipherMode CipherMode, const PaddingMode PaddingMode, const wchar_t* Name);
	public:
		SymmetricAlgorithmCng(const SymmetricAlgorithm& Source) = delete;

		SymmetricAlgorithmCng(SymmetricAlgorithmCng&& Right) noexcept = delete;

		virtual ~SymmetricAlgorithmCng();
	public:
		SymmetricAlgorithmCng& operator=(const SymmetricAlgorithmCng& Source) = delete;

		SymmetricAlgorithmCng& operator=(SymmetricAlgorithmCng&& Right) noexcept = delete;
	public:
		void Test();
	private:
		BCRYPT_ALG_HANDLE _AlgorithmHandle;

		static BCRYPT_ALG_HANDLE CreateNativeAlgorithmHandle(const wchar_t* Name);
	};
}
#endif
#endif
