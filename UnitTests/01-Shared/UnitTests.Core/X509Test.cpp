#include "CppUnitTest.h"

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_CONVERT
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Convert.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509STORE
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Security/X509Store.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CHAIN
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Security/X509Chain.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILESTREAM
#include "../../../Libraries/01-Shared/Elysium.Core.IO/FileStream.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_DERDECODER
#include "../../../Libraries/01-Shared/Elysium.Core.Security/DERDecoder.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_MEMORYSTREAM
#include "../../../Libraries/01-Shared/Elysium.Core.IO/MemoryStream.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_INVALIDDATAEXCEPTION
#include "../../../Libraries/01-Shared/Elysium.Core.IO/InvalidDataException.hpp"
#endif

using namespace Elysium::Core::Collections::Template;
using namespace Elysium::Core::IO;
using namespace Elysium::Core::Security::Cryptography::Asn1;
using namespace Elysium::Core::Security::Cryptography::X509Certificates;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Security::Cryptography
{
	TEST_CLASS(X509CertificatesTests)
	{
	public:
		TEST_METHOD(OpenStoreRootCurrentUser)
		{
			X509Store RootCurrentUserStore = X509Store(StoreName::Root, StoreLocation::CurrentUser);
			Assert::AreEqual(static_cast<size_t>(0), RootCurrentUserStore.GetCertificates().GetCount());

			RootCurrentUserStore.Open(OpenFlags::ReadOnly);
			Assert::AreNotEqual(static_cast<size_t>(0), RootCurrentUserStore.GetCertificates().GetCount());

			for (size_t i = 0; i < RootCurrentUserStore.GetCertificates().GetCount(); i++)
			{
				const X509Certificate& Certificate = RootCurrentUserStore.GetCertificates()[i];
			}
		}
		TEST_METHOD(BuildCertificateChain)
		{
			X509Store RootCurrentUserStore = X509Store(StoreName::Root, StoreLocation::CurrentUser);
			RootCurrentUserStore.Open(OpenFlags::ReadOnly);

			X509Chain Chain = X509Chain();
			bool Result = Chain.Build(RootCurrentUserStore.GetCertificates()[0]);

			Assert::IsTrue(Result);
		}

		TEST_METHOD(ReadCertificateFromBlob)
		{
			Elysium::Core::CharString Input = "-----BEGIN CERTIFICATE-----"
				"MIIF7zCCBNegAwIBAgIRANdVj9r18RBbshMoK3B3KaMwDQYJKoZIhvcNAQEFBQAw"
				"gZcxCzAJBgNVBAYTAlVTMQswCQYDVQQIEwJVVDEXMBUGA1UEBxMOU2FsdCBMYWtl"
				"IENpdHkxHjAcBgNVBAoTFVRoZSBVU0VSVFJVU1QgTmV0d29yazEhMB8GA1UECxMY"
				"aHR0cDovL3d3dy51c2VydHJ1c3QuY29tMR8wHQYDVQQDExZVVE4tVVNFUkZpcnN0"
				"LUhhcmR3YXJlMB4XDTExMDMxNTAwMDAwMFoXDTE0MDMxNDIzNTk1OVowgd8xCzAJ"
				"BgNVBAYTAlVTMQ4wDAYDVQQREwUzODQ3NzEQMA4GA1UECBMHRmxvcmlkYTEQMA4G"
				"A1UEBxMHRW5nbGlzaDEXMBUGA1UECRMOU2VhIFZpbGxhZ2UgMTAxFDASBgNVBAoT"
				"C0dvb2dsZSBMdGQuMRMwEQYDVQQLEwpUZWNoIERlcHQuMSgwJgYDVQQLEx9Ib3N0"
				"ZWQgYnkgR1RJIEdyb3VwIENvcnBvcmF0aW9uMRQwEgYDVQQLEwtQbGF0aW51bVNT"
				"TDEYMBYGA1UEAxMPbG9naW4ueWFob28uY29tMIIBIjANBgkqhkiG9w0BAQEFAAOC"
				"AQ8AMIIBCgKCAQEAoaQFPe2FRZOKGE3GAwBX4kB38Bzr0BnfIl0If9EHPEGJRhej"
				"Cfr8+KkE0ZaPq9dPPPmtGKl0gcRXCjomFs5iPrw/bCHuk43LDaAfmpbQj631k5OC"
				"7nIMoXUVo3uEVrit/1IRcYS8OjALfpio4ag/N1LQ8XxvkNhFCqw5cmph1bvDjPnC"
				"zN/9OnG5r7zcOtwMtrHS0Ym7Qbby3lfVFd/8/eIxxd/KwdiPLL/wDltx4DRxw8VN"
				"fXrU+u0wSy/qti6ekzziOvhCohru3N/ND6n2eYQajmwCtoblv1FqZvjznNNZDHul"
				"mXjNfJn6xpZH2DLUdHYOd0sgdKS3iXWSSrRbVQIDAQABo4IB6jCCAeYwHwYDVR0j"
				"BBgwFoAUoXJfJhsomEOVXQc31YWWnUvSw0UwHQYDVR0OBBYEFIZJRfwzGTPUBO0n"
				"Ye7oAckMfy9+MA4GA1UdDwEB/wQEAwIFoDAMBgNVHRMBAf8EAjAAMB0GA1UdJQQW"
				"MBQGCCsGAQUFBwMBBggrBgEFBQcDAjBGBgNVHSAEPzA9MDsGDCsGAQQBsjEBAgED"
				"BDArMCkGCCsGAQUFBwIBFh1odHRwczovL3NlY3VyZS5jb21vZG8uY29tL0NQUzB7"
				"BgNVHR8EdDByMDigNqA0hjJodHRwOi8vY3JsLmNvbW9kb2NhLmNvbS9VVE4tVVNF"
				"UkZpcnN0LUhhcmR3YXJlLmNybDA2oDSgMoYwaHR0cDovL2NybC5jb21vZG8ubmV0"
				"L1VUTi1VU0VSRmlyc3QtSGFyZHdhcmUuY3JsMHEGCCsGAQUFBwEBBGUwYzA7Bggr"
				"BgEFBQcwAoYvaHR0cDovL2NydC5jb21vZG9jYS5jb20vVVROQWRkVHJ1c3RTZXJ2"
				"ZXJDQS5jcnQwJAYIKwYBBQUHMAGGGGh0dHA6Ly9vY3NwLmNvbW9kb2NhLmNvbTAv"
				"BgNVHREEKDAmgg9sb2dpbi55YWhvby5jb22CE3d3dy5sb2dpbi55YWhvby5jb20w"
				"DQYJKoZIhvcNAQEFBQADggEBAD1XyUgkXO5kgfWuvlUpFv8qL4Tt2fijA8gwZrvI"
				"1IEtIfcI96yWQppBdXq6XRAjy5JCYfqK2m1lNBnlqdYtE3jXgUSSqW6AYxXL/jUf"
				"AtGKFLCozJQgO6ga8F02UNsNrulk5PaNaX0wyBQXAErlpjX7fQ0inXl2Uiy8lwaI"
				"mhX0c+bx9ZilzQdEkbinaGdF0nIRYOJxt1BV4oqpDdaS7gQqizCgogVGNG2Sxjuq"
				"TaDQqwEZCjK36OPP8dKXSXuspJf38FeuY3eaf5baTf2+3Ac24yW9iXmOKRITi4gH"
				"+2vbpM2zLSfp1Mpg14VT+3TGXDWMcB/5sreSJyDHlNVnFDA="
				"-----END CERTIFICATE-----";
			/*
			Elysium::Core::CharString Input = "-----BEGIN RSA PRIVATE KEY-----"
				"MIICXAIBAAKBgQCf6YAJOSBYPve1jpYDzq+w++8YVoATI/YCi/RKZaQk+l2ZfoUQ"
				"g0qrYrfkzeoOa/qd5VLjTTvHEgwXnlDXMfo+vSgxosUxDOZXMTBqJGOViv5K2QBv"
				"k8A1wi4k8tuo/7OWya29HvcfavUk3YXaV2YFe8V6ssaZjNcVWmDdjqNkXwIDAQAB"
				"AoGALrd+ijNAOcebglT3ioE1XpUbUpbir7TPyAqvAZUUESF7er41jY9tnwgmBRgL"
				"Cs+M1dgLERCdKBkjozrDDzswifFQmq6PrmYrBkFFqCoLJwepSYdWnK1gbZ/d43rR"
				"2sXzSGZngscx0CxO7KZ7xUkwENGd3+lKXV7J6/vgzJ4XnkECQQDTP6zWKT7YDckk"
				"We04hbhHyBuNOW068NgUUvoZdBewerR74MJx6nz28Tp+DeNvc0EveiQxsEnbV8u+"
				"NRkX5y0xAkEAwcnEAGBn5kJd6SpU0ALA9XEpUv7tHTAGQYgCRbfTT59hhOq6I22A"
				"ivjOCNG9c6E7EB2kcPVGuCpYUhy7XBIGjwJAK5lavKCqncDKoLwGn8HJdNcyCIWv"
				"q5iFoDw37gTt1ricg2yx9PzmabkDz3xiUmBBNeFJkw/FToXiQRGIakyGIQJAJIem"
				"PPPvYgZssYFbT4LVYO8d/Rk1FWVyKHQ9CWtnmADRXz7oK7l+m7PfEuaGsf9YpOcR"
				"koGJ/TluQLxNzUNQnQJBAImwr/yYFenIx3HQ6UX/fCt6qpGDv0VfOLyR64MNeegx"
				"o7DhNxHbFkIGzk4lKhMKcHKDrawZbdJtS9ie2geSwVQ="
				"-----END RSA PRIVATE KEY-----";
			*/
			Elysium::Core::Collections::Template::Array<Elysium::Core::byte> RawDataArray = Elysium::Core::Collections::Template::Array<Elysium::Core::byte>(Input.GetLength());
			for (size_t i = 0; i < Input.GetLength(); i++)
			{
				RawDataArray[i] = Input[i];
			}

			X509Certificate Certificate = X509Certificate::LoadFromBlob(RawDataArray);
			AssertExtended::AreEqual(u"C=US, S=UT, L=Salt Lake City, O=The USERTRUST Network, OU=http://www.usertrust.com, CN=UTN-USERFirst-Hardware", Certificate.GetIssuer().GetCharArray());
			AssertExtended::AreEqual(u"C=US, PostalCode=38477, S=Florida, L=English, STREET=Sea Village 10, O=Google Ltd., OU=Tech Dept., OU=Hosted by GTI Group Corporation, OU=PlatinumSSL, CN=login.yahoo.com", Certificate.GetSubject().GetCharArray());
		}

		TEST_METHOD(ReadCertificateFromFile)
		{
			Elysium::Core::IO::FileStream TargetStream = Elysium::Core::IO::FileStream(u"sample.crt", Elysium::Core::IO::FileMode::Create, Elysium::Core::IO::FileAccess::Write);
			Elysium::Core::CharString Input = "-----BEGIN CERTIFICATE-----"
				"MIIF7zCCBNegAwIBAgIRANdVj9r18RBbshMoK3B3KaMwDQYJKoZIhvcNAQEFBQAw"
				"gZcxCzAJBgNVBAYTAlVTMQswCQYDVQQIEwJVVDEXMBUGA1UEBxMOU2FsdCBMYWtl"
				"IENpdHkxHjAcBgNVBAoTFVRoZSBVU0VSVFJVU1QgTmV0d29yazEhMB8GA1UECxMY"
				"aHR0cDovL3d3dy51c2VydHJ1c3QuY29tMR8wHQYDVQQDExZVVE4tVVNFUkZpcnN0"
				"LUhhcmR3YXJlMB4XDTExMDMxNTAwMDAwMFoXDTE0MDMxNDIzNTk1OVowgd8xCzAJ"
				"BgNVBAYTAlVTMQ4wDAYDVQQREwUzODQ3NzEQMA4GA1UECBMHRmxvcmlkYTEQMA4G"
				"A1UEBxMHRW5nbGlzaDEXMBUGA1UECRMOU2VhIFZpbGxhZ2UgMTAxFDASBgNVBAoT"
				"C0dvb2dsZSBMdGQuMRMwEQYDVQQLEwpUZWNoIERlcHQuMSgwJgYDVQQLEx9Ib3N0"
				"ZWQgYnkgR1RJIEdyb3VwIENvcnBvcmF0aW9uMRQwEgYDVQQLEwtQbGF0aW51bVNT"
				"TDEYMBYGA1UEAxMPbG9naW4ueWFob28uY29tMIIBIjANBgkqhkiG9w0BAQEFAAOC"
				"AQ8AMIIBCgKCAQEAoaQFPe2FRZOKGE3GAwBX4kB38Bzr0BnfIl0If9EHPEGJRhej"
				"Cfr8+KkE0ZaPq9dPPPmtGKl0gcRXCjomFs5iPrw/bCHuk43LDaAfmpbQj631k5OC"
				"7nIMoXUVo3uEVrit/1IRcYS8OjALfpio4ag/N1LQ8XxvkNhFCqw5cmph1bvDjPnC"
				"zN/9OnG5r7zcOtwMtrHS0Ym7Qbby3lfVFd/8/eIxxd/KwdiPLL/wDltx4DRxw8VN"
				"fXrU+u0wSy/qti6ekzziOvhCohru3N/ND6n2eYQajmwCtoblv1FqZvjznNNZDHul"
				"mXjNfJn6xpZH2DLUdHYOd0sgdKS3iXWSSrRbVQIDAQABo4IB6jCCAeYwHwYDVR0j"
				"BBgwFoAUoXJfJhsomEOVXQc31YWWnUvSw0UwHQYDVR0OBBYEFIZJRfwzGTPUBO0n"
				"Ye7oAckMfy9+MA4GA1UdDwEB/wQEAwIFoDAMBgNVHRMBAf8EAjAAMB0GA1UdJQQW"
				"MBQGCCsGAQUFBwMBBggrBgEFBQcDAjBGBgNVHSAEPzA9MDsGDCsGAQQBsjEBAgED"
				"BDArMCkGCCsGAQUFBwIBFh1odHRwczovL3NlY3VyZS5jb21vZG8uY29tL0NQUzB7"
				"BgNVHR8EdDByMDigNqA0hjJodHRwOi8vY3JsLmNvbW9kb2NhLmNvbS9VVE4tVVNF"
				"UkZpcnN0LUhhcmR3YXJlLmNybDA2oDSgMoYwaHR0cDovL2NybC5jb21vZG8ubmV0"
				"L1VUTi1VU0VSRmlyc3QtSGFyZHdhcmUuY3JsMHEGCCsGAQUFBwEBBGUwYzA7Bggr"
				"BgEFBQcwAoYvaHR0cDovL2NydC5jb21vZG9jYS5jb20vVVROQWRkVHJ1c3RTZXJ2"
				"ZXJDQS5jcnQwJAYIKwYBBQUHMAGGGGh0dHA6Ly9vY3NwLmNvbW9kb2NhLmNvbTAv"
				"BgNVHREEKDAmgg9sb2dpbi55YWhvby5jb22CE3d3dy5sb2dpbi55YWhvby5jb20w"
				"DQYJKoZIhvcNAQEFBQADggEBAD1XyUgkXO5kgfWuvlUpFv8qL4Tt2fijA8gwZrvI"
				"1IEtIfcI96yWQppBdXq6XRAjy5JCYfqK2m1lNBnlqdYtE3jXgUSSqW6AYxXL/jUf"
				"AtGKFLCozJQgO6ga8F02UNsNrulk5PaNaX0wyBQXAErlpjX7fQ0inXl2Uiy8lwaI"
				"mhX0c+bx9ZilzQdEkbinaGdF0nIRYOJxt1BV4oqpDdaS7gQqizCgogVGNG2Sxjuq"
				"TaDQqwEZCjK36OPP8dKXSXuspJf38FeuY3eaf5baTf2+3Ac24yW9iXmOKRITi4gH"
				"+2vbpM2zLSfp1Mpg14VT+3TGXDWMcB/5sreSJyDHlNVnFDA="
				"-----END CERTIFICATE-----";
			TargetStream.Write((byte*)&Input[0], Input.GetLength());
			TargetStream.Close();

			X509Certificate Certificate = X509Certificate::LoadFromFile(u"sample.crt");
			AssertExtended::AreEqual(u"C=US, S=UT, L=Salt Lake City, O=The USERTRUST Network, OU=http://www.usertrust.com, CN=UTN-USERFirst-Hardware", Certificate.GetIssuer().GetCharArray());
			AssertExtended::AreEqual(u"C=US, PostalCode=38477, S=Florida, L=English, STREET=Sea Village 10, O=Google Ltd., OU=Tech Dept., OU=Hosted by GTI Group Corporation, OU=PlatinumSSL, CN=login.yahoo.com", Certificate.GetSubject().GetCharArray());
		}

		TEST_METHOD(ReadCertificateUsingDERDecoder)
		{
			DERDecoder Decoder = DERDecoder();
			for (uint32_t StoreNameInt = (uint32_t)StoreName::AddressBook; StoreNameInt != (uint32_t)StoreName::TrustedPublisher; StoreNameInt++)
			{
				for (uint8_t StoreLocationInt = (uint8_t)StoreLocation::CurrentUser; StoreLocationInt != (uint8_t)StoreLocation::LocalMachine; StoreLocationInt++)
				{
					X509Store CurrentStore = X509Store(static_cast<StoreName>(StoreNameInt), static_cast<StoreLocation>(StoreLocationInt));
					CurrentStore.Open(OpenFlags::ReadOnly);

					for (size_t i = 0; i < CurrentStore.GetCertificates().GetCount(); i++)
					{
						const X509Certificate& Certificate = CurrentStore.GetCertificates()[i];
						const Array<byte> RawData = Certificate.GetRawCertData();

						// need to use this offset until Certificate.GetRawCertData() has been implemented correctly
						size_t StartIndex = 352;
						MemoryStream InputStream = MemoryStream(RawData, StartIndex, RawData.GetLength() - StartIndex);
						/*
						Certificate  ::=  SEQUENCE  {
							tbsCertificate       TBSCertificate,
							signatureAlgorithm   AlgorithmIdentifier,
							signatureValue       BIT STRING  }

						TBSCertificate  ::=  SEQUENCE  {
							version         [0]  EXPLICIT Version DEFAULT v1,
							serialNumber         CertificateSerialNumber,
							signature            AlgorithmIdentifier,
							issuer               Name,
							validity             Validity,
							subject              Name,
							subjectPublicKeyInfo SubjectPublicKeyInfo,
							issuerUniqueID  [1]  IMPLICIT UniqueIdentifier OPTIONAL,
												 -- If present, version MUST be v2 or v3
							subjectUniqueID [2]  IMPLICIT UniqueIdentifier OPTIONAL,
												 -- If present, version MUST be v2 or v3
							extensions      [3]  EXPLICIT Extensions OPTIONAL
												 -- If present, version MUST be v3
							}

						Version  ::=  INTEGER  {  v1(0), v2(1), v3(2)  }
						*/
						Asn1Identifier CertificateSequence = Decoder.DecodeIdentifier(InputStream);
						if (CertificateSequence.GetTagNumber() != static_cast<const Elysium::Core::int32_t>(Asn1TagNumber::Sequence))
						{
							throw InvalidDataException(u"CertificateSequence");
						}
						Asn1Length CertificateLength = Decoder.DecodeLength(InputStream);
						
						Asn1Identifier TbsCertificateSequence = Decoder.DecodeIdentifier(InputStream);
						if (TbsCertificateSequence.GetTagNumber() != static_cast<const Elysium::Core::int32_t>(Asn1TagNumber::Sequence))
						{
							throw InvalidDataException(u"TbsCertificateSequence");
						}
						Asn1Length TbsCertificateLength = Decoder.DecodeLength(InputStream);

						Asn1Identifier PossibleVersionIdentifier = Decoder.DecodeIdentifier(InputStream);
						switch (PossibleVersionIdentifier.GetTagNumber())
						{
						case static_cast<const Elysium::Core::int32_t>(Asn1TagNumber::Integer):
						{
							Asn1Length VersionLength = Decoder.DecodeLength(InputStream);
							Asn1Integer Version = Decoder.DecodeInteger(PossibleVersionIdentifier, VersionLength, InputStream);
						}
							break;
						case static_cast<const Elysium::Core::int32_t>(Asn1TagNumber::EndOfContent):
						{
							Asn1Length EndOfContentLength = Decoder.DecodeLength(InputStream);

							Asn1Identifier VersionIdentifier = Decoder.DecodeIdentifier(InputStream);
							if (VersionIdentifier.GetTagNumber() != static_cast<const Elysium::Core::int32_t>(Asn1TagNumber::Integer))
							{
								throw InvalidDataException(u"VersionIdentifier");
							}
							Asn1Length VersionLength = Decoder.DecodeLength(InputStream);
							Asn1Integer Version = Decoder.DecodeInteger(VersionIdentifier, VersionLength, InputStream);
						}
							break;
						default:
							throw InvalidDataException(u"PossibleVersionIdentifier");
						}

						// at the moment we only look at the first certificate
						return;
					}
				}
			}
		}
	};
}
