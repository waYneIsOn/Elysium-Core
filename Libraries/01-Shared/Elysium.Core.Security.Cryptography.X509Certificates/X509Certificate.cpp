#include "X509Certificate.hpp"

#ifndef ELYSIUM_CORE_IO_FILESTREAM
#include "../Elysium.Core.IO/FileStream.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_CRYPTOGRAPHICEXCEPTION
#include "CryptographicException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMCPY
#include "../Elysium.Core.Template/MemCpy.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF16
#include "../Elysium.Core.Template/Utf16.hpp"
#endif

#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif

#ifndef __NCRYPT_H__
#include <ncrypt.h>
#endif

#endif

Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::X509Certificate() 
	: _CertificateContext(nullptr), _OwnsPrivateKeyHandle(false), _PrivateKeyHandle(0), _KeySpecifications(-1)
{ }

Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::X509Certificate(PCCERT_CONTEXT CertificateContext, HCRYPTPROV_OR_NCRYPT_KEY_HANDLE PrivateKeyHandle, const bool OwnsPrivateKeyHandle, const DWORD KeySpecifications)
	: _CertificateContext(CertDuplicateCertificateContext(CertificateContext)), _OwnsPrivateKeyHandle(OwnsPrivateKeyHandle), _PrivateKeyHandle(PrivateKeyHandle), _KeySpecifications(KeySpecifications)
{ }

Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::X509Certificate(const X509Certificate & Source)
	: _CertificateContext(CertDuplicateCertificateContext(Source._CertificateContext)), _OwnsPrivateKeyHandle(Source._OwnsPrivateKeyHandle), _PrivateKeyHandle(CopyPrivateKeyHandle(Source)), _KeySpecifications(Source._KeySpecifications)
{ }

Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::X509Certificate(X509Certificate && Right) noexcept
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}

Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::~X509Certificate()
{
	if (_OwnsPrivateKeyHandle && 0 != _PrivateKeyHandle)
	{
		switch (_KeySpecifications)
		{
		case 0: // CNG key
		{
			SECURITY_STATUS Result = NCryptFreeObject(_PrivateKeyHandle);
			if (SEC_E_OK != Result)
			{	// @ToDo:
				throw 1;
			}
		}
			break;
		case AT_KEYEXCHANGE: // CryptoAPI key
			[[__fallthrough__]]
		case AT_SIGNATURE:
		{
			SECURITY_STATUS Result = CryptReleaseContext(_PrivateKeyHandle, 0);
			if (SEC_E_OK != Result)
			{	// @ToDo:
				throw 1;
			}
		}
			break;
		default:
			// @ToDo: really nothing to do here?
			break;
		}
	}
	
	if (nullptr != _CertificateContext)
	{
		CertFreeCertificateContext(_CertificateContext);
		_CertificateContext = nullptr;
	}
}

Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate & Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::operator=(const X509Certificate & Source)
{
	if (this != &Source)
	{
		_CertificateContext = CertDuplicateCertificateContext(Source._CertificateContext);
		_OwnsPrivateKeyHandle = Source._OwnsPrivateKeyHandle;
		_PrivateKeyHandle = CopyPrivateKeyHandle(Source);
		_KeySpecifications = Source._KeySpecifications;
	}
	return *this;
}

Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate & Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::operator=(X509Certificate && Right) noexcept
{
	if (this != &Right)
	{
		_CertificateContext = Elysium::Core::Template::Functional::Move(Right._CertificateContext);
		_OwnsPrivateKeyHandle = Right._OwnsPrivateKeyHandle;
		_PrivateKeyHandle = Right._PrivateKeyHandle;
		_KeySpecifications = Right._KeySpecifications;

		Right._CertificateContext = nullptr;
		Right._OwnsPrivateKeyHandle = false;
		Right._PrivateKeyHandle = 0;
		Right._KeySpecifications = -1;
	}
	return *this;
}

const bool Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::operator==(const X509Certificate& Other) const
{	
	if (this == &Other)
	{
		return true;
	}

	return _CertificateContext == Other._CertificateContext && _PrivateKeyHandle == Other._PrivateKeyHandle;
}

const Elysium::Core::Utf8String Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::GetIssuer() const
{
	unsigned long BufferLength = CertNameToStrA(X509_ASN_ENCODING, &_CertificateContext->pCertInfo->Issuer, CERT_X500_NAME_STR, nullptr, 0);

	Elysium::Core::Container::VectorOfByte Buffer = Elysium::Core::Container::VectorOfByte(BufferLength);
	CertNameToStrA(X509_ASN_ENCODING, &_CertificateContext->pCertInfo->Issuer, CERT_X500_NAME_STR, (char*)&Buffer[0], BufferLength);

	return Elysium::Core::Text::Encoding::UTF8().GetString(&Buffer[0], Buffer.GetLength());
}

