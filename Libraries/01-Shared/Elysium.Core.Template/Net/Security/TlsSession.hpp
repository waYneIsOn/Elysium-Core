/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_NET_SECURITY_TLSSESSION
#define ELYSIUM_CORE_TEMPLATE_NET_SECURITY_TLSSESSION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VIEW_SPAN
#include "../../Container/View/Span.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_SECURITY_AUTHENTICATION_AUTHENTICATIONEXCEPTION
#include "../../Exceptions/Security/Authentication/AuthenticationException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_READRESULT
#include "../../IO/ReadResult.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMCPY
#include "../../Memory/MemCpy.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMMOVE
#include "../../Memory/MemMove.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SECURITY_TLSPOLICYERRORS
#include "TlsPolicyErrors.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_AUTHENTICATION_TLSPROTOCOL
#include "../../Security/Authentication/TlsProtocols.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATE
#include "../../Security/Cryptography/X509Certificates/X509Certificate.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CHAIN
#include "../../Security/Cryptography/X509Certificates/X509Chain.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_COMPILATIONSETTINGS
#include "../../System/CompilationSettings.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRINGVIEW
#include "../../Text/StringView.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF16
#include "../../Text/Unicode/Utf16.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
	#ifndef _WINTERNL_
	#include <winternl.h>
	#endif

	#define SECURITY_WIN32
	#include <security.h>
	/*
	#ifndef __SSPI_H__
	#include <sspi.h>
	#endif
	*/
	#ifndef __SCHANNEL_H__
	#define SCHANNEL_USE_BLACKLISTS
	#include <schannel.h>
	#endif

	#pragma comment(lib, "Secur32.lib")
#endif

namespace Elysium::Core::Template::Net::Security
{
#if defined ELYSIUM_CORE_USE_CUSTOM_IMPLEMENTATION_TLS
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="InnerSink"></typeparam>
	/// <typeparam name="InnerSource"></typeparam>
	template <class InnerSink, class InnerSource>
	class TlsSession
	{
	public:
		using DeviceType = InnerSink::DeviceType;
	public:
		inline constexpr TlsSession(InnerSink& Sink, InnerSource& Source)
			: _InnerSink(Sink), _InnerSource(Source)
		{ }

		constexpr TlsSession(const TlsSession& TlsSession) = delete;

		constexpr TlsSession(TlsSession&& TlsSession) noexcept = delete;

		constexpr ~TlsSession() = default;
	public:
		constexpr TlsSession& operator=(const TlsSession& Source) = delete;

		constexpr TlsSession& operator=(TlsSession&& Right) noexcept = delete;
	public:
		inline constexpr const bool operator==(const TlsSession& Other) const noexcept
		{	// @ToDo
			return this == &Other;
		}
	public:
		inline void AuthenticateAsClient(const Elysium::Core::Template::Text::StringView<char8_t> TargetHost,
			const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate>* ClientCertificates = nullptr,
			const Elysium::Core::Template::Security::Authentication::TlsProtocols EnabledTlsProtocols = Elysium::Core::Template::Security::Authentication::TlsProtocols::Tls12,
			const bool CheckCertficateRevocation = true)
		{
			WriteClientHello(EnabledTlsProtocols);
			ReadServerHello();
			ReadServerCertificates();
			ReadServerKeyExchange();
			ReadServerHelloDone();

			throw 1;
		}
		
		inline void AuthenticateAsServer(const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate& ServerCertificate,
			const bool ClientCertificateRequired, const Elysium::Core::Template::Security::Authentication::TlsProtocols EnabledTlsProtocols,
			const bool CheckCertficateRevocation)
		{
			throw 1;
		}
	public:
		inline void Write(const Elysium::Core::Template::System::byte* Data, const Elysium::Core::Template::System::size Length)
		{
			throw 1;
		}

		inline void Flush()
		{
			throw 1;
		}
	public:
		inline const Elysium::Core::Template::IO::ReadResult ReadBlock(Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte>& DataView)
		{
			throw 1;
		}

