#include "X509Certificate.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_CRYPTOGRAPHICEXCEPTION
#include "CryptographicException.hpp"
#endif

Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::X509Certificate(ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_CERTIFICATECONTEXTPOINTER CertificateContext)
	: _CertificateContext(CertDuplicateCertificateContext(CertificateContext))
{ }
Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::X509Certificate(const X509Certificate & Source)
	: _CertificateContext(CertDuplicateCertificateContext(Source._CertificateContext))
{ }
Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::X509Certificate(X509Certificate && Right) noexcept
{
	*this = std::move(Right);
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
		_CertificateContext = Right._CertificateContext;

		Right._CertificateContext = nullptr;
	}
	return *this;
}

Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::LoadFromBlob(const Collections::Template::Array<byte>& RawData, const String & Password, const X509KeyStorageFlags Flags)
{
	unsigned long BufferLength = 0;
	if (!CryptStringToBinaryA((const char*)&RawData[0], 0, CRYPT_STRING_BASE64HEADER, NULL, &BufferLength, NULL, NULL))
	{
		/*
		DWORD ErrorCode = GetLastError();
		HRESULT hr = HRESULT_FROM_WIN32(ErrorCode);
		LPSTR ErrorMessageBuffer = nullptr;
		size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, ErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&ErrorMessageBuffer, 0, NULL);
		LocalFree(ErrorMessageBuffer);
		*/
		// ToDo: message
		throw CryptographicException();
	}

	Collections::Template::Array<byte> Buffer = Collections::Template::Array<byte>(BufferLength);
	if (!CryptStringToBinaryA((const char*)&RawData[0], 0, CRYPT_STRING_BASE64HEADER, &Buffer[0], &BufferLength, NULL, NULL))
	{
		/*
		DWORD ErrorCode = GetLastError();
		HRESULT hr = HRESULT_FROM_WIN32(ErrorCode);
		LPSTR ErrorMessageBuffer = nullptr;
		size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, ErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&ErrorMessageBuffer, 0, NULL);
		LocalFree(ErrorMessageBuffer);
		*/
		// ToDo: message
		throw CryptographicException();
	}

	ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_CERTIFICATECONTEXTPOINTER CertificateContextPointer = 
		CertCreateCertificateContext(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, &Buffer[0], BufferLength);
	if (CertificateContextPointer == nullptr)
	{
		/*
		DWORD ErrorCode = GetLastError();
		HRESULT hr = HRESULT_FROM_WIN32(ErrorCode);
		LPSTR ErrorMessageBuffer = nullptr;
		size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, ErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&ErrorMessageBuffer, 0, NULL);
		LocalFree(ErrorMessageBuffer);
		*/
		// ToDo: message
		throw CryptographicException();
	}

	return X509Certificate(CertificateContextPointer);
}
Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::LoadFromFile(const String & FileName, const String & Password, const X509KeyStorageFlags Flags)
{
	// ToDo
	throw CryptographicException();
	return X509Certificate();
}

Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::X509Certificate()
{ }
