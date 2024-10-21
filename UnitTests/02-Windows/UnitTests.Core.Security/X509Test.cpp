#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core/String.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core/StringView.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/FileStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/InvalidDataException.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/MemoryStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Security/CryptographicException.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Security.Cryptography.X509Certificates/X509Store.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Security.Cryptography.X509Certificates/X509Chain.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Security.Cryptography.Encoding/DERDecoder.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Convert.hpp"
;
using namespace Elysium::Core;
using namespace Elysium::Core::Collections::Template;
using namespace Elysium::Core::IO;
using namespace Elysium::Core::Security::Cryptography;
using namespace Elysium::Core::Security::Cryptography::Encoding::Asn1;
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
			Assert::AreEqual(static_cast<Elysium::Core::size>(0), RootCurrentUserStore.GetCertificates().GetCount());

			RootCurrentUserStore.Open(OpenFlags::ReadOnly);
			Assert::AreNotEqual(static_cast<Elysium::Core::size>(0), RootCurrentUserStore.GetCertificates().GetCount());

			for (Elysium::Core::size i = 0; i < RootCurrentUserStore.GetCertificates().GetCount(); i++)
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
			Array<Elysium::Core::byte> RawDataArray = Array<Elysium::Core::byte>({
				0x30, 0x82, 0x05, 0xef, 0x30, 0x82, 0x04, 0xd7,		0xa0, 0x03, 0x02, 0x01, 0x02, 0x02, 0x11, 0x00,
				0xd7, 0x55, 0x8f, 0xda, 0xf5, 0xf1, 0x10, 0x5b,		0xb2, 0x13, 0x28, 0x2b, 0x70, 0x77, 0x29, 0xa3,
				0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86,		0xf7, 0x0d, 0x01, 0x01, 0x05, 0x05, 0x00, 0x30,
				0x81, 0x97, 0x31, 0x0b, 0x30, 0x09, 0x06, 0x03,		0x55, 0x04, 0x06, 0x13, 0x02, 0x55, 0x53, 0x31,
				0x0b, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x08,		0x13, 0x02, 0x55, 0x54, 0x31, 0x17, 0x30, 0x15,
				0x06, 0x03, 0x55, 0x04, 0x07, 0x13, 0x0e, 0x53,		0x61, 0x6c, 0x74, 0x20, 0x4c, 0x61, 0x6b, 0x65,
				0x20, 0x43, 0x69, 0x74, 0x79, 0x31, 0x1e, 0x30,		0x1c, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x13, 0x15,
				0x54, 0x68, 0x65, 0x20, 0x55, 0x53, 0x45, 0x52,		0x54, 0x52, 0x55, 0x53, 0x54, 0x20, 0x4e, 0x65,
				0x74, 0x77, 0x6f, 0x72, 0x6b, 0x31, 0x21, 0x30,		0x1f, 0x06, 0x03, 0x55, 0x04, 0x0b, 0x13, 0x18,
				0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x77,		0x77, 0x77, 0x2e, 0x75, 0x73, 0x65, 0x72, 0x74,
				0x72, 0x75, 0x73, 0x74, 0x2e, 0x63, 0x6f, 0x6d,		0x31, 0x1f, 0x30, 0x1d, 0x06, 0x03, 0x55, 0x04,
				0x03, 0x13, 0x16, 0x55, 0x54, 0x4e, 0x2d, 0x55,		0x53, 0x45, 0x52, 0x46, 0x69, 0x72, 0x73, 0x74,
				0x2d, 0x48, 0x61, 0x72, 0x64, 0x77, 0x61, 0x72,		0x65, 0x30, 0x1e, 0x17, 0x0d, 0x31, 0x31, 0x30,
				0x33, 0x31, 0x35, 0x30, 0x30, 0x30, 0x30, 0x30,		0x30, 0x5a, 0x17, 0x0d, 0x31, 0x34, 0x30, 0x33,
				0x31, 0x34, 0x32, 0x33, 0x35, 0x39, 0x35, 0x39,		0x5a, 0x30, 0x81, 0xdf, 0x31, 0x0b, 0x30, 0x09,
				0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x55,		0x53, 0x31, 0x0e, 0x30, 0x0c, 0x06, 0x03, 0x55,
				0x04, 0x11, 0x13, 0x05, 0x33, 0x38, 0x34, 0x37,		0x37, 0x31, 0x10, 0x30, 0x0e, 0x06, 0x03, 0x55,
				0x04, 0x08, 0x13, 0x07, 0x46, 0x6c, 0x6f, 0x72,		0x69, 0x64, 0x61, 0x31, 0x10, 0x30, 0x0e, 0x06,
				0x03, 0x55, 0x04, 0x07, 0x13, 0x07, 0x45, 0x6e,		0x67, 0x6c, 0x69, 0x73, 0x68, 0x31, 0x17, 0x30,
				0x15, 0x06, 0x03, 0x55, 0x04, 0x09, 0x13, 0x0e,		0x53, 0x65, 0x61, 0x20, 0x56, 0x69, 0x6c, 0x6c,
				0x61, 0x67, 0x65, 0x20, 0x31, 0x30, 0x31, 0x14,		0x30, 0x12, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x13,
				0x0b, 0x47, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x20,		0x4c, 0x74, 0x64, 0x2e, 0x31, 0x13, 0x30, 0x11,
				0x06, 0x03, 0x55, 0x04, 0x0b, 0x13, 0x0a, 0x54,		0x65, 0x63, 0x68, 0x20, 0x44, 0x65, 0x70, 0x74,
				0x2e, 0x31, 0x28, 0x30, 0x26, 0x06, 0x03, 0x55,		0x04, 0x0b, 0x13, 0x1f, 0x48, 0x6f, 0x73, 0x74,
				0x65, 0x64, 0x20, 0x62, 0x79, 0x20, 0x47, 0x54,		0x49, 0x20, 0x47, 0x72, 0x6f, 0x75, 0x70, 0x20,
				0x43, 0x6f, 0x72, 0x70, 0x6f, 0x72, 0x61, 0x74,		0x69, 0x6f, 0x6e, 0x31, 0x14, 0x30, 0x12, 0x06,
				0x03, 0x55, 0x04, 0x0b, 0x13, 0x0b, 0x50, 0x6c,		0x61, 0x74, 0x69, 0x6e, 0x75, 0x6d, 0x53, 0x53,
				0x4c, 0x31, 0x18, 0x30, 0x16, 0x06, 0x03, 0x55,		0x04, 0x03, 0x13, 0x0f, 0x6c, 0x6f, 0x67, 0x69,
				0x6e, 0x2e, 0x79, 0x61, 0x68, 0x6f, 0x6f, 0x2e,		0x63, 0x6f, 0x6d, 0x30, 0x82, 0x01, 0x22, 0x30,
				0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7,		0x0d, 0x01, 0x01, 0x01, 0x05, 0x00, 0x03, 0x82,
				0x01, 0x0f, 0x00, 0x30, 0x82, 0x01, 0x0a, 0x02,		0x82, 0x01, 0x01, 0x00, 0xa1, 0xa4, 0x05, 0x3d,
				0xed, 0x85, 0x45, 0x93, 0x8a, 0x18, 0x4d, 0xc6,		0x03, 0x00, 0x57, 0xe2, 0x40, 0x77, 0xf0, 0x1c,
				0xeb, 0xd0, 0x19, 0xdf, 0x22, 0x5d, 0x08, 0x7f,		0xd1, 0x07, 0x3c, 0x41, 0x89, 0x46, 0x17, 0xa3,
				0x09, 0xfa, 0xfc, 0xf8, 0xa9, 0x04, 0xd1, 0x96,		0x8f, 0xab, 0xd7, 0x4f, 0x3c, 0xf9, 0xad, 0x18,
				0xa9, 0x74, 0x81, 0xc4, 0x57, 0x0a, 0x3a, 0x26,		0x16, 0xce, 0x62, 0x3e, 0xbc, 0x3f, 0x6c, 0x21,
				0xee, 0x93, 0x8d, 0xcb, 0x0d, 0xa0, 0x1f, 0x9a,		0x96, 0xd0, 0x8f, 0xad, 0xf5, 0x93, 0x93, 0x82,
				0xee, 0x72, 0x0c, 0xa1, 0x75, 0x15, 0xa3, 0x7b,		0x84, 0x56, 0xb8, 0xad, 0xff, 0x52, 0x11, 0x71,
				0x84, 0xbc, 0x3a, 0x30, 0x0b, 0x7e, 0x98, 0xa8,		0xe1, 0xa8, 0x3f, 0x37, 0x52, 0xd0, 0xf1, 0x7c,
				0x6f, 0x90, 0xd8, 0x45, 0x0a, 0xac, 0x39, 0x72,		0x6a, 0x61, 0xd5, 0xbb, 0xc3, 0x8c, 0xf9, 0xc2,
				0xcc, 0xdf, 0xfd, 0x3a, 0x71, 0xb9, 0xaf, 0xbc,		0xdc, 0x3a, 0xdc, 0x0c, 0xb6, 0xb1, 0xd2, 0xd1,
				0x89, 0xbb, 0x41, 0xb6, 0xf2, 0xde, 0x57, 0xd5,		0x15, 0xdf, 0xfc, 0xfd, 0xe2, 0x31, 0xc5, 0xdf,
				0xca, 0xc1, 0xd8, 0x8f, 0x2c, 0xbf, 0xf0, 0x0e,		0x5b, 0x71, 0xe0, 0x34, 0x71, 0xc3, 0xc5, 0x4d,
				0x7d, 0x7a, 0xd4, 0xfa, 0xed, 0x30, 0x4b, 0x2f,		0xea, 0xb6, 0x2e, 0x9e, 0x93, 0x3c, 0xe2, 0x3a,
				0xf8, 0x42, 0xa2, 0x1a, 0xee, 0xdc, 0xdf, 0xcd,		0x0f, 0xa9, 0xf6, 0x79, 0x84, 0x1a, 0x8e, 0x6c,
				0x02, 0xb6, 0x86, 0xe5, 0xbf, 0x51, 0x6a, 0x66,		0xf8, 0xf3, 0x9c, 0xd3, 0x59, 0x0c, 0x7b, 0xa5,
				0x99, 0x78, 0xcd, 0x7c, 0x99, 0xfa, 0xc6, 0x96,		0x47, 0xd8, 0x32, 0xd4, 0x74, 0x76, 0x0e, 0x77,
				0x4b, 0x20, 0x74, 0xa4, 0xb7, 0x89, 0x75, 0x92,		0x4a, 0xb4, 0x5b, 0x55, 0x02, 0x03, 0x01, 0x00,
				0x01, 0xa3, 0x82, 0x01, 0xea, 0x30, 0x82, 0x01,		0xe6, 0x30, 0x1f, 0x06, 0x03, 0x55, 0x1d, 0x23,
				0x04, 0x18, 0x30, 0x16, 0x80, 0x14, 0xa1, 0x72,		0x5f, 0x26, 0x1b, 0x28, 0x98, 0x43, 0x95, 0x5d,
				0x07, 0x37, 0xd5, 0x85, 0x96, 0x9d, 0x4b, 0xd2,		0xc3, 0x45, 0x30, 0x1d, 0x06, 0x03, 0x55, 0x1d,
				0x0e, 0x04, 0x16, 0x04, 0x14, 0x86, 0x49, 0x45,		0xfc, 0x33, 0x19, 0x33, 0xd4, 0x04, 0xed, 0x27,
				0x61, 0xee, 0xe8, 0x01, 0xc9, 0x0c, 0x7f, 0x2f,		0x7e, 0x30, 0x0e, 0x06, 0x03, 0x55, 0x1d, 0x0f,
				0x01, 0x01, 0xff, 0x04, 0x04, 0x03, 0x02, 0x05,		0xa0, 0x30, 0x0c, 0x06, 0x03, 0x55, 0x1d, 0x13,
				0x01, 0x01, 0xff, 0x04, 0x02, 0x30, 0x00, 0x30,		0x1d, 0x06, 0x03, 0x55, 0x1d, 0x25, 0x04, 0x16,
				0x30, 0x14, 0x06, 0x08, 0x2b, 0x06, 0x01, 0x05,		0x05, 0x07, 0x03, 0x01, 0x06, 0x08, 0x2b, 0x06,
				0x01, 0x05, 0x05, 0x07, 0x03, 0x02, 0x30, 0x46,		0x06, 0x03, 0x55, 0x1d, 0x20, 0x04, 0x3f, 0x30,
				0x3d, 0x30, 0x3b, 0x06, 0x0c, 0x2b, 0x06, 0x01,		0x04, 0x01, 0xb2, 0x31, 0x01, 0x02, 0x01, 0x03,
				0x04, 0x30, 0x2b, 0x30, 0x29, 0x06, 0x08, 0x2b,		0x06, 0x01, 0x05, 0x05, 0x07, 0x02, 0x01, 0x16,
				0x1d, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a, 0x2f,		0x2f, 0x73, 0x65, 0x63, 0x75, 0x72, 0x65, 0x2e,
				0x63, 0x6f, 0x6d, 0x6f, 0x64, 0x6f, 0x2e, 0x63,		0x6f, 0x6d, 0x2f, 0x43, 0x50, 0x53, 0x30, 0x7b,
				0x06, 0x03, 0x55, 0x1d, 0x1f, 0x04, 0x74, 0x30,		0x72, 0x30, 0x38, 0xa0, 0x36, 0xa0, 0x34, 0x86,
				0x32, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f,		0x63, 0x72, 0x6c, 0x2e, 0x63, 0x6f, 0x6d, 0x6f,
				0x64, 0x6f, 0x63, 0x61, 0x2e, 0x63, 0x6f, 0x6d,		0x2f, 0x55, 0x54, 0x4e, 0x2d, 0x55, 0x53, 0x45,
				0x52, 0x46, 0x69, 0x72, 0x73, 0x74, 0x2d, 0x48,		0x61, 0x72, 0x64, 0x77, 0x61, 0x72, 0x65, 0x2e,
				0x63, 0x72, 0x6c, 0x30, 0x36, 0xa0, 0x34, 0xa0,		0x32, 0x86, 0x30, 0x68, 0x74, 0x74, 0x70, 0x3a,
				0x2f, 0x2f, 0x63, 0x72, 0x6c, 0x2e, 0x63, 0x6f,		0x6d, 0x6f, 0x64, 0x6f, 0x2e, 0x6e, 0x65, 0x74,
				0x2f, 0x55, 0x54, 0x4e, 0x2d, 0x55, 0x53, 0x45,		0x52, 0x46, 0x69, 0x72, 0x73, 0x74, 0x2d, 0x48,
				0x61, 0x72, 0x64, 0x77, 0x61, 0x72, 0x65, 0x2e,		0x63, 0x72, 0x6c, 0x30, 0x71, 0x06, 0x08, 0x2b,
				0x06, 0x01, 0x05, 0x05, 0x07, 0x01, 0x01, 0x04,		0x65, 0x30, 0x63, 0x30, 0x3b, 0x06, 0x08, 0x2b,
				0x06, 0x01, 0x05, 0x05, 0x07, 0x30, 0x02, 0x86,		0x2f, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f,
				0x63, 0x72, 0x74, 0x2e, 0x63, 0x6f, 0x6d, 0x6f,		0x64, 0x6f, 0x63, 0x61, 0x2e, 0x63, 0x6f, 0x6d,
				0x2f, 0x55, 0x54, 0x4e, 0x41, 0x64, 0x64, 0x54,		0x72, 0x75, 0x73, 0x74, 0x53, 0x65, 0x72, 0x76,
				0x65, 0x72, 0x43, 0x41, 0x2e, 0x63, 0x72, 0x74,		0x30, 0x24, 0x06, 0x08, 0x2b, 0x06, 0x01, 0x05,
				0x05, 0x07, 0x30, 0x01, 0x86, 0x18, 0x68, 0x74,		0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x6f, 0x63, 0x73,
				0x70, 0x2e, 0x63, 0x6f, 0x6d, 0x6f, 0x64, 0x6f,		0x63, 0x61, 0x2e, 0x63, 0x6f, 0x6d, 0x30, 0x2f,
				0x06, 0x03, 0x55, 0x1d, 0x11, 0x04, 0x28, 0x30,		0x26, 0x82, 0x0f, 0x6c, 0x6f, 0x67, 0x69, 0x6e,
				0x2e, 0x79, 0x61, 0x68, 0x6f, 0x6f, 0x2e, 0x63,		0x6f, 0x6d, 0x82, 0x13, 0x77, 0x77, 0x77, 0x2e,
				0x6c, 0x6f, 0x67, 0x69, 0x6e, 0x2e, 0x79, 0x61,		0x68, 0x6f, 0x6f, 0x2e, 0x63, 0x6f, 0x6d, 0x30,
				0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7,		0x0d, 0x01, 0x01, 0x05, 0x05, 0x00, 0x03, 0x82,
				0x01, 0x01, 0x00, 0x3d, 0x57, 0xc9, 0x48, 0x24,		0x5c, 0xee, 0x64, 0x81, 0xf5, 0xae, 0xbe, 0x55,
				0x29, 0x16, 0xff, 0x2a, 0x2f, 0x84, 0xed, 0xd9,		0xf8, 0xa3, 0x03, 0xc8, 0x30, 0x66, 0xbb, 0xc8,
				0xd4, 0x81, 0x2d, 0x21, 0xf7, 0x08, 0xf7, 0xac,		0x96, 0x42, 0x9a, 0x41, 0x75, 0x7a, 0xba, 0x5d,
				0x10, 0x23, 0xcb, 0x92, 0x42, 0x61, 0xfa, 0x8a,		0xda, 0x6d, 0x65, 0x34, 0x19, 0xe5, 0xa9, 0xd6,
				0x2d, 0x13, 0x78, 0xd7, 0x81, 0x44, 0x92, 0xa9,		0x6e, 0x80, 0x63, 0x15, 0xcb, 0xfe, 0x35, 0x1f,
				0x02, 0xd1, 0x8a, 0x14, 0xb0, 0xa8, 0xcc, 0x94,		0x20, 0x3b, 0xa8, 0x1a, 0xf0, 0x5d, 0x36, 0x50,
				0xdb, 0x0d, 0xae, 0xe9, 0x64, 0xe4, 0xf6, 0x8d,		0x69, 0x7d, 0x30, 0xc8, 0x14, 0x17, 0x00, 0x4a,
				0xe5, 0xa6, 0x35, 0xfb, 0x7d, 0x0d, 0x22, 0x9d,		0x79, 0x76, 0x52, 0x2c, 0xbc, 0x97, 0x06, 0x88,
				0x9a, 0x15, 0xf4, 0x73, 0xe6, 0xf1, 0xf5, 0x98,		0xa5, 0xcd, 0x07, 0x44, 0x91, 0xb8, 0xa7, 0x68,
				0x67, 0x45, 0xd2, 0x72, 0x11, 0x60, 0xe2, 0x71,		0xb7, 0x50, 0x55, 0xe2, 0x8a, 0xa9, 0x0d, 0xd6,
				0x92, 0xee, 0x04, 0x2a, 0x8b, 0x30, 0xa0, 0xa2,		0x05, 0x46, 0x34, 0x6d, 0x92, 0xc6, 0x3b, 0xaa,
				0x4d, 0xa0, 0xd0, 0xab, 0x01, 0x19, 0x0a, 0x32,		0xb7, 0xe8, 0xe3, 0xcf, 0xf1, 0xd2, 0x97, 0x49,
				0x7b, 0xac, 0xa4, 0x97, 0xf7, 0xf0, 0x57, 0xae,		0x63, 0x77, 0x9a, 0x7f, 0x96, 0xda, 0x4d, 0xfd,
				0xbe, 0xdc, 0x07, 0x36, 0xe3, 0x25, 0xbd, 0x89,		0x79, 0x8e, 0x29, 0x12, 0x13, 0x8b, 0x88, 0x07,
				0xfb, 0x6b, 0xdb, 0xa4, 0xcd, 0xb3, 0x2d, 0x27,		0xe9, 0xd4, 0xca, 0x60, 0xd7, 0x85, 0x53, 0xfb,
				0x74, 0xc6, 0x5c, 0x35, 0x8c, 0x70, 0x1f, 0xf9,		0xb2, 0xb7, 0x92, 0x27, 0x20, 0xc7, 0x94, 0xd5,
				0x67, 0x14, 0x30 });

			X509Certificate Certificate = X509Certificate::LoadFromBlob(RawDataArray);
			AssertExtended::AreEqual(u8"C=US, S=UT, L=Salt Lake City, O=The USERTRUST Network, OU=http://www.usertrust.com, CN=UTN-USERFirst-Hardware", &Certificate.GetIssuer()[0]);
			AssertExtended::AreEqual(u8"C=US, PostalCode=38477, S=Florida, L=English, STREET=Sea Village 10, O=Google Ltd., OU=Tech Dept., OU=Hosted by GTI Group Corporation, OU=PlatinumSSL, CN=login.yahoo.com", &Certificate.GetSubject()[0]);
		}

		TEST_METHOD(ReadCertificateFromFile)
		{
			Elysium::Core::IO::FileStream TargetStream = Elysium::Core::IO::FileStream(u8"sample.crt", Elysium::Core::IO::FileMode::Create, Elysium::Core::IO::FileAccess::Write);
			Elysium::Core::Utf8String Input = u8"-----BEGIN CERTIFICATE-----"
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

			X509Certificate Certificate = X509Certificate::LoadFromFile(u8"sample.crt");
			AssertExtended::AreEqual(u8"C=US, S=UT, L=Salt Lake City, O=The USERTRUST Network, OU=http://www.usertrust.com, CN=UTN-USERFirst-Hardware", &Certificate.GetIssuer()[0]);
			AssertExtended::AreEqual(u8"C=US, PostalCode=38477, S=Florida, L=English, STREET=Sea Village 10, O=Google Ltd., OU=Tech Dept., OU=Hosted by GTI Group Corporation, OU=PlatinumSSL, CN=login.yahoo.com", &Certificate.GetSubject()[0]);
		}

		TEST_METHOD(ReadCertificateUsingDERDecoder)
		{
			// https://tools.ietf.org/html/rfc5280

			Elysium::Core::int32_t Count = 0;

			DERDecoder Decoder = DERDecoder();
			for (Elysium::Core::uint32_t StoreNameInt = (Elysium::Core::uint32_t)StoreName::AddressBook; StoreNameInt <= (Elysium::Core::uint32_t)StoreName::TrustedPublisher; StoreNameInt++)
			{
				Logger::WriteMessage("-- StoreName: ");
				Logger::WriteMessage((char*)&Elysium::Core::Template::Text::Convert<char8_t>::ToString(StoreNameInt)[0]);
				Logger::WriteMessage(" --\r\n");

				for (Elysium::Core::uint8_t StoreLocationInt = (Elysium::Core::uint8_t)StoreLocation::CurrentUser; StoreLocationInt != (Elysium::Core::uint8_t)StoreLocation::LocalMachine; StoreLocationInt++)
				{
					Logger::WriteMessage("-- StoreLocation: ");
					Logger::WriteMessage((char*)&Elysium::Core::Template::Text::Convert<char8_t>::ToString(StoreLocationInt)[0]);
					Logger::WriteMessage(" --\r\n");

					X509Store CurrentStore = X509Store(static_cast<StoreName>(StoreNameInt), static_cast<StoreLocation>(StoreLocationInt));
					CurrentStore.Open(OpenFlags::ReadOnly);

					for (Elysium::Core::size i = 0; i < CurrentStore.GetCertificates().GetCount(); i++)
					{
						const X509Certificate& Certificate = CurrentStore.GetCertificates()[i];
						const Array<byte> RawData = Certificate.GetRawCertData();
						MemoryStream InputStream = MemoryStream(RawData, 0, RawData.GetLength());

						Logger::WriteMessage("X509Certificate #");
						Logger::WriteMessage((char*)&Elysium::Core::Template::Text::Convert<char8_t>::ToString(Count)[0]);
						Logger::WriteMessage(":\r\n");

						Asn1Identifier Identifier = Asn1Identifier(Asn1TagClass::Universal, false, Asn1UniversalTag::EndOfContent, 0);
						Asn1Length Length = Asn1Length(0, 0);
						ReadCertificate(Decoder, InputStream, Identifier, Length);

						Logger::WriteMessage("\r\n");

						Count++;
					}
				}
			}
		}

	private:
		void ReadCertificate(IAsn1Decoder& Decoder, Stream& InputStream, Asn1Identifier& Identifier, Asn1Length& Length)
		{
			/*
			Certificate  ::=  SEQUENCE  {
				tbsCertificate       TBSCertificate,
				signatureAlgorithm   AlgorithmIdentifier,
				signatureValue       BIT STRING  }
			*/
			ReadHeader(Decoder, InputStream, Identifier, Length);
			if (Identifier.GetUniversalTag() != Asn1UniversalTag::Sequence)
			{
				Logger::WriteMessage("Error: CertificateSequence\r\n");
				throw InvalidDataException(u8"CertificateSequence");
			}

			ReadTbsCertificate(Decoder, InputStream, Identifier, Length);
			ReadSignatureAlgorithm(Decoder, InputStream, Identifier, Length);
			ReadSignatureValue(Decoder, InputStream, Identifier, Length);

			if (InputStream.GetPosition() != InputStream.GetLength())
			{
				Logger::WriteMessage("Error: Certificate still contains data\r\n");
				throw InvalidDataException(u8"Certificate still contains data");
			}
		}

		void ReadTbsCertificate(IAsn1Decoder& Decoder, Stream& InputStream, Asn1Identifier& Identifier, Asn1Length& Length)
		{
			/*
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
			*/
			ReadHeader(Decoder, InputStream, Identifier, Length);
			if (Identifier.GetUniversalTag() != Asn1UniversalTag::Sequence)
			{
				Logger::WriteMessage("Error: TbsCertificateSequence\r\n");
				throw InvalidDataException(u8"TbsCertificateSequence");
			}

			ReadVersion(Decoder, InputStream, Identifier, Length);
			ReadSerialNumber(Decoder, InputStream, Identifier, Length);
			ReadSignature(Decoder, InputStream, Identifier, Length);
			ReadIssuer(Decoder, InputStream, Identifier, Length);
			ReadValidity(Decoder, InputStream, Identifier, Length);
			ReadSubject(Decoder, InputStream, Identifier, Length);
			ReadSubjectPublicKeyInfo(Decoder, InputStream, Identifier, Length);
			ReadIssuerUniqueID(Decoder, InputStream, Identifier, Length);
			ReadSubjectUniqueID(Decoder, InputStream, Identifier, Length);
			ReadExtensions(Decoder, InputStream, Identifier, Length);
		}

		void ReadVersion(IAsn1Decoder& Decoder, Stream& InputStream, Asn1Identifier& Identifier, Asn1Length& Length)
		{
			/*
			Version  ::=  INTEGER  {  v1(0), v2(1), v3(2)  }
			*/
			const Elysium::Core::size PositionBeforeHeader = InputStream.GetPosition();
			ReadHeader(Decoder, InputStream, Identifier, Length);
			if (Identifier.GetUniversalTag() == Asn1UniversalTag::Integer)
			{	// version NOT explicitly defined ergo the next field would be a certificate's serial number
				Logger::WriteMessage("Version: V1\r\n");
				InputStream.SetPosition(PositionBeforeHeader);
			}
			else if (Identifier.GetTagClass() == Asn1TagClass::Context && Identifier.GetIsConstructed())
			{	// version explicitly defined
				Logger::WriteMessage("Version: V");
				Asn1Integer Version = Decoder.DecodeInteger(Identifier, Length, InputStream);

				// ToDo: simply adding 2 obviously isn't correct
				Logger::WriteMessage((char*)&Elysium::Core::Template::Text::Convert<char8_t>::ToString(Version.GetValue().GetSign() + 2)[0]);
				Logger::WriteMessage("\r\n");
			}
			else
			{
				Logger::WriteMessage("Error: Version\r\n");
				throw InvalidDataException(u8"Version");
			}
		}

		void ReadSerialNumber(IAsn1Decoder& Decoder, Stream& InputStream, Asn1Identifier& Identifier, Asn1Length& Length)
		{
			/*
			CertificateSerialNumber  ::=  INTEGER
			*/
			ReadHeader(Decoder, InputStream, Identifier, Length);
			if (Identifier.GetUniversalTag() != Asn1UniversalTag::Integer)
			{
				Logger::WriteMessage("Error: CertificateSerialNumber\r\n");
				throw InvalidDataException(u8"CertificateSerialNumber");
			}

			Logger::WriteMessage("SerialNumber: ");
			Asn1Integer SerialNumber = Decoder.DecodeInteger(Identifier, Length, InputStream);
			Logger::WriteMessage("\r\n");
		}

		void ReadSignature(IAsn1Decoder& Decoder, Stream& InputStream, Asn1Identifier& Identifier, Asn1Length& Length)
		{
			/*
			AlgorithmIdentifier  ::=  SEQUENCE  {
				algorithm               OBJECT IDENTIFIER,
				parameters              ANY DEFINED BY algorithm OPTIONAL  }
			*/
			ReadHeader(Decoder, InputStream, Identifier, Length);
			if (Identifier.GetUniversalTag() != Asn1UniversalTag::Sequence)
			{
				Logger::WriteMessage("Error: SignatureSequence\r\n");
				throw InvalidDataException(u8"SignatureSequence");
			}

			Logger::WriteMessage("Signature:\r\n");
			ReadHeader(Decoder, InputStream, Identifier, Length);
			if (Identifier.GetUniversalTag() != Asn1UniversalTag::ObjectIdentifier)
			{
				Logger::WriteMessage("Error: OID\r\n");
				throw InvalidDataException(u8"OID");
			}
			Asn1ObjectIdentifier ObjectIdentifier = Decoder.DecodeObjectIdentifier(Identifier, Length, InputStream);
			const Oid ObjectIdentifierValue = ObjectIdentifier.GetValue();

			Logger::WriteMessage("\t");
			Logger::WriteMessage((char*)&ObjectIdentifierValue.GetValue()[0]);
			Logger::WriteMessage(" - ");
			Logger::WriteMessage((char*)&ObjectIdentifierValue.GetFriendlyName()[0]);
			Logger::WriteMessage("\r\n");

			// depending on the algorithm used, different paramaters (or none) can occurre:
			// https://datatracker.ietf.org/doc/html/rfc4055
			// https://datatracker.ietf.org/doc/html/rfc3279
			// https://datatracker.ietf.org/doc/html/rfc4491

			ReadHeader(Decoder, InputStream, Identifier, Length);
			Logger::WriteMessage("\tSignatureParameters:\r\n");
			if (Identifier.GetUniversalTag() == Asn1UniversalTag::Null)
			{
				Logger::WriteMessage("\t\tnull\r\n");
			}
			else if (Identifier.GetUniversalTag() == Asn1UniversalTag::Sequence)
			{
				const Elysium::Core::size CurrentPositionParameters = InputStream.GetPosition();
				const Elysium::Core::size ParametersLength = Length.GetLength();
				while (InputStream.GetPosition() < CurrentPositionParameters + ParametersLength)
				{
					ReadHeader(Decoder, InputStream, Identifier, Length);
					if (Identifier.GetUniversalTag() == Asn1UniversalTag::Set)
					{
						ReadHeader(Decoder, InputStream, Identifier, Length);
						if (Identifier.GetUniversalTag() != Asn1UniversalTag::Sequence)
						{
							Logger::WriteMessage("Error: SignatureParametersSetSequence\r\n");
							throw InvalidDataException(u8"SignatureParametersSetSequence");
						}

						ReadSignatureAttributeTypeAndValue(Decoder, InputStream, Identifier, Length);
					}
					else
					{
						Logger::WriteMessage("Error: SignatureParametersSet\r\n");
						throw InvalidDataException(u8"SignatureParametersSet");
					}
				}
				Logger::WriteMessage("\r\n");

				if (InputStream.GetPosition() != CurrentPositionParameters + ParametersLength)
				{
					Logger::WriteMessage("Error: SignatureParametersLength\r\n");
					throw InvalidDataException(u8"SignatureParametersLength");
				}
			}
			else
			{
				Logger::WriteMessage("Error: SignatureParameters\r\n");
				throw InvalidDataException(u8"SignatureParameters");
			}
		}

		void ReadSignatureAttributeTypeAndValue(IAsn1Decoder& Decoder, Stream& InputStream, Asn1Identifier& Identifier, Asn1Length& Length)
		{
			ReadHeader(Decoder, InputStream, Identifier, Length);
			if (Identifier.GetUniversalTag() != Asn1UniversalTag::ObjectIdentifier)
			{
				Logger::WriteMessage("Error: SignatureArgumentType\r\n");
				throw InvalidDataException(u8"SignatureArgumentType");
			}
			try
			{
				Asn1ObjectIdentifier ObjectIdentifier = Decoder.DecodeObjectIdentifier(Identifier, Length, InputStream);
				const Oid ObjectIdentifierValue = ObjectIdentifier.GetValue();
				Logger::WriteMessage("\t\t");
				Logger::WriteMessage((char*)&ObjectIdentifierValue.GetValue()[0]);
				Logger::WriteMessage(" - ");
				Logger::WriteMessage((char*)&ObjectIdentifierValue.GetFriendlyName()[0]);
				Logger::WriteMessage(": ");
			}
			catch (const CryptographicException& ex)
			{
				Logger::WriteMessage("\t\t0.0.0.0 - UNKNOWN: ");

			}

			ReadHeader(Decoder, InputStream, Identifier, Length);
			if (Identifier.GetUniversalTag() == Asn1UniversalTag::PrintableString)
			{
				Asn1String PrintableString = Decoder.DecodeString(Identifier, Length, InputStream);
				const Elysium::Core::Container::VectorOfByte& Data = PrintableString.GetData();
				const Elysium::Core::Utf8String DataString = Elysium::Core::Text::Encoding::UTF8().GetString(&Data[0], Data.GetLength());

				Logger::WriteMessage((char*)&DataString[0]);
				Logger::WriteMessage("\r\n");
			}
			else
			{
				Logger::WriteMessage("Error: SignatureArgumentValue\r\n");
				throw InvalidDataException(u8"SignatureArgumentValue");
			}
		}

		void ReadIssuer(IAsn1Decoder& Decoder, Stream& InputStream, Asn1Identifier& Identifier, Asn1Length& Length)
		{
			/*
			Name ::= CHOICE { -- only one possibility for now --
				rdnSequence  RDNSequence }

			RDNSequence ::= SEQUENCE OF RelativeDistinguishedName

			RelativeDistinguishedName ::=
				SET SIZE (1..MAX) OF AttributeTypeAndValue

			AttributeTypeAndValue ::= SEQUENCE {
				type     AttributeType,
				value    AttributeValue }

			AttributeType ::= OBJECT IDENTIFIER

			AttributeValue ::= ANY -- DEFINED BY AttributeType
			*/
			const Elysium::Core::size InitialPosition = InputStream.GetPosition();
			ReadHeader(Decoder, InputStream, Identifier, Length);
			if (Identifier.GetUniversalTag() != Asn1UniversalTag::Sequence)
			{
				Logger::WriteMessage("Error: IssuerSequence\r\n");
				throw InvalidDataException(u8"IssuerSequence");
			}

			Logger::WriteMessage("Issuer:\r\n");
			const Elysium::Core::size CurrentPositionIssuer = InputStream.GetPosition();
			const Elysium::Core::size IssuerLength = Length.GetLength();
			while (InputStream.GetPosition() < CurrentPositionIssuer + IssuerLength)
			{
				ReadHeader(Decoder, InputStream, Identifier, Length);
				if (Identifier.GetUniversalTag() == Asn1UniversalTag::Set)
				{
					ReadHeader(Decoder, InputStream, Identifier, Length);
					if (Identifier.GetUniversalTag() == Asn1UniversalTag::Sequence)
					{
						const Elysium::Core::size CurrentPositionAttributeTypeAndValue = InputStream.GetPosition();
						const Elysium::Core::size AttributeTypeAndValueLength = Length.GetLength();
						while (InputStream.GetPosition() < CurrentPositionAttributeTypeAndValue + AttributeTypeAndValueLength)
						{
							ReadIssuerAttributeTypeAndValue(Decoder, InputStream, Identifier, Length);
						}

						if (InputStream.GetPosition() != CurrentPositionAttributeTypeAndValue + AttributeTypeAndValueLength)
						{
							Logger::WriteMessage("Error: IssuerSequenceSetSequenceLength\r\n");
							throw InvalidDataException(u8"IssuerSequenceSetSequenceLength");
						}
					}
					else
					{
						Logger::WriteMessage("Error: IssuerSequenceSetSequence\r\n");
						throw InvalidDataException(u8"IssuerSequenceSetSequence");
					}
				}
				else if (Identifier.GetUniversalTag() == Asn1UniversalTag::Sequence)
				{
					const Elysium::Core::size CurrentPositionAttributeTypeAndValue = InputStream.GetPosition();
					const Elysium::Core::size AttributeTypeAndValueLength = Length.GetLength();
					while (InputStream.GetPosition() < CurrentPositionAttributeTypeAndValue + AttributeTypeAndValueLength)
					{
						ReadIssuerAttributeTypeAndValue(Decoder, InputStream, Identifier, Length);
					}

					if (InputStream.GetPosition() != CurrentPositionAttributeTypeAndValue + AttributeTypeAndValueLength)
					{
						Logger::WriteMessage("Error: IssuerSequenceSequenceLength\r\n");
						throw InvalidDataException(u8"IssuerSequenceSequenceLength");
					}
				}
				else if(Identifier.GetUniversalTag() == Asn1UniversalTag::UTCTime)
				{	// no issuer > we've already landed on validity > reset position and return
					InputStream.SetPosition(InitialPosition);
					Logger::WriteMessage("\tnone\r\n");
					return;
				}
				else
				{
					Logger::WriteMessage("Error: IssuerSequenceSet\r\n");
					throw InvalidDataException(u8"IssuerSequenceSet");
				}
			}

			if (InputStream.GetPosition() != CurrentPositionIssuer + IssuerLength)
			{
				Logger::WriteMessage("Error: IssuerSequenceLength\r\n");
				throw InvalidDataException(u8"IssuerSequenceLength");
			}
		}

		void ReadIssuerAttributeTypeAndValue(IAsn1Decoder& Decoder, Stream& InputStream, Asn1Identifier& Identifier, Asn1Length& Length)
		{
			ReadHeader(Decoder, InputStream, Identifier, Length);
			if (Identifier.GetUniversalTag() != Asn1UniversalTag::ObjectIdentifier)
			{
				Logger::WriteMessage("Error: IssuerArgumentType\r\n");
				throw InvalidDataException(u8"IssuerArgumentType");
			}
			Asn1ObjectIdentifier ObjectIdentifier = Decoder.DecodeObjectIdentifier(Identifier, Length, InputStream);
			const Oid ObjectIdentifierValue = ObjectIdentifier.GetValue();
			Logger::WriteMessage("\t");
			Logger::WriteMessage((char*)&ObjectIdentifierValue.GetValue()[0]);
			Logger::WriteMessage(" - ");
			Logger::WriteMessage((char*)&ObjectIdentifierValue.GetFriendlyName()[0]);
			Logger::WriteMessage(": ");

			ReadHeader(Decoder, InputStream, Identifier, Length);
			if (Identifier.GetUniversalTag() == Asn1UniversalTag::PrintableString)
			{
				Asn1String PrintableString = Decoder.DecodeString(Identifier, Length, InputStream);
				const Elysium::Core::Container::VectorOfByte& Data = PrintableString.GetData();
				const Elysium::Core::Utf8String DataString = Elysium::Core::Text::Encoding::UTF8().GetString(&Data[0], Data.GetLength());

				Logger::WriteMessage((char*)&DataString[0]);
				Logger::WriteMessage("\r\n");
			}
			else if (Identifier.GetUniversalTag() == Asn1UniversalTag::IA5String)
			{
				Asn1String IA5String = Decoder.DecodeString(Identifier, Length, InputStream);
				const Elysium::Core::Container::VectorOfByte& Data = IA5String.GetData();
				const Elysium::Core::Utf8String DataString = Elysium::Core::Text::Encoding::UTF8().GetString(&Data[0], Data.GetLength());

				Logger::WriteMessage((char*)&DataString[0]);
				Logger::WriteMessage("\r\n");
			}
			else if (Identifier.GetUniversalTag() == Asn1UniversalTag::UTF8String)
			{
				Asn1String Utf8String = Decoder.DecodeString(Identifier, Length, InputStream);
				const Elysium::Core::Container::VectorOfByte& Data = Utf8String.GetData();
				const Elysium::Core::Utf8String DataString = Elysium::Core::Text::Encoding::UTF8().GetString(&Data[0], Data.GetLength());

				Logger::WriteMessage((char*)&DataString[0]);
				Logger::WriteMessage("\r\n");
			}
			else
			{
				Logger::WriteMessage("Error: IssuerArgumentValue\r\n");
				throw InvalidDataException(u8"IssuerArgumentValue");
			}
		}

		void ReadValidity(IAsn1Decoder& Decoder, Stream& InputStream, Asn1Identifier& Identifier, Asn1Length& Length)
		{
			/*
			Validity ::= SEQUENCE {
				notBefore      Time,
				notAfter       Time }
			*/
			ReadHeader(Decoder, InputStream, Identifier, Length);
			if (Identifier.GetUniversalTag() != Asn1UniversalTag::Sequence)
			{
				Logger::WriteMessage("Error: ValiditySequence\r\n");
				throw InvalidDataException(u8"ValiditySequence");
			}
			Logger::WriteMessage("Validity:\r\n");

			ReadHeader(Decoder, InputStream, Identifier, Length);
			if (Identifier.GetUniversalTag() != Asn1UniversalTag::UTCTime)
			{
				Logger::WriteMessage("Error: ValidityNotBefore\r\n");
				throw InvalidDataException(u8"ValidityNotBefore");
			}
			Asn1DateTime ValidityNotBefore = Decoder.DecodeDateTime(Identifier, Length, InputStream);
			const Elysium::Core::DateTime& ValidityNotBeforeValue = ValidityNotBefore.GetValue();
			Logger::WriteMessage("\tNotBefore: ");
			Logger::WriteMessage((char*)&Elysium::Core::Template::Text::Convert<char8_t>::ToString(ValidityNotBeforeValue.GetYear())[0]);
			Logger::WriteMessage("-");
			Logger::WriteMessage((char*)&Elysium::Core::Template::Text::Convert<char8_t>::ToString(ValidityNotBeforeValue.GetMonth())[0]);
			Logger::WriteMessage("-");
			Logger::WriteMessage((char*)&Elysium::Core::Template::Text::Convert<char8_t>::ToString(ValidityNotBeforeValue.GetDay())[0]);
			Logger::WriteMessage(" ");
			Logger::WriteMessage((char*)&Elysium::Core::Template::Text::Convert<char8_t>::ToString(ValidityNotBeforeValue.GetHour())[0]);
			Logger::WriteMessage(":");
			Logger::WriteMessage((char*)&Elysium::Core::Template::Text::Convert<char8_t>::ToString(ValidityNotBeforeValue.GetMinute())[0]);
			Logger::WriteMessage(":");
			Logger::WriteMessage((char*)&Elysium::Core::Template::Text::Convert<char8_t>::ToString(ValidityNotBeforeValue.GetSecond())[0]);
			Logger::WriteMessage(" UTC\r\n");

			ReadHeader(Decoder, InputStream, Identifier, Length);
			if (Identifier.GetUniversalTag() != Asn1UniversalTag::UTCTime)
			{
				Logger::WriteMessage("Error: ValidityNotAfter\r\n");
				throw InvalidDataException(u8"ValidityNotAfter");
			}
			Asn1DateTime ValidityNotAfter = Decoder.DecodeDateTime(Identifier, Length, InputStream);
			const Elysium::Core::DateTime& ValidityNotAfterValue = ValidityNotAfter.GetValue();
			Logger::WriteMessage("\tNotAfter: ");
			Logger::WriteMessage((char*)&Elysium::Core::Template::Text::Convert<char8_t>::ToString(ValidityNotAfterValue.GetYear())[0]);
			Logger::WriteMessage("-");
			Logger::WriteMessage((char*)&Elysium::Core::Template::Text::Convert<char8_t>::ToString(ValidityNotAfterValue.GetMonth())[0]);
			Logger::WriteMessage("-");
			Logger::WriteMessage((char*)&Elysium::Core::Template::Text::Convert<char8_t>::ToString(ValidityNotAfterValue.GetDay())[0]);
			Logger::WriteMessage(" ");
			Logger::WriteMessage((char*)&Elysium::Core::Template::Text::Convert<char8_t>::ToString(ValidityNotAfterValue.GetHour())[0]);
			Logger::WriteMessage(":");
			Logger::WriteMessage((char*)&Elysium::Core::Template::Text::Convert<char8_t>::ToString(ValidityNotAfterValue.GetMinute())[0]);
			Logger::WriteMessage(":");
			Logger::WriteMessage((char*)&Elysium::Core::Template::Text::Convert<char8_t>::ToString(ValidityNotAfterValue.GetSecond())[0]);
			Logger::WriteMessage(" UTC\r\n");
		}

		void ReadSubject(IAsn1Decoder& Decoder, Stream& InputStream, Asn1Identifier& Identifier, Asn1Length& Length)
		{
			/*
			Name ::= CHOICE { -- only one possibility for now --
				rdnSequence  RDNSequence }

			RDNSequence ::= SEQUENCE OF RelativeDistinguishedName

			RelativeDistinguishedName ::=
				SET SIZE (1..MAX) OF AttributeTypeAndValue

			AttributeTypeAndValue ::= SEQUENCE {
				type     AttributeType,
				value    AttributeValue }

			AttributeType ::= OBJECT IDENTIFIER

			AttributeValue ::= ANY -- DEFINED BY AttributeType
			*/
			ReadHeader(Decoder, InputStream, Identifier, Length);
			if (Identifier.GetUniversalTag() != Asn1UniversalTag::Sequence)
			{
				Logger::WriteMessage("Error: SubjectSequence\r\n");
				throw InvalidDataException(u8"SubjectSequence");
			}
			Logger::WriteMessage("Subject:\r\n");

			const Elysium::Core::size CurrentPositionSubject = InputStream.GetPosition();
			const Elysium::Core::size SubjectLength = Length.GetLength();
			while (InputStream.GetPosition() < CurrentPositionSubject + SubjectLength)
			{
				ReadHeader(Decoder, InputStream, Identifier, Length);
				if (Identifier.GetUniversalTag() == Asn1UniversalTag::Set)
				{
					ReadHeader(Decoder, InputStream, Identifier, Length);
					if (Identifier.GetUniversalTag() == Asn1UniversalTag::Sequence)
					{
						const Elysium::Core::size CurrentPositionAttributeTypeAndValue = InputStream.GetPosition();
						const Elysium::Core::size AttributeTypeAndValueLength = Length.GetLength();
						while (InputStream.GetPosition() < CurrentPositionAttributeTypeAndValue + AttributeTypeAndValueLength)
						{
							ReadSubjectAttributeTypeAndValue(Decoder, InputStream, Identifier, Length);
						}

						if (InputStream.GetPosition() != CurrentPositionAttributeTypeAndValue + AttributeTypeAndValueLength)
						{
							Logger::WriteMessage("Error: SubjectSequenceSetSequenceLength\r\n");
							throw InvalidDataException(u8"SubjectSequenceSetSequenceLength");
						}
					}
					else
					{
						Logger::WriteMessage("Error: SubjectSequenceSetSequence\r\n");
						throw InvalidDataException(u8"SubjectSequenceSetSequence");
					}
				}
				else
				{
					Logger::WriteMessage("Error: SubjectSequenceSet\r\n");
					throw InvalidDataException(u8"SubjectSequenceSet");
				}
			}

			if (InputStream.GetPosition() != CurrentPositionSubject + SubjectLength)
			{
				Logger::WriteMessage("Error: SubjectSequenceLength\r\n");
				throw InvalidDataException(u8"SubjectSequenceLength");
			}
		}

		void ReadSubjectAttributeTypeAndValue(IAsn1Decoder& Decoder, Stream& InputStream, Asn1Identifier& Identifier, Asn1Length& Length)
		{
			ReadHeader(Decoder, InputStream, Identifier, Length);
			if (Identifier.GetUniversalTag() != Asn1UniversalTag::ObjectIdentifier)
			{
				Logger::WriteMessage("Error: SubjectArgumentType\r\n");
				throw InvalidDataException(u8"SubjectArgumentType");
			}
			try
			{
				Asn1ObjectIdentifier ObjectIdentifier = Decoder.DecodeObjectIdentifier(Identifier, Length, InputStream);
				const Oid ObjectIdentifierValue = ObjectIdentifier.GetValue();
				Logger::WriteMessage("\t");
				Logger::WriteMessage((char*)&ObjectIdentifierValue.GetValue()[0]);
				Logger::WriteMessage(" - ");
				Logger::WriteMessage((char*)&ObjectIdentifierValue.GetFriendlyName()[0]);
				Logger::WriteMessage(": ");
			}
			catch (const CryptographicException& ex)
			{
				Logger::WriteMessage("\t0.0.0.0 - UNKNOWN: ");

			}

			ReadHeader(Decoder, InputStream, Identifier, Length);
			if (Identifier.GetUniversalTag() == Asn1UniversalTag::PrintableString)
			{
				Asn1String PrintableString = Decoder.DecodeString(Identifier, Length, InputStream);
				const Elysium::Core::Container::VectorOfByte& Data = PrintableString.GetData();
				const Elysium::Core::Utf8String DataString = Elysium::Core::Text::Encoding::UTF8().GetString(&Data[0], Data.GetLength());

				Logger::WriteMessage((char*)&DataString[0]);
				Logger::WriteMessage("\r\n");
			}
			else if (Identifier.GetUniversalTag() == Asn1UniversalTag::IA5String)
			{
				Asn1String IA5String = Decoder.DecodeString(Identifier, Length, InputStream);
				const Elysium::Core::Container::VectorOfByte& Data = IA5String.GetData();
				const Elysium::Core::Utf8String DataString = Elysium::Core::Text::Encoding::UTF8().GetString(&Data[0], Data.GetLength());

				Logger::WriteMessage((char*)&DataString[0]);
				Logger::WriteMessage("\r\n");
			}
			else if (Identifier.GetUniversalTag() == Asn1UniversalTag::UTF8String)
			{
				Asn1String Utf8String = Decoder.DecodeString(Identifier, Length, InputStream);
				const Elysium::Core::Container::VectorOfByte& Data = Utf8String.GetData();
				const Elysium::Core::Utf8String DataString = Elysium::Core::Text::Encoding::UTF8().GetString(&Data[0], Data.GetLength());

				Logger::WriteMessage((char*)&DataString[0]);
				Logger::WriteMessage("\r\n");
			}
			else
			{
				Logger::WriteMessage("Error: SubjectArgumentValue\r\n");
				throw InvalidDataException(u8"SubjectArgumentValue");
			}
		}

		void ReadSubjectPublicKeyInfo(IAsn1Decoder& Decoder, Stream& InputStream, Asn1Identifier& Identifier, Asn1Length& Length)
		{
			/*
			SubjectPublicKeyInfo  ::=  SEQUENCE  {
				algorithm            AlgorithmIdentifier,
				subjectPublicKey     BIT STRING  }
			*/
			ReadHeader(Decoder, InputStream, Identifier, Length);
			if (Identifier.GetUniversalTag() != Asn1UniversalTag::Sequence)
			{
				Logger::WriteMessage("Error: SubjectPublicKeyInfoSequence\r\n");
				throw InvalidDataException(u8"SubjectPublicKeyInfoSequence");
			}
			Logger::WriteMessage("SubjectPublicKeyInfo:\r\n");

			const Elysium::Core::size CurrentPositionSubjectPublicKeyInfo = InputStream.GetPosition();
			const Elysium::Core::size SubjectPublicKeyInfoLength = Length.GetLength();
			while (InputStream.GetPosition() < CurrentPositionSubjectPublicKeyInfo + SubjectPublicKeyInfoLength)
			{
				const Oid SignatureHashAlgorithm = ReadSubjectPublicKeyInfoAlgorithm(Decoder, InputStream, Identifier, Length);

				ReadHeader(Decoder, InputStream, Identifier, Length);
				if (Identifier.GetUniversalTag() != Asn1UniversalTag::BitString)
				{
					Logger::WriteMessage("Error: SubjectPublicKeyInfoSequenceSequenceBitString\r\n");
					throw InvalidDataException(u8"SubjectPublicKeyInfoSequenceSequenceBitString");
				}
				Asn1ByteArray BitString = Decoder.DecodeByteArray(Identifier, Length, InputStream);

				if (SignatureHashAlgorithm.GetFriendlyName() == u8"RSA")
				{	// 1.2.840.113549.1.1.1 - RSA
					const Elysium::Core::Collections::Template::Array<Elysium::Core::byte>& Data = BitString.GetData();

					Elysium::Core::size Index = 0;
					const Elysium::Core::uint8_t NumberOfUnusedBits = Data[Index++];
					Asn1Identifier PublicKeySequenceIdentifier = Decoder.DecodeIdentifier(Data, Index, Data.GetLength() - Index);
					Index += PublicKeySequenceIdentifier.GetEncodedLength();
					Asn1Length PublicKeySequenceLength = Decoder.DecodeLength(Data, Index, Data.GetLength() - Index);
					Index += PublicKeySequenceLength.GetEncodedLength();
					if (PublicKeySequenceIdentifier.GetUniversalTag() != Asn1UniversalTag::Sequence)
					{
						Logger::WriteMessage("Error: PublicKeySequenceIdentifier\r\n");
						throw InvalidDataException(u8"PublicKeySequenceIdentifier");
					}

					Asn1Identifier PublicKeyIdentifier = Decoder.DecodeIdentifier(Data, Index, Data.GetLength() - Index);
					Index += PublicKeyIdentifier.GetEncodedLength();
					Asn1Length PublicKeyLength = Decoder.DecodeLength(Data, Index, Data.GetLength() - Index);
					Index += PublicKeyLength.GetEncodedLength();
					if (PublicKeyIdentifier.GetUniversalTag() != Asn1UniversalTag::Integer)
					{
						Logger::WriteMessage("Error: PublicKeyIdentifier\r\n");
						throw InvalidDataException(u8"PublicKeyIdentifier");
					}
					Asn1Integer PublicKey = Decoder.DecodeInteger(PublicKeyIdentifier, PublicKeyLength, Data, Index, Data.GetLength() - Index);
					Index += PublicKeyLength.GetLength();

					Asn1Identifier SomeIntegerIdentifier = Decoder.DecodeIdentifier(Data, Index, Data.GetLength() - Index);
					Index += SomeIntegerIdentifier.GetEncodedLength();
					Asn1Length SomeIntegerLength = Decoder.DecodeLength(Data, Index, Data.GetLength() - Index);
					Index += SomeIntegerLength.GetEncodedLength();
					if (SomeIntegerIdentifier.GetUniversalTag() != Asn1UniversalTag::Integer)
					{
						Logger::WriteMessage("Error: SomeIntegerIdentifier\r\n");
						throw InvalidDataException(u8"SomeIntegerIdentifier");
					}
					Asn1Integer SomeInteger = Decoder.DecodeInteger(PublicKeyIdentifier, PublicKeyLength, Data, Index, Data.GetLength() - Index);
					Index += PublicKeyLength.GetLength();

					Logger::WriteMessage("\tPublicKey (RSA) length: ");
					// ToDo: simply subtracting one is certainly not goind to be correct (also NumberOfUnusedBits)!
					Logger::WriteMessage((char*)&Elysium::Core::Template::Text::Convert<char8_t>::ToString((PublicKeyLength.GetLength() - 1) * 8)[0]);
					Logger::WriteMessage(" bits\r\n");
				}
				else if (SignatureHashAlgorithm.GetFriendlyName() == u8"ECC")
				{	// 1.2.840.10045.2.1 - ECC
					const Elysium::Core::Collections::Template::Array<Elysium::Core::byte>& Data = BitString.GetData();

					Elysium::Core::size Index = 0;
					Asn1Identifier EndOfContentIdentifier = Decoder.DecodeIdentifier(Data, Index, Data.GetLength() - Index);
					Index += EndOfContentIdentifier.GetEncodedLength();
					if (EndOfContentIdentifier.GetUniversalTag() != Asn1UniversalTag::EndOfContent)
					{
						Logger::WriteMessage("Error: PublicKeyEndOfContentIdentifier\r\n");
						throw InvalidDataException(u8"PublicKeyEndOfContentIdentifier");
					}

					Asn1Identifier OctetStringIdentifier = Decoder.DecodeIdentifier(Data, Index, Data.GetLength() - Index);
					Index += OctetStringIdentifier.GetEncodedLength();
					Asn1Length OctetStringLength = Decoder.DecodeLength(Data, Index, Data.GetLength() - Index);
					Index += OctetStringLength.GetEncodedLength();
					if (OctetStringIdentifier.GetUniversalTag() != Asn1UniversalTag::OctetString)
					{
						Logger::WriteMessage("Error: OctetStringIdentifier\r\n");
						throw InvalidDataException(u8"OctetStringIdentifier");
					}
					/*
					The first octet of the OCTET STRING indicates whether the key is
					compressed or uncompressed.  The uncompressed form is indicated
					by 0x04 and the compressed form is indicated by either 0x02 or
					0x03 (see 2.3.3 in [SEC1]).  The public key MUST be rejected if
					any other value is included in the first octet.
					*/
					//const Elysium::Core::uint8_t CompressedB = Data[Index++];
					//const Elysium::Core::uint8_t CompressedE = Data[Data.GetLength() - 1];

					// ToDo: read public key (length)
					throw 1;
				}
				else
				{
					throw 1;
				}
			}

			if (InputStream.GetPosition() != CurrentPositionSubjectPublicKeyInfo + SubjectPublicKeyInfoLength)
			{
				Logger::WriteMessage("Error: SubjectPublicKeyInfoSequenceLength\r\n");
				throw InvalidDataException(u8"SubjectPublicKeyInfoSequenceLength");
			}
		}

		const Oid ReadSubjectPublicKeyInfoAlgorithm(IAsn1Decoder& Decoder, Stream& InputStream, Asn1Identifier& Identifier, Asn1Length& Length)
		{
			/*
			AlgorithmIdentifier  ::=  SEQUENCE  {
				algorithm               OBJECT IDENTIFIER,
				parameters              ANY DEFINED BY algorithm OPTIONAL  }
			*/
			ReadHeader(Decoder, InputStream, Identifier, Length);
			if (Identifier.GetUniversalTag() != Asn1UniversalTag::Sequence)
			{
				Logger::WriteMessage("Error: SubjectPublicKeyInfoSequenceSequence\r\n");
				throw InvalidDataException(u8"SubjectPublicKeyInfoSequenceSequence");
			}

			const Elysium::Core::size CurrentPositionSubjectPublicKeyInfoSequenceSequence = InputStream.GetPosition();
			const Elysium::Core::size SubjectPublicKeyInfoSequenceSequenceLength = Length.GetLength();

			// algorithm
			ReadHeader(Decoder, InputStream, Identifier, Length);
			if (Identifier.GetUniversalTag() != Asn1UniversalTag::ObjectIdentifier)
			{
				Logger::WriteMessage("Error: OID\r\n");
				throw InvalidDataException(u8"OID");
			}
			Asn1ObjectIdentifier ObjectIdentifier = Decoder.DecodeObjectIdentifier(Identifier, Length, InputStream);
			const Oid ObjectIdentifierValue = ObjectIdentifier.GetValue();

			Logger::WriteMessage("\t");
			Logger::WriteMessage((char*)&ObjectIdentifierValue.GetValue()[0]);
			Logger::WriteMessage(" - ");
			Logger::WriteMessage((char*)&ObjectIdentifierValue.GetFriendlyName()[0]);
			Logger::WriteMessage("\r\n");

			// parameters
			ReadHeader(Decoder, InputStream, Identifier, Length);
			Logger::WriteMessage("\tParameters:\r\n");
			if (Identifier.GetUniversalTag() == Asn1UniversalTag::Null)
			{
				Logger::WriteMessage("\t\tnull\r\n");
			}
			else if (Identifier.GetUniversalTag() == Asn1UniversalTag::ObjectIdentifier)
			{
				Asn1ObjectIdentifier ObjectIdentifier = Decoder.DecodeObjectIdentifier(Identifier, Length, InputStream);
				const Oid ObjectIdentifierValue = ObjectIdentifier.GetValue();

				Logger::WriteMessage("\t\t");
				Logger::WriteMessage((char*)&ObjectIdentifierValue.GetValue()[0]);
				Logger::WriteMessage(" - ");
				Logger::WriteMessage((char*)&ObjectIdentifierValue.GetFriendlyName()[0]);
				Logger::WriteMessage("\r\n");
			}
			else
			{
				Logger::WriteMessage("Error: SubjectPublicKeyInfoAlgorithmParameters\r\n");
				throw InvalidDataException(u8"SubjectPublicKeyInfoAlgorithmParameters");
			}

			if (InputStream.GetPosition() != CurrentPositionSubjectPublicKeyInfoSequenceSequence + SubjectPublicKeyInfoSequenceSequenceLength)
			{
				Logger::WriteMessage("Error: SubjectPublicKeyInfoSequenceSequenceLength\r\n");
				throw InvalidDataException(u8"SubjectPublicKeyInfoSequenceSequenceLength");
			}

			return ObjectIdentifierValue;
		}

		void ReadIssuerUniqueID(IAsn1Decoder& Decoder, Stream& InputStream, Asn1Identifier& Identifier, Asn1Length& Length)
		{
			/*
			issuerUniqueID  [1]  IMPLICIT UniqueIdentifier OPTIONAL,
									-- If present, version MUST be v2 or v3

			UniqueIdentifier  ::=  BIT STRING
			*/
			const Elysium::Core::size InitialPosition = InputStream.GetPosition();
			ReadHeader(Decoder, InputStream, Identifier, Length);
			if (Identifier.GetUniversalTag() == Asn1UniversalTag::BitString)
			{
				Asn1ByteArray BitString = Decoder.DecodeByteArray(Identifier, Length, InputStream);
				Logger::WriteMessage("IssuerUniqueID:\r\n");
				Logger::WriteMessage("\tLength: ");
				Logger::WriteMessage((char*)&Elysium::Core::Template::Text::Convert<char8_t>::ToString(BitString.GetData().GetLength())[0]);
				Logger::WriteMessage("\r\n\tValue: ");
				//Logger::WriteMessage((char*)&BitString.GetValue()[0]);
				Logger::WriteMessage("\r\n");
			}
			else
			{	// optional > reset position
				InputStream.SetPosition(InitialPosition);
			}
		}

		void ReadSubjectUniqueID(IAsn1Decoder& Decoder, Stream& InputStream, Asn1Identifier& Identifier, Asn1Length& Length)
		{
			/*
			subjectUniqueID [2]  IMPLICIT UniqueIdentifier OPTIONAL,
									-- If present, version MUST be v2 or v3

			UniqueIdentifier  ::=  BIT STRING
			*/
			const Elysium::Core::size InitialPosition = InputStream.GetPosition();
			ReadHeader(Decoder, InputStream, Identifier, Length);
			if (Identifier.GetUniversalTag() == Asn1UniversalTag::BitString)
			{
				Logger::WriteMessage("SubjectUniqueID: ");
				Asn1String BitString = Decoder.DecodeString(Identifier, Length, InputStream);
				const Elysium::Core::Container::VectorOfByte& Data = BitString.GetData();
				const Elysium::Core::Utf8String DataString = Elysium::Core::Text::Encoding::UTF8().GetString(&Data[0], Data.GetLength());

				Logger::WriteMessage((char*)&DataString[0]);
				Logger::WriteMessage("\r\n");
			}
			else
			{	// optional > reset position
				InputStream.SetPosition(InitialPosition);
			}
		}

		void ReadExtensions(IAsn1Decoder& Decoder, Stream& InputStream, Asn1Identifier& Identifier, Asn1Length& Length)
		{
			/*
			extensions      [3]  EXPLICIT Extensions OPTIONAL
									-- If present, version MUST be v3

			Extensions  ::=  SEQUENCE SIZE (1..MAX) OF Extension

			Extension  ::=  SEQUENCE  {
				extnID      OBJECT IDENTIFIER,
				critical    BOOLEAN DEFAULT FALSE,
				extnValue   OCTET STRING
							-- contains the DER encoding of an ASN.1 value
							-- corresponding to the extension type identified
							-- by extnID
				}
			*/
			const Elysium::Core::size InitialPosition = InputStream.GetPosition();
			ReadHeader(Decoder, InputStream, Identifier, Length);
			if (Identifier.GetUniversalTag() != Asn1UniversalTag::Sequence)
			{
				Logger::WriteMessage("Error: Extensions\r\n");
				throw InvalidDataException(u8"Extensions");
			}
			Logger::WriteMessage("Extensions:\r\n");

			const Elysium::Core::size CurrentPositionExtension = InputStream.GetPosition();
			const Elysium::Core::size ExtensionLength = Length.GetLength();
			while (InputStream.GetPosition() < CurrentPositionExtension + ExtensionLength)
			{
				ReadHeader(Decoder, InputStream, Identifier, Length);
				if (Identifier.GetUniversalTag() != Asn1UniversalTag::ObjectIdentifier)
				{
					Logger::WriteMessage("Error: ExtensionOid\r\n");
					throw InvalidDataException(u8"ExtensionOid");
				}
				Asn1ObjectIdentifier Oid = Decoder.DecodeObjectIdentifier(Identifier, Length, InputStream);

				const Elysium::Core::size CurrentPositionBooleanExtension = InputStream.GetPosition();
				ReadHeader(Decoder, InputStream, Identifier, Length);
				if (Identifier.GetUniversalTag() == Asn1UniversalTag::Boolean)
				{
					Asn1Boolean Boolean = Decoder.DecodeBoolean(Identifier, Length, InputStream);

					ReadHeader(Decoder, InputStream, Identifier, Length);
					if (Identifier.GetUniversalTag() == Asn1UniversalTag::BitString)
					{
						Asn1String BitString = Decoder.DecodeString(Identifier, Length, InputStream);
					}
					else
					{
						Logger::WriteMessage("Error: ExtensionOctetString\r\n");
						throw InvalidDataException(u8"ExtensionOctetString");
					}

					Logger::WriteMessage("\tbla\r\n");
				}
				else
				{	// optional > reset position
					InputStream.SetPosition(InitialPosition);
					return;
				}
			}

			if (InputStream.GetPosition() != CurrentPositionExtension + ExtensionLength)
			{
				Logger::WriteMessage("Error: ExtensionLength\r\n");
				throw InvalidDataException(u8"ExtensionLength");
			}
		}

		void ReadSignatureAlgorithm(IAsn1Decoder& Decoder, Stream& InputStream, Asn1Identifier& Identifier, Asn1Length& Length)
		{
			/*
			AlgorithmIdentifier  ::=  SEQUENCE  {
				algorithm               OBJECT IDENTIFIER,
				parameters              ANY DEFINED BY algorithm OPTIONAL  }
			*/
			ReadHeader(Decoder, InputStream, Identifier, Length);
			if (Identifier.GetUniversalTag() != Asn1UniversalTag::Sequence)
			{
				Logger::WriteMessage("Error: SignatureAlgorithmSequence\r\n");
				throw InvalidDataException(u8"SignatureAlgorithmSequence");
			}
			Logger::WriteMessage("SignatureAlgorithm:\r\n");

			const Elysium::Core::size CurrentPositionSignatureAlgorithm = InputStream.GetPosition();
			const Elysium::Core::size SignatureAlgorithmLength = Length.GetLength();
			while (InputStream.GetPosition() < CurrentPositionSignatureAlgorithm + SignatureAlgorithmLength)
			{
				InputStream.ReadByte();
			}

			if (InputStream.GetPosition() != CurrentPositionSignatureAlgorithm + SignatureAlgorithmLength)
			{
				Logger::WriteMessage("Error: SignatureAlgorithmLength\r\n");
				throw InvalidDataException(u8"SignatureAlgorithmLength");
			}
		}

		void ReadSignatureValue(IAsn1Decoder& Decoder, Stream& InputStream, Asn1Identifier& Identifier, Asn1Length& Length)
		{
			ReadHeader(Decoder, InputStream, Identifier, Length);
			if (Identifier.GetUniversalTag() != Asn1UniversalTag::BitString)
			{
				Logger::WriteMessage("Error: SignatureValue\r\n");
				throw InvalidDataException(u8"SignatureValue");
			}
			Asn1ByteArray Signature = Decoder.DecodeByteArray(Identifier, Length, InputStream);

			Logger::WriteMessage("SignatureValue: ");
			//Logger::WriteMessage((char*)&Signature.GetValue()[0]);
			Logger::WriteMessage("\r\n");
		}

		void ReadHeader(IAsn1Decoder& Decoder, Stream& InputStream, Asn1Identifier& Identifier, Asn1Length& Length)
		{
			Identifier = Decoder.DecodeIdentifier(InputStream);
			Length = Decoder.DecodeLength(InputStream);
		}
	};
}
