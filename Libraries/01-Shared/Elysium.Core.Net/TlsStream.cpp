#include "TlsStream.hpp"

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_AUTHENTICATION_AUTHENTICATIONEXCEPTION
#include "../Elysium.Core.Security/AuthenticationException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CHAIN
#include "../Elysium.Core.Security.Cryptography.X509Certificates/X509Chain.hpp"
#endif

#ifndef _NTDEF_
//#include <ntdef.h>
#endif

#ifndef __SCHANNEL_H__
//#define SCHANNEL_USE_BLACKLISTS
#include <schannel.h>
#endif

Elysium::Core::Net::Security::TlsStream::TlsStream(IO::Stream& InnerStream, const bool LeaveInnerStreamOpen, const TlsClientAuthenticationOptions& AuthenticationOptions)
	: Elysium::Core::Net::Security::AuthenticatedStream(InnerStream, LeaveInnerStreamOpen),
	_AuthenticationOptions(AuthenticationOptions),
	_ExtraBuffer(), _InBuffer(16384), _OutBuffer(16384), _TargetHost(), _TlsProtocols(Elysium::Core::Security::Authentication::TlsProtocols::Latest),
	_CredentialHandle(), _Context(), _Sizes()
{ }
Elysium::Core::Net::Security::TlsStream::~TlsStream()
{
	DeleteSecurityContext(&_Context);
	FreeCredentialHandle(&_CredentialHandle);
}

const bool Elysium::Core::Net::Security::TlsStream::GetCanRead() const
{
	return _InnerStream.GetCanRead();
}

const bool Elysium::Core::Net::Security::TlsStream::GetCanSeek() const
{
	return _InnerStream.GetCanSeek();
}

const bool Elysium::Core::Net::Security::TlsStream::GetCanTimeout() const
{
	return _InnerStream.GetCanTimeout();
}

const bool Elysium::Core::Net::Security::TlsStream::GetCanWrite() const
{
	return _InnerStream.GetCanWrite();
}

const size_t Elysium::Core::Net::Security::TlsStream::GetLength()  const
{
	return _InnerStream.GetLength();
}

const bool Elysium::Core::Net::Security::TlsStream::GetIsAuthenticated() const
{
	return false;
}
const bool Elysium::Core::Net::Security::TlsStream::GetIsEncrypted() const
{
	return false;
}
const bool Elysium::Core::Net::Security::TlsStream::GetIsMutuallyAuthenticated() const
{
	return false;
}
const bool Elysium::Core::Net::Security::TlsStream::GetIsServer() const
{
	return false;
}
const bool Elysium::Core::Net::Security::TlsStream::GetIsSigned() const
{
	return false;
}

void Elysium::Core::Net::Security::TlsStream::SetLength(const size_t Value)
{
	_InnerStream.SetLength(Value);
}

void Elysium::Core::Net::Security::TlsStream::SetPosition(const Elysium::Core::uint64_t Position)
{
	_InnerStream.SetPosition(Position);
}

void Elysium::Core::Net::Security::TlsStream::Close()
{
	_InnerStream.Close();
}

void Elysium::Core::Net::Security::TlsStream::Flush()
{
	_InnerStream.Flush();
}

const size_t Elysium::Core::Net::Security::TlsStream::Seek(const Elysium::Core::int64_t Offset, const IO::SeekOrigin Origin)
{
	return _InnerStream.Seek(Offset, Origin);
}