const Elysium::Core::Utf8String Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::GetSubject() const
{
	unsigned long BufferLength = CertNameToStrA(X509_ASN_ENCODING, &_CertificateContext->pCertInfo->Subject, CERT_X500_NAME_STR, nullptr, 0);

	Elysium::Core::Container::VectorOfByte Buffer = Elysium::Core::Container::VectorOfByte(BufferLength);
	CertNameToStrA(X509_ASN_ENCODING, &_CertificateContext->pCertInfo->Subject, CERT_X500_NAME_STR, (char*)&Buffer[0], BufferLength);

	return Elysium::Core::Text::Encoding::UTF8().GetString(&Buffer[0], Buffer.GetLength());
}

const Elysium::Core::Container::VectorOfByte Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::GetRawCertData() const
{
	if (_CertificateContext->dwCertEncodingType != X509_ASN_ENCODING)
	{
		int sdf = 45;
	}

	// get the size of the certificate
	unsigned long ByteLength = 0;
	if (CertSerializeCertificateStoreElement(_CertificateContext, 0, nullptr, &ByteLength))
	{
		// serialize the certificate context's encoded certificate and its properties.
		Elysium::Core::Container::VectorOfByte RawData = Elysium::Core::Container::VectorOfByte(ByteLength);
		if (CertSerializeCertificateStoreElement(_CertificateContext, 0, &RawData[0], &ByteLength))
		{
			// we don't care for the encoded certificate but only it's properties here
			Elysium::Core::Container::VectorOfByte PropertyData = Elysium::Core::Container::VectorOfByte(_CertificateContext->cbCertEncoded);
			Elysium::Core::Template::Memory::MemCpy(&PropertyData[0], &RawData[ByteLength - _CertificateContext->cbCertEncoded], _CertificateContext->cbCertEncoded);

			return PropertyData;
		}
		else
		{
			// ToDo: throw specific exception
			throw GetLastError();
		}
	}
	else
	{
		// ToDo: throw specific exception
		throw GetLastError();
	}
}

