#include "TlsStream.hpp"

#ifndef ELYSIUM_CORE_BITCONVERTER
#include "../Elysium.Core/BitConverter.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SECURITY_TLSCONTENTTYPE
#include "TlsContentType.hpp"
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

void Elysium::Core::Net::Security::TlsStream::AuthenticateAsClient(const String & TargetHost, const Core::Security::Cryptography::X509Certificates::X509CertificateCollection * ClientCertificates, const Elysium::Core::Security::Authentication::TlsProtocols EnabledTlsProtocols, const bool CheckCertficateRevocation)
{
	WriteClientHello(EnabledTlsProtocols);
	ReadServerHello();
}
void Elysium::Core::Net::Security::TlsStream::AuthenticateAsServer(const Core::Security::Cryptography::X509Certificates::X509CertificateCollection & ClientCertificates, const bool ClientCertificateRequired, const Elysium::Core::Security::Authentication::TlsProtocols EnabledTlsProtocols, const bool CheckCertficateRevocation)
{
}


void Elysium::Core::Net::Security::TlsStream::WriteClientHello(const Elysium::Core::Security::Authentication::TlsProtocols EnabledTlsProtocols)
{
	// pre-calculate array size
	const Collections::Template::Array<TlsCipherSuite>& CipherSuites = _AuthenticationOptions.GetAllowedCipherSuites();
	const size_t NumberOfCipherSuites = CipherSuites.GetLength();
	
	uint16_t MessageSize = 0;
	//MessageSize += 1;	// record type
	//MessageSize += 2;	// tls protocol version
	//MessageSize += 2;	// length of "wrapped" message

	//MessageSize += 1;	// "internal" type
	//MessageSize += 3;	// length of "internal" message
	MessageSize += 2;	// client version
	MessageSize += 32;	// client random
	MessageSize += 1;	// session id length
	MessageSize += 32;	// session id
	MessageSize += 2;	// length of cipher suite data
	MessageSize += NumberOfCipherSuites * 2;	// cipher suite data
	MessageSize += 2;	// compression methods
	MessageSize += 2;	// length of extension data
	// FOR EACH extension: MessageSize += x;	// xxxxxxxxxx

	// record layer
	Collections::Template::Array<byte> ProtocolVersion = BitConverter::GetBytes(static_cast<uint16_t>(Elysium::Core::Security::Authentication::TlsProtocols::Tls10));
	Collections::Template::Array<byte> HandshakeMessageLength = BitConverter::GetBytes(static_cast<uint16_t>(MessageSize + 4));	// 1 byte handshake type, 3 bytes length of data to follow
	if (BitConverter::GetIsLittleEndian())
	{
		Collections::Template::Array<byte>::Reverse(ProtocolVersion);	// 0x01 0x03 -> 0x03 0x01
		Collections::Template::Array<byte>::Reverse(HandshakeMessageLength);
	}

	_InnerStream.WriteByte(static_cast<byte>(TlsContentType::Handshake));
	_InnerStream.Write(&ProtocolVersion[0], ProtocolVersion.GetLength());
	_InnerStream.Write(&HandshakeMessageLength[0], HandshakeMessageLength.GetLength());

	// handshake layer
	Collections::Template::Array<byte> UpcomingLength = BitConverter::GetBytes(static_cast<uint32_t>(MessageSize));
	Collections::Template::Array<byte> ClientVersion = BitConverter::GetBytes(static_cast<uint16_t>(EnabledTlsProtocols));
	Collections::Template::Array<byte> ClientRandom = Collections::Template::Array<byte>(32);
	Collections::Template::Array<byte> SessionId = Collections::Template::Array<byte>(32);
	Collections::Template::Array<byte> CipherSuitesLength = BitConverter::GetBytes(static_cast<uint16_t>(NumberOfCipherSuites * 2));
	if (BitConverter::GetIsLittleEndian())
	{
		Collections::Template::Array<byte>::Reverse(UpcomingLength);
		Collections::Template::Array<byte>::Reverse(ClientVersion);
		Collections::Template::Array<byte>::Reverse(ClientRandom);
		Collections::Template::Array<byte>::Reverse(SessionId);
		Collections::Template::Array<byte>::Reverse(CipherSuitesLength);
	}

	byte b1 = CipherSuitesLength[0];
	byte bb = CipherSuitesLength[1];

	_InnerStream.WriteByte(static_cast<byte>(0x01));	// type
	_InnerStream.Write(&UpcomingLength[1], UpcomingLength.GetLength() - 1);	// handshake message length
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
		throw 1;
	}
	else
	{
		throw 1;
	}
}

