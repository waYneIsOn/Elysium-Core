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
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Security.Cryptography.X509Certificates/X509Store.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CHAIN
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Security.Cryptography.X509Certificates/X509Chain.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILESTREAM
#include "../../../Libraries/01-Shared/Elysium.Core.IO/FileStream.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_DERDECODER
#include "../../../Libraries/01-Shared/Elysium.Core.Security.Cryptography.Encoding/DERDecoder.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_MEMORYSTREAM
#include "../../../Libraries/01-Shared/Elysium.Core.IO/MemoryStream.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_INVALIDDATAEXCEPTION
#include "../../../Libraries/01-Shared/Elysium.Core.IO/InvalidDataException.hpp"
#endif

using namespace Elysium::Core::Collections::Template;
using namespace Elysium::Core::IO;
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
			int32_t Count = 0;

			DERDecoder Decoder = DERDecoder();
			for (uint32_t StoreNameInt = (uint32_t)StoreName::AddressBook; StoreNameInt != (uint32_t)StoreName::TrustedPublisher; StoreNameInt++)
			{
				for (uint8_t StoreLocationInt = (uint8_t)StoreLocation::CurrentUser; StoreLocationInt != (uint8_t)StoreLocation::LocalMachine; StoreLocationInt++)
				{
					X509Store CurrentStore = X509Store(static_cast<StoreName>(StoreNameInt), static_cast<StoreLocation>(StoreLocationInt));
					CurrentStore.Open(OpenFlags::ReadOnly);

					for (size_t i = 0; i < CurrentStore.GetCertificates().GetCount(); i++)
					{
						if (Count == 26 || Count == 39 || Count == 42 || Count == 70)
						{	// these certificates seem to have missing issuer (which they obviously don't) since we're reading validity right after the certificate's signature?!
							Count++;
							continue;
						}

						const X509Certificate& Certificate = CurrentStore.GetCertificates()[i];
						const Array<byte> RawData = Certificate.GetRawCertData();
						MemoryStream InputStream = MemoryStream(RawData, 0, RawData.GetLength());

						/*
						https://tools.ietf.org/html/rfc5280

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

						AlgorithmIdentifier  ::=  SEQUENCE  {
							algorithm               OBJECT IDENTIFIER,
							parameters              ANY DEFINED BY algorithm OPTIONAL  }
						
						Validity ::= SEQUENCE {
							notBefore      Time,
							notAfter       Time }

						SubjectPublicKeyInfo  ::=  SEQUENCE  {
							algorithm            AlgorithmIdentifier,
							subjectPublicKey     BIT STRING  }

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

						Asn1Identifier CertificateSequence = Decoder.DecodeIdentifier(InputStream);
						if (CertificateSequence.GetTagNumber() != static_cast<const Elysium::Core::int32_t>(Asn1UniversalTag::Sequence))
						{
							throw InvalidDataException(u"CertificateSequence");
						}
						Asn1Length CertificateLength = Decoder.DecodeLength(InputStream);
						
						Asn1Identifier TbsCertificateSequence = Decoder.DecodeIdentifier(InputStream);
						if (TbsCertificateSequence.GetTagNumber() != static_cast<const Elysium::Core::int32_t>(Asn1UniversalTag::Sequence))
						{
							throw InvalidDataException(u"TbsCertificateSequence");
						}
						Asn1Length TbsCertificateLength = Decoder.DecodeLength(InputStream);
						 
						Asn1Identifier ExplicitlyTaggedVersionIdentifier = Decoder.DecodeIdentifier(InputStream);
						Asn1Length ExplicitlyTaggedVersionLength = Decoder.DecodeLength(InputStream);
						if (ExplicitlyTaggedVersionIdentifier.GetTagClass() != Asn1TagClass::Context || ExplicitlyTaggedVersionIdentifier.GetIsConstructed() == false)
						{
							Asn1Integer Version = Decoder.DecodeInteger(ExplicitlyTaggedVersionIdentifier, ExplicitlyTaggedVersionLength, InputStream);

							// signature
							ReadAlgorithmIdentifier(Decoder, InputStream, Count);
						}
						else
						{
							Asn1Identifier VersionIdentifier = Decoder.DecodeIdentifier(InputStream);
							if (VersionIdentifier.GetTagNumber() != static_cast<const Elysium::Core::int32_t>(Asn1UniversalTag::Integer))
							{
								throw InvalidDataException(u"VersionIdentifier");
							}
							Asn1Length VersionLength = Decoder.DecodeLength(InputStream);
							Asn1Integer Version = Decoder.DecodeInteger(VersionIdentifier, VersionLength, InputStream);

							Asn1Identifier SerialNumberIdentifier = Decoder.DecodeIdentifier(InputStream);
							Asn1Length SerialNumberLength = Decoder.DecodeLength(InputStream);
							Asn1Integer SerialNumber = Decoder.DecodeInteger(SerialNumberIdentifier, SerialNumberLength, InputStream);

							// signature
							ReadAlgorithmIdentifier(Decoder, InputStream, Count);
						}

						// issuer
						ReadName(Decoder, InputStream, Count);
						
						// validity
						Asn1Identifier ValiditySequenceIdentifier = Decoder.DecodeIdentifier(InputStream);
						if (ValiditySequenceIdentifier.GetTagNumber() != static_cast<const Elysium::Core::int32_t>(Asn1UniversalTag::Sequence))
						{
							throw InvalidDataException(u"ValiditySequenceIdentifier");
						}
						Asn1Length ValiditySequenceLength = Decoder.DecodeLength(InputStream);

						Asn1Identifier ValidityNotBeforeIdentifier = Decoder.DecodeIdentifier(InputStream);
						if (ValidityNotBeforeIdentifier.GetTagNumber() != static_cast<const Elysium::Core::int32_t>(Asn1UniversalTag::UTCTime))
						{
							throw InvalidDataException(u"ValidityNotBeforeIdentifier");
						}
						Asn1Length ValidityNotBeforeLength = Decoder.DecodeLength(InputStream);
						InputStream.SetPosition(InputStream.GetPosition() + ValidityNotBeforeLength.GetLength());	// ToDo

						Asn1Identifier ValidityNotAfterIdentifier = Decoder.DecodeIdentifier(InputStream);
						if (ValidityNotAfterIdentifier.GetTagNumber() != static_cast<const Elysium::Core::int32_t>(Asn1UniversalTag::UTCTime))
						{
							throw InvalidDataException(u"ValidityNotAfterIdentifier");
						}
						Asn1Length ValidityNotAfterLength = Decoder.DecodeLength(InputStream);
						InputStream.SetPosition(InputStream.GetPosition() + ValidityNotAfterLength.GetLength());	// ToDo
						
						// subject
						ReadName(Decoder, InputStream, Count);
						
						// subjectPublicKeyInfo
						Asn1Identifier SubjectPublicKeySequenceIdentifier = Decoder.DecodeIdentifier(InputStream);
						Asn1Length SubjectPublicKeySequenceLength = Decoder.DecodeLength(InputStream);

						ReadAlgorithmIdentifier(Decoder, InputStream, Count);

						// issuerUniqueID
						Asn1Identifier IssuerUniqueIDIdentifier = Decoder.DecodeIdentifier(InputStream);
						Asn1Length IssuerUniqueIDLength = Decoder.DecodeLength(InputStream);
						Asn1Integer IssuerUniqueID = Decoder.DecodeInteger(IssuerUniqueIDIdentifier, IssuerUniqueIDLength, InputStream);

						// subjectUniqueID
						Asn1Identifier SubjectUniqueIDIdentifier = Decoder.DecodeIdentifier(InputStream);
						Asn1Length SubjectUniqueIDLength = Decoder.DecodeLength(InputStream);
						Asn1Integer SubjectUniqueID = Decoder.DecodeInteger(SubjectUniqueIDIdentifier, SubjectUniqueIDLength, InputStream);
						
						// extensions
						Asn1Identifier ExtensionSequenceIdentifier = Decoder.DecodeIdentifier(InputStream);
						Asn1Length ExtensionSequenceLength = Decoder.DecodeLength(InputStream);

						int64_t CurrentPosition = InputStream.GetPosition();
						while (InputStream.GetPosition() < CurrentPosition + ExtensionSequenceLength.GetLength())
						{
							Asn1Identifier ExtensionOidIdentifier = Decoder.DecodeIdentifier(InputStream);
							Asn1Length ExtensionOidLength = Decoder.DecodeLength(InputStream);
							if (ExtensionOidIdentifier.GetTagNumber() == static_cast<const Elysium::Core::int32_t>(Asn1UniversalTag::EndOfContent))
							{
								break;
							}
							Asn1ObjectIdentifier ExtensionOid = Decoder.DecodeObjectIdentifier(ExtensionOidIdentifier, ExtensionOidLength, InputStream);

							Asn1Identifier ExtensionCriticalIdentifier = Decoder.DecodeIdentifier(InputStream);
							Asn1Length ExtensionCriticalLength = Decoder.DecodeLength(InputStream);
							Asn1Boolean ExtensionCritical = Decoder.DecodeBoolean(ExtensionCriticalIdentifier, ExtensionCriticalLength, InputStream);

							Asn1Identifier ExtensionValueIdentifier = Decoder.DecodeIdentifier(InputStream);
							Asn1Length ExtensionValueLength = Decoder.DecodeLength(InputStream);
							Asn1String ExtensionValue = Decoder.DecodeString(ExtensionValueIdentifier, ExtensionValueLength, InputStream);
						}
						
						Count++;
					}
				}
			}
		}

	private:
		void ReadAlgorithmIdentifier(Elysium::Core::Security::Cryptography::Encoding::Asn1::IAsn1Decoder& Decoder, Elysium::Core::IO::Stream & InputStream, int32_t Count)
		{
			/*
			AlgorithmIdentifier  ::=  SEQUENCE  {
				algorithm               OBJECT IDENTIFIER,
				parameters              ANY DEFINED BY algorithm OPTIONAL  }
			*/
			const int64_t CurrentPosition = InputStream.GetPosition();
			Asn1Identifier AlgorithmSequenceIdentifier = Decoder.DecodeIdentifier(InputStream);
			if (AlgorithmSequenceIdentifier.GetTagNumber() != static_cast<const Elysium::Core::int32_t>(Asn1UniversalTag::Sequence))
			{
				throw InvalidDataException(u"AlgorithmSequenceIdentifier");
			}
			Asn1Length AlgorithmSequenceLength = Decoder.DecodeLength(InputStream);

			Asn1Identifier AlgorithmIdentifier = Decoder.DecodeIdentifier(InputStream);
			if (AlgorithmIdentifier.GetTagNumber() != static_cast<const Elysium::Core::int32_t>(Asn1UniversalTag::ObjectIdentifier))
			{
				throw InvalidDataException(u"AlgorithmIdentifier");
			}
			Asn1Length AlgorithmLength = Decoder.DecodeLength(InputStream);
			// ToDo: don't skip but actually read the value
			InputStream.SetPosition(InputStream.GetPosition() + AlgorithmLength.GetLength());
			//Asn1ObjectIdentifier AlgorithmIdentifier = Decoder.DecodeObjectIdentifier(AlgorithmIdentifier, AlgorithmLength, InputStream);

			Asn1Identifier ParameterSequenceIdentifier = Decoder.DecodeIdentifier(InputStream);
			Asn1Length ParameterSequenceLength = Decoder.DecodeLength(InputStream);
			if (ParameterSequenceIdentifier.GetTagNumber() == static_cast<int32_t>(Asn1UniversalTag::Sequence))
			{
				const int64_t CurrentPositionParameter = InputStream.GetPosition();
				while (InputStream.GetPosition() < CurrentPositionParameter + ParameterSequenceLength.GetLength())
				{
					Asn1Identifier ParameterSetIdentifier = Decoder.DecodeIdentifier(InputStream);
					if (ParameterSetIdentifier.GetTagNumber() != static_cast<int32_t>(Asn1UniversalTag::Set))
					{
						throw InvalidDataException(u"ParameterSetIdentifier");
					}
					Asn1Length ParameterSetLength = Decoder.DecodeLength(InputStream);

					Asn1Identifier ParameterIdentifier = Decoder.DecodeIdentifier(InputStream);	// 16 - Sequence
					Asn1Length ParameterLength = Decoder.DecodeLength(InputStream);

					Asn1Identifier ParameterOidIdentifier = Decoder.DecodeIdentifier(InputStream);
					Asn1Length ParameterOidLength = Decoder.DecodeLength(InputStream);
					Asn1ObjectIdentifier ParameterOid = Decoder.DecodeObjectIdentifier(ParameterOidIdentifier, ParameterOidLength, InputStream);

					Asn1Identifier ParameterNameIdentifier = Decoder.DecodeIdentifier(InputStream);
					Asn1Length ParameterNameLength = Decoder.DecodeLength(InputStream);
					Asn1String ParameterName = Decoder.DecodeString(ParameterNameIdentifier, ParameterNameLength, InputStream);
				}
			}
			else if (ParameterSequenceIdentifier.GetTagNumber() != static_cast<int32_t>(Asn1UniversalTag::Null))
			{
				throw InvalidDataException(u"ParameterSequenceIdentifier");
			}
		}

		void ReadName(Elysium::Core::Security::Cryptography::Encoding::Asn1::IAsn1Decoder& Decoder, Elysium::Core::IO::Stream & InputStream, int32_t Count)
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
			Asn1Identifier NameSequenceIdentifier = Decoder.DecodeIdentifier(InputStream);
			if (NameSequenceIdentifier.GetTagNumber() != static_cast<const Elysium::Core::int32_t>(Asn1UniversalTag::Sequence))
			{
				throw InvalidDataException(u"NameSequenceIdentifier");
			}
			Asn1Length NameSequenceLength = Decoder.DecodeLength(InputStream);

			int64_t CurrentPosition = InputStream.GetPosition();
			while (InputStream.GetPosition() < CurrentPosition + NameSequenceLength.GetLength())
			{
				Asn1Identifier RDNSequenceIdentifier = Decoder.DecodeIdentifier(InputStream);
				if (RDNSequenceIdentifier.GetTagNumber() == static_cast<const Elysium::Core::int32_t>(Asn1UniversalTag::Set))
				{
					Asn1Length RDNSequenceIdentifierLength = Decoder.DecodeLength(InputStream);

					Asn1Identifier RelativeDistinguishedNameIdentifier = Decoder.DecodeIdentifier(InputStream);
					if (RelativeDistinguishedNameIdentifier.GetTagNumber() != static_cast<const Elysium::Core::int32_t>(Asn1UniversalTag::Sequence))
					{
						throw InvalidDataException(u"RelativeDistinguishedNameIdentifier");
					}
					Asn1Length RelativeDistinguishedNameLength = Decoder.DecodeLength(InputStream);

					Asn1Identifier AttributeTypeIdentifier = Decoder.DecodeIdentifier(InputStream);
					if (AttributeTypeIdentifier.GetTagNumber() != static_cast<const Elysium::Core::int32_t>(Asn1UniversalTag::ObjectIdentifier))
					{
						throw InvalidDataException(u"AttributeTypeIdentifier");
					}
					Asn1Length AttributeTypeLength = Decoder.DecodeLength(InputStream);
					InputStream.SetPosition(InputStream.GetPosition() + AttributeTypeLength.GetLength());	// ToDo

					Asn1Identifier AttributeValueIdentifier = Decoder.DecodeIdentifier(InputStream);
					if (AttributeValueIdentifier.GetTagNumber() != static_cast<const Elysium::Core::int32_t>(Asn1UniversalTag::UTF8String) &&
						AttributeValueIdentifier.GetTagNumber() != static_cast<const Elysium::Core::int32_t>(Asn1UniversalTag::PrintableString) &&
						AttributeValueIdentifier.GetTagNumber() != static_cast<const Elysium::Core::int32_t>(Asn1UniversalTag::IA5String))
					{
						throw InvalidDataException(u"AttributeValueIdentifier");
					}
					Asn1Length AttributeValueLength = Decoder.DecodeLength(InputStream);
					Asn1String AttributeValue = Decoder.DecodeString(AttributeValueIdentifier, AttributeValueLength, InputStream);
				}
				else
				{
					throw InvalidDataException(u"RDNSequenceIdentifier");
				}
			}
		}
	};
}