const size_t Elysium::Core::Net::Security::TlsStream::Read(Elysium::Core::byte* Buffer, const size_t Count)
{
	// prepare secure buffers (as far as possible)
	SecBuffer SecureBuffers[4];

	SecureBuffers[0].BufferType = SECBUFFER_DATA;
	SecureBuffers[0].pvBuffer = &_InBuffer[0];
	SecureBuffers[0].cbBuffer = 0;

	SecureBuffers[1].BufferType = SECBUFFER_EMPTY;
	SecureBuffers[1].pvBuffer = nullptr;
	SecureBuffers[1].cbBuffer = 0;

	SecureBuffers[2].BufferType = SECBUFFER_EMPTY;
	SecureBuffers[2].pvBuffer = nullptr;
	SecureBuffers[2].cbBuffer = 0;

	SecureBuffers[3].BufferType = SECBUFFER_EMPTY;
	SecureBuffers[3].pvBuffer = nullptr;
	SecureBuffers[3].cbBuffer = 0;

	// setup secure buffer descriptor
	SecBufferDesc SecureBuffersDescriptor;
	SecureBuffersDescriptor.ulVersion = SECBUFFER_VERSION;
	SecureBuffersDescriptor.cBuffers = 4;
	SecureBuffersDescriptor.pBuffers = SecureBuffers;

	// read until we can decrypt the message
	SECURITY_STATUS Result = SEC_E_INCOMPLETE_MESSAGE;
	while (Result != SEC_E_OK)
	{
		SecureBuffers[0].cbBuffer += _InnerStream.Read(&_InBuffer[0], _InBuffer.GetLength());
		Result = DecryptMessage(&_Context, &SecureBuffersDescriptor, 0, NULL);
		switch (Result)
		{
		case SEC_E_INCOMPLETE_MESSAGE:
			// ToDo: more data to read
			throw 1;
		case SEC_I_RENEGOTIATE:
			ClientHandshakeLoop(false);
			break;
		case SEC_E_OK:
			break;
		default:
			throw Elysium::Core::Security::Authentication::AuthenticationException();
		}
	}

	// find data- and extra-buffer
	SecBuffer* DataBuffer = nullptr;
	SecBuffer* ExtraBuffer = nullptr;
	for (Elysium::Core::uint8_t i = 1; i < 4; i++)
	{
		if (DataBuffer == nullptr && SecureBuffers[i].BufferType == SECBUFFER_DATA)
		{
			DataBuffer = &SecureBuffers[i];
		}
		if (ExtraBuffer == nullptr && SecureBuffers[i].BufferType == SECBUFFER_EXTRA)
		{
			ExtraBuffer = &SecureBuffers[i];
		}
	}

	// ...
	if (ExtraBuffer != nullptr)
	{
		// ToDo: copy memory to _ExtraBuffer and make use of it
		throw 1;
	}

	// validate DataBuffer and copy to user-buffer
	if (DataBuffer == nullptr)
	{	// ToDo: throw specific exception
		throw 1;
	}
	Elysium::Core::Collections::Template::Array<Elysium::Core::byte>::Copy((Elysium::Core::byte*)DataBuffer->pvBuffer, Buffer, DataBuffer->cbBuffer);

	// clear inbuffer after every method-call
	Elysium::Core::Collections::Template::Array<Elysium::Core::byte>::Clear(&_InBuffer[0], _InBuffer.GetLength());

	return DataBuffer->cbBuffer;
}

Elysium::Core::byte Elysium::Core::Net::Security::TlsStream::ReadByte()
{	// ToDo
	throw 1;
}

