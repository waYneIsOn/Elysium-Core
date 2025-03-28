#include "ExperimentalTlsStream.hpp"

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

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_RANDOMNUMBERGENERATOR
#include "../Elysium.Core.Security.Cryptography.Algorithms/RandomNumberGenerator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMCPY
#include "../Elysium.Core.Template/MemCpy.hpp"
#endif

Elysium::Core::Net::Security::ExperimentalTlsStream::ExperimentalTlsStream(IO::Stream & InnerStream, const bool LeaveInnerStreamOpen, const TlsClientAuthenticationOptions& AuthenticationOptions)
	: Elysium::Core::Net::Security::AuthenticatedStream(InnerStream, LeaveInnerStreamOpen),
	_AuthenticationOptions(AuthenticationOptions), _LocalRandom(32), _SessionId(32), _RemoteRandom(32), _ServerSelectedCipherSuite(),
	_ServerSelectedCompressionMethod()
{ }

Elysium::Core::Net::Security::ExperimentalTlsStream::~ExperimentalTlsStream()
{ }

const bool Elysium::Core::Net::Security::ExperimentalTlsStream::GetCanRead() const
{
	return _InnerStream.GetCanRead();
}

const bool Elysium::Core::Net::Security::ExperimentalTlsStream::GetCanSeek() const
{
	return _InnerStream.GetCanSeek();
}

const bool Elysium::Core::Net::Security::ExperimentalTlsStream::GetCanTimeout() const
{
	return _InnerStream.GetCanTimeout();
}

const bool Elysium::Core::Net::Security::ExperimentalTlsStream::GetCanWrite() const
{
	return _InnerStream.GetCanWrite();
}

const Elysium::Core::size Elysium::Core::Net::Security::ExperimentalTlsStream::GetLength()  const
{
	return _InnerStream.GetLength();
}

const bool Elysium::Core::Net::Security::ExperimentalTlsStream::GetIsAuthenticated() const
{
	return false;
}

const bool Elysium::Core::Net::Security::ExperimentalTlsStream::GetIsEncrypted() const
{
	return false;
}

const bool Elysium::Core::Net::Security::ExperimentalTlsStream::GetIsMutuallyAuthenticated() const
{
	return false;
}

const bool Elysium::Core::Net::Security::ExperimentalTlsStream::GetIsServer() const
{
	return false;
}

const bool Elysium::Core::Net::Security::ExperimentalTlsStream::GetIsSigned() const
{
	return false;
}

void Elysium::Core::Net::Security::ExperimentalTlsStream::SetLength(const Elysium::Core::size Value)
{
	_InnerStream.SetLength(Value);
}

void Elysium::Core::Net::Security::ExperimentalTlsStream::SetPosition(const Elysium::Core::uint64_t Position)
{
	_InnerStream.SetPosition(Position);
}

void Elysium::Core::Net::Security::ExperimentalTlsStream::Close()
{
	_InnerStream.Close();
}

void Elysium::Core::Net::Security::ExperimentalTlsStream::Flush()
{
	_InnerStream.Flush();
}

const Elysium::Core::size Elysium::Core::Net::Security::ExperimentalTlsStream::Seek(const Elysium::Core::int64_t Offset, const IO::SeekOrigin Origin)
{
	return _InnerStream.Seek(Offset, Origin);
}

const Elysium::Core::size Elysium::Core::Net::Security::ExperimentalTlsStream::Read(Elysium::Core::byte* Buffer, const Elysium::Core::size Count)
{
	return _InnerStream.Read(Buffer, Count);
}

Elysium::Core::byte Elysium::Core::Net::Security::ExperimentalTlsStream::ReadByte()
{
	return _InnerStream.ReadByte();
}

void Elysium::Core::Net::Security::ExperimentalTlsStream::Write(const Elysium::Core::byte* Buffer, const Elysium::Core::size Count)
{
	_InnerStream.Write(Buffer, Count);
}