		inline void AdvanceReadingBlock(const Elysium::Core::Template::System::size Length)
		{
			throw 1;
		}
	private:
		inline void WriteClientHello(const Elysium::Core::Template::Security::Authentication::TlsProtocols EnabledTlsProtocols)
		{	
			// https://tls12.xargs.org/
			// https://tls13.xargs.org/
			// https://github.com/waYneIsOn/Elysium-Core/blob/4c62241b489e093f5786d2d320e0470a58a118d1/Libraries/01-Shared/Elysium.Core.Net/ExperimentalTlsStream.cpp#L143

		}

		inline void ReadServerHello()
		{

		}

		inline void ReadServerCertificates()
		{

		}

		inline void ReadServerKeyExchange()
		{

		}

		inline void ReadServerHelloDone()
		{

		}
	private:
		InnerSink& _InnerSink;
		InnerSource& _InnerSource;
	};
#elif defined ELYSIUM_CORE_OS_WINDOWS
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="InnerSink"></typeparam>
	/// <typeparam name="InnerSource"></typeparam>
	template <class InnerSink, class InnerSource>
	class TlsSession
	{
	public:
		using DeviceType = InnerSink::DeviceType;
	public:
		inline constexpr TlsSession(InnerSink& Sink, InnerSource& Source)
			: _InnerSink(Sink), _InnerSource(Source),
			_CredentialHandle{}, _CredentialHandleValid(false), _ContextHandle{}, _StreamSizes{},
			_InBuffer(16384), _OutBuffer(16384), _UncompressedOutBuffer(2048)
		{
			_InBuffer.Clear();
			_OutBuffer.Clear();
			_UncompressedOutBuffer.Clear();
		}

		constexpr TlsSession(const TlsSession& TlsSession) = delete;

		constexpr TlsSession(TlsSession&& TlsSession) noexcept = delete;

		constexpr ~TlsSession() = default;
	public:
		constexpr TlsSession& operator=(const TlsSession& Source) = delete;

		constexpr TlsSession& operator=(TlsSession&& Right) noexcept = delete;
	public:
		inline constexpr const bool operator==(const TlsSession& Other) const noexcept
		{	// @ToDo
			return this == &Other;
		}
	public:
		inline void AuthenticateAsClient(const Elysium::Core::Template::Text::StringView<char8_t> TargetHost,
			const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate>* ClientCertificates = nullptr,
			const Elysium::Core::Template::Security::Authentication::TlsProtocols EnabledTlsProtocols = Elysium::Core::Template::Security::Authentication::TlsProtocols::Tls12,
			const bool CheckCertficateRevocation = true)
		{
			// @ToDo: validate input! (TargetHost)
			Elysium::Core::Template::Text::String<wchar_t> TargetHostUTF16LE = Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString(&TargetHost[0], TargetHost.GetLength());

			AcquireClientCredentials(EnabledTlsProtocols);
			PerformClientHandshake(TargetHostUTF16LE, nullptr);
			QueryStreamSizes();
			ValidateServerCertificate();
		}
		
		inline void AuthenticateAsServer(const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate& ServerCertificate,
			const bool ClientCertificateRequired, const Elysium::Core::Template::Security::Authentication::TlsProtocols EnabledTlsProtocols,
			const bool CheckCertficateRevocation)
		{
			AcquireServerCredentials(EnabledTlsProtocols, &ServerCertificate._CertificateContext);
			PerformServerHandshake(nullptr);
			QueryStreamSizes();
		}
	public:
		inline void Write(const Elysium::Core::Template::System::byte* Data, const Elysium::Core::Template::System::size Length)
		{
			if (Length > _StreamSizes.cbMaximumMessage)
			{
				// @ToDo: split and run in a loop!
				throw Elysium::Core::Template::Exceptions::Security::Authentication::AuthenticationException(SEC_E_BUFFER_TOO_SMALL);
			}

			SecBuffer OutBuffers[3]{};

			OutBuffers[0].BufferType = SECBUFFER_STREAM_HEADER;
			OutBuffers[0].cbBuffer = _StreamSizes.cbHeader;

			OutBuffers[1].BufferType = SECBUFFER_DATA;
			OutBuffers[1].cbBuffer = Length;

			OutBuffers[2].BufferType = SECBUFFER_STREAM_TRAILER;
			OutBuffers[2].cbBuffer = _StreamSizes.cbTrailer;

			_OutBuffer.Resize(_StreamSizes.cbHeader + Length + _StreamSizes.cbTrailer);

			OutBuffers[0].pvBuffer = &_OutBuffer[0];
			OutBuffers[1].pvBuffer = &_OutBuffer[_StreamSizes.cbHeader];
			OutBuffers[2].pvBuffer = &_OutBuffer[_StreamSizes.cbHeader + Length];

			Elysium::Core::Template::Memory::MemCpy(OutBuffers[1].pvBuffer, Data, Length);

			SecBufferDesc BufferDesc{};
			BufferDesc.ulVersion = SECBUFFER_VERSION;
			BufferDesc.cBuffers = 3;
			BufferDesc.pBuffers = OutBuffers;

			SECURITY_STATUS Status = EncryptMessage(&_ContextHandle, 0, &BufferDesc, 0);
			if (SEC_E_OK != Status)
			{
				throw Elysium::Core::Template::Exceptions::Security::Authentication::AuthenticationException(Status);
			}

			_InnerSink.Write(&_OutBuffer[0], _OutBuffer.GetLength());
		}