Elysium::Core::Container::VectorOfByte Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::Export(const X509ContentType ContentType, const char8_t* Password)
{
	if (ContentType != X509ContentType::Cert && ContentType != X509ContentType::SerializedCert && ContentType != X509ContentType::Pkcs12)
	{	// @ToDo: message
		throw CryptographicException();
	}

	throw 1;
}

Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::LoadFromBlob(const Elysium::Core::Container::VectorOfByte& RawData, const Elysium::Core::Utf8String& Password, const X509KeyStorageFlags Flags)
{
	return LoadFromBlob(&RawData[0], static_cast<const int32_t>(RawData.GetLength()), Password, Flags);
}

Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::LoadFromBlob(const byte * RawData, const uint32_t DataLength, const Elysium::Core::Utf8String& Password, const X509KeyStorageFlags Flags)
{
	PCCERT_CONTEXT CertificateContext = nullptr;
	HCRYPTPROV_OR_NCRYPT_KEY_HANDLE PrivateKeyHandle = 0;
	DWORD KeySpecifications = 0;
	BOOL FreeKey = FALSE;

	CRYPT_DATA_BLOB CryptDataBlob = CRYPT_DATA_BLOB();
	CryptDataBlob.pbData = (BYTE*)RawData;
	CryptDataBlob.cbData = DataLength;

	// @ToDo: input isn't safe
	Elysium::Core::WideString Utf16Password = Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString(&Password[0], Password.GetLength());

	HCERTSTORE InMemoryCertificateStore = PFXImportCertStore(&CryptDataBlob, &Utf16Password[0], CRYPT_EXPORTABLE);
	if (nullptr != InMemoryCertificateStore) 
	{	// pfx?
		PCCERT_CONTEXT CertificateContextIteration = nullptr;
		while ((CertificateContextIteration = CertEnumCertificatesInStore(InMemoryCertificateStore, CertificateContextIteration)) != nullptr)
		{
			CertificateContext = CertDuplicateCertificateContext(CertificateContextIteration);
			
			// get private key handle
			BOOL Result = CryptAcquireCertificatePrivateKey(CertificateContext,
				CRYPT_ACQUIRE_SILENT_FLAG | CRYPT_ACQUIRE_ALLOW_NCRYPT_KEY_FLAG, nullptr, &PrivateKeyHandle, 
				&KeySpecifications, &FreeKey);
			if (FALSE == Result)
			{	// @ToDo
				bool sdf = false;
			}
		}

		BOOL CloseCertificateStoreResult = CertCloseStore(InMemoryCertificateStore, 0);
		if (FALSE == CloseCertificateStoreResult)
		{
			// @ToDo: throw what?
			bool bla = false;
		}
	}
	else
	{	// pem?
		CertificateContext = CertCreateCertificateContext(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, RawData, DataLength);
	}

	if (CertificateContext == nullptr)
	{
		throw CryptographicException();
	}
	return X509Certificate(CertificateContext, PrivateKeyHandle, FreeKey == TRUE ? true : false, KeySpecifications);
}

Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::LoadFromFile(const char8_t* FileName, const Elysium::Core::Utf8String& Password, const X509KeyStorageFlags Flags)
{
	IO::FileStream SourceStream = IO::FileStream(FileName, IO::FileMode::Open, IO::FileAccess::Read);
	Elysium::Core::Container::VectorOfByte RawData = Elysium::Core::Container::VectorOfByte(SourceStream.GetLength());
	SourceStream.Read(&RawData[0], SourceStream.GetLength());
	
	unsigned long BufferLength = 0;
	if (!CryptStringToBinaryA((const char*)&RawData[0], 0, CRYPT_STRING_BASE64HEADER, NULL, &BufferLength, NULL, NULL))
	{
		unsigned long ErrorCode = GetLastError();
		char* ErrorMessageBuffer = nullptr;
		Elysium::Core::size size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, ErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&ErrorMessageBuffer, 0, NULL);
		LocalFree(ErrorMessageBuffer);

		// ToDo: message
		throw CryptographicException();
	}

	Elysium::Core::Container::VectorOfByte Buffer = Elysium::Core::Container::VectorOfByte(BufferLength);
	if (!CryptStringToBinaryA((const char*)&RawData[0], 0, CRYPT_STRING_BASE64HEADER, &Buffer[0], &BufferLength, NULL, NULL))
	{
		unsigned long ErrorCode = GetLastError();
		char* ErrorMessageBuffer = nullptr;
		Elysium::Core::size size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, ErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&ErrorMessageBuffer, 0, NULL);
		LocalFree(ErrorMessageBuffer);

		// ToDo: message
		throw CryptographicException();
	}

	return LoadFromBlob(Buffer, Password, Flags);
}

HCRYPTPROV_OR_NCRYPT_KEY_HANDLE Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::CopyPrivateKeyHandle(const X509Certificate& Source)
{
	if (0 == _PrivateKeyHandle)
	{
		return 0;
	}

	HCRYPTPROV_OR_NCRYPT_KEY_HANDLE KeyHandleCopy = 0;
	switch (_KeySpecifications)
	{
	case 0: // CNG key
		if (CryptContextAddRef(Source._PrivateKeyHandle, nullptr, 0))
		{
			KeyHandleCopy = Source._PrivateKeyHandle; // now you have a reference you can free independently
		}
		break;
	case AT_KEYEXCHANGE: // CryptoAPI key
		[[__fallthrough__]]
	case AT_SIGNATURE:
	{
		DWORD RequiredSize = 0;
		SECURITY_STATUS Status = NCryptExportKey(Source._PrivateKeyHandle, 0, BCRYPT_OPAQUE_KEY_BLOB, nullptr, nullptr, 0, 
			&RequiredSize, 0);
		if (ERROR_SUCCESS != Status)
		{
			// @Todo
			throw 1;
		}

		Elysium::Core::Container::VectorOfByte Data = Elysium::Core::Container::VectorOfByte(RequiredSize);
		Status = NCryptExportKey(Source._PrivateKeyHandle, 0, BCRYPT_OPAQUE_KEY_BLOB, nullptr, &Data[0], RequiredSize,
			&RequiredSize, 0);
		if (ERROR_SUCCESS != Status)
		{
			// @Todo
			throw 1;
		}

		Status = NCryptImportKey(0, 0, BCRYPT_OPAQUE_KEY_BLOB, nullptr, &KeyHandleCopy, &Data[0], RequiredSize, 0);
		if (ERROR_SUCCESS != Status)
		{
			// @Todo
			throw 1;
		}
	}
	break;
	default:
		// @ToDo
		throw 1;
	}

	return KeyHandleCopy;
}
