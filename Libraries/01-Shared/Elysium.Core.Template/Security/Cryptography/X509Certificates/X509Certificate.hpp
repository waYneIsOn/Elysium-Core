/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATE
#define ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_SYSTEMEXCEPTION
#include "../../../Exceptions/SystemException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_SECURITY_CRYPTOGRAPHY_CRYPTOGRAPHICEXCEPTION
#include "../../../Exceptions/Security/Cryptography/CryptographicException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../../../Functional/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_DEVICE_FILEDEVICE
#include "../../../IO/Device/FileDevice.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMCPY
#include "../../../Memory/MemCpy.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CONTENTTYPE
#include "X509ContentType.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509KEYSTORAGEFLAGS
#include "X509KeyStorageFlags.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_COMPILATIONSETTINGS
#include "../../../System/CompilationSettings.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRINGVIEW
#include "../../../Text/StringView.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF16
#include "../../../Text/Unicode/Utf16.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#ifndef __NCRYPT_H__
#include <ncrypt.h>
#endif

#ifndef __WINCRYPT_H__
#include <wincrypt.h>
#endif

#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "Crypt32.Lib")
#pragma comment(lib, "Ncrypt.Lib")
#endif



// @ToDo: remove asap
namespace Elysium::Core::Net::Security
{
	class TlsStream;
}


namespace Elysium::Core::Template::Security::Cryptography::X509Certificates
{
#if defined ELYSIUM_CORE_USEEXPERIMENTALIMPLEMENTATION_X509CERTIFICATE
	/*
	class X509Certificate
	{
	public:

	public:

	private:

	};
	*/
#elif defined ELYSIUM_CORE_OS_WINDOWS
	class X509Certificate
	{
	public:
		friend class X509Chain;
		friend class Elysium::Core::Template::Container::Vector<X509Certificate>;

		friend class Elysium::Core::Net::Security::TlsStream;
	private:
		inline constexpr X509Certificate()
			: _CertificateContext{}, _OwnsPrivateKeyHandle{}, _PrivateKeyHandle{}, _KeySpecifications(-1)
		{ }
	public:
		inline constexpr X509Certificate(PCCERT_CONTEXT CertificateContext, HCRYPTPROV_OR_NCRYPT_KEY_HANDLE PrivateKeyHandle = 0,
			const bool OwnsPrivateKeyHandle = false, const DWORD KeySpecifications = -1) 
			: _CertificateContext(CertDuplicateCertificateContext(CertificateContext)), _OwnsPrivateKeyHandle(OwnsPrivateKeyHandle), _PrivateKeyHandle(PrivateKeyHandle), 
			_KeySpecifications(KeySpecifications)
		{ }

		inline constexpr X509Certificate(const X509Certificate& Source)
			: _CertificateContext(CertDuplicateCertificateContext(Source._CertificateContext)), _OwnsPrivateKeyHandle(Source._OwnsPrivateKeyHandle), 
			_PrivateKeyHandle(CopyPrivateKeyHandle(Source)), _KeySpecifications(Source._KeySpecifications)
		{ }

		inline constexpr X509Certificate(X509Certificate&& Right) noexcept
			: _CertificateContext{}, _OwnsPrivateKeyHandle{}, _PrivateKeyHandle{}, _KeySpecifications{}
		{
			*this = Elysium::Core::Template::Functional::Move(Right);
		}

		inline constexpr ~X509Certificate()
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
	public:
		inline constexpr X509Certificate& operator=(const X509Certificate& Source)
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

		inline constexpr X509Certificate& operator=(X509Certificate&& Right) noexcept
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
	public:
		inline constexpr const bool operator==(const X509Certificate& Other) const
		{
			if (this == &Other)
			{
				return true;
			}

			return _CertificateContext == Other._CertificateContext && _PrivateKeyHandle == Other._PrivateKeyHandle;
		}
	public:
		inline constexpr const Elysium::Core::Template::Text::String<char8_t> GetIssuer() const
		{
			const DWORD BufferLength = CertNameToStrW(X509_ASN_ENCODING, &_CertificateContext->pCertInfo->Issuer, CERT_X500_NAME_STR, nullptr, 0);

			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> Buffer(BufferLength * sizeof(wchar_t));
			CertNameToStrW(X509_ASN_ENCODING, &_CertificateContext->pCertInfo->Issuer, CERT_X500_NAME_STR, reinterpret_cast<wchar_t*>(&Buffer[0]), BufferLength);

			return Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<char8_t>(reinterpret_cast<wchar_t*>(&Buffer[0]), Buffer.GetLength() / sizeof(wchar_t));
		}

