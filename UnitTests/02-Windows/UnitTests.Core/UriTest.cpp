#include "CppUnitTest.h"

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#include "CppUnitTestFrameworkExtension.hpp"
#endif

#ifndef ELYSIUM_CORE_URI
#include "../../../Libraries/01-Shared/Elysium.Core/Uri.hpp"
#endif

using namespace Elysium::Core;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsCore
{
	TEST_CLASS(Core_Uri)
	{
	public:
		TEST_METHOD(StaticFields)
		{
			AssertExtended::AreEqual(u"://", Uri::SchemeDelimiter.GetCharArray());

			AssertExtended::AreEqual(u"file", Uri::UriSchemeFile.GetCharArray());
			AssertExtended::AreEqual(u"ftp", Uri::UriSchemeFtp.GetCharArray());
			AssertExtended::AreEqual(u"gopher", Uri::UriSchemeGopher.GetCharArray());
			AssertExtended::AreEqual(u"http", Uri::UriSchemeHttp.GetCharArray());
			AssertExtended::AreEqual(u"https", Uri::UriSchemeHttps.GetCharArray());
			AssertExtended::AreEqual(u"irc", Uri::UriSchemeIrc.GetCharArray());
			AssertExtended::AreEqual(u"ldap", Uri::UriSchemeLdap.GetCharArray());
			AssertExtended::AreEqual(u"mailto", Uri::UriSchemeMailto.GetCharArray());
			AssertExtended::AreEqual(u"net.pipe", Uri::UriSchemeNetPipe.GetCharArray());
			AssertExtended::AreEqual(u"net.tcp", Uri::UriSchemeNetTcp.GetCharArray());
			AssertExtended::AreEqual(u"news", Uri::UriSchemeNews.GetCharArray());
			AssertExtended::AreEqual(u"nntp", Uri::UriSchemeNntp.GetCharArray());
			AssertExtended::AreEqual(u"wss", Uri::UriSchemeSecureWebSocket.GetCharArray());
			AssertExtended::AreEqual(u"teu", Uri::UriSchemeTel.GetCharArray());
			AssertExtended::AreEqual(u"telnet", Uri::UriSchemeTelNet.GetCharArray());
			AssertExtended::AreEqual(u"urn", Uri::UriSchemeUrn.GetCharArray());
			AssertExtended::AreEqual(u"ws", Uri::UriSchemeWebSocket.GetCharArray());
		}

		TEST_METHOD(GetAbsoluteUri)
		{
			AssertExtended::AreEqual(u"https://www.google.com:447/someFold/subfol/bla?xyz=123&jkhsdf=8ndsf#fragmentstuff", ((String)_TestUriHttps.GetAbsoluteUri()).GetCharArray());
			AssertExtended::AreEqual(u"ftp://username:password@www.google.com/xomeFold/subfol/bla?xyz=123&jkhsdf=8ndsf#", ((String)_TestUriFtp.GetAbsoluteUri()).GetCharArray());
			AssertExtended::AreEqual(u"mailto:some@mail.com", ((String)_TestUriMailTo.GetAbsoluteUri()).GetCharArray());
			
			AssertExtended::AreEqual(u"news:comp.infosystems.www.servers.unix/some/random/path#fragmentyoyo", ((String)_TestUriNews.GetAbsoluteUri()).GetCharArray());
			AssertExtended::AreEqual(u"ldap://[2001:db8::7]/c=GB?objectClass?onex", ((String)_TestUriLdap.GetAbsoluteUri()).GetCharArray());
			AssertExtended::AreEqual(u"tel:+1-816-555-1212", ((String)_TestUriTel.GetAbsoluteUri()).GetCharArray());
			AssertExtended::AreEqual(u"telnet://192.0.2.16:80/some/path?query=something", ((String)_TestUriTelNet.GetAbsoluteUri()).GetCharArray());
			AssertExtended::AreEqual(u"urn:oasis:names:specification:docbook:dtd:xml:4.1.2", ((String)_TestUriUrn.GetAbsoluteUri()).GetCharArray());
		}

		TEST_METHOD(GetSchema)
		{
			AssertExtended::AreEqual(u"https", ((String)_TestUriHttps.GetSchema()).GetCharArray());
			AssertExtended::AreEqual(u"ftp", ((String)_TestUriFtp.GetSchema()).GetCharArray());
			AssertExtended::AreEqual(u"mailto", ((String)_TestUriMailTo.GetSchema()).GetCharArray());
			
			AssertExtended::AreEqual(u"news", ((String)_TestUriNews.GetSchema()).GetCharArray());
			AssertExtended::AreEqual(u"ldap", ((String)_TestUriLdap.GetSchema()).GetCharArray());
			AssertExtended::AreEqual(u"tel", ((String)_TestUriTel.GetSchema()).GetCharArray());
			AssertExtended::AreEqual(u"telnet", ((String)_TestUriTelNet.GetSchema()).GetCharArray());
			AssertExtended::AreEqual(u"urn", ((String)_TestUriUrn.GetSchema()).GetCharArray());
		}

		TEST_METHOD(GetAuthorities)
		{
			AssertExtended::AreEqual(u"www.google.com:447", ((String)_TestUriHttps.GetAuthority()).GetCharArray());
			AssertExtended::AreEqual(u"username:password@www.google.com", ((String)_TestUriFtp.GetAuthority()).GetCharArray());
			AssertExtended::AreEqual(u"some@mail.com", ((String)_TestUriMailTo.GetAuthority()).GetCharArray());
			
			AssertExtended::AreEqual(u"comp.infosystems.www.servers.unix", ((String)_TestUriNews.GetAuthority()).GetCharArray());
			AssertExtended::AreEqual(u"[2001:db8::7]", ((String)_TestUriLdap.GetAuthority()).GetCharArray());
			AssertExtended::AreEqual(u"+1-816-555-1212", ((String)_TestUriTel.GetAuthority()).GetCharArray());
			AssertExtended::AreEqual(u"192.0.2.16:80", ((String)_TestUriTelNet.GetAuthority()).GetCharArray());
			AssertExtended::AreEqual(u"oasis:names:specification:docbook:dtd:xml:4.1.2", ((String)_TestUriUrn.GetAuthority()).GetCharArray());
		}

		TEST_METHOD(GetUserInfo)
		{
			AssertExtended::AreEqual(u"", ((String)_TestUriHttps.GetUserInfo()).GetCharArray());
			AssertExtended::AreEqual(u"username:password", ((String)_TestUriFtp.GetUserInfo()).GetCharArray());
			AssertExtended::AreEqual(u"some", ((String)_TestUriMailTo.GetUserInfo()).GetCharArray());
			
			AssertExtended::AreEqual(u"", ((String)_TestUriNews.GetUserInfo()).GetCharArray());
			AssertExtended::AreEqual(u"", ((String)_TestUriLdap.GetUserInfo()).GetCharArray());
			AssertExtended::AreEqual(u"", ((String)_TestUriTel.GetUserInfo()).GetCharArray());
			AssertExtended::AreEqual(u"", ((String)_TestUriTelNet.GetUserInfo()).GetCharArray());
			AssertExtended::AreEqual(u"", ((String)_TestUriUrn.GetUserInfo()).GetCharArray());
		}

		TEST_METHOD(GetHost)
		{
			AssertExtended::AreEqual(u"www.google.com", ((String)_TestUriHttp.GetHost()).GetCharArray());
			AssertExtended::AreEqual(u"www.google.com", ((String)_TestUriHttps.GetHost()).GetCharArray());
			AssertExtended::AreEqual(u"www.google.com", ((String)_TestUriFtp.GetHost()).GetCharArray());
			AssertExtended::AreEqual(u"mail.com", ((String)_TestUriMailTo.GetHost()).GetCharArray());
			
			AssertExtended::AreEqual(u"comp.infosystems.www.servers.unix", ((String)_TestUriNews.GetHost()).GetCharArray());
			// ToDo: ':' is not allowed in the host normally resulting in "[2001" - a specific LDAP-Uri-Parser should probably do this differently
			AssertExtended::AreEqual(u"[2001", ((String)_TestUriLdap.GetHost()).GetCharArray());
			// ToDo: does a specific TEL-Uri-Parser handle this differently? probably
			AssertExtended::AreEqual(u"+1-816-555-1212", ((String)_TestUriTel.GetHost()).GetCharArray());
			AssertExtended::AreEqual(u"192.0.2.16", ((String)_TestUriTelNet.GetHost()).GetCharArray());
			// ToDo: does a specific URN-Uri-Parser handle this differently? probably
			AssertExtended::AreEqual(u"oasis", ((String)_TestUriUrn.GetHost()).GetCharArray());
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
			AssertExtended::AreEqual(u"", ((String)_TestUriHttp.GetPathAndQuery()).GetCharArray());
			AssertExtended::AreEqual(u"someFold/subfol/bla?xyz=123&jkhsdf=8ndsf", ((String)_TestUriHttps.GetPathAndQuery()).GetCharArray());
			AssertExtended::AreEqual(u"xomeFold/subfol/bla?xyz=123&jkhsdf=8ndsf", ((String)_TestUriFtp.GetPathAndQuery()).GetCharArray());
			AssertExtended::AreEqual(u"", ((String)_TestUriMailTo.GetPathAndQuery()).GetCharArray());
			
			AssertExtended::AreEqual(u"some/random/path", ((String)_TestUriNews.GetPathAndQuery()).GetCharArray());
			AssertExtended::AreEqual(u"c=GB?objectClass?onex", ((String)_TestUriLdap.GetPathAndQuery()).GetCharArray());
			AssertExtended::AreEqual(u"", ((String)_TestUriTel.GetPathAndQuery()).GetCharArray());
			AssertExtended::AreEqual(u"some/path?query=something", ((String)_TestUriTelNet.GetPathAndQuery()).GetCharArray());
			AssertExtended::AreEqual(u"", ((String)_TestUriUrn.GetPathAndQuery()).GetCharArray());
		}

		TEST_METHOD(GetPath)
		{
			AssertExtended::AreEqual(u"someFold/subfol/bla", ((String)_TestUriHttps.GetPath()).GetCharArray());
			AssertExtended::AreEqual(u"xomeFold/subfol/bla", ((String)_TestUriFtp.GetPath()).GetCharArray());
			AssertExtended::AreEqual(u"", ((String)_TestUriMailTo.GetPath()).GetCharArray());
			
			AssertExtended::AreEqual(u"some/random/path", ((String)_TestUriNews.GetPath()).GetCharArray());
			AssertExtended::AreEqual(u"c=GB", ((String)_TestUriLdap.GetPath()).GetCharArray());
			AssertExtended::AreEqual(u"", ((String)_TestUriTel.GetPath()).GetCharArray());
			AssertExtended::AreEqual(u"some/path", ((String)_TestUriTelNet.GetPath()).GetCharArray());
			AssertExtended::AreEqual(u"", ((String)_TestUriUrn.GetPath()).GetCharArray());
		}

		TEST_METHOD(GetQuery)
		{
			AssertExtended::AreEqual(u"xyz=123&jkhsdf=8ndsf", ((String)_TestUriHttps.GetQuery()).GetCharArray());
			AssertExtended::AreEqual(u"xyz=123&jkhsdf=8ndsf", ((String)_TestUriFtp.GetQuery()).GetCharArray());
			AssertExtended::AreEqual(u"", ((String)_TestUriMailTo.GetQuery()).GetCharArray());
			
			AssertExtended::AreEqual(u"", ((String)_TestUriNews.GetQuery()).GetCharArray());
			AssertExtended::AreEqual(u"objectClass?onex", ((String)_TestUriLdap.GetQuery()).GetCharArray());
			AssertExtended::AreEqual(u"", ((String)_TestUriTel.GetQuery()).GetCharArray());
			AssertExtended::AreEqual(u"query=something", ((String)_TestUriTelNet.GetQuery()).GetCharArray());
			AssertExtended::AreEqual(u"", ((String)_TestUriUrn.GetQuery()).GetCharArray());
		}

		TEST_METHOD(GetFragment)
		{
			AssertExtended::AreEqual(u"fragmentstuff", ((String)_TestUriHttps.GetFragment()).GetCharArray());
			AssertExtended::AreEqual(u"", ((String)_TestUriFtp.GetFragment()).GetCharArray());
			AssertExtended::AreEqual(u"", ((String)_TestUriMailTo.GetFragment()).GetCharArray());
			
			AssertExtended::AreEqual(u"fragmentyoyo", ((String)_TestUriNews.GetFragment()).GetCharArray());
			AssertExtended::AreEqual(u"", ((String)_TestUriLdap.GetFragment()).GetCharArray());
			AssertExtended::AreEqual(u"", ((String)_TestUriTel.GetFragment()).GetCharArray());
			AssertExtended::AreEqual(u"", ((String)_TestUriTelNet.GetFragment()).GetCharArray());
			AssertExtended::AreEqual(u"", ((String)_TestUriUrn.GetFragment()).GetCharArray());
		}
	private:
		// fields
		Uri _TestUriHttp = Uri(u"http://www.google.com");
		Uri _TestUriHttps = Uri(u"https://www.google.com:447/someFold/subfol/bla?xyz=123&jkhsdf=8ndsf#fragmentstuff");
		Uri _TestUriFtp = Uri(u"ftp://username:password@www.google.com/xomeFold/subfol/bla?xyz=123&jkhsdf=8ndsf#");
		Uri _TestUriMailTo = Uri(u"mailto:some@mail.com");
		
		Uri _TestUriNews = Uri(u"news:comp.infosystems.www.servers.unix/some/random/path#fragmentyoyo");
		Uri _TestUriLdap = Uri(u"ldap://[2001:db8::7]/c=GB?objectClass?onex");
		Uri _TestUriTel = Uri(u"tel:+1-816-555-1212");
		Uri _TestUriTelNet = Uri(u"telnet://192.0.2.16:80/some/path?query=something");
		Uri _TestUriUrn = Uri(u"urn:oasis:names:specification:docbook:dtd:xml:4.1.2");
	};
}