void Elysium::Core::Net::Security::ExperimentalTlsStream::AuthenticateAsClient(const Elysium::Core::Utf8String & TargetHost, const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection * ClientCertificates, const Elysium::Core::Security::Authentication::TlsProtocols EnabledTlsProtocols, const bool CheckCertficateRevocation)
{
	WriteClientHello(EnabledTlsProtocols);
	ReadServerHello();
	ReadServerCertificates();
	ReadServerKeyExchange();
	ReadServerHelloDone();
}

void Elysium::Core::Net::Security::ExperimentalTlsStream::AuthenticateAsServer(const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection & ClientCertificates, const bool ClientCertificateRequired, const Elysium::Core::Security::Authentication::TlsProtocols EnabledTlsProtocols, const bool CheckCertficateRevocation)
{
}

void Elysium::Core::Net::Security::ExperimentalTlsStream::WriteClientHello(const Elysium::Core::Security::Authentication::TlsProtocols EnabledTlsProtocols)
{
	// pre-calculate message size
	const Elysium::Core::Template::Container::Vector<TlsCipherSuite>& CipherSuites = _AuthenticationOptions.GetAllowedCipherSuites();
	const Elysium::Core::size NumberOfCipherSuites = CipherSuites.GetLength();
	
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
	Elysium::Core::Container::VectorOfByte ProtocolVersion = BitConverter::GetBytes(static_cast<uint16_t>(Elysium::Core::Security::Authentication::TlsProtocols::Tls10));
	Elysium::Core::Container::VectorOfByte UpcomingLength = BitConverter::GetBytes(static_cast<uint16_t>(HandshakeSize + 4));	// additional 1 byte handshake type, 3 bytes length of data to follow
	if (BitConverter::GetIsLittleEndian())
	{
		/*
		* @ToDo
		Collections::Template::Array<byte>::Reverse(ProtocolVersion);	// 0x01 0x03 -> 0x03 0x01
		Collections::Template::Array<byte>::Reverse(UpcomingLength);
		*/
	}

	_InnerStream.WriteByte(static_cast<byte>(TlsContentType::Handshake));
	_InnerStream.Write(&ProtocolVersion[0], ProtocolVersion.GetLength());
	_InnerStream.Write(&UpcomingLength[0], UpcomingLength.GetLength());

	// handshake layer
	Elysium::Core::Security::Cryptography::RandomNumberGenerator RNG = Elysium::Core::Security::Cryptography::RandomNumberGenerator();

	Elysium::Core::Container::VectorOfByte HandshakeLength = BitConverter::GetBytes(static_cast<uint32_t>(HandshakeSize));
	Elysium::Core::Container::VectorOfByte ClientVersion = BitConverter::GetBytes(static_cast<uint16_t>(EnabledTlsProtocols));
	RNG.GetBytes(_LocalRandom);
	Elysium::Core::Container::VectorOfByte CipherSuitesLength = BitConverter::GetBytes(static_cast<uint16_t>(NumberOfCipherSuites * 2));
	if (BitConverter::GetIsLittleEndian())
	{
		/*
		* @ToDo
		Collections::Template::Array<byte>::Reverse(HandshakeLength);
		Collections::Template::Array<byte>::Reverse(ClientVersion);
		Collections::Template::Array<byte>::Reverse(_LocalRandom);
		Collections::Template::Array<byte>::Reverse(_SessionId);
		Collections::Template::Array<byte>::Reverse(CipherSuitesLength);
		*/
	}

	_InnerStream.WriteByte(static_cast<byte>(TlsHandshakeMessageType::ClientHello));
	_InnerStream.Write(&HandshakeLength[1], HandshakeLength.GetLength() - 1);	// handshake message length
	_InnerStream.Write(&ClientVersion[0], ClientVersion.GetLength());	// client version
	_InnerStream.Write(&_LocalRandom[0], _LocalRandom.GetLength());	// client random
	_InnerStream.WriteByte(static_cast<byte>(_SessionId.GetLength()));
	_InnerStream.Write(&_SessionId[0], _SessionId.GetLength());
	_InnerStream.Write(&CipherSuitesLength[0], CipherSuitesLength.GetLength());
	for (Elysium::Core::size i = 0; i < NumberOfCipherSuites; i++)
	{
		Elysium::Core::Container::VectorOfByte CipherSuite = BitConverter::GetBytes(static_cast<uint16_t>(CipherSuites[i]));
		if (BitConverter::GetIsLittleEndian())
		{
			/*
			* @ToDo
			Collections::Template::Array<byte>::Reverse(CipherSuite);
			*/
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

void Elysium::Core::Net::Security::ExperimentalTlsStream::ReadServerHello()
{
	// read tls record header -> 1 byte content type, 2 bytes tls version, 2 bytes length
	Elysium::Core::Container::VectorOfByte RecordBuffer = Elysium::Core::Container::VectorOfByte(5);
	const Elysium::Core::size RecordBufferLength = RecordBuffer.GetLength();
	Elysium::Core::size TotalBytesRead = 0;
	do
	{
		Elysium::Core::size BytesRead = _InnerStream.Read(&RecordBuffer[TotalBytesRead], RecordBuffer.GetLength() - TotalBytesRead);
		TotalBytesRead += BytesRead;
	} while (TotalBytesRead < RecordBufferLength);

	const TlsContentType ContentType = static_cast<const TlsContentType>(RecordBuffer[0]);
	const Elysium::Core::Security::Authentication::TlsProtocols ProtocolVersion = static_cast<const Elysium::Core::Security::Authentication::TlsProtocols>(BitConverter::ToUInt16(&RecordBuffer[1]));
	const uint16_t ContentLength = BitConverter::ToUInt16(&RecordBuffer[3]);

	// read tls content
	Elysium::Core::Container::VectorOfByte ContentBuffer = Elysium::Core::Container::VectorOfByte(ContentLength);
	TotalBytesRead = 0;
	do
	{
		Elysium::Core::size BytesRead = _InnerStream.Read(&ContentBuffer[TotalBytesRead], ContentBuffer.GetLength() - TotalBytesRead);
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
		const uint32_t ResponseLength = BitConverter::ToUInt24(&ContentBuffer[1]);
		const Elysium::Core::Security::Authentication::TlsProtocols ServerVersion = static_cast<const Elysium::Core::Security::Authentication::TlsProtocols>(BitConverter::ToUInt16(&ContentBuffer[4]));
		Elysium::Core::Template::Memory::MemCpy(&_RemoteRandom[0], &ContentBuffer[6], 32);

		const uint8_t SessionIdLength = ContentBuffer[38];
		if (SessionIdLength != 0x20)
		{
			throw 1;
		}
		Elysium::Core::Template::Memory::MemCpy(&_SessionId[0], &ContentBuffer[39], SessionIdLength);
		_ServerSelectedCipherSuite = static_cast<const TlsCipherSuite>(BitConverter::ToUInt16(&ContentBuffer[71]));
		_ServerSelectedCompressionMethod = ContentBuffer[72];
		// ToDo: extensions
	}
	else
	{
		throw 1;
	}
}

void Elysium::Core::Net::Security::ExperimentalTlsStream::ReadServerCertificates()
{
	// read tls record header -> 1 byte content type, 2 bytes tls version, 2 bytes length
	Elysium::Core::Container::VectorOfByte RecordBuffer = Elysium::Core::Container::VectorOfByte(5);
	const Elysium::Core::size RecordBufferLength = RecordBuffer.GetLength();
	Elysium::Core::size TotalBytesRead = 0;
	do
	{
		Elysium::Core::size BytesRead = _InnerStream.Read(&RecordBuffer[TotalBytesRead], RecordBuffer.GetLength() - TotalBytesRead);
		TotalBytesRead += BytesRead;
	} while (TotalBytesRead < RecordBufferLength);

	const TlsContentType ContentType = static_cast<const TlsContentType>(RecordBuffer[0]);
	const Elysium::Core::Security::Authentication::TlsProtocols ProtocolVersion = static_cast<const Elysium::Core::Security::Authentication::TlsProtocols>(BitConverter::ToUInt16(&RecordBuffer[1]));
	const uint16_t ContentLength = BitConverter::ToUInt16(&RecordBuffer[3]);

	// read tls content
	Elysium::Core::Container::VectorOfByte ContentBuffer = Elysium::Core::Container::VectorOfByte(ContentLength);
	TotalBytesRead = 0;
	do
	{
		Elysium::Core::size BytesRead = _InnerStream.Read(&ContentBuffer[TotalBytesRead], ContentBuffer.GetLength() - TotalBytesRead);
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
		const uint32_t ResponseLength = BitConverter::ToUInt24(&ContentBuffer[1]);
		const uint32_t CertificatesLength = BitConverter::ToUInt24(&ContentBuffer[4]);

		Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection ServerCertificates = Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection();
		Elysium::Core::size CertificateBytesRead = 0;
		do
		{
			const uint32_t CertificateLength = BitConverter::ToUInt24(&ContentBuffer[CertificateBytesRead + 7]);
			ServerCertificates.Add(Elysium::Core::Template::Functional::Move(Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::LoadFromBlob(&ContentBuffer[CertificateBytesRead + 10], CertificateLength)));
			CertificateBytesRead += CertificateLength + 3;
		} while (CertificateBytesRead < CertificatesLength);



		/*
		const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate* ServerCertificate;
		const Elysium::Core::size NumberOfServerCertificates = ServerCertificates.GetCount();
		switch (NumberOfServerCertificates)
		{
		case 0:
			throw 1;
		case 1:
			ServerCertificate = &ServerCertificates[0];
			break;
		default:
			const Elysium::Core::Delegate<const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const void*, const Elysium::Core::Utf8String&, const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection&, const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const Elysium::Core::Collections::Template::Array<Elysium::Core::Utf8String>&>& SelectionCallback = _AuthenticationOptions.GetUserCertificateSelectionCallback();
			ServerCertificate = &SelectionCallback(this, Elysium::Core::Utf8String(u8""), ServerCertificates, ServerCertificates[0], Collections::Template::Array<Elysium::Core::Utf8String>(0));
			break;
		}

		const bool IsCertificateValidDespiteErrors = _AuthenticationOptions.GetUserCertificateValidationCallback()(this, *ServerCertificate, Elysium::Core::Security::Cryptography::X509Certificates::X509Chain(), TlsPolicyErrors::None);
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

void Elysium::Core::Net::Security::ExperimentalTlsStream::ReadServerKeyExchange()
{
	// read tls record header -> 1 byte content type, 2 bytes tls version, 2 bytes length
	Elysium::Core::Container::VectorOfByte RecordBuffer = Elysium::Core::Container::VectorOfByte(5);
	const Elysium::Core::size RecordBufferLength = RecordBuffer.GetLength();
	Elysium::Core::size TotalBytesRead = 0;
	do
	{
		Elysium::Core::size BytesRead = _InnerStream.Read(&RecordBuffer[TotalBytesRead], RecordBuffer.GetLength() - TotalBytesRead);
		TotalBytesRead += BytesRead;
	} while (TotalBytesRead < RecordBufferLength);

	const TlsContentType ContentType = static_cast<const TlsContentType>(RecordBuffer[0]);
	const Elysium::Core::Security::Authentication::TlsProtocols ProtocolVersion = static_cast<const Elysium::Core::Security::Authentication::TlsProtocols>(BitConverter::ToUInt16(&RecordBuffer[1]));
	const uint16_t ContentLength = BitConverter::ToUInt16(&RecordBuffer[3]);

	// read tls content
	Elysium::Core::Container::VectorOfByte ContentBuffer = Elysium::Core::Container::VectorOfByte(ContentLength);
	TotalBytesRead = 0;
	do
	{
		Elysium::Core::size BytesRead = _InnerStream.Read(&ContentBuffer[TotalBytesRead], ContentBuffer.GetLength() - TotalBytesRead);
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
		const uint32_t ResponseLength = BitConverter::ToUInt24(&ContentBuffer[1]);
		const byte CurveInfoType = ContentBuffer[4];
		// Curve types:
		// - 0x01 explicit prime
		// - 0x02 explicit char2
		// - 0x03 named curve
		if (CurveInfoType != 0x03)
		{	// not "named curve"
			throw 1;
		}
		// named curves:
		// - 0x13 (19d) secp192r1
		// - 0x17 (23d) secp256r1
		const uint16_t CurveInfo = BitConverter::ToUInt16(&ContentBuffer[5]);
		const uint8_t LengthOfPublicKey = static_cast<uint8_t>(ContentBuffer[7]);
		// public key
		const uint16_t SignatureType = BitConverter::ToUInt16(&ContentBuffer[8 + LengthOfPublicKey]);
		const uint16_t LengthOfSignature = BitConverter::ToUInt16(&ContentBuffer[9 + LengthOfPublicKey]);
		// computed signature for ENCRYPT(client_hello_random + server_hello_random + curve_info + public_key)




		Elysium::Core::Container::VectorOfByte PublicKeyBytes = Elysium::Core::Container::VectorOfByte(LengthOfPublicKey);
		Elysium::Core::Template::Memory::MemCpy(&PublicKeyBytes[0], &ContentBuffer[8], LengthOfPublicKey);

		Elysium::Core::Container::VectorOfByte SignatureBytes = Elysium::Core::Container::VectorOfByte(LengthOfSignature);
		Elysium::Core::Template::Memory::MemCpy(&SignatureBytes[0], &ContentBuffer[9 + LengthOfPublicKey], LengthOfSignature);




		//throw 1;
		int sdf = 45;
	}
	else
	{
		throw 1;
	}
}

void Elysium::Core::Net::Security::ExperimentalTlsStream::ReadServerHelloDone()
{
	// read tls record header -> 1 byte content type, 2 bytes tls version, 2 bytes length
	Elysium::Core::Container::VectorOfByte RecordBuffer = Elysium::Core::Container::VectorOfByte(5);
	const Elysium::Core::size RecordBufferLength = RecordBuffer.GetLength();
	Elysium::Core::size TotalBytesRead = 0;
	do
	{
		Elysium::Core::size BytesRead = _InnerStream.Read(&RecordBuffer[TotalBytesRead], RecordBuffer.GetLength() - TotalBytesRead);
		TotalBytesRead += BytesRead;
	} while (TotalBytesRead < RecordBufferLength);

	const TlsContentType ContentType = static_cast<const TlsContentType>(RecordBuffer[0]);
	const Elysium::Core::Security::Authentication::TlsProtocols ProtocolVersion = static_cast<const Elysium::Core::Security::Authentication::TlsProtocols>(BitConverter::ToUInt16(&RecordBuffer[1]));
	const uint16_t ContentLength = BitConverter::ToUInt16(&RecordBuffer[3]);

	// read tls content
	Elysium::Core::Container::VectorOfByte ContentBuffer = Elysium::Core::Container::VectorOfByte(ContentLength);
	TotalBytesRead = 0;
	do
	{
		Elysium::Core::size BytesRead = _InnerStream.Read(&ContentBuffer[TotalBytesRead], ContentBuffer.GetLength() - TotalBytesRead);
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
		const uint32_t ResponseLength = BitConverter::ToUInt24(&ContentBuffer[1]);

		throw 1;
	}
	else
	{
		throw 1;
	}
}