void Elysium::Core::Net::Security::TlsStream::Write(const Elysium::Core::byte* Buffer, const size_t Count)
{
	// prepare secure buffers (as far as possible)
	SecBuffer SecureBuffers[4];

	SecureBuffers[0].BufferType = SECBUFFER_STREAM_HEADER;
	SecureBuffers[0].pvBuffer = (void*)&_OutBuffer[0];
	SecureBuffers[0].cbBuffer = _Sizes.cbHeader;

	SecureBuffers[1].BufferType = SECBUFFER_DATA;

	SecureBuffers[2].BufferType = SECBUFFER_STREAM_TRAILER;
	SecureBuffers[2].cbBuffer = _Sizes.cbTrailer;
	
	SecureBuffers[3].BufferType = SECBUFFER_EMPTY;
	SecureBuffers[3].pvBuffer = nullptr;
	SecureBuffers[3].cbBuffer = 0;
	
	// setup secure buffer descriptor
	SecBufferDesc SecureBuffersDescriptor;
	SecureBuffersDescriptor.ulVersion = SECBUFFER_VERSION;
	SecureBuffersDescriptor.cBuffers = 4;
	SecureBuffersDescriptor.pBuffers = SecureBuffers;

	// loop until all data has been sent
	const size_t AvailableSize = _OutBuffer.GetLength() - _Sizes.cbHeader - _Sizes.cbTrailer;
	size_t TotalBytesSent = 0;
	size_t CurrentMessageSize = 0;
	while (TotalBytesSent < Count)
	{
		CurrentMessageSize = (Count - TotalBytesSent < _Sizes.cbMaximumMessage) ? Count - TotalBytesSent : _Sizes.cbMaximumMessage;
		CurrentMessageSize = CurrentMessageSize < AvailableSize ? CurrentMessageSize : AvailableSize;
		Elysium::Core::Collections::Template::Array<Elysium::Core::byte>::Copy(Buffer, &_OutBuffer[_Sizes.cbHeader], CurrentMessageSize);

		// variable buffer/length (actual data and trailer)
		SecureBuffers[1].pvBuffer = (void*)&_OutBuffer[_Sizes.cbHeader];
		SecureBuffers[1].cbBuffer = CurrentMessageSize;

		SecureBuffers[2].pvBuffer = (void*)&_OutBuffer[_Sizes.cbHeader + CurrentMessageSize];

		// encrypt message and send
		SECURITY_STATUS Result = EncryptMessage(&_Context, 0, &SecureBuffersDescriptor, 0);
		if (FAILED(Result))
		{
			throw Elysium::Core::Security::Authentication::AuthenticationException();
		}

		_InnerStream.Write((const Elysium::Core::byte*)SecureBuffers[0].pvBuffer, (size_t)SecureBuffers[0].cbBuffer + SecureBuffers[1].cbBuffer + 
			SecureBuffers[2].cbBuffer + SecureBuffers[3].cbBuffer);
		TotalBytesSent += CurrentMessageSize;
	}

	// clear outbuffer after every method-call
	Elysium::Core::Collections::Template::Array<Elysium::Core::byte>::Clear(&_OutBuffer[0], _OutBuffer.GetLength());
}

void Elysium::Core::Net::Security::TlsStream::AuthenticateAsClient(const Elysium::Core::String& TargetHost, const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection* ClientCertificates, const Elysium::Core::Security::Authentication::TlsProtocols EnabledTlsProtocols, const bool CheckCertficateRevocation)
{
	_TargetHost = TargetHost;
	_TlsProtocols = EnabledTlsProtocols;

	PerformClientHandshake();
	GetServersCertificate();
}

void Elysium::Core::Net::Security::TlsStream::AuthenticateAsServer(const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection& ClientCertificates, const bool ClientCertificateRequired, const Elysium::Core::Security::Authentication::TlsProtocols EnabledTlsProtocols, const bool CheckCertficateRevocation)
{

}

