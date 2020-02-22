#include "CppUnitTest.h"

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#include "CppUnitTestFrameworkExtension.hpp"
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

using namespace Elysium::Core::Security::Cryptography::X509Certificates;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsCore
{
	TEST_CLASS(Core_Security_Cryptography_X509Certificates_Test)
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

				int x = 25;
			}
		}

		TEST_METHOD(ReadCertificate)
		{
			Elysium::Core::String Input = u"MIIF7zCCBNegAwIBAgIRANdVj9r18RBbshMoK3B3KaMwDQYJKoZIhvcNAQEFBQAwgZcxCzAJBgNVBAYTAlVTMQswCQYDVQQIEwJVVDEXMBUGA1UEBxMOU2FsdCBMYWtlIENpdHkxHjAcBgNVBAoTFVRoZSBVU0VSVFJVU1QgTmV0d29yazEhMB8GA1UECxMYaHR0cDovL3d3dy51c2VydHJ1c3QuY29tMR8wHQYDVQQDExZVVE4tVVNFUkZpcnN0LUhhcmR3YXJlMB4XDTExMDMxNTAwMDAwMFoXDTE0MDMxNDIzNTk1OVowgd8xCzAJBgNVBAYTAlVTMQ4wDAYDVQQREwUzODQ3NzEQMA4GA1UECBMHRmxvcmlkYTEQMA4GA1UEBxMHRW5nbGlzaDEXMBUGA1UECRMOU2VhIFZpbGxhZ2UgMTAxFDASBgNVBAoTC0dvb2dsZSBMdGQuMRMwEQYDVQQLEwpUZWNoIERlcHQuMSgwJgYDVQQLEx9Ib3N0ZWQgYnkgR1RJIEdyb3VwIENvcnBvcmF0aW9uMRQwEgYDVQQLEwtQbGF0aW51bVNTTDEYMBYGA1UEAxMPbG9naW4ueWFob28uY29tMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAoaQFPe2FRZOKGE3GAwBX4kB38Bzr0BnfIl0If9EHPEGJRhejCfr8+KkE0ZaPq9dPPPmtGKl0gcRXCjomFs5iPrw/bCHuk43LDaAfmpbQj631k5OC7nIMoXUVo3uEVrit/1IRcYS8OjALfpio4ag/N1LQ8XxvkNhFCqw5cmph1bvDjPnCzN/9OnG5r7zcOtwMtrHS0Ym7Qbby3lfVFd/8/eIxxd/KwdiPLL/wDltx4DRxw8VNfXrU+u0wSy/qti6ekzziOvhCohru3N/ND6n2eYQajmwCtoblv1FqZvjznNNZDHulmXjNfJn6xpZH2DLUdHYOd0sgdKS3iXWSSrRbVQIDAQABo4IB6jCCAeYwHwYDVR0jBBgwFoAUoXJfJhsomEOVXQc31YWWnUvSw0UwHQYDVR0OBBYEFIZJRfwzGTPUBO0nYe7oAckMfy9+MA4GA1UdDwEB/wQEAwIFoDAMBgNVHRMBAf8EAjAAMB0GA1UdJQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjBGBgNVHSAEPzA9MDsGDCsGAQQBsjEBAgEDBDArMCkGCCsGAQUFBwIBFh1odHRwczovL3NlY3VyZS5jb21vZG8uY29tL0NQUzB7BgNVHR8EdDByMDigNqA0hjJodHRwOi8vY3JsLmNvbW9kb2NhLmNvbS9VVE4tVVNFUkZpcnN0LUhhcmR3YXJlLmNybDA2oDSgMoYwaHR0cDovL2NybC5jb21vZG8ubmV0L1VUTi1VU0VSRmlyc3QtSGFyZHdhcmUuY3JsMHEGCCsGAQUFBwEBBGUwYzA7BggrBgEFBQcwAoYvaHR0cDovL2NydC5jb21vZG9jYS5jb20vVVROQWRkVHJ1c3RTZXJ2ZXJDQS5jcnQwJAYIKwYBBQUHMAGGGGh0dHA6Ly9vY3NwLmNvbW9kb2NhLmNvbTAvBgNVHREEKDAmgg9sb2dpbi55YWhvby5jb22CE3d3dy5sb2dpbi55YWhvby5jb20wDQYJKoZIhvcNAQEFBQADggEBAD1XyUgkXO5kgfWuvlUpFv8qL4Tt2fijA8gwZrvI1IEtIfcI96yWQppBdXq6XRAjy5JCYfqK2m1lNBnlqdYtE3jXgUSSqW6AYxXL/jUfAtGKFLCozJQgO6ga8F02UNsNrulk5PaNaX0wyBQXAErlpjX7fQ0inXl2Uiy8lwaImhX0c+bx9ZilzQdEkbinaGdF0nIRYOJxt1BV4oqpDdaS7gQqizCgogVGNG2SxjuqTaDQqwEZCjK36OPP8dKXSXuspJf38FeuY3eaf5baTf2+3Ac24yW9iXmOKRITi4gH+2vbpM2zLSfp1Mpg14VT+3TGXDWMcB/5sreSJyDHlNVnFDA=";
			Elysium::Core::Collections::Template::List<Elysium::Core::byte> Output = Elysium::Core::Convert::FromBase64String(Input);

			int x = 25;
		}
	};
}
