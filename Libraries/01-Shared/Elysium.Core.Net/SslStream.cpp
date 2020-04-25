#include "SslStream.hpp"

#ifndef __SCHANNEL_H__
#include <schannel.h>
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_NETWORKSTREAM
#include "NetworkStream.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "../Elysium.Core/Exception.hpp"
#endif

Elysium::Core::Net::Security::SslStream::SslStream(IO::Stream & InnerStream, const bool LeaveInnerStreamOpen, const RemoteCertificateValidationCallback* UserCertificateValidationCallback, const LocalCertificateSelectionCallback* UserCertificateSelectionCallback, const EncryptionPolicy EncryptionPolicy)
	: AuthenticatedStream(InnerStream, LeaveInnerStreamOpen),
	_SecurityLibraryHandle(LoadSecurityLibrary())
{
	PrepareCredentials();
}
Elysium::Core::Net::Security::SslStream::~SslStream()
{
	UnloadSecurityLibrary();
}

bool Elysium::Core::Net::Security::SslStream::GetCanRead() const
{
	return _InnerStream.GetCanRead();
}
bool Elysium::Core::Net::Security::SslStream::GetCanSeek() const
{
	return _InnerStream.GetCanSeek();
}
bool Elysium::Core::Net::Security::SslStream::GetCanTimeout() const
{
	return _InnerStream.GetCanTimeout();
}
bool Elysium::Core::Net::Security::SslStream::GetCanWrite() const
{
	return _InnerStream.GetCanWrite();
}

const size_t Elysium::Core::Net::Security::SslStream::GetLength()
{
	return _InnerStream.GetLength();
}

const bool Elysium::Core::Net::Security::SslStream::GetIsAuthenticated() const
{
	return false;
}
const bool Elysium::Core::Net::Security::SslStream::GetIsEncrypted() const
{
	return false;
}
const bool Elysium::Core::Net::Security::SslStream::GetIsMutuallyAuthenticated() const
{
	return false;
}
const bool Elysium::Core::Net::Security::SslStream::GetIsServer() const
{
	return false;
}
const bool Elysium::Core::Net::Security::SslStream::GetIsSigned() const
{
	return false;
}

void Elysium::Core::Net::Security::SslStream::SetLength(size_t Value)
{
	_InnerStream.SetLength(Value);
}
void Elysium::Core::Net::Security::SslStream::SetPosition(int64_t Position)
{
	_InnerStream.SetPosition(Position);
}

void Elysium::Core::Net::Security::SslStream::Close()
{
	_InnerStream.Close();
}
void Elysium::Core::Net::Security::SslStream::Flush()
{
	_InnerStream.Flush();
}
void Elysium::Core::Net::Security::SslStream::Seek(const int64_t Offset, const IO::SeekOrigin Origin)
{
	_InnerStream.Seek(Offset, Origin);
}
size_t Elysium::Core::Net::Security::SslStream::Read(byte * Buffer, const size_t Count)
{
	return _InnerStream.Read(Buffer, Count);
}
Elysium::Core::int32_t Elysium::Core::Net::Security::SslStream::ReadByte()
{
	return _InnerStream.ReadByte();
}
void Elysium::Core::Net::Security::SslStream::Write(const byte * Buffer, const size_t Count)
{
	_InnerStream.Write(Buffer, Count);
}