		inline constexpr const Elysium::Core::Template::Text::String<char8_t> GetSubject() const
		{
			const DWORD BufferLength = CertNameToStrW(X509_ASN_ENCODING, &_CertificateContext->pCertInfo->Subject, CERT_X500_NAME_STR, nullptr, 0);

			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> Buffer(BufferLength * sizeof(wchar_t));
			CertNameToStrW(X509_ASN_ENCODING, &_CertificateContext->pCertInfo->Subject, CERT_X500_NAME_STR, reinterpret_cast<wchar_t*>(&Buffer[0]), BufferLength);

			return Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<char8_t>(reinterpret_cast<wchar_t*>(&Buffer[0]), Buffer.GetLength() / sizeof(wchar_t));
		}

		inline constexpr const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> GetRawCertData() const
		{
			/*
			if (X509_ASN_ENCODING != _CertificateContext->dwCertEncodingType)
			{
				int sdf = 45;
			}
			*/
			// get the size of the certificate
			DWORD ByteLength = 0;
			if (CertSerializeCertificateStoreElement(_CertificateContext, 0, nullptr, &ByteLength))
			{
				// serialize the certificate context's encoded certificate and its properties.
				Elysium::Core::Container::VectorOfByte RawData = Elysium::Core::Container::VectorOfByte(ByteLength);
				if (CertSerializeCertificateStoreElement(_CertificateContext, 0, &RawData[0], &ByteLength))
				{
					// I don't care for the encoded certificate but only it's properties here
					Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> PropertyData(_CertificateContext->cbCertEncoded);
					Elysium::Core::Template::Memory::MemCpy(&PropertyData[0], &RawData[ByteLength - _CertificateContext->cbCertEncoded], _CertificateContext->cbCertEncoded);

					return PropertyData;
				}
				else
				{
					throw Elysium::Core::Template::Exceptions::Security::Cryptography::CryptographicException();
				}
			}
			else
			{
				throw Elysium::Core::Template::Exceptions::Security::Cryptography::CryptographicException();
			}
		}
	public:
		inline Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> Export(
			const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509ContentType ContentType, const Elysium::Core::Template::Text::StringView<char8_t>* Password)
		{
			if (ContentType != Elysium::Core::Template::Security::Cryptography::X509Certificates::X509ContentType::Cert &&
				ContentType != Elysium::Core::Template::Security::Cryptography::X509Certificates::X509ContentType::SerializedCert &&
				ContentType != Elysium::Core::Template::Security::Cryptography::X509Certificates::X509ContentType::Pkcs12)
			{	// @ToDo: message
				throw Elysium::Core::Template::Exceptions::Security::Cryptography::CryptographicException(u8"");
			}

			// @ToDo
			throw;
		}
	public:
		inline static constexpr X509Certificate LoadFromBlob(const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte>& RawData,
			const Elysium::Core::Utf8String& Password = u8"", const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509KeyStorageFlags Flags = 
			Elysium::Core::Template::Security::Cryptography::X509Certificates::X509KeyStorageFlags::All)
		{
			return LoadFromBlob(&RawData[0], RawData.GetLength(), Password, Flags);
		}

		inline static constexpr X509Certificate LoadFromBlob(const Elysium::Core::Template::System::byte* RawData, const Elysium::Core::Template::System::size DataLength,
			const Elysium::Core::Utf8String& Password = u8"", const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509KeyStorageFlags Flags =
			Elysium::Core::Template::Security::Cryptography::X509Certificates::X509KeyStorageFlags::All)
		{
			PCCERT_CONTEXT CertificateContext = nullptr;
			HCRYPTPROV_OR_NCRYPT_KEY_HANDLE PrivateKeyHandle = 0;
			DWORD KeySpecifications = 0;
			BOOL FreeKey = FALSE;

			CRYPT_DATA_BLOB CryptDataBlob = CRYPT_DATA_BLOB();
			CryptDataBlob.pbData = (BYTE*)RawData;
			CryptDataBlob.cbData = DataLength;

			// @ToDo: input isn't safe
			Elysium::Core::Template::Text::String<wchar_t> Utf16Password = Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString(&Password[0], Password.GetLength());

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
						throw;
					}
				}

