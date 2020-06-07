#include "TlsStream.hpp"

#ifndef ELYSIUM_CORE_BITCONVERTER
#include "../Elysium.Core/BitConverter.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SECURITY_TLSCONTENTTYPE
#include "TlsContentType.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SECURITY_TLSHANDSHAKEMESSAGETYPE
#include "TlsHandshakeMessageType.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SECURITY_TLSALERTLEVEL
#include "TlsAlertLevel.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SECURITY_TLSALERTDESCRIPTION
#include "TlsAlertDescription.hpp"
#endif

Elysium::Core::Net::Security::TlsStream::TlsStream(IO::Stream & InnerStream, const bool LeaveInnerStreamOpen, const TlsClientAuthenticationOptions& AuthenticationOptions)
	: AuthenticatedStream(InnerStream, LeaveInnerStreamOpen),
	_AuthenticationOptions(AuthenticationOptions)
{ }
Elysium::Core::Net::Security::TlsStream::~TlsStream()
{ }

bool Elysium::Core::Net::Security::TlsStream::GetCanRead() const
{
	return _InnerStream.GetCanRead();
}
bool Elysium::Core::Net::Security::TlsStream::GetCanSeek() const
{
	return _InnerStream.GetCanSeek();
}
bool Elysium::Core::Net::Security::TlsStream::GetCanTimeout() const
{
	return _InnerStream.GetCanTimeout();
}
bool Elysium::Core::Net::Security::TlsStream::GetCanWrite() const
{
	return _InnerStream.GetCanWrite();
}

const size_t Elysium::Core::Net::Security::TlsStream::GetLength()
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

void Elysium::Core::Net::Security::TlsStream::SetLength(size_t Value)
{
	_InnerStream.SetLength(Value);
}
void Elysium::Core::Net::Security::TlsStream::SetPosition(int64_t Position)
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
void Elysium::Core::Net::Security::TlsStream::Seek(const int64_t Offset, const IO::SeekOrigin Origin)
{
	_InnerStream.Seek(Offset, Origin);
}
size_t Elysium::Core::Net::Security::TlsStream::Read(byte * Buffer, const size_t Count)
{
	return _InnerStream.Read(Buffer, Count);
}
Elysium::Core::int32_t Elysium::Core::Net::Security::TlsStream::ReadByte()
{
	return _InnerStream.ReadByte();
}
void Elysium::Core::Net::Security::TlsStream::Write(const byte * Buffer, const size_t Count)
{
	_InnerStream.Write(Buffer, Count);
}

void Elysium::Core::Net::Security::TlsStream::AuthenticateAsClient(const String & TargetHost, const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection * ClientCertificates, const Elysium::Core::Security::Authentication::TlsProtocols EnabledTlsProtocols, const bool CheckCertficateRevocation)
{
	WriteClientHello(EnabledTlsProtocols);
	ReadServerHello();
	ReadServerCertificates();
	ReadServerKeyExchange();
	ReadServerHelloDone();
}
void Elysium::Core::Net::Security::TlsStream::AuthenticateAsServer(const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection & ClientCertificates, const bool ClientCertificateRequired, const Elysium::Core::Security::Authentication::TlsProtocols EnabledTlsProtocols, const bool CheckCertficateRevocation)
{
}


