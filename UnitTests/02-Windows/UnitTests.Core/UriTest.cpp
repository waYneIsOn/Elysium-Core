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
			Assert::AreEqual(u8"://", Uri::SchemeDelimiter.GetCharArray());

			Assert::AreEqual(u8"file", Uri::UriSchemeFile.GetCharArray());
			Assert::AreEqual(u8"ftp", Uri::UriSchemeFtp.GetCharArray());
			Assert::AreEqual(u8"gopher", Uri::UriSchemeGopher.GetCharArray());
			Assert::AreEqual(u8"http", Uri::UriSchemeHttp.GetCharArray());
			Assert::AreEqual(u8"https", Uri::UriSchemeHttps.GetCharArray());
			Assert::AreEqual(u8"irc", Uri::UriSchemeIrc.GetCharArray());
			Assert::AreEqual(u8"ldap", Uri::UriSchemeLdap.GetCharArray());
			Assert::AreEqual(u8"mailto", Uri::UriSchemeMailto.GetCharArray());
			Assert::AreEqual(u8"net.pipe", Uri::UriSchemeNetPipe.GetCharArray());
			Assert::AreEqual(u8"net.tcp", Uri::UriSchemeNetTcp.GetCharArray());
			Assert::AreEqual(u8"news", Uri::UriSchemeNews.GetCharArray());
			Assert::AreEqual(u8"nntp", Uri::UriSchemeNntp.GetCharArray());
			Assert::AreEqual(u8"wss", Uri::UriSchemeSecureWebSocket.GetCharArray());
			Assert::AreEqual(u8"teu", Uri::UriSchemeTel.GetCharArray());
			Assert::AreEqual(u8"telnet", Uri::UriSchemeTelNet.GetCharArray());
			Assert::AreEqual(u8"urn", Uri::UriSchemeUrn.GetCharArray());
			Assert::AreEqual(u8"ws", Uri::UriSchemeWebSocket.GetCharArray());
		}

		TEST_METHOD(GetAbsoluteUri)
		{
			Assert::AreEqual(u8"https://www.google.com:447/someFold/subfol/bla?xyz=123&jkhsdf=8ndsf#fragmentstuff", ((String)_TestUriHttps.GetAbsoluteUri()).GetCharArray());
			Assert::AreEqual(u8"ftp://username:password@www.google.com/xomeFold/subfol/bla?xyz=123&jkhsdf=8ndsf#", ((String)_TestUriFtp.GetAbsoluteUri()).GetCharArray());
			Assert::AreEqual(u8"mailto:some@mail.com", ((String)_TestUriMailTo.GetAbsoluteUri()).GetCharArray());
			
			Assert::AreEqual(u8"news:comp.infosystems.www.servers.unix/some/random/path#fragmentyoyo", ((String)_TestUriNews.GetAbsoluteUri()).GetCharArray());
			Assert::AreEqual(u8"ldap://[2001:db8::7]/c=GB?objectClass?onex", ((String)_TestUriLdap.GetAbsoluteUri()).GetCharArray());
			Assert::AreEqual(u8"tel:+1-816-555-1212", ((String)_TestUriTel.GetAbsoluteUri()).GetCharArray());
			Assert::AreEqual(u8"telnet://192.0.2.16:80/some/path?query=something", ((String)_TestUriTelNet.GetAbsoluteUri()).GetCharArray());
			Assert::AreEqual(u8"urn:oasis:names:specification:docbook:dtd:xml:4.1.2", ((String)_TestUriUrn.GetAbsoluteUri()).GetCharArray());
		}

		TEST_METHOD(GetSchema)
		{
			Assert::AreEqual(u8"https", ((String)_TestUriHttps.GetSchema()).GetCharArray());
			Assert::AreEqual(u8"ftp", ((String)_TestUriFtp.GetSchema()).GetCharArray());
			Assert::AreEqual(u8"mailto", ((String)_TestUriMailTo.GetSchema()).GetCharArray());
			
			Assert::AreEqual(u8"news", ((String)_TestUriNews.GetSchema()).GetCharArray());
			Assert::AreEqual(u8"ldap", ((String)_TestUriLdap.GetSchema()).GetCharArray());
			Assert::AreEqual(u8"tel", ((String)_TestUriTel.GetSchema()).GetCharArray());
			Assert::AreEqual(u8"telnet", ((String)_TestUriTelNet.GetSchema()).GetCharArray());
			Assert::AreEqual(u8"urn", ((String)_TestUriUrn.GetSchema()).GetCharArray());
		}

		TEST_METHOD(GetAuthorities)
		{
			Assert::AreEqual(u8"www.google.com:447", ((String)_TestUriHttps.GetAuthority()).GetCharArray());
			Assert::AreEqual(u8"username:password@www.google.com", ((String)_TestUriFtp.GetAuthority()).GetCharArray());
			Assert::AreEqual(u8"some@mail.com", ((String)_TestUriMailTo.GetAuthority()).GetCharArray());
			
			Assert::AreEqual(u8"comp.infosystems.www.servers.unix", ((String)_TestUriNews.GetAuthority()).GetCharArray());
			Assert::AreEqual(u8"[2001:db8::7]", ((String)_TestUriLdap.GetAuthority()).GetCharArray());
			Assert::AreEqual(u8"+1-816-555-1212", ((String)_TestUriTel.GetAuthority()).GetCharArray());
			Assert::AreEqual(u8"192.0.2.16:80", ((String)_TestUriTelNet.GetAuthority()).GetCharArray());
			Assert::AreEqual(u8"oasis:names:specification:docbook:dtd:xml:4.1.2", ((String)_TestUriUrn.GetAuthority()).GetCharArray());
		}

		TEST_METHOD(GetUserInfo)
		{
			Assert::AreEqual(u8"", ((String)_TestUriHttps.GetUserInfo()).GetCharArray());
			Assert::AreEqual(u8"username:password", ((String)_TestUriFtp.GetUserInfo()).GetCharArray());
			Assert::AreEqual(u8"some", ((String)_TestUriMailTo.GetUserInfo()).GetCharArray());
			
			Assert::AreEqual(u8"", ((String)_TestUriNews.GetUserInfo()).GetCharArray());
			Assert::AreEqual(u8"", ((String)_TestUriLdap.GetUserInfo()).GetCharArray());
			Assert::AreEqual(u8"", ((String)_TestUriTel.GetUserInfo()).GetCharArray());
			Assert::AreEqual(u8"", ((String)_TestUriTelNet.GetUserInfo()).GetCharArray());
			Assert::AreEqual(u8"", ((String)_TestUriUrn.GetUserInfo()).GetCharArray());
		}

		TEST_METHOD(GetHost)
		{
			Assert::AreEqual(u8"www.google.com", ((String)_TestUriHttp.GetHost()).GetCharArray());
			Assert::AreEqual(u8"www.google.com", ((String)_TestUriHttps.GetHost()).GetCharArray());
			Assert::AreEqual(u8"www.google.com", ((String)_TestUriFtp.GetHost()).GetCharArray());
			Assert::AreEqual(u8"mail.com", ((String)_TestUriMailTo.GetHost()).GetCharArray());
			
			Assert::AreEqual(u8"comp.infosystems.www.servers.unix", ((String)_TestUriNews.GetHost()).GetCharArray());
			// ToDo: ':' is not allowed in the host normally resulting in "[2001" - a specific LDAP-Uri-Parser should probably do this differently
			Assert::AreEqual(u8"[2001", ((String)_TestUriLdap.GetHost()).GetCharArray());
			// ToDo: does a specific TEL-Uri-Parser handle this differently? probably
			Assert::AreEqual(u8"+1-816-555-1212", ((String)_TestUriTel.GetHost()).GetCharArray());
			Assert::AreEqual(u8"192.0.2.16", ((String)_TestUriTelNet.GetHost()).GetCharArray());
			// ToDo: does a specific URN-Uri-Parser handle this differently? probably
			Assert::AreEqual(u8"oasis", ((String)_TestUriUrn.GetHost()).GetCharArray());
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
			Assert::AreEqual(u8"", ((String)_TestUriHttp.GetPathAndQuery()).GetCharArray());
			Assert::AreEqual(u8"someFold/subfol/bla?xyz=123&jkhsdf=8ndsf", ((String)_TestUriHttps.GetPathAndQuery()).GetCharArray());
			Assert::AreEqual(u8"xomeFold/subfol/bla?xyz=123&jkhsdf=8ndsf", ((String)_TestUriFtp.GetPathAndQuery()).GetCharArray());
			Assert::AreEqual(u8"", ((String)_TestUriMailTo.GetPathAndQuery()).GetCharArray());
			
			Assert::AreEqual(u8"some/random/path", ((String)_TestUriNews.GetPathAndQuery()).GetCharArray());
			Assert::AreEqual(u8"c=GB?objectClass?onex", ((String)_TestUriLdap.GetPathAndQuery()).GetCharArray());
			Assert::AreEqual(u8"", ((String)_TestUriTel.GetPathAndQuery()).GetCharArray());
			Assert::AreEqual(u8"some/path?query=something", ((String)_TestUriTelNet.GetPathAndQuery()).GetCharArray());
			Assert::AreEqual(u8"", ((String)_TestUriUrn.GetPathAndQuery()).GetCharArray());
		}

		TEST_METHOD(GetPath)
		{
			Assert::AreEqual(u8"someFold/subfol/bla", ((String)_TestUriHttps.GetPath()).GetCharArray());
			Assert::AreEqual(u8"xomeFold/subfol/bla", ((String)_TestUriFtp.GetPath()).GetCharArray());
			Assert::AreEqual(u8"", ((String)_TestUriMailTo.GetPath()).GetCharArray());
			
			Assert::AreEqual(u8"some/random/path", ((String)_TestUriNews.GetPath()).GetCharArray());
			Assert::AreEqual(u8"c=GB", ((String)_TestUriLdap.GetPath()).GetCharArray());
			Assert::AreEqual(u8"", ((String)_TestUriTel.GetPath()).GetCharArray());
			Assert::AreEqual(u8"some/path", ((String)_TestUriTelNet.GetPath()).GetCharArray());
			Assert::AreEqual(u8"", ((String)_TestUriUrn.GetPath()).GetCharArray());
		}

		TEST_METHOD(GetQuery)
		{
			Assert::AreEqual(u8"xyz=123&jkhsdf=8ndsf", ((String)_TestUriHttps.GetQuery()).GetCharArray());
			Assert::AreEqual(u8"xyz=123&jkhsdf=8ndsf", ((String)_TestUriFtp.GetQuery()).GetCharArray());
			Assert::AreEqual(u8"", ((String)_TestUriMailTo.GetQuery()).GetCharArray());
			
			Assert::AreEqual(u8"", ((String)_TestUriNews.GetQuery()).GetCharArray());
			Assert::AreEqual(u8"objectClass?onex", ((String)_TestUriLdap.GetQuery()).GetCharArray());
			Assert::AreEqual(u8"", ((String)_TestUriTel.GetQuery()).GetCharArray());
			Assert::AreEqual(u8"query=something", ((String)_TestUriTelNet.GetQuery()).GetCharArray());
			Assert::AreEqual(u8"", ((String)_TestUriUrn.GetQuery()).GetCharArray());
		}

		TEST_METHOD(GetFragment)
		{
			Assert::AreEqual(u8"fragmentstuff", ((String)_TestUriHttps.GetFragment()).GetCharArray());
			Assert::AreEqual(u8"", ((String)_TestUriFtp.GetFragment()).GetCharArray());
			Assert::AreEqual(u8"", ((String)_TestUriMailTo.GetFragment()).GetCharArray());
			
			Assert::AreEqual(u8"fragmentyoyo", ((String)_TestUriNews.GetFragment()).GetCharArray());
			Assert::AreEqual(u8"", ((String)_TestUriLdap.GetFragment()).GetCharArray());
			Assert::AreEqual(u8"", ((String)_TestUriTel.GetFragment()).GetCharArray());
			Assert::AreEqual(u8"", ((String)_TestUriTelNet.GetFragment()).GetCharArray());
			Assert::AreEqual(u8"", ((String)_TestUriUrn.GetFragment()).GetCharArray());
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