void Elysium::Core::Net::Security::TlsStream::PerformClientHandshake()
{
	// Setup SChannel Credentials
	SCHANNEL_CRED SChannelCredentials = SCHANNEL_CRED();
	//ZeroMemory(&SChannelCredentials, sizeof(SChannelCredentials));
	SChannelCredentials.dwVersion = SCHANNEL_CRED_VERSION;
	SChannelCredentials.dwFlags = SCH_CRED_NO_DEFAULT_CREDS | SCH_CRED_MANUAL_CRED_VALIDATION;
	switch (_TlsProtocols)
	{
	case Elysium::Core::Security::Authentication::TlsProtocols::Tls10:
		SChannelCredentials.grbitEnabledProtocols = SP_PROT_TLS1_0;
		break;
	case Elysium::Core::Security::Authentication::TlsProtocols::Tls11:
		SChannelCredentials.grbitEnabledProtocols = SP_PROT_TLS1_1;
		break;
	case Elysium::Core::Security::Authentication::TlsProtocols::Tls12:
		SChannelCredentials.grbitEnabledProtocols = SP_PROT_TLS1_2;
		break;
	case Elysium::Core::Security::Authentication::TlsProtocols::Tls13:
		SChannelCredentials.grbitEnabledProtocols = SP_PROT_TLS1_3;
		break;
	default:
		throw Elysium::Core::NotImplementedException(u8"Unhandled TlsProtocols.");
	}
	/*
	SCH_CREDENTIALS SChannelCredentials = SCH_CREDENTIALS();
	SChannelCredentials.dwVersion = SCH_CREDENTIALS_VERSION;
	//SChannelCredentials.dwCredFormat =
	//SChannelCredentials.cCreds = 
	SChannelCredentials.paCred = nullptr;
	//SChannelCredentials.hRootStore = 
	//SChannelCredentials.cMappers = 
	SChannelCredentials.aphMappers = nullptr;
	SChannelCredentials.dwSessionLifespan = 0;
	//SChannelCredentials.dwFlags = 
	//SChannelCredentials.cTlsParameters = 
	SChannelCredentials.pTlsParameters = nullptr;
	*/
	// Get Client Credentials handle
	SECURITY_STATUS Status;
	TimeStamp Lifetime;

	Status = AcquireCredentialsHandle(nullptr, (LPWSTR)UNISP_NAME_W, SECPKG_CRED_OUTBOUND, nullptr, &SChannelCredentials, nullptr, nullptr, 
		&_CredentialHandle, &Lifetime);
	if (Status != SEC_E_OK)
	{
		throw Elysium::Core::Security::Authentication::AuthenticationException();
	}

	// ...
	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> TargetHostUTF16LE =
		Elysium::Core::Text::Encoding::UTF16LE().GetBytes(&_TargetHost[0], _TargetHost.GetLength(), sizeof(char16_t));

	DWORD RequiredContext = ISC_REQ_SEQUENCE_DETECT | ISC_REQ_REPLAY_DETECT | ISC_REQ_CONFIDENTIALITY | ISC_RET_EXTENDED_ERROR | ISC_REQ_ALLOCATE_MEMORY |
		ISC_REQ_STREAM;

	SecBuffer SecureBuffer;
	SecureBuffer.BufferType = SECBUFFER_TOKEN;
	SecureBuffer.cbBuffer = _InBuffer.GetLength();
	SecureBuffer.pvBuffer = &_InBuffer[0];

	SecBufferDesc SecureBufferDescriptor;
	SecureBufferDescriptor.ulVersion = SECBUFFER_VERSION;
	SecureBufferDescriptor.cBuffers = 1;
	SecureBufferDescriptor.pBuffers = &SecureBuffer;

	ULONG ContextAttributes;

	Status = InitializeSecurityContext(&_CredentialHandle, nullptr, (wchar_t*)&TargetHostUTF16LE[0], RequiredContext, 0, SECURITY_NATIVE_DREP, nullptr,
		0, &_Context, &SecureBufferDescriptor, &ContextAttributes, &Lifetime);
	if (FAILED(Status))
	{
		throw Elysium::Core::Security::Authentication::AuthenticationException();
	}

	if (Status != SEC_I_CONTINUE_NEEDED)
	{
		throw Elysium::Core::Security::Authentication::AuthenticationException();
	}

	// send client hello
	if (SecureBuffer.cbBuffer != 0 && SecureBuffer.pvBuffer != nullptr)
	{
		_InnerStream.Write((const Elysium::Core::byte*)SecureBuffer.pvBuffer, SecureBuffer.cbBuffer);
		SecureBuffer.pvBuffer = nullptr;
	}

	ClientHandshakeLoop(true);
	GetStreamEncryptionProperties();
}