void Elysium::Core::Net::Security::SslStream::AuthenticateAsClient(const String & TargetHost, const Core::Security::Cryptography::X509Certificates::X509CertificateCollection * ClientCertificates, const SslProtocols EnabledSslProtocols, const bool CheckCertficateRevocation)
{
	unsigned long dwSSPIFlags = ISC_REQ_SEQUENCE_DETECT | ISC_REQ_REPLAY_DETECT | ISC_REQ_CONFIDENTIALITY | ISC_RET_EXTENDED_ERROR | ISC_REQ_ALLOCATE_MEMORY | ISC_REQ_STREAM;
	
	//  Initiate a ClientHello message and generate a token.
	SecBuffer OutBuffers[1];
	OutBuffers[0].pvBuffer = NULL;
	OutBuffers[0].BufferType = SECBUFFER_TOKEN;
	OutBuffers[0].cbBuffer = 0;

	SecBufferDesc OutBuffer;
	OutBuffer.cBuffers = 1;
	OutBuffer.pBuffers = OutBuffers;
	OutBuffer.ulVersion = SECBUFFER_VERSION;

	unsigned long dwSSPIOutFlags;
	TimeStamp tsExpiry;
	SECURITY_STATUS scRet = _SecuritySupportProviderInterface->InitializeSecurityContext(&_hClientCreds, nullptr, (SECURITY_PSTR)L"httpbin.org", dwSSPIFlags, 0, 
		SECURITY_NATIVE_DREP, nullptr, 0, &_hContext, &OutBuffer, &dwSSPIOutFlags, &tsExpiry);
	if (scRet != SEC_I_CONTINUE_NEEDED)
	{	// ToDo: throw specific exception
		throw Exception();
	}

	// Send response to server if there is one.
	if (OutBuffers[0].cbBuffer != 0 && OutBuffers[0].pvBuffer != NULL)
	{
		Sockets::NetworkStream* UnderlyingNetworkStream = static_cast<Sockets::NetworkStream*>(&_InnerStream);
		const Sockets::Socket& Socket = UnderlyingNetworkStream->GetSocket();
		//unsigned long cbData = send(Socket._WinSocketHandle, (char*)OutBuffers[0].pvBuffer, OutBuffers[0].cbBuffer, 0);
		size_t BytesReceived = Socket.Send((byte*)&OutBuffers[0].pvBuffer, OutBuffers[0].cbBuffer);
		//if (BytesReceived == SOCKET_ERROR || BytesReceived == 0)
		if (BytesReceived == 0)
		{
			_SecuritySupportProviderInterface->FreeContextBuffer(OutBuffers[0].pvBuffer);
			_SecuritySupportProviderInterface->DeleteSecurityContext(&_hContext);

			// ToDo: throw specific exception
			throw Exception();	//return SEC_E_INTERNAL_ERROR;
		}
		_SecuritySupportProviderInterface->FreeContextBuffer(OutBuffers[0].pvBuffer); // Free output buffer.
		OutBuffers[0].pvBuffer = NULL;
	}

	ClientHandshakeLoop(true);

	// Authenticate server's credentials. Get server's certificate.
	PCCERT_CONTEXT pRemoteCertContext = NULL;
	SECURITY_STATUS Status = _SecuritySupportProviderInterface->QueryContextAttributes(&_hContext, SECPKG_ATTR_REMOTE_CERT_CONTEXT, (PVOID)&pRemoteCertContext);
	if (Status != SEC_E_OK)
	{	// ToDo: throw specific exception
		throw Exception();
	}



	int x = 45;
}
void Elysium::Core::Net::Security::SslStream::AuthenticateAsServer(const Core::Security::Cryptography::X509Certificates::X509CertificateCollection & ClientCertificates, const bool ClientCertificateRequired, const SslProtocols EnabledSslProtocols, const bool CheckCertficateRevocation)
{
}

HINSTANCE Elysium::Core::Net::Security::SslStream::LoadSecurityLibrary()
{
	HINSTANCE Library = LoadLibrary(L"Security.dll");	// ToDo: L"Secur32.dll" for VER_PLATFORM_WIN32_WINDOWS/VER_PLATFORM_WIN32_NT 
	if (Library == nullptr)
	{	// ToDo: throw specific exception (FileNotFoundException, FileLoadException, BadImageFormatException)
		throw Exception();
	}

#ifdef UNICODE
	INIT_SECURITY_INTERFACE SecurityInterface = (INIT_SECURITY_INTERFACE)GetProcAddress(Library, "InitSecurityInterfaceW");
#else
	INIT_SECURITY_INTERFACE SecurityInterface = (INIT_SECURITY_INTERFACE)GetProcAddress(Library, "InitSecurityInterfaceA");
#endif
	if (SecurityInterface == nullptr)
	{	
		UnloadSecurityLibrary();
		
		// ToDo: throw specific exception
		throw Exception();
	}

	_SecuritySupportProviderInterface = SecurityInterface();
	if (_SecuritySupportProviderInterface == nullptr)
	{
		UnloadSecurityLibrary();
		
		// ToDo: throw specific exception
		throw Exception();
	}

	return Library;
}

