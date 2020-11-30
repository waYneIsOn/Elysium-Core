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
		TEST_METHOD(StaticFields)
		{
			AssertExtended::AreEqual(u8"://", &Uri::SchemeDelimiter[0]);

			AssertExtended::AreEqual(u8"file", &Uri::UriSchemeFile[0]);
			AssertExtended::AreEqual(u8"ftp", &Uri::UriSchemeFtp[0]);
			AssertExtended::AreEqual(u8"gopher", &Uri::UriSchemeGopher[0]);
			AssertExtended::AreEqual(u8"http", &Uri::UriSchemeHttp[0]);
			AssertExtended::AreEqual(u8"https", &Uri::UriSchemeHttps[0]);
			AssertExtended::AreEqual(u8"irc", &Uri::UriSchemeIrc[0]);
			AssertExtended::AreEqual(u8"ldap", &Uri::UriSchemeLdap[0]);
			AssertExtended::AreEqual(u8"mailto", &Uri::UriSchemeMailto[0]);
			AssertExtended::AreEqual(u8"net.pipe", &Uri::UriSchemeNetPipe[0]);
			AssertExtended::AreEqual(u8"net.tcp", &Uri::UriSchemeNetTcp[0]);
			AssertExtended::AreEqual(u8"news", &Uri::UriSchemeNews[0]);
			AssertExtended::AreEqual(u8"nntp", &Uri::UriSchemeNntp[0]);
			AssertExtended::AreEqual(u8"wss", &Uri::UriSchemeSecureWebSocket[0]);
			AssertExtended::AreEqual(u8"teu", &Uri::UriSchemeTel[0]);
			AssertExtended::AreEqual(u8"telnet", &Uri::UriSchemeTelNet[0]);
			AssertExtended::AreEqual(u8"urn", &Uri::UriSchemeUrn[0]);
			AssertExtended::AreEqual(u8"ws", &Uri::UriSchemeWebSocket[0]);
		}

		TEST_METHOD(GetAbsoluteUri)
		{
			AssertExtended::AreEqual(u8"https://www.google.com:447/someFold/subfol/bla?xyz=123&jkhsdf=8ndsf#fragmentstuff", &_TestUriHttps.GetAbsoluteUri()[0]);
			AssertExtended::AreEqual(u8"ftp://username:password@www.google.com/xomeFold/subfol/bla?xyz=123&jkhsdf=8ndsf#", &_TestUriFtp.GetAbsoluteUri()[0]);
			AssertExtended::AreEqual(u8"mailto:some@mail.com", &_TestUriMailTo.GetAbsoluteUri()[0]);
			
			AssertExtended::AreEqual(u8"news:comp.infosystems.www.servers.unix/some/random/path#fragmentyoyo", &_TestUriNews.GetAbsoluteUri()[0]);
			AssertExtended::AreEqual(u8"ldap://[2001:db8::7]/c=GB?objectClass?onex", &_TestUriLdap.GetAbsoluteUri()[0]);
			AssertExtended::AreEqual(u8"tel:+1-816-555-1212", &_TestUriTel.GetAbsoluteUri()[0]);
			AssertExtended::AreEqual(u8"telnet://192.0.2.16:80/some/path?query=something", &_TestUriTelNet.GetAbsoluteUri()[0]);
			AssertExtended::AreEqual(u8"urn:oasis:names:specification:docbook:dtd:xml:4.1.2", &_TestUriUrn.GetAbsoluteUri()[0]);
		}

		TEST_METHOD(GetSchema)
		{
			AssertExtended::AreEqual(u8"https", &_TestUriHttps.GetSchema()[0]);
			AssertExtended::AreEqual(u8"ftp", &_TestUriFtp.GetSchema()[0]);
			AssertExtended::AreEqual(u8"mailto", &_TestUriMailTo.GetSchema()[0]);
			
			AssertExtended::AreEqual(u8"news", &_TestUriNews.GetSchema()[0]);
			AssertExtended::AreEqual(u8"ldap", &_TestUriLdap.GetSchema()[0]);
			AssertExtended::AreEqual(u8"tel", &_TestUriTel.GetSchema()[0]);
			AssertExtended::AreEqual(u8"telnet", &_TestUriTelNet.GetSchema()[0]);
			AssertExtended::AreEqual(u8"urn", &_TestUriUrn.GetSchema()[0]);
		}

		TEST_METHOD(GetAuthorities)
		{
			AssertExtended::AreEqual(u8"www.google.com:447", &_TestUriHttps.GetAuthority()[0]);
			AssertExtended::AreEqual(u8"username:password@www.google.com", &_TestUriFtp.GetAuthority()[0]);
			AssertExtended::AreEqual(u8"some@mail.com", &_TestUriMailTo.GetAuthority()[0]);
			
			AssertExtended::AreEqual(u8"comp.infosystems.www.servers.unix", &_TestUriNews.GetAuthority()[0]);
			AssertExtended::AreEqual(u8"[2001:db8::7]", &_TestUriLdap.GetAuthority()[0]);
			AssertExtended::AreEqual(u8"+1-816-555-1212", &_TestUriTel.GetAuthority()[0]);
			AssertExtended::AreEqual(u8"192.0.2.16:80", &_TestUriTelNet.GetAuthority()[0]);
			AssertExtended::AreEqual(u8"oasis:names:specification:docbook:dtd:xml:4.1.2", &_TestUriUrn.GetAuthority()[0]);
		}

		TEST_METHOD(GetUserInfo)
		{
			AssertExtended::AreEqual(u8"", &_TestUriHttps.GetUserInfo()[0]);
			AssertExtended::AreEqual(u8"username:password", &_TestUriFtp.GetUserInfo()[0]);
			AssertExtended::AreEqual(u8"some", &_TestUriMailTo.GetUserInfo()[0]);
			
			AssertExtended::AreEqual(u8"", &_TestUriNews.GetUserInfo()[0]);
			AssertExtended::AreEqual(u8"", &_TestUriLdap.GetUserInfo()[0]);
			AssertExtended::AreEqual(u8"", &_TestUriTel.GetUserInfo()[0]);
			AssertExtended::AreEqual(u8"", &_TestUriTelNet.GetUserInfo()[0]);
			AssertExtended::AreEqual(u8"", &_TestUriUrn.GetUserInfo()[0]);
		}

		TEST_METHOD(GetHost)
		{
			AssertExtended::AreEqual(u8"www.google.com", &_TestUriHttp.GetHost()[0]);
			AssertExtended::AreEqual(u8"www.google.com", &_TestUriHttps.GetHost()[0]);
			AssertExtended::AreEqual(u8"www.google.com", &_TestUriFtp.GetHost()[0]);
			AssertExtended::AreEqual(u8"mail.com", &_TestUriMailTo.GetHost()[0]);
			
			AssertExtended::AreEqual(u8"comp.infosystems.www.servers.unix", &_TestUriNews.GetHost()[0]);
			// ToDo: ':' is not allowed in the host normally resulting in "[2001" - a specific LDAP-Uri-Parser should probably do this differently
			AssertExtended::AreEqual(u8"[2001", &_TestUriLdap.GetHost()[0]);
			// ToDo: does a specific TEL-Uri-Parser handle this differently? probably
			AssertExtended::AreEqual(u8"+1-816-555-1212", &_TestUriTel.GetHost()[0]);
			AssertExtended::AreEqual(u8"192.0.2.16", &_TestUriTelNet.GetHost()[0]);
			// ToDo: does a specific URN-Uri-Parser handle this differently? probably
			AssertExtended::AreEqual(u8"oasis", &_TestUriUrn.GetHost()[0]);
		}

		TEST_METHOD(GetPort)
		{
			Assert::AreEqual(447, _TestUriHttps.GetPort());
			Assert::AreEqual(21, _TestUriFtp.GetPort());
			Assert::AreEqual(-1, _TestUriMailTo.GetPort());
			
			Assert::AreEqual(-1, _TestUriNews.GetPort());
			Assert::AreEqual(389, _TestUriLdap.GetPort());
			Assert::AreEqual(-1, _TestUriTel.GetPort());
			Assert::AreEqual(22, _TestUriTelNet.GetPort());
			Assert::AreEqual(-1, _TestUriUrn.GetPort());
		}

		TEST_METHOD(GetPathAndQuery)
		{
			AssertExtended::AreEqual(u8"", &_TestUriHttp.GetPathAndQuery()[0]);
			AssertExtended::AreEqual(u8"someFold/subfol/bla?xyz=123&jkhsdf=8ndsf", &_TestUriHttps.GetPathAndQuery()[0]);
			AssertExtended::AreEqual(u8"xomeFold/subfol/bla?xyz=123&jkhsdf=8ndsf", &_TestUriFtp.GetPathAndQuery()[0]);
			AssertExtended::AreEqual(u8"", &_TestUriMailTo.GetPathAndQuery()[0]);
			
			AssertExtended::AreEqual(u8"some/random/path", &_TestUriNews.GetPathAndQuery()[0]);
			AssertExtended::AreEqual(u8"c=GB?objectClass?onex", &_TestUriLdap.GetPathAndQuery()[0]);
			AssertExtended::AreEqual(u8"", &_TestUriTel.GetPathAndQuery()[0]);
			AssertExtended::AreEqual(u8"some/path?query=something", &_TestUriTelNet.GetPathAndQuery()[0]);
			AssertExtended::AreEqual(u8"", &_TestUriUrn.GetPathAndQuery()[0]);
		}

		TEST_METHOD(GetPath)
		{
			AssertExtended::AreEqual(u8"someFold/subfol/bla", &_TestUriHttps.GetPath()[0]);
			AssertExtended::AreEqual(u8"xomeFold/subfol/bla", &_TestUriFtp.GetPath()[0]);
			AssertExtended::AreEqual(u8"", &_TestUriMailTo.GetPath()[0]);
			
			AssertExtended::AreEqual(u8"some/random/path", &_TestUriNews.GetPath()[0]);
			AssertExtended::AreEqual(u8"c=GB", &_TestUriLdap.GetPath()[0]);
			AssertExtended::AreEqual(u8"", &_TestUriTel.GetPath()[0]);
			AssertExtended::AreEqual(u8"some/path", &_TestUriTelNet.GetPath()[0]);
			AssertExtended::AreEqual(u8"", &_TestUriUrn.GetPath()[0]);
		}

		TEST_METHOD(GetQuery)
		{
			AssertExtended::AreEqual(u8"xyz=123&jkhsdf=8ndsf", &_TestUriHttps.GetQuery()[0]);
			AssertExtended::AreEqual(u8"xyz=123&jkhsdf=8ndsf", &_TestUriFtp.GetQuery()[0]);
			AssertExtended::AreEqual(u8"", &_TestUriMailTo.GetQuery()[0]);
			
			AssertExtended::AreEqual(u8"", &_TestUriNews.GetQuery()[0]);
			AssertExtended::AreEqual(u8"objectClass?onex", &_TestUriLdap.GetQuery()[0]);
			AssertExtended::AreEqual(u8"", &_TestUriTel.GetQuery()[0]);
			AssertExtended::AreEqual(u8"query=something", &_TestUriTelNet.GetQuery()[0]);
			AssertExtended::AreEqual(u8"", &_TestUriUrn.GetQuery()[0]);
		}

		TEST_METHOD(GetFragment)
		{
			AssertExtended::AreEqual(u8"fragmentstuff", &_TestUriHttps.GetFragment()[0]);
			AssertExtended::AreEqual(u8"", &_TestUriFtp.GetFragment()[0]);
			AssertExtended::AreEqual(u8"", &_TestUriMailTo.GetFragment()[0]);
			
			AssertExtended::AreEqual(u8"fragmentyoyo", &_TestUriNews.GetFragment()[0]);
			AssertExtended::AreEqual(u8"", &_TestUriLdap.GetFragment()[0]);
			AssertExtended::AreEqual(u8"", &_TestUriTel.GetFragment()[0]);
			AssertExtended::AreEqual(u8"", &_TestUriTelNet.GetFragment()[0]);
			AssertExtended::AreEqual(u8"", &_TestUriUrn.GetFragment()[0]);
		}
	private:
		// fields
		Uri _TestUriEmpty = Uri(String());
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
