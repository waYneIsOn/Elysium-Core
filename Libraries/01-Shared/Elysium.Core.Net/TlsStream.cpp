#include "TlsStream.hpp"

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_IOEXCEPTION
#include "../Elysium.Core.IO/IOException.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_AUTHENTICATION_AUTHENTICATIONEXCEPTION
#include "../Elysium.Core.Security/AuthenticationException.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CHAIN
#include "../Elysium.Core.Security.Cryptography.X509Certificates/X509Chain.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CHAINPOLICY
#include "../Elysium.Core.Security.Cryptography.X509Certificates/X509ChainPolicy.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMCPY
#include "../Elysium.Core.Template/MemCpy.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMSET
#include "../Elysium.Core.Template/MemSet.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

Elysium::Core::Net::Security::TlsStream::TlsStream(IO::Stream& InnerStream, const bool LeaveInnerStreamOpen, const TlsClientAuthenticationOptions& AuthenticationOptions)
	: Elysium::Core::Net::Security::AuthenticatedStream(InnerStream, LeaveInnerStreamOpen),
	_AuthenticationOptions(AuthenticationOptions),
	_ExtraBuffer(), _InBuffer(16384), _OutBuffer(16384), _TargetHost(), _TlsProtocols(Elysium::Core::Template::Security::Authentication::TlsProtocols::Latest),
	_CredentialHandle(), _Context(), _Sizes()
{ }