		inline void Flush()
		{
			_InnerSink.Flush();
		}
	public:
		inline const Elysium::Core::Template::IO::ReadResult ReadBlock(Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte>& DataView)
		{
			if (0 < _UncompressedOutBuffer.GetLength())
			{	// previous data available
				DataView.SetData(&_UncompressedOutBuffer[0]);
				DataView.SetLength(_UncompressedOutBuffer.GetLength());

				return Elysium::Core::Template::IO::ReadResult::HasData;
			}

			Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> EncryptedView{};

			SecBuffer InputBuffers[4]{};

			SecBufferDesc InBufferDescriptor{};
			InBufferDescriptor.ulVersion = SECBUFFER_VERSION;
			InBufferDescriptor.cBuffers = 4;
			InBufferDescriptor.pBuffers = InputBuffers;

			while(true)
			{
				// ...
				const Elysium::Core::Template::IO::ReadResult Result = _InnerSource.ReadBlock(EncryptedView);
				if (Elysium::Core::Template::IO::ReadResult::Pending == Result)
				{
					continue;
				}

				Elysium::Core::Template::System::size OldLength = _InBuffer.GetLength();
				Elysium::Core::Template::System::size AvailableBytes = EncryptedView.GetLength();
				_InBuffer.Resize(OldLength + AvailableBytes);
				Elysium::Core::Template::Memory::MemCpy(&_InBuffer[OldLength], EncryptedView.GetData(), AvailableBytes);

				// ...
				InputBuffers[0].BufferType = SECBUFFER_DATA;
				InputBuffers[0].pvBuffer = &_InBuffer[0];
				InputBuffers[0].cbBuffer = _InBuffer.GetLength();

				InputBuffers[1].BufferType = SECBUFFER_EMPTY;
				InputBuffers[2].BufferType = SECBUFFER_EMPTY;
				InputBuffers[3].BufferType = SECBUFFER_EMPTY;

				SECURITY_STATUS Status = DecryptMessage(&_ContextHandle, &InBufferDescriptor, 0, nullptr);
				switch (Status)
				{
				case SEC_E_OK:
				{
					SecBuffer* DataBuffer = nullptr;
					SecBuffer* ExtraBuffer = nullptr;
					for (Elysium::Core::Template::System::uint8_t i = 0; i < 4; ++i)
					{
						switch (InputBuffers[i].BufferType)
						{
						case SECBUFFER_DATA:
							DataBuffer = &InputBuffers[i];
							break;
						case SECBUFFER_EXTRA:
							ExtraBuffer = &InputBuffers[i];
							break;
						}
					}

					if (nullptr != DataBuffer && DataBuffer->cbBuffer != 0)
					{
						_UncompressedOutBuffer.Resize(DataBuffer->cbBuffer);
						Elysium::Core::Template::Memory::MemCpy(&_UncompressedOutBuffer[0], DataBuffer->pvBuffer, DataBuffer->cbBuffer);
					}

					PreserveExtraInput(ExtraBuffer);

					DataView.SetData(&_UncompressedOutBuffer[0]);
					DataView.SetLength(_UncompressedOutBuffer.GetLength());

					_InnerSource.AdvanceReadingBlock(EncryptedView.GetLength());

					return Elysium::Core::Template::IO::ReadResult::HasData;
				}
					break;
				case SEC_E_INCOMPLETE_MESSAGE:
					continue;
				case SEC_I_CONTEXT_EXPIRED:
					_InBuffer.Clear();
					_UncompressedOutBuffer.Clear();
					return Elysium::Core::Template::IO::ReadResult::EndOfStream;
				case SEC_I_RENEGOTIATE:
					// @ToDo
					throw 1;
					/*
					SecBuffer* RenegotiationBuffer = nullptr;
					for (Elysium::Core::Template::System::uint8_t i = 0; i < 4; ++i)
					{

					}
					PerformClientHandshake(&RenegotiationBuffer);
					continue;
					*/
				default:
					throw Elysium::Core::Template::Exceptions::Security::Authentication::AuthenticationException(Status);
				}
			}

			return Elysium::Core::Template::IO::ReadResult::Pending;
		}