void Elysium::Core::Net::Security::TlsStream::ClientHandshakeLoop(const bool Read)
{
	bool ShouldRead = Read;

	DWORD dwSSPIFlags = ISC_REQ_SEQUENCE_DETECT | ISC_REQ_REPLAY_DETECT | ISC_REQ_CONFIDENTIALITY | ISC_RET_EXTENDED_ERROR | ISC_REQ_ALLOCATE_MEMORY | 
		ISC_REQ_STREAM;

	SecBuffer InBuffers[2];
	SecBufferDesc InBuffer;

	SecBuffer OutBuffers[1];
	SecBufferDesc OutBuffer;

	DWORD dwSSPIOutFlags;
	TimeStamp tsExpiry;

	// Loop until the handshake is finished or an error occurs.
	SECURITY_STATUS Status = SEC_I_CONTINUE_NEEDED;
	size_t TotalBytesRead = 0;
	while (Status == SEC_I_CONTINUE_NEEDED || Status == SEC_E_INCOMPLETE_MESSAGE || Status == SEC_I_INCOMPLETE_CREDENTIALS)
	{
		if (TotalBytesRead == 0 || Status == SEC_E_INCOMPLETE_MESSAGE)
		{
			if (ShouldRead)
			{
				const size_t BytesRead = _InnerStream.Read(&_InBuffer[TotalBytesRead], _InBuffer.GetLength() - TotalBytesRead);
				if (BytesRead == 0)
				{
					throw Elysium::Core::Security::Authentication::AuthenticationException();
				}
				TotalBytesRead += BytesRead;
			}
			else
			{
				ShouldRead = true;
			}
		}

		// Set up the input buffers. Buffer 0 is used to pass in data received from the server. Schannel will consume some or all of this. 
		// Leftover data (if any) will be placed in buffer 1 and given a buffer type of SECBUFFER_EXTRA.
		InBuffers[0].BufferType = SECBUFFER_TOKEN;
		InBuffers[0].pvBuffer = &_InBuffer[0];
		InBuffers[0].cbBuffer = TotalBytesRead;

		InBuffers[1].BufferType = SECBUFFER_EMPTY;
		InBuffers[1].pvBuffer = nullptr;
		InBuffers[1].cbBuffer = 0;

		InBuffer.ulVersion = SECBUFFER_VERSION;
		InBuffer.pBuffers = InBuffers;
		InBuffer.cBuffers = 2;

		// Set up the output buffers. These are initialized to NULL so as to make it less likely we'll attempt to free random garbage later.
		OutBuffers[0].BufferType = SECBUFFER_TOKEN;
		OutBuffers[0].pvBuffer = nullptr;
		OutBuffers[0].cbBuffer = 0;

		OutBuffer.ulVersion = SECBUFFER_VERSION;
		OutBuffer.pBuffers = OutBuffers;
		OutBuffer.cBuffers = 1;

		Status = InitializeSecurityContextW(&_CredentialHandle, &_Context, nullptr, dwSSPIFlags, 0, SECURITY_NATIVE_DREP, &InBuffer, 0, nullptr,
			&OutBuffer, &dwSSPIOutFlags, &tsExpiry);

		// If InitializeSecurityContext was successful (or if the error was one of the special extended ones), send the contends of the output
		// buffer to the server.
		if (Status == SEC_E_OK || Status == SEC_I_CONTINUE_NEEDED || FAILED(Status) && (dwSSPIOutFlags & ISC_RET_EXTENDED_ERROR))
		{
			if (OutBuffers[0].cbBuffer != 0 && OutBuffers[0].pvBuffer != NULL)
			{
				_InnerStream.Write((const Elysium::Core::byte*)OutBuffers[0].pvBuffer, OutBuffers[0].cbBuffer);
				OutBuffers[0].pvBuffer = nullptr;
			}
		}

		// If InitializeSecurityContext returned SEC_E_INCOMPLETE_MESSAGE, then we need to read more data from the server and try again.
		if (Status == SEC_E_INCOMPLETE_MESSAGE)
		{
			continue;
		}

		// If InitializeSecurityContext returned SEC_E_OK, then thehandshake completed successfully.
		if (Status == SEC_E_OK)
		{
			// If the "extra" buffer contains data, this is encrypted application protocol layer stuff. It needs to be saved.
			// The application layer will later decrypt it with DecryptMessage.
			if (InBuffers[1].BufferType == SECBUFFER_EXTRA)// && InBuffers[1].pvBuffer != nullptr)
			{
				_ExtraBuffer.AddRange((Elysium::Core::byte*)InBuffers[1].pvBuffer, InBuffers[1].cbBuffer);
				/*
				pExtraData->pvBuffer = LocalAlloc(LMEM_FIXED, InBuffers[1].cbBuffer);
				if (pExtraData->pvBuffer == NULL)
				{ 
					printf("**** Out of memory (2)\n");
					return SEC_E_INTERNAL_ERROR;
				}
				
				std::memmove(pExtraData->pvBuffer, IoBuffer + (cbIoBuffer - InBuffers[1].cbBuffer), InBuffers[1].cbBuffer);
				
				pExtraData->cbBuffer = InBuffers[1].cbBuffer;
				pExtraData->BufferType = SECBUFFER_TOKEN;

				printf("%d bytes of app data was bundled with handshake data\n", pExtraData->cbBuffer);
				*/
			}
			else
			{
				/*
				pExtraData->pvBuffer = NULL;
				pExtraData->cbBuffer = 0;
				pExtraData->BufferType = SECBUFFER_EMPTY;
				*/
			}
			break; // Bail out to quit
		}

		// Check for fatal error.
		if (FAILED(Status))
		{
			//printf("**** Error 0x%x returned by InitializeSecurityContext (2)\n", Status);
			throw Elysium::Core::Security::Authentication::AuthenticationException();
		}

		// If InitializeSecurityContext returned SEC_I_INCOMPLETE_CREDENTIALS, then the server just requested client authentication.
		if (Status == SEC_I_INCOMPLETE_CREDENTIALS)
		{
			// Busted. The server has requested client authentication and the credential we supplied didn't contain a client certificate.
			// This function will read the list of trusted certificate authorities ("issuers") that was received from the server and 
			// attempt to find a suitable client certificate that was issued by one of these. If this function is successful,
			// then we will connect using the new certificate. Otherwise, we will attempt to connect anonymously (using our current credentials).
			PerformClientHandshake();

			// Go around again.
			ShouldRead = false;
			Status = SEC_I_CONTINUE_NEEDED;
			continue;
		}

		// Copy any leftover data from the "extra" buffer, and go around again.
		if (InBuffers[1].BufferType == SECBUFFER_EXTRA)
		{
			std::memmove(&_InBuffer[0], &_InBuffer[0] + (TotalBytesRead - InBuffers[1].cbBuffer), InBuffers[1].cbBuffer);
			TotalBytesRead = InBuffers[1].cbBuffer;
		}
		else
		{
			TotalBytesRead = 0;
		}
	}
}

