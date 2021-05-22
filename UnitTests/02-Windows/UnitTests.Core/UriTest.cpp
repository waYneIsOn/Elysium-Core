#include "CppUnitTest.h"

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#include "CppUnitTestFrameworkExtension.hpp"
#endif

#ifndef ELYSIUM_CORE_URI
#include "../../../Libraries/01-Shared/Elysium.Core/Uri.hpp"
#endif

using namespace Elysium::Core;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core
{
	TEST_CLASS(UriTests)
	{
	public:
		TEST_METHOD(GetAbsoluteUri)
		{
			AssertExtended::AreEqual(u8"https://www.google.com:447/someFold/subfol/bla?xyz=123&jkhsdf=8ndsf#fragmentstuff", _TestUriHttps.GetAbsoluteUri());
			AssertExtended::AreEqual(u8"ftp://username:password@www.google.com/xomeFold/subfol/bla?xyz=123&jkhsdf=8ndsf#", _TestUriFtp.GetAbsoluteUri());
			AssertExtended::AreEqual(u8"mailto:some@mail.com", _TestUriMailTo.GetAbsoluteUri());
			
			AssertExtended::AreEqual(u8"news:comp.infosystems.www.servers.unix/some/random/path#fragmentyoyo", _TestUriNews.GetAbsoluteUri());
			AssertExtended::AreEqual(u8"ldap://[2001:db8::7]/c=GB?objectClass?onex", _TestUriLdap.GetAbsoluteUri());
			AssertExtended::AreEqual(u8"tel:+1-816-555-1212", _TestUriTel.GetAbsoluteUri());
			AssertExtended::AreEqual(u8"telnet://192.0.2.16:80/some/path?query=something", _TestUriTelNet.GetAbsoluteUri());
			AssertExtended::AreEqual(u8"urn:oasis:names:specification:docbook:dtd:xml:4.1.2", _TestUriUrn.GetAbsoluteUri());
		}

		TEST_METHOD(GetSchema)
		{
			AssertExtended::AreEqual(u8"https", _TestUriHttps.GetSchema());
			AssertExtended::AreEqual(u8"ftp", _TestUriFtp.GetSchema());
			AssertExtended::AreEqual(u8"mailto", _TestUriMailTo.GetSchema());
			
			AssertExtended::AreEqual(u8"news", _TestUriNews.GetSchema());
			AssertExtended::AreEqual(u8"ldap", _TestUriLdap.GetSchema());
			AssertExtended::AreEqual(u8"tel", _TestUriTel.GetSchema());
			AssertExtended::AreEqual(u8"telnet", _TestUriTelNet.GetSchema());
			AssertExtended::AreEqual(u8"urn", _TestUriUrn.GetSchema());
		}

		TEST_METHOD(GetAuthorities)
		{
			AssertExtended::AreEqual(u8"www.google.com:447", _TestUriHttps.GetAuthority());
			AssertExtended::AreEqual(u8"username:password@www.google.com", _TestUriFtp.GetAuthority());
			AssertExtended::AreEqual(u8"some@mail.com", _TestUriMailTo.GetAuthority());
			
			AssertExtended::AreEqual(u8"comp.infosystems.www.servers.unix", _TestUriNews.GetAuthority());
			AssertExtended::AreEqual(u8"[2001:db8::7]", _TestUriLdap.GetAuthority());
			AssertExtended::AreEqual(u8"+1-816-555-1212", _TestUriTel.GetAuthority());
			AssertExtended::AreEqual(u8"192.0.2.16:80", _TestUriTelNet.GetAuthority());
			AssertExtended::AreEqual(u8"oasis:names:specification:docbook:dtd:xml:4.1.2", _TestUriUrn.GetAuthority());
		}

		TEST_METHOD(GetUserInfo)
		{
			AssertExtended::AreEqual(u8"", _TestUriHttps.GetUserInfo());
			AssertExtended::AreEqual(u8"username:password", _TestUriFtp.GetUserInfo());
			AssertExtended::AreEqual(u8"some", _TestUriMailTo.GetUserInfo());
			
			AssertExtended::AreEqual(u8"", _TestUriNews.GetUserInfo());
			AssertExtended::AreEqual(u8"", _TestUriLdap.GetUserInfo());
			AssertExtended::AreEqual(u8"", _TestUriTel.GetUserInfo());
			AssertExtended::AreEqual(u8"", _TestUriTelNet.GetUserInfo());
			AssertExtended::AreEqual(u8"", _TestUriUrn.GetUserInfo());
		}

		TEST_METHOD(GetHost)
		{
			AssertExtended::AreEqual(u8"www.google.com", _TestUriHttp.GetHost());
			AssertExtended::AreEqual(u8"www.google.com", _TestUriHttps.GetHost());
			AssertExtended::AreEqual(u8"www.google.com", _TestUriFtp.GetHost());
			AssertExtended::AreEqual(u8"mail.com", _TestUriMailTo.GetHost());
			
			AssertExtended::AreEqual(u8"comp.infosystems.www.servers.unix", _TestUriNews.GetHost());
			// ToDo: ':' is not allowed in the host normally resulting in "[2001" - a specific LDAP-Uri-Parser should probably do this differently
			AssertExtended::AreEqual(u8"[2001", _TestUriLdap.GetHost());
			// ToDo: does a specific TEL-Uri-Parser handle this differently? probably
			AssertExtended::AreEqual(u8"+1-816-555-1212", _TestUriTel.GetHost());
			AssertExtended::AreEqual(u8"192.0.2.16", _TestUriTelNet.GetHost());
			// ToDo: does a specific URN-Uri-Parser handle this differently? probably
			AssertExtended::AreEqual(u8"oasis", _TestUriUrn.GetHost());
		}

		TEST_METHOD(GetPort)
		{
			Assert::AreEqual(447_ui32, _TestUriHttps.GetPort());
			Assert::AreEqual(21_ui32, _TestUriFtp.GetPort());
			Assert::AreEqual(-1_ui32, _TestUriMailTo.GetPort());
			
			Assert::AreEqual(-1_ui32, _TestUriNews.GetPort());
			Assert::AreEqual(389_ui32, _TestUriLdap.GetPort());
			Assert::AreEqual(-1_ui32, _TestUriTel.GetPort());
			Assert::AreEqual(22_ui32, _TestUriTelNet.GetPort());
			Assert::AreEqual(-1_ui32, _TestUriUrn.GetPort());
		}

		TEST_METHOD(GetPathAndQuery)
		{
			AssertExtended::AreEqual(u8"", _TestUriHttp.GetPathAndQuery());
			AssertExtended::AreEqual(u8"someFold/subfol/bla?xyz=123&jkhsdf=8ndsf", _TestUriHttps.GetPathAndQuery());
			AssertExtended::AreEqual(u8"xomeFold/subfol/bla?xyz=123&jkhsdf=8ndsf", _TestUriFtp.GetPathAndQuery());
			AssertExtended::AreEqual(u8"", _TestUriMailTo.GetPathAndQuery());
			
			AssertExtended::AreEqual(u8"some/random/path", _TestUriNews.GetPathAndQuery());
			AssertExtended::AreEqual(u8"c=GB?objectClass?onex", _TestUriLdap.GetPathAndQuery());
			AssertExtended::AreEqual(u8"", _TestUriTel.GetPathAndQuery());
			AssertExtended::AreEqual(u8"some/path?query=something", _TestUriTelNet.GetPathAndQuery());
			AssertExtended::AreEqual(u8"", _TestUriUrn.GetPathAndQuery());
		}

		TEST_METHOD(GetPath)
		{
			AssertExtended::AreEqual(u8"someFold/subfol/bla", _TestUriHttps.GetPath());
			AssertExtended::AreEqual(u8"xomeFold/subfol/bla", _TestUriFtp.GetPath());
			AssertExtended::AreEqual(u8"", _TestUriMailTo.GetPath());
			
			AssertExtended::AreEqual(u8"some/random/path", _TestUriNews.GetPath());
			AssertExtended::AreEqual(u8"c=GB", _TestUriLdap.GetPath());
			AssertExtended::AreEqual(u8"", _TestUriTel.GetPath());
			AssertExtended::AreEqual(u8"some/path", _TestUriTelNet.GetPath());
			AssertExtended::AreEqual(u8"", _TestUriUrn.GetPath());
		}

		TEST_METHOD(GetQuery)
		{
			AssertExtended::AreEqual(u8"xyz=123&jkhsdf=8ndsf", _TestUriHttps.GetQuery());
			AssertExtended::AreEqual(u8"xyz=123&jkhsdf=8ndsf", _TestUriFtp.GetQuery());
			AssertExtended::AreEqual(u8"", _TestUriMailTo.GetQuery());
			
			AssertExtended::AreEqual(u8"", _TestUriNews.GetQuery());
			AssertExtended::AreEqual(u8"objectClass?onex", _TestUriLdap.GetQuery());
			AssertExtended::AreEqual(u8"", _TestUriTel.GetQuery());
			AssertExtended::AreEqual(u8"query=something", _TestUriTelNet.GetQuery());
			AssertExtended::AreEqual(u8"", _TestUriUrn.GetQuery());
		}

		TEST_METHOD(GetFragment)
		{
			AssertExtended::AreEqual(u8"fragmentstuff", _TestUriHttps.GetFragment());
			AssertExtended::AreEqual(u8"", _TestUriFtp.GetFragment());
			AssertExtended::AreEqual(u8"", _TestUriMailTo.GetFragment());
			
			AssertExtended::AreEqual(u8"fragmentyoyo", _TestUriNews.GetFragment());
			AssertExtended::AreEqual(u8"", _TestUriLdap.GetFragment());
			AssertExtended::AreEqual(u8"", _TestUriTel.GetFragment());
			AssertExtended::AreEqual(u8"", _TestUriTelNet.GetFragment());
			AssertExtended::AreEqual(u8"", _TestUriUrn.GetFragment());
		}
	private:
		//Uri _TestUriEmpty = Uri(String());
		Uri _TestUriHttp = Uri(u8"http://www.google.com");
		Uri _TestUriHttps = Uri(u8"https://www.google.com:447/someFold/subfol/bla?xyz=123&jkhsdf=8ndsf#fragmentstuff");
		Uri _TestUriFtp = Uri(u8"ftp://username:password@www.google.com/xomeFold/subfol/bla?xyz=123&jkhsdf=8ndsf#");
		Uri _TestUriMailTo = Uri(u8"mailto:some@mail.com");
		
		Uri _TestUriNews = Uri(u8"news:comp.infosystems.www.servers.unix/some/random/path#fragmentyoyo");
		Uri _TestUriLdap = Uri(u8"ldap://[2001:db8::7]/c=GB?objectClass?onex");
		Uri _TestUriTel = Uri(u8"tel:+1-816-555-1212");
		Uri _TestUriTelNet = Uri(u8"telnet://192.0.2.16:80/some/path?query=something");
		Uri _TestUriUrn = Uri(u8"urn:oasis:names:specification:docbook:dtd:xml:4.1.2");
	};
}