		inline void AdvanceReadingBlock(const Elysium::Core::Template::System::size Length)
		{
			if (Length > _UncompressedOutBuffer.GetLength())
			{	// @ToDo
				throw 1;
			}
			else if (Length == _UncompressedOutBuffer.GetLength())
			{
				_UncompressedOutBuffer.Clear();
			}
			else
			{
				const Elysium::Core::Template::System::size RemainingLength = _UncompressedOutBuffer.GetLength() - Length;
				Elysium::Core::Template::Memory::MemCpy(&_UncompressedOutBuffer[0], &_UncompressedOutBuffer[Length], RemainingLength);
				_UncompressedOutBuffer.Resize(RemainingLength);
			}
		}
	private:
		inline void AcquireClientCredentials(const Elysium::Core::Template::Security::Authentication::TlsProtocols EnabledTlsProtocols)
		{
			TLS_PARAMETERS TlsParameters{};
			switch (EnabledTlsProtocols)
			{
			case Elysium::Core::Template::Security::Authentication::TlsProtocols::Tls12:
				TlsParameters.grbitDisabledProtocols = SP_PROT_TLS1_0_CLIENT | SP_PROT_TLS1_1_CLIENT;
				break;
			case Elysium::Core::Template::Security::Authentication::TlsProtocols::Tls13:
				TlsParameters.grbitDisabledProtocols = SP_PROT_TLS1_0_CLIENT | SP_PROT_TLS1_1_CLIENT | SP_PROT_TLS1_2_CLIENT;
				break;
			default:
				// @ToDo
				throw 1;
			}

			SCH_CREDENTIALS SChannelCredentials{};
			SChannelCredentials.dwVersion = SCH_CREDENTIALS_VERSION;
			SChannelCredentials.dwFlags = SCH_CRED_NO_DEFAULT_CREDS | SCH_CRED_MANUAL_CRED_VALIDATION | SCH_USE_STRONG_CRYPTO;
			SChannelCredentials.cTlsParameters = 1;
			SChannelCredentials.pTlsParameters = &TlsParameters;

			// @ToDo: client certificates (need to change dwFlags accordingly!!!!)
			SChannelCredentials.cCreds = 0;
			SChannelCredentials.paCred = nullptr;

			TimeStamp Lifetime{};
			SECURITY_STATUS Status = AcquireCredentialsHandleW(nullptr, const_cast<LPWSTR>(UNISP_NAME_W), SECPKG_CRED_OUTBOUND, nullptr, &SChannelCredentials, nullptr, nullptr,
				&_CredentialHandle, &Lifetime);
			if (SEC_E_OK != Status)
			{
				throw Elysium::Core::Template::Exceptions::Security::Authentication::AuthenticationException(Status);
			}

			_CredentialHandleValid = true;
		}