				BOOL CloseCertificateStoreResult = CertCloseStore(InMemoryCertificateStore, 0);
				if (FALSE == CloseCertificateStoreResult)
				{
					// @ToDo: throw what?
					throw;
				}
			}
			else
			{	// pem?
				CertificateContext = CertCreateCertificateContext(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, RawData, DataLength);
			}

			if (CertificateContext == nullptr)
			{
				throw Elysium::Core::Template::Exceptions::Security::Cryptography::CryptographicException();
			}
			return X509Certificate(CertificateContext, PrivateKeyHandle, FreeKey == TRUE ? true : false, KeySpecifications);
		}

		inline static constexpr X509Certificate LoadFromFile(const char8_t* FileName,
			const Elysium::Core::Utf8String& Password = u8"", const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509KeyStorageFlags Flags =
			Elysium::Core::Template::Security::Cryptography::X509Certificates::X509KeyStorageFlags::All)
		{
			Elysium::Core::Template::IO::Device::FileDevice Source(FileName, Elysium::Core::Template::IO::FileMode::Open, Elysium::Core::Template::IO::FileAccess::Read);
			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> RawData(Source.GetLength());
			Elysium::Core::Template::System::size TotalBytesCopied = 0;
			while (TotalBytesCopied < Source.GetLength())
			{
				Elysium::Core::Template::System::size BytesRead = Source.Read(&RawData[TotalBytesCopied], Source.GetLength( )- TotalBytesCopied);
				TotalBytesCopied += BytesRead;
			}

			DWORD BufferLength = 0;
			if (FALSE == CryptStringToBinaryA(reinterpret_cast<const char*>(&RawData[0]), 0, CRYPT_STRING_BASE64HEADER, NULL, &BufferLength, NULL, NULL))
			{
				DWORD ErrorCode = GetLastError();
				CHAR* ErrorMessageBuffer = nullptr;
				const Elysium::Core::Template::System::size Length = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL, ErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPSTR>(&ErrorMessageBuffer), 0, NULL);
				Elysium::Core::Template::Exceptions::Security::Cryptography::CryptographicException Exception(ErrorCode, reinterpret_cast<char8_t*>(ErrorMessageBuffer));
				LocalFree(ErrorMessageBuffer);

				throw Exception;
			}

			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> Buffer(BufferLength);
			if (FALSE == CryptStringToBinaryA(reinterpret_cast<const char*>(&RawData[0]), 0, CRYPT_STRING_BASE64HEADER, &Buffer[0], &BufferLength, NULL, NULL))
			{
				DWORD ErrorCode = GetLastError();
				CHAR* ErrorMessageBuffer = nullptr;
				const Elysium::Core::Template::System::size Length = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL, ErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&ErrorMessageBuffer, 0, NULL);
				Elysium::Core::Template::Exceptions::Security::Cryptography::CryptographicException Exception(ErrorCode, reinterpret_cast<char8_t*>(ErrorMessageBuffer));
				LocalFree(ErrorMessageBuffer);

				throw Exception;
			}

			return LoadFromBlob(Buffer, Password, Flags);
		}
	private:
		inline HCRYPTPROV_OR_NCRYPT_KEY_HANDLE CopyPrivateKeyHandle(const X509Certificate& Source)
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
				SECURITY_STATUS Status = NCryptExportKey(Source._PrivateKeyHandle, 0, BCRYPT_OPAQUE_KEY_BLOB, nullptr, nullptr, 0, &RequiredSize, 0);
				if (ERROR_SUCCESS != Status)
				{
					// @Todo
					throw;
				}

				Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> Data(RequiredSize);
				Status = NCryptExportKey(Source._PrivateKeyHandle, 0, BCRYPT_OPAQUE_KEY_BLOB, nullptr, &Data[0], RequiredSize, &RequiredSize, 0);
				if (ERROR_SUCCESS != Status)
				{
					// @Todo
					throw;
				}

				Status = NCryptImportKey(0, 0, BCRYPT_OPAQUE_KEY_BLOB, nullptr, &KeyHandleCopy, &Data[0], RequiredSize, 0);
				if (ERROR_SUCCESS != Status)
				{
					// @Todo
					throw;
				}
			}
				break;
			default:
				// @ToDo
				throw;
			}

			return KeyHandleCopy;
		}
	private:
		PCCERT_CONTEXT _CertificateContext;

		bool _OwnsPrivateKeyHandle;
		HCRYPTPROV_OR_NCRYPT_KEY_HANDLE _PrivateKeyHandle;
		DWORD _KeySpecifications;
	};
#endif
}
#endif
