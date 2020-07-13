#include "CppUnitTest.h"

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_OID
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Security.Cryptography.Encoding/Oid.hpp"
#endif

using namespace Elysium::Core::Security::Cryptography;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Security::Cryptography
{
	TEST_CLASS(OidTests)
	{
	public:
		TEST_METHOD(StaticConstruction)
		{
			Oid OidFromFriendlyName = Oid::FromFriendlyName(u"sha1", OidGroup::All);
			AssertExtended::AreEqual(u"sha1", OidFromFriendlyName.GetFriendlyName().GetCharArray());
			AssertExtended::AreEqual(u"1.3.14.3.2.26", &OidFromFriendlyName.GetValue()[0]);

			Oid OidFromOidValue = Oid::FromOidValue(u"1.2.840.113549.1.1.1", OidGroup::All);
			AssertExtended::AreEqual(u"RSA", OidFromOidValue.GetFriendlyName().GetCharArray());
			AssertExtended::AreEqual(u"1.2.840.113549.1.1.1", &OidFromOidValue.GetValue()[0]);
		}
	};
}