void Elysium::Core::Net::Security::SslStream::UnloadSecurityLibrary()
{
	if (_SecurityLibraryHandle != nullptr)
	{
		FreeLibrary(_SecurityLibraryHandle);
		_SecurityLibraryHandle = nullptr;
	}
}

void Elysium::Core::Net::Security::SslStream::PrepareCredentials()
{
	SCHANNEL_CRED SchannelCred;
	ZeroMemory(&SchannelCred, sizeof(SchannelCred));
	SchannelCred.dwVersion = SCHANNEL_CRED_VERSION;
	/*
	SchannelCred.cCreds = 1;
	SchannelCred.paCred = &pCertContext;
	*/
	SchannelCred.grbitEnabledProtocols = SP_PROT_TLS1;
	/*
	if (aiKeyExch)
	{
		rgbSupportedAlgs[cSupportedAlgs++] = aiKeyExch;
	}

	if (cSupportedAlgs)
	{
		SchannelCred.cSupportedAlgs = cSupportedAlgs;
		SchannelCred.palgSupportedAlgs = rgbSupportedAlgs;
	}
	*/
	SchannelCred.dwFlags |= SCH_CRED_NO_DEFAULT_CREDS;
	SchannelCred.dwFlags |= SCH_CRED_MANUAL_CRED_VALIDATION;

	TimeStamp LifeTime;
	SECURITY_STATUS Status = _SecuritySupportProviderInterface->AcquireCredentialsHandle(nullptr, (SECURITY_PSTR)UNISP_NAME, SECPKG_CRED_OUTBOUND, nullptr, &SchannelCred,
		nullptr, nullptr, &_hClientCreds, &LifeTime);
	if (Status != SEC_E_OK)
	{	// ToDo: throw specific exception
		throw Exception();
	}

	// free certificate context since schannel has made it's own copy
	//x509certificate.~();
}

