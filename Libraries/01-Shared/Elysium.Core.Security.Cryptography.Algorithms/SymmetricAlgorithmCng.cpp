#include "SymmetricAlgorithmCng.hpp"

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_CRYPTOGRAPHICEXCEPTION
#include "../Elysium.Core.Security/CryptographicException.hpp"
#endif

Elysium::Core::Security::Cryptography::Windows::SymmetricAlgorithmCng::SymmetricAlgorithmCng(const Elysium::Core::uint32_t BlockSize, const Elysium::Core::uint32_t KeySize, const Elysium::Core::uint32_t FeedbackSize, const CipherMode CipherMode, const PaddingMode PaddingMode, const wchar_t* Name)
	: SymmetricAlgorithm(BlockSize, KeySize, FeedbackSize, CipherMode, PaddingMode),
	_AlgorithmHandle(CreateNativeAlgorithmHandle(Name))
{ }

Elysium::Core::Security::Cryptography::Windows::SymmetricAlgorithmCng::~SymmetricAlgorithmCng()
{
	if (_AlgorithmHandle != nullptr)
	{
		BCryptCloseAlgorithmProvider(_AlgorithmHandle, 0);
	}
}

void Elysium::Core::Security::Cryptography::Windows::SymmetricAlgorithmCng::Test()
{
	/*
	ULONG cbBuffer = 0;
	PCRYPT_PROVIDERS pBuffer = NULL;
	Status = BCryptEnumRegisteredProviders(&cbBuffer, &pBuffer);
	if (pBuffer != NULL)
	{
		for (ULONG i = 0; i < pBuffer->cProviders; i++)
		{
			wchar_t* xy = pBuffer->rgpszProviders[i];

			bool bla = false;
		}
		BCryptFreeBuffer(pBuffer);
	}
	*/
	// https://docs.microsoft.com/en-us/windows/win32/seccng/encrypting-data-with-cng#encrypting-data-example

	NTSTATUS Status;
	DWORD cbData;

	DWORD cbKeyObjectLen;
	Status = BCryptGetProperty(_AlgorithmHandle, BCRYPT_OBJECT_LENGTH, (PBYTE)&cbKeyObjectLen, sizeof(DWORD), &cbData, 0);
	if (Status > 0x7FFFFFFF)	// !NT_SUCCESS(Status)
	{
		throw CryptographicException();
	}

	DWORD cbBlockLen;
	Status = BCryptGetProperty(_AlgorithmHandle, BCRYPT_BLOCK_LENGTH, (PBYTE)&cbBlockLen, sizeof(DWORD), &cbData, 0);
	if (Status > 0x7FFFFFFF)	// !NT_SUCCESS(Status)
	{
		throw CryptographicException();
	}

	bool bla = false;
}

BCRYPT_ALG_HANDLE Elysium::Core::Security::Cryptography::Windows::SymmetricAlgorithmCng::CreateNativeAlgorithmHandle(const wchar_t* Name)
{
	BCRYPT_ALG_HANDLE AlgorithmHandle;
	NTSTATUS Status = BCryptOpenAlgorithmProvider(&AlgorithmHandle, Name, 0, 0);
	if (Status > 0x7FFFFFFF)	// !NT_SUCCESS(Status)
	{
		throw CryptographicException();
	}

	return AlgorithmHandle;
}