Elysium::Core::Net::Security::TlsStream::~TlsStream()
{
	Close();
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

void Elysium::Core::Net::Security::TlsStream::Close()
{
	/*
	* 
	* THIS IS THE CLIENT SHUTDOWN MESSAGE
	* 
	// inform schannel about sending tls close notification
	DWORD Shutdown = SCHANNEL_SHUTDOWN;

	SecBuffer SecureBuffers[4];
	SecureBuffers[0].BufferType = SECBUFFER_TOKEN;
	SecureBuffers[0].pvBuffer = &Shutdown;
	SecureBuffers[0].cbBuffer = sizeof(DWORD);

	SecBufferDesc SecureBuffersDescriptor;
	SecureBuffersDescriptor.ulVersion = SECBUFFER_VERSION;
	SecureBuffersDescriptor.cBuffers = 1;
	SecureBuffersDescriptor.pBuffers = SecureBuffers;

	SECURITY_STATUS Status = ApplyControlToken(&_Context, &SecureBuffersDescriptor);
	if (SEC_E_OK != Status)
	{	// @ToDo: throw specific exception
		throw Elysium::Core::Security::Authentication::AuthenticationException();
	}

	// create tls close notification record
	SecureBuffers[0].BufferType = SECBUFFER_TOKEN;
	SecureBuffers[0].pvBuffer = &Shutdown;
	SecureBuffers[0].cbBuffer = sizeof(DWORD);

	ULONG ContextAttributes = 0;
	Status = InitializeSecurityContextW(&_CredentialHandle, &_Context, nullptr, 
		ISC_REQ_SEQUENCE_DETECT | ISC_REQ_STREAM | ISC_REQ_ALLOCATE_MEMORY, 0, SECURITY_NETWORK_DREP, nullptr, 0,
		&_Context, &SecureBuffersDescriptor, &ContextAttributes, nullptr);
	//if (FAILED(Status))
	if (SEC_E_OK != Status && SEC_I_CONTEXT_EXPIRED != Status)
	{	// @ToDo: throw specific exception
		throw Elysium::Core::Security::Authentication::AuthenticationException();
	}
	
	// send encoded close notification message
	if (SecureBuffers[0].cbBuffer && SecureBuffers[0].pvBuffer)
	{
		Write(static_cast<Elysium::Core::byte*>(SecureBuffers[0].pvBuffer), SecureBuffers[0].cbBuffer);
		FreeContextBuffer(SecureBuffers[0].pvBuffer);
		SecureBuffers[0].pvBuffer = nullptr;
	}

	// receive close notification response
	{
		Elysium::Core::Template::System::size BytesInBuffer = 0;

		SecureBuffers[0].BufferType = SECBUFFER_TOKEN;
		SecureBuffers[0].cbBuffer = BytesInBuffer;
		SecureBuffers[0].pvBuffer = &_InBuffer[0];

		SecureBuffers[1].BufferType = SECBUFFER_EMPTY;
		SecureBuffers[1].cbBuffer = 0;
		SecureBuffers[1].pvBuffer = nullptr;

		SecureBuffersDescriptor.ulVersion = SECBUFFER_VERSION;
		SecureBuffersDescriptor.cBuffers = 2;
		SecureBuffersDescriptor.pBuffers = SecureBuffers;

		Status = SEC_I_CONTINUE_NEEDED;
		while (Status != SEC_E_OK)
		{
			BytesInBuffer += _InnerStream.Read(&_InBuffer[BytesInBuffer], _InBuffer.GetLength() - BytesInBuffer);
			Status = DecryptMessage(&_Context, &SecureBuffersDescriptor, 0, nullptr);
			switch (Status)
			{
			case SEC_E_INCOMPLETE_MESSAGE:
				// reset values
				SecureBuffers[0].BufferType = SECBUFFER_DATA;
				SecureBuffers[0].cbBuffer = BytesInBuffer;	// crucial detail as DecryptMessage(...) manipulates this value!
				SecureBuffers[1].BufferType = SECBUFFER_EMPTY;
				continue;
			case SEC_E_BUFFER_TOO_SMALL:
				throw 1;
			case SEC_E_CRYPTO_SYSTEM_INVALID:
				throw 1;
			case SEC_E_INVALID_HANDLE:
				throw 1;
			case SEC_E_MESSAGE_ALTERED:
				throw 1;
			case SEC_E_OUT_OF_SEQUENCE:
				throw 1;
			case SEC_E_QOP_NOT_SUPPORTED:
				throw 1;
			case SEC_I_RENEGOTIATE:
				//ClientHandshakeLoop(false);
				//return Read(Buffer, Count);
				throw 1;
			case SEC_E_OK:
				break;
			case SEC_E_INVALID_TOKEN:
				// message cannot be decrypted - might be corrupted
				//throw Elysium::Core::IO::IOException();

				// server sent something unexcepted (alert or partial record?)
				// for a shutdown it should be safe to be done here
				Status = SEC_E_OK;

				// need to make sure to drain any remaining bytes from the server though
				while (true)
				{
					Elysium::Core::Template::System::size BytesRead = _InnerStream.Read(&_InBuffer[0], _InBuffer.GetLength());
					if (0 == BytesRead)
					{
						break;
					}
				}

				break;
			default:
				throw Elysium::Core::Security::Authentication::AuthenticationException();
			}
		}
	}
	*/
	//if (INVALID_HANDLE_VALUE != _Context)
	{
		DeleteSecurityContext(&_Context);
	}

	//if (INVALID_HANDLE_VALUE != _CredentialHandle)
	{
		FreeCredentialHandle(&_CredentialHandle);
	}

	Elysium::Core::Net::Security::AuthenticatedStream::Close();
	//_InnerStream.Close();
}

void Elysium::Core::Net::Security::TlsStream::Flush()
{
	_InnerStream.Flush();
}

const Elysium::Core::size Elysium::Core::Net::Security::TlsStream::Seek(const Elysium::Core::int64_t Offset, const IO::SeekOrigin Origin)
{
	return _InnerStream.Seek(Offset, Origin);
}

const Elysium::Core::size Elysium::Core::Net::Security::TlsStream::Read(Elysium::Core::byte* Buffer, const Elysium::Core::size Count)
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
	Elysium::Core::Template::System::size BytesInBuffer = 0;
	while (Result != SEC_E_OK)
	{
		BytesInBuffer += _InnerStream.Read(&_InBuffer[BytesInBuffer], _InBuffer.GetLength() - BytesInBuffer);
		Result = DecryptMessage(&_Context, &SecureBuffersDescriptor, 0, nullptr);
		switch (Result)
		{
		case SEC_E_INCOMPLETE_MESSAGE:
			// reset values
			SecureBuffers[0].BufferType = SECBUFFER_DATA;
			SecureBuffers[0].cbBuffer = BytesInBuffer;	// crucial detail as DecryptMessage(...) manipulates this value!
			SecureBuffers[1].BufferType = SECBUFFER_EMPTY;
			continue;
		case SEC_E_BUFFER_TOO_SMALL:
			throw 1;
		case SEC_E_CRYPTO_SYSTEM_INVALID:
			throw 1;
		case SEC_E_INVALID_HANDLE:
			throw 1;
		case SEC_E_MESSAGE_ALTERED:
			throw 1;
		case SEC_E_OUT_OF_SEQUENCE:
			throw 1;
		case SEC_E_QOP_NOT_SUPPORTED:
			throw 1;
		case SEC_I_RENEGOTIATE:
			/*
			ClientHandshakeLoop(false);
			return Read(Buffer, Count);
			*/
			throw 1;
		case SEC_E_OK:
			break;
		case SEC_E_INVALID_TOKEN:
			// message cannot be decrypted - might be corrupted
			throw Elysium::Core::IO::IOException();
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
	Elysium::Core::Template::Memory::MemCpy(Buffer, (Elysium::Core::byte*)DataBuffer->pvBuffer, DataBuffer->cbBuffer);

	// clear inbuffer after every method-call
	Elysium::Core::Template::Memory::MemSet(&_InBuffer[0], 0, _InBuffer.GetLength());

	return DataBuffer->cbBuffer;
}

Elysium::Core::byte Elysium::Core::Net::Security::TlsStream::ReadByte()
{	// ToDo
	throw 1;
}

void Elysium::Core::Net::Security::TlsStream::Write(const Elysium::Core::byte* Buffer, const Elysium::Core::size Count)
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
	const Elysium::Core::size AvailableSize = _OutBuffer.GetLength() - _Sizes.cbHeader - _Sizes.cbTrailer;
	Elysium::Core::size TotalBytesSent = 0;
	Elysium::Core::size CurrentMessageSize = 0;
	while (TotalBytesSent < Count)
	{
		CurrentMessageSize = (Count - TotalBytesSent < _Sizes.cbMaximumMessage) ? Count - TotalBytesSent : _Sizes.cbMaximumMessage;
		CurrentMessageSize = CurrentMessageSize < AvailableSize ? CurrentMessageSize : AvailableSize;
		Elysium::Core::Template::Memory::MemCpy(&_OutBuffer[_Sizes.cbHeader], Buffer, CurrentMessageSize);

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

		_InnerStream.Write((const Elysium::Core::byte*)SecureBuffers[0].pvBuffer, (Elysium::Core::size)SecureBuffers[0].cbBuffer + SecureBuffers[1].cbBuffer + 
			SecureBuffers[2].cbBuffer + SecureBuffers[3].cbBuffer);
		TotalBytesSent += CurrentMessageSize;
	}

	// clear outbuffer after every method-call
	Elysium::Core::Template::Memory::MemSet(&_OutBuffer[0], 0, _OutBuffer.GetLength());
}

void Elysium::Core::Net::Security::TlsStream::AuthenticateAsClient(const Elysium::Core::Utf8String& TargetHost, const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate>* ClientCertificates, const Elysium::Core::Template::Security::Authentication::TlsProtocols EnabledTlsProtocols, const bool CheckCertficateRevocation)
{
	_TargetHost = TargetHost;
	_TlsProtocols = EnabledTlsProtocols;

	_CredentialHandle = CredHandle();
	_Context = SecHandle();
	_Sizes = SecPkgContext_StreamSizes();

	PerformClientHandshake();
	GetServersCertificate();
}

void Elysium::Core::Net::Security::TlsStream::AuthenticateAsServer(const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate& ServerCertificate, const bool ClientCertificateRequired, const Elysium::Core::Template::Security::Authentication::TlsProtocols EnabledTlsProtocols, const bool CheckCertficateRevocation)
{
	_TargetHost = u8"127.0.0.1";
	_TlsProtocols = EnabledTlsProtocols;
	
	SECURITY_STATUS Status = {};
	TimeStamp Lifetime = {};
	
	// ...
	SCHANNEL_CRED SChannelCredentials = SCHANNEL_CRED();
	SChannelCredentials.dwVersion = SCHANNEL_CRED_VERSION;
	SChannelCredentials.cCreds = 1;
	SChannelCredentials.paCred = const_cast<PCCERT_CONTEXT*>(&ServerCertificate._CertificateContext);
	//SChannelCredentials.dwFlags = SCH_USE_STRONG_CRYPTO | SCH_CRED_NO_DEFAULT_CREDS | SCH_CRED_MANUAL_CRED_VALIDATION | SCH_CRED_REVOCATION_CHECK_CHAIN;
	SChannelCredentials.dwFlags = SCH_USE_STRONG_CRYPTO | SCH_CRED_NO_DEFAULT_CREDS;
	if (!CheckCertficateRevocation)
	{
		SChannelCredentials.dwFlags &= ~(SCH_CRED_REVOCATION_CHECK_CHAIN);
	}

	if (ClientCertificateRequired)
	{
		SChannelCredentials.dwFlags |= SCH_CRED_AUTO_CRED_VALIDATION;
	}

	switch (_TlsProtocols)
	{
	case Elysium::Core::Template::Security::Authentication::TlsProtocols::Tls10:
		SChannelCredentials.grbitEnabledProtocols = SP_PROT_TLS1_0;
		break;
	case Elysium::Core::Template::Security::Authentication::TlsProtocols::Tls11:
		SChannelCredentials.grbitEnabledProtocols = SP_PROT_TLS1_1;
		break;
	case Elysium::Core::Template::Security::Authentication::TlsProtocols::Tls12:
		SChannelCredentials.grbitEnabledProtocols = SP_PROT_TLS1_2;
		break;
	case Elysium::Core::Template::Security::Authentication::TlsProtocols::Tls13:
		SChannelCredentials.grbitEnabledProtocols = SP_PROT_TLS1_3;
		break;
	default:
		throw Elysium::Core::NotImplementedException(u8"Unhandled TlsProtocols.");
	}

	Status = AcquireCredentialsHandleW(nullptr, const_cast<LPWSTR>(UNISP_NAME_W), SECPKG_CRED_INBOUND, nullptr, &SChannelCredentials,
		nullptr, nullptr, &_CredentialHandle, &Lifetime);
	switch (Status)
	{
	case SEC_E_ALGORITHM_MISMATCH:
		// This status is not documented by microsoft!
		// maybe (?): tls 1.3
		// maybe (?): client and server cannot communicate because they do not possess a common algorithm
		// @ToDo: just forcefully close the tcp-connection?
		throw Elysium::Core::Security::Authentication::AuthenticationException();
	case SEC_E_NO_CREDENTIALS:
		// schannel is not able to use the provided certificate
		// @ToDo
		throw 1;
	case SEC_E_INSUFFICIENT_MEMORY:
		// @ToDo (scenario not encountered)
		throw 1;
	case SEC_E_INTERNAL_ERROR:
		// @ToDo (scenario not encountered)
		throw 1;
	case SEC_E_NOT_OWNER:
		// @ToDo (scenario not encountered)
		throw 1;
	case SEC_E_SECPKG_NOT_FOUND:
		// @ToDo (scenario not encountered)
		throw 1;
	case SEC_E_OK:
		break;
	default:
		// @ToDo: unhandled Status
		throw 1;
	}

	// handshake
	Elysium::Core::size TotalBytesRead = 0;

	SecBuffer InBuffers[2];
	InBuffers[0].BufferType = SECBUFFER_TOKEN;
	InBuffers[0].pvBuffer = &_InBuffer[0];
	InBuffers[0].cbBuffer = TotalBytesRead;

	InBuffers[1].BufferType = SECBUFFER_EMPTY;
	InBuffers[1].pvBuffer = nullptr;
	InBuffers[1].cbBuffer = 0;

	SecBufferDesc InBufferDescriptor;
	InBufferDescriptor.ulVersion = SECBUFFER_VERSION;
	InBufferDescriptor.pBuffers = &InBuffers[0];
	InBufferDescriptor.cBuffers = 2;

	SecBuffer OutBuffers[1];
	OutBuffers[0].BufferType = SECBUFFER_TOKEN;
	OutBuffers[0].pvBuffer = nullptr;
	OutBuffers[0].cbBuffer = 0;
	//OutBuffers[0].pvBuffer = &_OutBuffer[0];
	//OutBuffers[0].cbBuffer = _OutBuffer.GetLength();

	SecBufferDesc OutBufferDescriptor;
	OutBufferDescriptor.ulVersion = SECBUFFER_VERSION;
	OutBufferDescriptor.cBuffers = 1;
	OutBufferDescriptor.pBuffers = &OutBuffers[0];

	DWORD ContextAttributes = 0;

	bool FirstCall = true;
	Status = SEC_I_CONTINUE_NEEDED;
	//while (Status == SEC_I_CONTINUE_NEEDED || Status == SEC_E_INCOMPLETE_MESSAGE)
	while (SEC_E_OK != Status)
	{
		Status = AcceptSecurityContext(&_CredentialHandle,
			FirstCall  ? nullptr : &_Context,
			&InBufferDescriptor,
			ASC_REQ_ALLOCATE_MEMORY | ASC_REQ_CONFIDENTIALITY | ASC_REQ_STREAM,
			SECURITY_NATIVE_DREP,
			&_Context,
			&OutBufferDescriptor,
			&ContextAttributes,
			&Lifetime
		);
		/*
		// send any output token
		if (nullptr != OutBuffers[0].pvBuffer && 0 < OutBuffers[0].cbBuffer)
		{
			_InnerStream.Write(
				static_cast<Elysium::Core::byte*>(OutBufferDescriptor.pBuffers[0].pvBuffer),
				OutBufferDescriptor.pBuffers[0].cbBuffer
			);

			FreeContextBuffer(OutBufferDescriptor.pBuffers[0].pvBuffer);
			OutBufferDescriptor.pBuffers[0].pvBuffer = nullptr;
			OutBufferDescriptor.pBuffers[0].cbBuffer = 0;

			bool sdfsdf = false;
		}

		// Handle leftover bytes in input
		if (InBuffers[1].BufferType == SECBUFFER_EXTRA && InBuffers[1].cbBuffer > 0)
		{
			memmove(&_InBuffer[0], &_InBuffer[TotalBytesRead - InBuffers[1].cbBuffer], InBuffers[1].cbBuffer);
			TotalBytesRead = InBuffers[1].cbBuffer;
		}
		else
		{
			TotalBytesRead = 0;
		}
		*/
		switch (Status)
		{
		case SEC_E_INCOMPLETE_MESSAGE:
			// more data required -> read more
		{
			//if (TotalBytesRead == 0 || Status == SEC_E_INCOMPLETE_MESSAGE)
			{
				const Elysium::Core::size BytesRead = _InnerStream.Read(&_InBuffer[TotalBytesRead], _InBuffer.GetLength() - TotalBytesRead);
				if (BytesRead == 0)
				{
					throw Elysium::Core::Security::Authentication::AuthenticationException();
				}
				TotalBytesRead += BytesRead;
			}

			InBuffers[0].BufferType = SECBUFFER_TOKEN;
			InBuffers[0].cbBuffer = TotalBytesRead;	// crucial detail as DecryptMessage(...) manipulates this value!
			InBuffers[1].BufferType = SECBUFFER_EMPTY;

			bool bla = false;
		}
			continue;
		case SEC_E_INSUFFICIENT_MEMORY:
			// send response to client
		{
			bool bla = false;
		}
		break;
		case SEC_E_INTERNAL_ERROR:
			// send response to client
		{
			bool bla = false;
		}
		break;
		case SEC_E_INVALID_HANDLE:
		{
			bool bla = false;
		}
		break;
		case SEC_I_CONTINUE_NEEDED:
			// send response to client
		{
			bool bla = false;
		}
		FirstCall = false;
			break;
		case SEC_E_BUFFER_TOO_SMALL:
		{
			bool bla = false;
		}
		break;
		case SEC_E_INVALID_TOKEN:
		{
			bool bla = false;
		}
		break;
		case SEC_E_NO_CREDENTIALS:
		{
			bool bla = false;
		}
		break;
		case SEC_E_OK:
			// handshake complete
		{
			bool bla = false;
		}
		FirstCall = false;
			break;
		default:
			// @ToDo
			//throw 1;
		{
			bool bla = false;
		}
			break;
		}
	}














	// ...
	Status = QueryContextAttributesW(&_Context, SECPKG_ATTR_STREAM_SIZES, &_Sizes);
	switch (Status)
	{
	case SEC_E_INCOMPLETE_MESSAGE:
		// @ToDo
		throw 1;
		break;
	case SEC_I_CONTINUE_NEEDED:
		// @ToDo
		throw 1;
		break;
	case SEC_E_OK:
		break;
	default:
		// @ToDo
		throw 1;
		break;
	}
	/*
	// Optional: handle leftover application data in _InBuffer here
	for (int i = 0; i < InBufferDescriptor.cBuffers; ++i)
	{
		if (InBuffers[i].BufferType == SECBUFFER_EXTRA && InBuffers[i].cbBuffer > 0)
		{
			// Remaining bytes are likely HTTP GET or TLS application data
		}
	}
	*/
}

void Elysium::Core::Net::Security::TlsStream::PerformClientHandshake()
{
	SECURITY_STATUS Status = {};
	TimeStamp Lifetime = {};

	// aquire credentials handle
	if (Elysium::Core::Template::Security::Authentication::TlsProtocols::Tls13 == (_TlsProtocols & Elysium::Core::Template::Security::Authentication::TlsProtocols::Tls13))
	{
		SCH_CREDENTIALS SChannelCredentials = SCH_CREDENTIALS();
		SChannelCredentials.dwVersion = SCHANNEL_CRED_VERSION;
		SChannelCredentials.dwFlags = SCH_CRED_NO_DEFAULT_CREDS | SCH_CRED_MANUAL_CRED_VALIDATION | SCH_USE_STRONG_CRYPTO;

		// client certificates
		SChannelCredentials.cCreds = 0;
		SChannelCredentials.paCred = nullptr;

		// ...
		Status = AcquireCredentialsHandleW(nullptr, (LPWSTR)UNISP_NAME_W, SECPKG_CRED_OUTBOUND, nullptr, &SChannelCredentials, nullptr, nullptr,
			&_CredentialHandle, &Lifetime);
		if (Status != SEC_E_OK)
		{
			throw Elysium::Core::Security::Authentication::AuthenticationException();
		}
	}
	else
	{
		SCHANNEL_CRED SChannelCredentials = SCHANNEL_CRED();
		//ZeroMemory(&SChannelCredentials, sizeof(SChannelCredentials));
		SChannelCredentials.dwVersion = SCHANNEL_CRED_VERSION;
		SChannelCredentials.dwFlags = SCH_CRED_NO_DEFAULT_CREDS | SCH_CRED_MANUAL_CRED_VALIDATION;
		switch (_TlsProtocols)
		{
		case Elysium::Core::Template::Security::Authentication::TlsProtocols::Tls10:
			SChannelCredentials.grbitEnabledProtocols = SP_PROT_TLS1_0;
			break;
		case Elysium::Core::Template::Security::Authentication::TlsProtocols::Tls11:
			SChannelCredentials.grbitEnabledProtocols = SP_PROT_TLS1_1;
			break;
		case Elysium::Core::Template::Security::Authentication::TlsProtocols::Tls12:
			SChannelCredentials.grbitEnabledProtocols = SP_PROT_TLS1_2;
			break;
		case Elysium::Core::Template::Security::Authentication::TlsProtocols::Tls13:
			SChannelCredentials.grbitEnabledProtocols = SP_PROT_TLS1_3;
			break;
		default:
			throw Elysium::Core::NotImplementedException(u8"Unhandled TlsProtocols.");
		}

		// ...
		Status = AcquireCredentialsHandleW(nullptr, (LPWSTR)UNISP_NAME_W, SECPKG_CRED_OUTBOUND, nullptr, &SChannelCredentials, nullptr, nullptr,
			&_CredentialHandle, &Lifetime);
		if (Status != SEC_E_OK)
		{
			throw Elysium::Core::Security::Authentication::AuthenticationException();
		}
	}

	// ...
	Elysium::Core::Container::VectorOfByte TargetHostUTF16LE =
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

	Status = InitializeSecurityContextW(&_CredentialHandle, nullptr, (wchar_t*)&TargetHostUTF16LE[0], RequiredContext, 0, SECURITY_NATIVE_DREP, nullptr,
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
	Elysium::Core::size TotalBytesRead = 0;
	while (Status == SEC_I_CONTINUE_NEEDED || Status == SEC_E_INCOMPLETE_MESSAGE || Status == SEC_I_INCOMPLETE_CREDENTIALS)
	{
		if (TotalBytesRead == 0 || Status == SEC_E_INCOMPLETE_MESSAGE)
		{
			if (ShouldRead)
			{
				const Elysium::Core::size BytesRead = _InnerStream.Read(&_InBuffer[TotalBytesRead], _InBuffer.GetLength() - TotalBytesRead);
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
				_ExtraBuffer.PushBackRange((Elysium::Core::byte*)InBuffers[1].pvBuffer, InBuffers[1].cbBuffer);
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
			memmove(&_InBuffer[0], &_InBuffer[0] + (TotalBytesRead - InBuffers[1].cbBuffer), InBuffers[1].cbBuffer);
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
	ChainPolicy.SetRevocationMode(Elysium::Core::Template::Security::Cryptography::X509Certificates::X509RevocationMode::Online);
	ChainPolicy.SetRevocationFlag(Elysium::Core::Template::Security::Cryptography::X509Certificates::X509RevocationFlag::ExcludeRoot);

	const bool Verified = Chain.Build(Certificate);
	if (!Verified)
	{
		// ToDo: TlsPolicyErrors
		if (!_AuthenticationOptions.GetUserCertificateValidationCallback()(this, Certificate, Chain, Elysium::Core::Template::Net::Security::TlsPolicyErrors::None))
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
	if ((Elysium::Core::size)_Sizes.cbHeader + _Sizes.cbTrailer > _OutBuffer.GetLength())
	{
		throw Elysium::Core::NotImplementedException(u8"Unhandled header- and trailer-size.");
	}
}