void Elysium::Core::Net::Security::SslStream::ClientHandshakeLoop(const bool PerformInitialRead)
{
	Sockets::NetworkStream* UnderlyingNetworkStream = static_cast<Sockets::NetworkStream*>(&_InnerStream);
	const Sockets::Socket& Socket = UnderlyingNetworkStream->GetSocket();

	unsigned long dwSSPIFlags = ISC_REQ_SEQUENCE_DETECT | ISC_REQ_REPLAY_DETECT | ISC_REQ_CONFIDENTIALITY | ISC_RET_EXTENDED_ERROR | ISC_REQ_ALLOCATE_MEMORY | ISC_REQ_STREAM;

	// Allocate data buffer.
	Collections::Template::Array<byte> Buffer = Collections::Template::Array<byte>(65536);
	size_t TotalBytesReceived = 0;
	bool fDoRead = PerformInitialRead;

	// Loop until the handshake is finished or an error occurs.
	SECURITY_STATUS scRet = SEC_I_CONTINUE_NEEDED;
	SecBufferDesc OutBuffer, InBuffer;
	SecBuffer InBuffers[2], OutBuffers[1];
	unsigned long dwSSPIOutFlags;
	TimeStamp tsExpiry;
	while (scRet == SEC_I_CONTINUE_NEEDED || scRet == SEC_E_INCOMPLETE_MESSAGE || scRet == SEC_I_INCOMPLETE_CREDENTIALS)
	{
		if (0 == TotalBytesReceived || scRet == SEC_E_INCOMPLETE_MESSAGE) // Read data from server.
		{
			if (fDoRead)
			{
				//unsigned long BytesReceived = recv(Socket._WinSocketHandle, IoBuffer + TotalBytesReceived, IO_BUFFER_SIZE - TotalBytesReceived, 0);
				size_t BytesReceived = Socket.Receive(&Buffer[TotalBytesReceived], Buffer.GetLength() - TotalBytesReceived);
				if (BytesReceived == 0)
				{
					//printf("**** Server unexpectedly disconnected\n");
					scRet = SEC_E_INTERNAL_ERROR;
					break;
				}
				/*
				printf("%d bytes of handshake data received\n", cbData);
				if (fVerbose)
				{ 
					PrintHexDump(cbData, IoBuffer + cbIoBuffer); 
					printf("\n"); 
				}
				*/
				TotalBytesReceived += BytesReceived;
			}
			else
			{
				fDoRead = TRUE;
			}
		}

		// Set up the input buffers. Buffer 0 is used to pass in data
		// received from the server. Schannel will consume some or all
		// of this. Leftover data (if any) will be placed in buffer 1 and
		// given a buffer type of SECBUFFER_EXTRA.
		InBuffers[0].pvBuffer = &Buffer[0];
		InBuffers[0].cbBuffer = TotalBytesReceived;
		InBuffers[0].BufferType = SECBUFFER_TOKEN;

		InBuffers[1].pvBuffer = NULL;
		InBuffers[1].cbBuffer = 0;
		InBuffers[1].BufferType = SECBUFFER_EMPTY;

		InBuffer.cBuffers = 2;
		InBuffer.pBuffers = InBuffers;
		InBuffer.ulVersion = SECBUFFER_VERSION;

		// Set up the output buffers. These are initialized to NULL
		// so as to make it less likely we'll attempt to free random
		// garbage later.
		OutBuffers[0].pvBuffer = NULL;
		OutBuffers[0].BufferType = SECBUFFER_TOKEN;
		OutBuffers[0].cbBuffer = 0;

		OutBuffer.cBuffers = 1;
		OutBuffer.pBuffers = OutBuffers;
		OutBuffer.ulVersion = SECBUFFER_VERSION;

		// Call InitializeSecurityContext.
		scRet = _SecuritySupportProviderInterface->InitializeSecurityContext(&_hClientCreds, &_hContext, NULL, dwSSPIFlags, 0, SECURITY_NATIVE_DREP,
			&InBuffer, 0, NULL, &OutBuffer, &dwSSPIOutFlags, &tsExpiry);
		if (scRet == SEC_E_OK || scRet == SEC_I_CONTINUE_NEEDED || FAILED(scRet) && (dwSSPIOutFlags & ISC_RET_EXTENDED_ERROR))
		{
			if (OutBuffers[0].cbBuffer != 0 && OutBuffers[0].pvBuffer != NULL)
			{
				//int cbData = send(Socket, OutBuffers[0].pvBuffer, OutBuffers[0].cbBuffer, 0);
				//int cbData = send(Socket._WinSocketHandle, (char*)OutBuffers[0].pvBuffer, OutBuffers[0].cbBuffer, 0);
				size_t BytesSent = Socket.Send((byte*)&OutBuffers[0].pvBuffer, OutBuffers[0].cbBuffer);
				//if (cbData == SOCKET_ERROR || cbData == 0)
				if (BytesSent == 0)
				{
					//printf("**** Error %d sending data to server (2)\n", WSAGetLastError());
					//DisplayWinSockError(WSAGetLastError());
					_SecuritySupportProviderInterface->FreeContextBuffer(OutBuffers[0].pvBuffer);
					_SecuritySupportProviderInterface->DeleteSecurityContext(&_hContext);
					//return SEC_E_INTERNAL_ERROR;
					// ToDo: throw specific exception
					throw Exception();
				}
				/*
				printf("%d bytes of handshake data sent\n", cbData);
				if (fVerbose)
				{
					PrintHexDump(cbData, OutBuffers[0].pvBuffer); printf("\n");
				}
				*/
				// Free output buffer.
				_SecuritySupportProviderInterface->FreeContextBuffer(OutBuffers[0].pvBuffer);
				OutBuffers[0].pvBuffer = NULL;
			}
		}

		// If InitializeSecurityContext returned SEC_E_INCOMPLETE_MESSAGE, then we need to read more data from the server and try again.
		if (scRet == SEC_E_INCOMPLETE_MESSAGE)
		{
			continue;
		}

		// If InitializeSecurityContext returned SEC_E_OK, then the handshake completed successfully.
		if (scRet == SEC_E_OK)
		{
			// If the "extra" buffer contains data, this is encrypted application
			// protocol layer stuff. It needs to be saved. The application layer
			// will later decrypt it with DecryptMessage.
			//printf("Handshake was successful\n");

			if (InBuffers[1].BufferType == SECBUFFER_EXTRA)
			{
				_ExtraData.pvBuffer = LocalAlloc(LMEM_FIXED, InBuffers[1].cbBuffer);
				if (_ExtraData.pvBuffer == NULL)
				{	// ToDo: throw specific exception
					throw Exception();
					/*
					printf("**** Out of memory (2)\n");
					return SEC_E_INTERNAL_ERROR;
					*/
				}

				//MoveMemory(_ExtraData.pvBuffer, IoBuffer + (cbIoBuffer - InBuffers[1].cbBuffer), InBuffers[1].cbBuffer);
				MoveMemory(_ExtraData.pvBuffer, &Buffer[TotalBytesReceived - InBuffers[1].cbBuffer], InBuffers[1].cbBuffer);

				_ExtraData.cbBuffer = InBuffers[1].cbBuffer;
				_ExtraData.BufferType = SECBUFFER_TOKEN;

				//printf("%d bytes of app data was bundled with handshake data\n", pExtraData->cbBuffer);
			}
			else
			{
				_ExtraData.pvBuffer = NULL;
				_ExtraData.cbBuffer = 0;
				_ExtraData.BufferType = SECBUFFER_EMPTY;
			}
			break; // Bail out to quit
		}

		// Check for fatal error.
		if (FAILED(scRet))
		{
			//printf("**** Error 0x%x returned by InitializeSecurityContext (2)\n", scRet);
			// ToDo: throw specific exception
			throw Exception();
		}

		// If InitializeSecurityContext returned SEC_I_INCOMPLETE_CREDENTIALS, then the server just requested client authentication.
		if (scRet == SEC_I_INCOMPLETE_CREDENTIALS)
		{
			// Busted. The server has requested client authentication and
			// the credential we supplied didn't contain a client certificate.
			// This function will read the list of trusted certificate
			// authorities ("issuers") that was received from the server
			// and attempt to find a suitable client certificate that
			// was issued by one of these. If this function is successful,
			// then we will connect using the new certificate. Otherwise,
			// we will attempt to connect anonymously (using our current credentials).
			//GetNewClientCredentials(phCreds, phContext);
			throw Exception(u"not implemented");

			// Go around again.
			fDoRead = FALSE;
			scRet = SEC_I_CONTINUE_NEEDED;
			continue;
		}

		// Copy any leftover data from the "extra" buffer, and go around again.
		if (InBuffers[1].BufferType == SECBUFFER_EXTRA)
		{
			//MoveMemory(IoBuffer, IoBuffer + (cbIoBuffer - InBuffers[1].cbBuffer), InBuffers[1].cbBuffer);
			MoveMemory(&Buffer[0], &Buffer[TotalBytesReceived - InBuffers[1].cbBuffer], InBuffers[1].cbBuffer);
			TotalBytesReceived = InBuffers[1].cbBuffer;
		}
		else
		{
			TotalBytesReceived = 0;
		}
	}

	// Delete the security context in the case of a fatal error.
	if (FAILED(scRet))
	{
		_SecuritySupportProviderInterface->DeleteSecurityContext(&_hContext);
	}
	//LocalFree(IoBuffer);
}