		inline void PerformClientHandshake(Elysium::Core::Template::Text::String<wchar_t>& TargetHost, SecBuffer* RenegotiationBuffer)
		{
			// create schannel security context
			SecBuffer OutputBuffers[2]{};
			SecBufferDesc OutputBufferDescriptor{};
			OutputBufferDescriptor.ulVersion = SECBUFFER_VERSION;
			OutputBufferDescriptor.cBuffers = 2;
			OutputBufferDescriptor.pBuffers = OutputBuffers;

			SecBuffer InputBuffers[2]{};
			SecBufferDesc InputBuffersDesc{};
			InputBuffersDesc.ulVersion = SECBUFFER_VERSION;
			InputBuffersDesc.cBuffers = 2;
			InputBuffersDesc.pBuffers = InputBuffers;
			
			ULONG ContextAttributes = 0;
			TimeStamp Lifetime{};
			const ULONG RequiredContext = ISC_REQ_SEQUENCE_DETECT | ISC_REQ_REPLAY_DETECT | ISC_REQ_CONFIDENTIALITY | ISC_REQ_ALLOCATE_MEMORY | ISC_REQ_EXTENDED_ERROR |
				ISC_REQ_MANUAL_CRED_VALIDATION | ISC_REQ_USE_SUPPLIED_CREDS | ISC_REQ_STREAM;

			SECURITY_STATUS Status{};

			bool ContextEstablished = false;
			while(true)
			{
				OutputBuffers[0].BufferType = SECBUFFER_TOKEN;
				OutputBuffers[0].cbBuffer = 0;
				OutputBuffers[0].pvBuffer = nullptr;
				OutputBuffers[1].BufferType = SECBUFFER_ALERT;
				OutputBuffers[1].cbBuffer = 0;
				OutputBuffers[1].pvBuffer = nullptr;

				InputBuffers[0].BufferType = SECBUFFER_EMPTY;
				InputBuffers[1].BufferType = SECBUFFER_EMPTY;
				
				if (ContextEstablished && nullptr != RenegotiationBuffer)
				{
					InputBuffers[0] = *RenegotiationBuffer;

					InputBuffers[1].BufferType = SECBUFFER_EMPTY;
					InputBuffers[1].pvBuffer = nullptr;
					InputBuffers[1].cbBuffer = 0;

				}
				else if (ContextEstablished)
				{
					InputBuffers[0].BufferType = SECBUFFER_TOKEN;
					InputBuffers[0].pvBuffer = &_InBuffer[0];
					InputBuffers[0].cbBuffer = _InBuffer.GetLength();

					InputBuffers[1].BufferType = SECBUFFER_EMPTY;
					InputBuffers[1].pvBuffer = nullptr;
					InputBuffers[1].cbBuffer = 0;
				}

				Status = InitializeSecurityContextW(&_CredentialHandle, !ContextEstablished && nullptr == RenegotiationBuffer ? nullptr : &_ContextHandle, &TargetHost[0],
					RequiredContext, 0, SECURITY_NATIVE_DREP, !ContextEstablished ? nullptr : &InputBuffersDesc, !ContextEstablished ? 0 : InputBuffersDesc.cBuffers, &_ContextHandle,
					&OutputBufferDescriptor, &ContextAttributes, &Lifetime);
				ContextEstablished = 0 != _ContextHandle.dwUpper || 0 != _ContextHandle.dwLower;

				switch (Status)
				{
				case SEC_E_OK:
				{
					if (ContextEstablished)
					{
						ConsumeHandshakeInput(InputBuffers[1]);
					}

					SendOutputToken(OutputBufferDescriptor);
				}
					return;
				case SEC_I_CONTINUE_NEEDED:
				{
					if (ContextEstablished)
					{
						ConsumeHandshakeInput(InputBuffers[1]);
					}

					SendOutputToken(OutputBufferDescriptor);
					if (!ReadHandshakeData())
					{
						// Depending on windows version (<11/server 2022), this might be an alert that the server has closed the connection gracefully!
						// @ToDo: throw a more specific exception!
						throw Elysium::Core::Template::Exceptions::Security::Authentication::AuthenticationException(SEC_E_INTERNAL_ERROR);
					}
				}
					break;
				case SEC_E_INCOMPLETE_MESSAGE:
				{
					if (!ReadHandshakeData())
					{
						throw Elysium::Core::Template::Exceptions::Security::Authentication::AuthenticationException(SEC_E_INTERNAL_ERROR);
					}
				}
					break;
				case SEC_I_COMPLETE_NEEDED:
				{
					if (ContextEstablished)
					{
						ConsumeHandshakeInput(InputBuffers[1]);
					}

					Status = CompleteAuthToken(&_ContextHandle, &OutputBufferDescriptor);
					if (SEC_E_OK != Status)
					{
						throw Elysium::Core::Template::Exceptions::Security::Authentication::AuthenticationException(Status);
					}

					SendOutputToken(OutputBufferDescriptor);
				}
					break;
				case SEC_I_COMPLETE_AND_CONTINUE:
				{
					if (ContextEstablished)
					{
						ConsumeHandshakeInput(InputBuffers[1]);
					}

					Status = CompleteAuthToken(&_ContextHandle, &OutputBufferDescriptor);
					if (SEC_E_OK != Status)
					{
						throw Elysium::Core::Template::Exceptions::Security::Authentication::AuthenticationException(Status);
					}

					SendOutputToken(OutputBufferDescriptor);

					if (!ReadHandshakeData())
					{
						throw Elysium::Core::Template::Exceptions::Security::Authentication::AuthenticationException(SEC_E_INTERNAL_ERROR);
					}
				}
					break;
				default:
					throw Elysium::Core::Template::Exceptions::Security::Authentication::AuthenticationException(Status);
				}
			}
		}