void Elysium::Core::Net::Security::TlsStream::GetServersCertificate()
{
	PCCERT_CONTEXT RemoteCertificateContext = nullptr;
	SECURITY_STATUS Status = QueryContextAttributes(&_Context, SECPKG_ATTR_REMOTE_CERT_CONTEXT, (PVOID)&RemoteCertificateContext);
	if (Status != SEC_E_OK)
	{
		throw Elysium::Core::Security::Authentication::AuthenticationException();
	}

	Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate Certificate = 
		Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate(RemoteCertificateContext);

	// validate certificate
	Elysium::Core::Security::Cryptography::X509Certificates::X509Chain Chain = Elysium::Core::Security::Cryptography::X509Certificates::X509Chain();
	Elysium::Core::Security::Cryptography::X509Certificates::X509ChainPolicy& ChainPolicy = Chain.GetChainPolicy();
	ChainPolicy.SetRevocationMode(Elysium::Core::Security::Cryptography::X509Certificates::X509RevocationMode::Online);
	ChainPolicy.SetRevocationFlag(Elysium::Core::Security::Cryptography::X509Certificates::X509RevocationFlag::ExcludeRoot);

	const bool Verified = Chain.Build(Certificate);
	if (!Verified)
	{
		// ToDo: TlsPolicyErrors
		if (!_AuthenticationOptions.GetUserCertificateValidationCallback()(this, Certificate, Chain, TlsPolicyErrors::None))
		{
			throw Elysium::Core::Security::Authentication::AuthenticationException();
		}
	}
}

void Elysium::Core::Net::Security::TlsStream::GetStreamEncryptionProperties()
{
	SECURITY_STATUS Result = QueryContextAttributes(&_Context, SECPKG_ATTR_STREAM_SIZES, &_Sizes);
	if (Result != SEC_E_OK)
	{
		throw Elysium::Core::Security::Authentication::AuthenticationException();
	}
	
	// these are just some checks to make sure the implementation works and can be removed once it does
	if (_Sizes.cBuffers != 4)
	{
		throw Elysium::Core::NotImplementedException(u8"Unhandled number of SecurityBuffers.");
	}
	if ((size_t)_Sizes.cbHeader + _Sizes.cbTrailer > _OutBuffer.GetLength())
	{
		throw Elysium::Core::NotImplementedException(u8"Unhandled header- and trailer-size.");
	}
}
