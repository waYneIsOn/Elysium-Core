#include "WinCNG.hpp"

#if defined ELYSIUM_CORE_OS_WINDOWS
void Elysium::Core::Security::Cryptography::Internal::WinCNG::Test()
{
	NTSTATUS Status;
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
	BCRYPT_ALG_HANDLE AlgorithmHandle;
	Status = BCryptOpenAlgorithmProvider(&AlgorithmHandle, BCRYPT_DES_ALGORITHM, 0, 0);
	if (Status > 0x3FFFFFFF)	// NT_SUCCESS(Status)
	{	// ToDo: throw specific exception
		throw 1;
	}

	DWORD cbData;

	DWORD cbKeyObjectLen;
	Status = BCryptGetProperty(AlgorithmHandle, BCRYPT_OBJECT_LENGTH, (PBYTE)&cbKeyObjectLen, sizeof(DWORD), &cbData, 0);
	if (Status > 0x3FFFFFFF)	// NT_SUCCESS(Status)
	{	// ToDo: throw specific exception
		throw 1;
	}

	DWORD cbBlockLen;
	Status = BCryptGetProperty(AlgorithmHandle, BCRYPT_BLOCK_LENGTH, (PBYTE)&cbBlockLen, sizeof(DWORD), &cbData, 0);
	if (Status > 0x3FFFFFFF)	// NT_SUCCESS(Status)
	{	// ToDo: throw specific exception
		throw 1;
	}

	if (AlgorithmHandle != nullptr)
	{
		BCryptCloseAlgorithmProvider(AlgorithmHandle, 0);
	}
}
#endif