		inline void QueryStreamSizes()
		{
			SecPkgContext_StreamSizes Sizes{};
			SECURITY_STATUS Status = QueryContextAttributesW(&_ContextHandle, SECPKG_ATTR_STREAM_SIZES, &Sizes);
			if (SEC_E_OK != Status)
			{
				throw Elysium::Core::Template::Exceptions::Security::Authentication::AuthenticationException(Status);
			}

			_StreamSizes = Sizes;
		}

		inline void ValidateServerCertificate()
		{
			PCCERT_CONTEXT ServerCertificate = nullptr;
			SECURITY_STATUS Status = QueryContextAttributesW(&_ContextHandle, SECPKG_ATTR_REMOTE_CERT_CONTEXT, &ServerCertificate);
			if (SEC_E_OK != Status)
			{
				throw Elysium::Core::Template::Exceptions::Security::Authentication::AuthenticationException(Status);
			}

			// @ToDo: perform actual certificate-chain + hostname validation here.
			bool sdaf = false;

			CertFreeCertificateContext(ServerCertificate);
		}
	private:
		inline void AcquireServerCredentials(const Elysium::Core::Template::Security::Authentication::TlsProtocols EnabledTlsProtocols, const PCCERT_CONTEXT* NativeServerCertificate)
		{
			TLS_PARAMETERS TlsParameters{};
			switch (EnabledTlsProtocols)
			{
			case Elysium::Core::Template::Security::Authentication::TlsProtocols::Tls12:
				TlsParameters.grbitDisabledProtocols = SP_PROT_TLS1_0_SERVER | SP_PROT_TLS1_1_SERVER;
				break;
			case Elysium::Core::Template::Security::Authentication::TlsProtocols::Tls13:
				TlsParameters.grbitDisabledProtocols = SP_PROT_TLS1_0_SERVER | SP_PROT_TLS1_1_SERVER | SP_PROT_TLS1_2_SERVER;
				break;
			default:
				// @ToDo
				throw 1;
			}

			SCH_CREDENTIALS SChannelCredentials{};
			SChannelCredentials.dwVersion = SCH_CREDENTIALS_VERSION;
			SChannelCredentials.dwFlags = SCH_CRED_NO_DEFAULT_CREDS | SCH_USE_STRONG_CRYPTO; // | SCH_CRED_MANUAL_CRED_VALIDATION 
			SChannelCredentials.cTlsParameters = 1;
			SChannelCredentials.pTlsParameters = &TlsParameters;
			SChannelCredentials.cCreds = 1;
			SChannelCredentials.paCred = const_cast<PCCERT_CONTEXT*>(NativeServerCertificate);

			TimeStamp Lifetime{};
			SECURITY_STATUS Status = AcquireCredentialsHandleW(nullptr, const_cast<LPWSTR>(UNISP_NAME_W), SECPKG_CRED_INBOUND, nullptr, &SChannelCredentials, nullptr, nullptr,
				&_CredentialHandle, &Lifetime);
			if (SEC_E_OK != Status)
			{
				throw Elysium::Core::Template::Exceptions::Security::Authentication::AuthenticationException(Status);
			}

			_CredentialHandleValid = true;
		}
		
