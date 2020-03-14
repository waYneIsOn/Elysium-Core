#include "SslStream.hpp"

#ifndef __SCHANNEL_H__
#include <schannel.h>
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_NETWORKSTREAM
#include "NetworkStream.hpp"
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
	SECURITY_STATUS scRet = _SecuritySupportProviderInterface->InitializeSecurityContext(&_hClientCreds, nullptr, (SECURITY_PSTR)L"httpbin.org", dwSSPIFlags, 0, SECURITY_NATIVE_DREP, nullptr, 0,
		&_hContext, &OutBuffer, &dwSSPIOutFlags, &tsExpiry);
	if (scRet != SEC_I_CONTINUE_NEEDED)
	{	// ToDo: throw specific exception
		throw Exception();
	}

	// Send response to server if there is one.
	if (OutBuffers[0].cbBuffer != 0 && OutBuffers[0].pvBuffer != NULL)
	{
		/*
		Sockets::NetworkStream* testNetworkStream = static_cast<Sockets::NetworkStream*>(&_InnerStream);
		const Sockets::Socket& testSocket = testNetworkStream->GetSocket();
		/*
		unsigned long cbData = send(Socket, (char*)OutBuffers[0].pvBuffer, OutBuffers[0].cbBuffer, 0);
		if (cbData == SOCKET_ERROR || cbData == 0)
		{
			printf("**** Error %d sending data to server (1)\n", WSAGetLastError());
			_SecuritySupportProviderInterface->FreeContextBuffer(OutBuffers[0].pvBuffer);
			_SecuritySupportProviderInterface->DeleteSecurityContext(&_hContext);

			throw Exception();
			//return SEC_E_INTERNAL_ERROR;
		}
		printf("%d bytes of handshake data sent\n", cbData);
		_SecuritySupportProviderInterface->FreeContextBuffer(OutBuffers[0].pvBuffer); // Free output buffer.
		OutBuffers[0].pvBuffer = NULL;
		*/
	}

	// ToDo: ClientHandshakeLoop

	// ...
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
