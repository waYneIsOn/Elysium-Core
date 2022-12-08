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

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif
#endif

Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::X509Certificate()
{ }

Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::X509Certificate(ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_CERTIFICATECONTEXTPOINTER CertificateContext)
	: _CertificateContext(CertDuplicateCertificateContext(CertificateContext))
{ }

Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::X509Certificate(const X509Certificate & Source)
	: _CertificateContext(CertDuplicateCertificateContext(Source._CertificateContext))
{ }

Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::X509Certificate(X509Certificate && Right) noexcept
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}

Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::~X509Certificate()
{
	if (_CertificateContext != nullptr)
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
	}
	return *this;
}

Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate & Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::operator=(X509Certificate && Right) noexcept
{
	if (this != &Right)
	{
		_CertificateContext = Elysium::Core::Template::Functional::Move(Right._CertificateContext);

		Right._CertificateContext = nullptr;
	}
	return *this;
}

const Elysium::Core::Utf8String Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::GetIssuer() const
{
	unsigned long BufferLength = CertNameToStrA(X509_ASN_ENCODING, &_CertificateContext->pCertInfo->Issuer, CERT_X500_NAME_STR, nullptr, 0);

	Collections::Template::Array<byte> Buffer = Collections::Template::Array<byte>(BufferLength);
	CertNameToStrA(X509_ASN_ENCODING, &_CertificateContext->pCertInfo->Issuer, CERT_X500_NAME_STR, (char*)&Buffer[0], BufferLength);

	return Elysium::Core::Text::Encoding::UTF8().GetString(&Buffer[0], Buffer.GetLength());
}

const Elysium::Core::Utf8String Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::GetSubject() const
{
	unsigned long BufferLength = CertNameToStrA(X509_ASN_ENCODING, &_CertificateContext->pCertInfo->Subject, CERT_X500_NAME_STR, nullptr, 0);

	Collections::Template::Array<byte> Buffer = Collections::Template::Array<byte>(BufferLength);
	CertNameToStrA(X509_ASN_ENCODING, &_CertificateContext->pCertInfo->Subject, CERT_X500_NAME_STR, (char*)&Buffer[0], BufferLength);

	return Elysium::Core::Text::Encoding::UTF8().GetString(&Buffer[0], Buffer.GetLength());
}

const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::GetRawCertData() const
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
		Collections::Template::Array<byte> RawData = Collections::Template::Array<byte>(ByteLength);
		if (CertSerializeCertificateStoreElement(_CertificateContext, 0, &RawData[0], &ByteLength))
		{
			// we don't care for the encoded certificate but only it's properties here
			Collections::Template::Array<byte> PropertyData = Collections::Template::Array<byte>(_CertificateContext->cbCertEncoded);
			Collections::Template::Array<byte>::Copy(&RawData[ByteLength - _CertificateContext->cbCertEncoded], &PropertyData[0], _CertificateContext->cbCertEncoded);

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

Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::LoadFromBlob(const Collections::Template::Array<byte>& RawData, const Elysium::Core::Utf8String& Password, const X509KeyStorageFlags Flags)
{
	return LoadFromBlob(&RawData[0], static_cast<const int32_t>(RawData.GetLength()), Password, Flags);
}

Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::LoadFromBlob(const byte * RawData, const uint32_t DataLength, const Elysium::Core::Utf8String& Password, const X509KeyStorageFlags Flags)
{
	ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_CERTIFICATECONTEXTPOINTER CertificateContextPointer = CertCreateCertificateContext(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, RawData, DataLength);
	if (CertificateContextPointer == nullptr)
	{
		throw CryptographicException();
	}
	return X509Certificate(CertificateContextPointer);
}

Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::LoadFromFile(const Elysium::Core::Utf8String& FileName, const Elysium::Core::Utf8String& Password, const X509KeyStorageFlags Flags)
{
	IO::FileStream SourceStream = IO::FileStream(FileName, IO::FileMode::Open, IO::FileAccess::Read);
	Collections::Template::Array<byte> RawData = Collections::Template::Array<byte>(SourceStream.GetLength());
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

	Collections::Template::Array<byte> Buffer = Collections::Template::Array<byte>(BufferLength);
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