		inline void PerformServerHandshake(SecBuffer* RenegotiationBuffer)
		{
			// create schannel security context
			SecBuffer OutputBuffers[2]{};
			SecBufferDesc OutputBufferDescriptor{};
			OutputBufferDescriptor.ulVersion = SECBUFFER_VERSION;
			OutputBufferDescriptor.cBuffers = 2;
			OutputBufferDescriptor.pBuffers = OutputBuffers;

			SecBuffer InputBuffers[2]{};
			SecBufferDesc InputBuffersDescriptor{};
			InputBuffersDescriptor.ulVersion = SECBUFFER_VERSION;
			InputBuffersDescriptor.cBuffers = 2;
			InputBuffersDescriptor.pBuffers = InputBuffers;

			ULONG ContextAttributes = 0;
			TimeStamp Lifetime{};
			const ULONG RequiredContext = ASC_REQ_SEQUENCE_DETECT | ASC_REQ_REPLAY_DETECT | ASC_REQ_CONFIDENTIALITY | ASC_REQ_ALLOCATE_MEMORY | ASC_REQ_EXTENDED_ERROR | ASC_REQ_STREAM;

			SECURITY_STATUS Status{};

			bool ContextEstablished = false;
			while (true)
			{
				OutputBuffers[0].BufferType = SECBUFFER_TOKEN;
				OutputBuffers[0].cbBuffer = 0;
				OutputBuffers[0].pvBuffer = nullptr;

				OutputBuffers[1].BufferType = SECBUFFER_ALERT;
				OutputBuffers[1].cbBuffer = 0;
				OutputBuffers[1].pvBuffer = nullptr;

				InputBuffers[0].BufferType = SECBUFFER_EMPTY;
				InputBuffers[0].cbBuffer = 0;
				InputBuffers[0].pvBuffer = nullptr;

				InputBuffers[1].BufferType = SECBUFFER_EMPTY;
				InputBuffers[1].cbBuffer = 0;
				InputBuffers[1].pvBuffer = nullptr;

				if (RenegotiationBuffer != nullptr)
				{
					InputBuffers[0] = *RenegotiationBuffer;
				}
				else
				{
					InputBuffers[0].BufferType = SECBUFFER_TOKEN;
					InputBuffers[0].pvBuffer = &_InBuffer[0];
					InputBuffers[0].cbBuffer = _InBuffer.GetLength();
				}

				Status = AcceptSecurityContext(&_CredentialHandle, !ContextEstablished && RenegotiationBuffer == nullptr ? nullptr : &_ContextHandle, &InputBuffersDescriptor, RequiredContext, 0,
					&_ContextHandle, &OutputBufferDescriptor, &ContextAttributes, &Lifetime);
				ContextEstablished = 0 != _ContextHandle.dwUpper || 0 != _ContextHandle.dwLower;

				switch (Status)
				{
				case SEC_E_OK:
				{
					ConsumeHandshakeInput(InputBuffers[1]);
					SendOutputToken(OutputBufferDescriptor);
				}
					return;
				case SEC_I_CONTINUE_NEEDED:
				{
					ConsumeHandshakeInput(InputBuffers[1]);
					SendOutputToken(OutputBufferDescriptor);

					if (!ReadHandshakeData())
					{
						throw Elysium::Core::Template::Exceptions::Security::Authentication::AuthenticationException(SEC_E_INTERNAL_ERROR);
					}
				}
					break;
				case SEC_E_INCOMPLETE_MESSAGE:
				{
					if (!ReadHandshakeData())
					{
						throw Elysium::Core::Template::Exceptions::Security::Authentication::AuthenticationException(SEC_E_INTERNAL_ERROR);
					}
				}
					break;
				case SEC_I_COMPLETE_NEEDED:
				{
					ConsumeHandshakeInput(InputBuffers[1]);

					Status = CompleteAuthToken(&_ContextHandle, &OutputBufferDescriptor);

					if (SEC_E_OK != Status)
					{
						throw Elysium::Core::Template::Exceptions::Security::Authentication::AuthenticationException(Status);
					}

					SendOutputToken(OutputBufferDescriptor);
				}
					break;
				case SEC_I_COMPLETE_AND_CONTINUE:
				{
					ConsumeHandshakeInput(InputBuffers[1]);

					Status = CompleteAuthToken(&_ContextHandle, &OutputBufferDescriptor);
					if (SEC_E_OK != Status)
					{
						throw Elysium::Core::Template::Exceptions::Security::Authentication::AuthenticationException(Status);
					}

					SendOutputToken(OutputBufferDescriptor);
					if (!ReadHandshakeData())
					{
						throw Elysium::Core::Template::Exceptions::Security::Authentication::AuthenticationException(SEC_E_INTERNAL_ERROR);
					}
				}
					break;
				default:
					throw Elysium::Core::Template::Exceptions::Security::Authentication::AuthenticationException(Status);
				}
			}
		}
	private:
		inline void SendOutputToken(SecBufferDesc& OutputBufferDescriptor)
		{
			for (unsigned long i = 0; i < OutputBufferDescriptor.cBuffers; ++i)
			{
				SecBuffer& Buffer = OutputBufferDescriptor.pBuffers[i];
				if (nullptr != Buffer.pvBuffer && 0 != Buffer.cbBuffer)
				{
					switch (Buffer.BufferType)
					{
					case SECBUFFER_TOKEN:
					case SECBUFFER_ALERT:
						_InnerSink.Write(reinterpret_cast<Elysium::Core::Template::System::byte*>(Buffer.pvBuffer), Buffer.cbBuffer);
						_InnerSink.Flush();
						break;
					default:
						break;
					}

					FreeContextBuffer(Buffer.pvBuffer);
				}

				Buffer.pvBuffer = nullptr;
				Buffer.cbBuffer = 0;
			}
		}