void Elysium::Core::Net::Security::TlsStream::WriteClientHello(const Elysium::Core::Security::Authentication::TlsProtocols EnabledTlsProtocols)
{
	// pre-calculate message size
	const Collections::Template::Array<TlsCipherSuite>& CipherSuites = _AuthenticationOptions.GetAllowedCipherSuites();
	const size_t NumberOfCipherSuites = CipherSuites.GetLength();
	
	uint16_t HandshakeSize = 0;
	HandshakeSize += 2;	// client version
	HandshakeSize += 32;	// client random
	HandshakeSize += 1;	// session id length
	HandshakeSize += 32;	// session id
	HandshakeSize += 2;	// length of cipher suite data
	HandshakeSize += NumberOfCipherSuites * 2;	// cipher suite data
	HandshakeSize += 2;	// compression methods
	HandshakeSize += 2;	// length of extension data
	// ToDo: FOR EACH extension: MessageSize += x;

	// record layer
	Collections::Template::Array<byte> ProtocolVersion = BitConverter::GetBytes(static_cast<uint16_t>(Elysium::Core::Security::Authentication::TlsProtocols::Tls10));
	Collections::Template::Array<byte> UpcomingLength = BitConverter::GetBytes(static_cast<uint16_t>(HandshakeSize + 4));	// additional 1 byte handshake type, 3 bytes length of data to follow
	if (BitConverter::GetIsLittleEndian())
	{
		Collections::Template::Array<byte>::Reverse(ProtocolVersion);	// 0x01 0x03 -> 0x03 0x01
		Collections::Template::Array<byte>::Reverse(UpcomingLength);
	}

	_InnerStream.WriteByte(static_cast<byte>(TlsContentType::Handshake));
	_InnerStream.Write(&ProtocolVersion[0], ProtocolVersion.GetLength());
	_InnerStream.Write(&UpcomingLength[0], UpcomingLength.GetLength());

	// handshake layer
	Collections::Template::Array<byte> HandshakeLength = BitConverter::GetBytes(static_cast<uint32_t>(HandshakeSize));
	Collections::Template::Array<byte> ClientVersion = BitConverter::GetBytes(static_cast<uint16_t>(EnabledTlsProtocols));
	Collections::Template::Array<byte> ClientRandom = Collections::Template::Array<byte>(32);
	Collections::Template::Array<byte> SessionId = Collections::Template::Array<byte>(32);
	Collections::Template::Array<byte> CipherSuitesLength = BitConverter::GetBytes(static_cast<uint16_t>(NumberOfCipherSuites * 2));
	if (BitConverter::GetIsLittleEndian())
	{
		Collections::Template::Array<byte>::Reverse(HandshakeLength);
		Collections::Template::Array<byte>::Reverse(ClientVersion);
		Collections::Template::Array<byte>::Reverse(ClientRandom);
		Collections::Template::Array<byte>::Reverse(SessionId);
		Collections::Template::Array<byte>::Reverse(CipherSuitesLength);
	}

	_InnerStream.WriteByte(static_cast<byte>(TlsHandshakeMessageType::ClientHello));
	_InnerStream.Write(&HandshakeLength[1], HandshakeLength.GetLength() - 1);	// handshake message length
	_InnerStream.Write(&ClientVersion[0], ClientVersion.GetLength());	// client version
	_InnerStream.Write(&ClientRandom[0], ClientRandom.GetLength());	// client random
	_InnerStream.WriteByte(static_cast<byte>(0x20));	// session id length
	_InnerStream.Write(&SessionId[0], SessionId.GetLength());	// session id
	_InnerStream.Write(&CipherSuitesLength[0], CipherSuitesLength.GetLength());
	for (size_t i = 0; i < NumberOfCipherSuites; i++)
	{
		Collections::Template::Array<byte> CipherSuite = BitConverter::GetBytes(static_cast<uint16_t>(CipherSuites[i]));
		if (BitConverter::GetIsLittleEndian())
		{
			Collections::Template::Array<byte>::Reverse(CipherSuite);
		}
		_InnerStream.Write(&CipherSuite[0], CipherSuite.GetLength());
	}
	_InnerStream.WriteByte(static_cast<byte>(0x01));	// compression methods
	_InnerStream.WriteByte(static_cast<byte>(0x00));	// no compression

	// ToDo:
	_InnerStream.WriteByte(static_cast<byte>(0x00));	// extension length p1
	_InnerStream.WriteByte(static_cast<byte>(0x00));	// extension length p2

	_InnerStream.Flush();
}
void Elysium::Core::Net::Security::TlsStream::ReadServerHello()
{
	// read tls record header -> 1 byte content type, 2 bytes tls version, 2 bytes length
	Collections::Template::Array<byte> RecordBuffer = Collections::Template::Array<byte>(5);
	const size_t RecordBufferLength = RecordBuffer.GetLength();
	size_t TotalBytesRead = 0;
	do
	{
		size_t BytesRead = _InnerStream.Read(&RecordBuffer[TotalBytesRead], RecordBuffer.GetLength() - TotalBytesRead);
		TotalBytesRead += BytesRead;
	} while (TotalBytesRead < RecordBufferLength);

	const TlsContentType ContentType = static_cast<const TlsContentType>(RecordBuffer[0]);
	const Elysium::Core::Security::Authentication::TlsProtocols ProtocolVersion = static_cast<const Elysium::Core::Security::Authentication::TlsProtocols>(BitConverter::ToUint16(&RecordBuffer[1]));
	const uint16_t ContentLength = BitConverter::ToUint16(&RecordBuffer[3]);

	// read tls content
	Collections::Template::Array<byte> ContentBuffer = Collections::Template::Array<byte>(ContentLength);
	TotalBytesRead = 0;
	do
	{
		size_t BytesRead = _InnerStream.Read(&ContentBuffer[TotalBytesRead], ContentBuffer.GetLength() - TotalBytesRead);
		TotalBytesRead += BytesRead;
	} while (TotalBytesRead < ContentLength);

	if (ContentType == TlsContentType::Alert)
	{
		const TlsAlertLevel Level = static_cast<const TlsAlertLevel>(ContentBuffer[0]);
		const TlsAlertDescription Decription = static_cast<const TlsAlertDescription>(ContentBuffer[1]);

		// ToDo: throw specific AuthenticationException
		throw 1;
	}
	else if(ContentType == TlsContentType::Handshake)
	{
		const TlsHandshakeMessageType HandshakeMessageType = static_cast<TlsHandshakeMessageType>(ContentBuffer[0]);
		const uint32_t ResponseLength = BitConverter::ToUint24(&ContentBuffer[1]);
		const Elysium::Core::Security::Authentication::TlsProtocols ServerVersion = static_cast<const Elysium::Core::Security::Authentication::TlsProtocols>(BitConverter::ToUint16(&ContentBuffer[4]));
		// ToDo: 32 bytes: server random
		const uint8_t SessionIdLength = ContentBuffer[38];
		// ToDo: SessionIdLength bytes (should be 32): session id
		const TlsCipherSuite ServerSelectedCipherSuite = static_cast<const TlsCipherSuite>(BitConverter::ToUint16(&ContentBuffer[71]));
		const uint8_t ServerSelectedCompressionMethod = ContentBuffer[72];
		// ToDo: extensions
	}
	else
	{
		throw 1;
	}
}
void Elysium::Core::Net::Security::TlsStream::ReadServerCertificates()
{
	// read tls record header -> 1 byte content type, 2 bytes tls version, 2 bytes length
	Collections::Template::Array<byte> RecordBuffer = Collections::Template::Array<byte>(5);
	const size_t RecordBufferLength = RecordBuffer.GetLength();
	size_t TotalBytesRead = 0;
	do
	{
		size_t BytesRead = _InnerStream.Read(&RecordBuffer[TotalBytesRead], RecordBuffer.GetLength() - TotalBytesRead);
		TotalBytesRead += BytesRead;
	} while (TotalBytesRead < RecordBufferLength);

	const TlsContentType ContentType = static_cast<const TlsContentType>(RecordBuffer[0]);
	const Elysium::Core::Security::Authentication::TlsProtocols ProtocolVersion = static_cast<const Elysium::Core::Security::Authentication::TlsProtocols>(BitConverter::ToUint16(&RecordBuffer[1]));
	const uint16_t ContentLength = BitConverter::ToUint16(&RecordBuffer[3]);

	// read tls content
	Collections::Template::Array<byte> ContentBuffer = Collections::Template::Array<byte>(ContentLength);
	TotalBytesRead = 0;
	do
	{
		size_t BytesRead = _InnerStream.Read(&ContentBuffer[TotalBytesRead], ContentBuffer.GetLength() - TotalBytesRead);
		TotalBytesRead += BytesRead;
	} while (TotalBytesRead < ContentLength);

	if (ContentType == TlsContentType::Alert)
	{
		const TlsAlertLevel Level = static_cast<const TlsAlertLevel>(ContentBuffer[0]);
		const TlsAlertDescription Decription = static_cast<const TlsAlertDescription>(ContentBuffer[1]);

		// ToDo: throw specific AuthenticationException
		throw 1;
	}
	else if (ContentType == TlsContentType::Handshake)
	{
		const TlsHandshakeMessageType HandshakeMessageType = static_cast<TlsHandshakeMessageType>(ContentBuffer[0]);
		const uint32_t ResponseLength = BitConverter::ToUint24(&ContentBuffer[1]);
		const uint32_t CertificatesLength = BitConverter::ToUint24(&ContentBuffer[4]);

		Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection ServerCertificates = Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection();
		size_t CertificateBytesRead = 0;
		do
		{
			const uint32_t CertificateLength = BitConverter::ToUint24(&ContentBuffer[CertificateBytesRead + 7]);
			ServerCertificates.Add(std::move(Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::LoadFromBlob(&ContentBuffer[CertificateBytesRead + 10], CertificateLength)));
			CertificateBytesRead += CertificateLength + 3;
		} while (CertificateBytesRead < CertificatesLength);



		/*
		const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate* ServerCertificate;
		const size_t NumberOfServerCertificates = ServerCertificates.GetCount();
		switch (NumberOfServerCertificates)
		{
		case 0:
			throw 1;
		case 1:
			ServerCertificate = &ServerCertificates[0];
			break;
		default:
			const Elysium::Core::Delegate<const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const void*, const Elysium::Core::String&, const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection&, const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const Elysium::Core::Collections::Template::Array<Elysium::Core::String>&>& SelectionCallback = _AuthenticationOptions.GetUserCertificateSelectionCallback();
			ServerCertificate = &SelectionCallback(nullptr, Elysium::Core::String(u""), ServerCertificates, ServerCertificates[0], Collections::Template::Array<Elysium::Core::String>(0));
			break;
		}
		const bool IsCertificateValidDespiteErrors = _AuthenticationOptions.GetUserCertificateValidationCallback()(nullptr, *ServerCertificate, Elysium::Core::Security::Cryptography::X509Certificates::X509Chain(), TlsPolicyErrors::None);
		*/



		if (CertificateBytesRead != CertificatesLength)
		{
			throw 1;
		}
	}
	else
	{
		throw 1;
	}
}
void Elysium::Core::Net::Security::TlsStream::ReadServerKeyExchange()
{
	// read tls record header -> 1 byte content type, 2 bytes tls version, 2 bytes length
	Collections::Template::Array<byte> RecordBuffer = Collections::Template::Array<byte>(5);
	const size_t RecordBufferLength = RecordBuffer.GetLength();
	size_t TotalBytesRead = 0;
	do
	{
		size_t BytesRead = _InnerStream.Read(&RecordBuffer[TotalBytesRead], RecordBuffer.GetLength() - TotalBytesRead);
		TotalBytesRead += BytesRead;
	} while (TotalBytesRead < RecordBufferLength);

	const TlsContentType ContentType = static_cast<const TlsContentType>(RecordBuffer[0]);
	const Elysium::Core::Security::Authentication::TlsProtocols ProtocolVersion = static_cast<const Elysium::Core::Security::Authentication::TlsProtocols>(BitConverter::ToUint16(&RecordBuffer[1]));
	const uint16_t ContentLength = BitConverter::ToUint16(&RecordBuffer[3]);

	// read tls content
	Collections::Template::Array<byte> ContentBuffer = Collections::Template::Array<byte>(ContentLength);
	TotalBytesRead = 0;
	do
	{
		size_t BytesRead = _InnerStream.Read(&ContentBuffer[TotalBytesRead], ContentBuffer.GetLength() - TotalBytesRead);
		TotalBytesRead += BytesRead;
	} while (TotalBytesRead < ContentLength);

	if (ContentType == TlsContentType::Alert)
	{
		const TlsAlertLevel Level = static_cast<const TlsAlertLevel>(ContentBuffer[0]);
		const TlsAlertDescription Decription = static_cast<const TlsAlertDescription>(ContentBuffer[1]);

		// ToDo: throw specific AuthenticationException
		throw 1;
	}
	else if (ContentType == TlsContentType::Handshake)
	{
		const TlsHandshakeMessageType HandshakeMessageType = static_cast<TlsHandshakeMessageType>(ContentBuffer[0]);
		const uint32_t ResponseLength = BitConverter::ToUint24(&ContentBuffer[1]);
		const uint32_t CurveInfo = BitConverter::ToUint24(&ContentBuffer[4]);
		const uint8_t LengthOfPublicKey = static_cast<uint8_t>(ContentBuffer[7]);
		// public key
		const uint16_t SignatureType = BitConverter::ToUint16(&ContentBuffer[7 + LengthOfPublicKey]);
		const uint16_t LengthOfSignature = BitConverter::ToUint16(&ContentBuffer[7 + LengthOfPublicKey]);
		// computed signature for ENCRYPT(client_hello_random + server_hello_random + curve_info + public_key)

		//throw 1;
	}
	else
	{
		throw 1;
	}
}
void Elysium::Core::Net::Security::TlsStream::ReadServerHelloDone()
{
	// read tls record header -> 1 byte content type, 2 bytes tls version, 2 bytes length
	Collections::Template::Array<byte> RecordBuffer = Collections::Template::Array<byte>(5);
	const size_t RecordBufferLength = RecordBuffer.GetLength();
	size_t TotalBytesRead = 0;
	do
	{
		size_t BytesRead = _InnerStream.Read(&RecordBuffer[TotalBytesRead], RecordBuffer.GetLength() - TotalBytesRead);
		TotalBytesRead += BytesRead;
	} while (TotalBytesRead < RecordBufferLength);

	const TlsContentType ContentType = static_cast<const TlsContentType>(RecordBuffer[0]);
	const Elysium::Core::Security::Authentication::TlsProtocols ProtocolVersion = static_cast<const Elysium::Core::Security::Authentication::TlsProtocols>(BitConverter::ToUint16(&RecordBuffer[1]));
	const uint16_t ContentLength = BitConverter::ToUint16(&RecordBuffer[3]);

	// read tls content
	Collections::Template::Array<byte> ContentBuffer = Collections::Template::Array<byte>(ContentLength);
	TotalBytesRead = 0;
	do
	{
		size_t BytesRead = _InnerStream.Read(&ContentBuffer[TotalBytesRead], ContentBuffer.GetLength() - TotalBytesRead);
		TotalBytesRead += BytesRead;
	} while (TotalBytesRead < ContentLength);

	if (ContentType == TlsContentType::Alert)
	{
		const TlsAlertLevel Level = static_cast<const TlsAlertLevel>(ContentBuffer[0]);
		const TlsAlertDescription Decription = static_cast<const TlsAlertDescription>(ContentBuffer[1]);

		// ToDo: throw specific AuthenticationException
		throw 1;
	}
	else if (ContentType == TlsContentType::Handshake)
	{
		const TlsHandshakeMessageType HandshakeMessageType = static_cast<TlsHandshakeMessageType>(ContentBuffer[0]);
		const uint32_t ResponseLength = BitConverter::ToUint24(&ContentBuffer[1]);

		throw 1;
	}
	else
	{
		throw 1;
	}
}