		inline const bool ReadHandshakeData()
		{
			Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> View;
			const Elysium::Core::Template::IO::ReadResult Result = _InnerSource.ReadBlock(View);
			if (Elysium::Core::Template::IO::ReadResult::HasData != Result)
			{	// @ToDo: this is not correct with non-blocking sockets!
				return false;
			}

			const Elysium::Core::Template::System::size BytesAvailable = View.GetLength();
			const Elysium::Core::Template::System::size OldLength = _InBuffer.GetLength();
			_InBuffer.Resize(OldLength + BytesAvailable);
			Elysium::Core::Template::Memory::MemCpy(&_InBuffer[OldLength], View.GetData(), BytesAvailable);

			_InnerSource.AdvanceReadingBlock(BytesAvailable);

			return true;
		}

		inline void ConsumeHandshakeInput(const SecBuffer& ExtraBuffer)
		{
			if (SECBUFFER_EXTRA != ExtraBuffer.BufferType)
			{
				_InBuffer.Clear();
				return;
			}

			const Elysium::Core::Template::System::size ExtraBytes = ExtraBuffer.cbBuffer;
			if (0 == ExtraBytes)
			{
				_InBuffer.Clear();
				return;
			}

			if (ExtraBytes > _InBuffer.GetLength())
			{
				throw Elysium::Core::Template::Exceptions::Security::Authentication::AuthenticationException(SEC_E_INTERNAL_ERROR);
			}

			const Elysium::Core::Template::System::size ExtraOffset = _InBuffer.GetLength() - ExtraBytes;
			Elysium::Core::Template::Memory::MemMove(&_InBuffer[0], &_InBuffer[ExtraOffset], ExtraBytes);
			_InBuffer.Resize(ExtraBytes);
		}

		inline void PreserveExtraInput(const SecBuffer* ExtraBuffer)
		{
			if (nullptr == ExtraBuffer)
			{
				_InBuffer.Clear();
				return;
			}

			const Elysium::Core::Template::System::size ExtraBytes = ExtraBuffer->cbBuffer;
			if (0 == ExtraBytes)
			{
				_InBuffer.Clear();
				return;
			}

			if (ExtraBytes > _InBuffer.GetLength())
			{
				throw Elysium::Core::Template::Exceptions::Security::Authentication::AuthenticationException(SEC_E_INTERNAL_ERROR);
			}

			const Elysium::Core::Template::System::size ExtraOffset = _InBuffer.GetLength() - ExtraBytes;
			Elysium::Core::Template::Memory::MemMove(&_InBuffer[0], &_InBuffer[ExtraOffset], ExtraBytes);

			_InBuffer.Resize(ExtraBytes);
		}
	private:
		InnerSink& _InnerSink;
		InnerSource& _InnerSource;

		CredHandle _CredentialHandle;
		bool _CredentialHandleValid;

		CtxtHandle _ContextHandle;
		SecPkgContext_StreamSizes _StreamSizes;

		Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> _InBuffer;
		Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> _OutBuffer;

		Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> _UncompressedOutBuffer;
	};
#endif
}
#endif