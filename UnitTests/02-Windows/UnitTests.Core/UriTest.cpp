#include "CppUnitTest.h"

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
			Assert::AreEqual(L"://", Uri::SchemeDelimiter.GetCharArray());

			Assert::AreEqual(L"file", Uri::UriSchemeFile.GetCharArray());
			Assert::AreEqual(L"ftp", Uri::UriSchemeFtp.GetCharArray());
			Assert::AreEqual(L"gopher", Uri::UriSchemeGopher.GetCharArray());
			Assert::AreEqual(L"http", Uri::UriSchemeHttp.GetCharArray());
			Assert::AreEqual(L"https", Uri::UriSchemeHttps.GetCharArray());
			Assert::AreEqual(L"irc", Uri::UriSchemeIrc.GetCharArray());
			Assert::AreEqual(L"ldap", Uri::UriSchemeLdap.GetCharArray());
			Assert::AreEqual(L"mailto", Uri::UriSchemeMailto.GetCharArray());
			Assert::AreEqual(L"net.pipe", Uri::UriSchemeNetPipe.GetCharArray());
			Assert::AreEqual(L"net.tcp", Uri::UriSchemeNetTcp.GetCharArray());
			Assert::AreEqual(L"news", Uri::UriSchemeNews.GetCharArray());
			Assert::AreEqual(L"nntp", Uri::UriSchemeNntp.GetCharArray());
			Assert::AreEqual(L"wss", Uri::UriSchemeSecureWebSocket.GetCharArray());
			Assert::AreEqual(L"tel", Uri::UriSchemeTel.GetCharArray());
			Assert::AreEqual(L"telnet", Uri::UriSchemeTelNet.GetCharArray());
			Assert::AreEqual(L"urn", Uri::UriSchemeUrn.GetCharArray());
			Assert::AreEqual(L"ws", Uri::UriSchemeWebSocket.GetCharArray());
		}

		TEST_METHOD(GetAbsoluteUri)
		{
			Assert::AreEqual(L"https://www.google.com:447/someFold/subfol/bla?xyz=123&jkhsdf=8ndsf#fragmentstuff", ((String)_TestUriHttps.GetAbsoluteUri()).GetCharArray());
			Assert::AreEqual(L"ftp://username:password@www.google.com/xomeFold/subfol/bla?xyz=123&jkhsdf=8ndsf#", ((String)_TestUriFtp.GetAbsoluteUri()).GetCharArray());
			Assert::AreEqual(L"mailto:some@mail.com", ((String)_TestUriMailTo.GetAbsoluteUri()).GetCharArray());

			Assert::AreEqual(L"news:comp.infosystems.www.servers.unix/some/random/path#fragmentyoyo", ((String)_TestUriNews.GetAbsoluteUri()).GetCharArray());
			Assert::AreEqual(L"ldap://[2001:db8::7]/c=GB?objectClass?onex", ((String)_TestUriLdap.GetAbsoluteUri()).GetCharArray());
			Assert::AreEqual(L"tel:+1-816-555-1212", ((String)_TestUriTel.GetAbsoluteUri()).GetCharArray());
			Assert::AreEqual(L"telnet://192.0.2.16:80/some/path?query=something", ((String)_TestUriTelNet.GetAbsoluteUri()).GetCharArray());
			Assert::AreEqual(L"urn:oasis:names:specification:docbook:dtd:xml:4.1.2", ((String)_TestUriUrn.GetAbsoluteUri()).GetCharArray());
		}

		TEST_METHOD(GetSchema)
		{
			Assert::AreEqual(L"https", ((String)_TestUriHttps.GetSchema()).GetCharArray());
			Assert::AreEqual(L"ftp", ((String)_TestUriFtp.GetSchema()).GetCharArray());
			Assert::AreEqual(L"mailto", ((String)_TestUriMailTo.GetSchema()).GetCharArray());

			Assert::AreEqual(L"news", ((String)_TestUriNews.GetSchema()).GetCharArray());
			Assert::AreEqual(L"ldap", ((String)_TestUriLdap.GetSchema()).GetCharArray());
			Assert::AreEqual(L"tel", ((String)_TestUriTel.GetSchema()).GetCharArray());
			Assert::AreEqual(L"telnet", ((String)_TestUriTelNet.GetSchema()).GetCharArray());
			Assert::AreEqual(L"urn", ((String)_TestUriUrn.GetSchema()).GetCharArray());
		}

		TEST_METHOD(GetAuthorities)
		{
			Assert::AreEqual(L"www.google.com:447", ((String)_TestUriHttps.GetAuthority()).GetCharArray());
			Assert::AreEqual(L"username:password@www.google.com", ((String)_TestUriFtp.GetAuthority()).GetCharArray());
			Assert::AreEqual(L"some@mail.com", ((String)_TestUriMailTo.GetAuthority()).GetCharArray());

			Assert::AreEqual(L"comp.infosystems.www.servers.unix", ((String)_TestUriNews.GetAuthority()).GetCharArray());
			Assert::AreEqual(L"[2001:db8::7]", ((String)_TestUriLdap.GetAuthority()).GetCharArray());
			Assert::AreEqual(L"+1-816-555-1212", ((String)_TestUriTel.GetAuthority()).GetCharArray());
			Assert::AreEqual(L"192.0.2.16:80", ((String)_TestUriTelNet.GetAuthority()).GetCharArray());
			Assert::AreEqual(L"oasis:names:specification:docbook:dtd:xml:4.1.2", ((String)_TestUriUrn.GetAuthority()).GetCharArray());
		}

		TEST_METHOD(GetUserInfo)
		{
			Assert::AreEqual(L"", ((String)_TestUriHttps.GetUserInfo()).GetCharArray());
			Assert::AreEqual(L"username:password", ((String)_TestUriFtp.GetUserInfo()).GetCharArray());
			Assert::AreEqual(L"some", ((String)_TestUriMailTo.GetUserInfo()).GetCharArray());

			Assert::AreEqual(L"", ((String)_TestUriNews.GetUserInfo()).GetCharArray());
			Assert::AreEqual(L"", ((String)_TestUriLdap.GetUserInfo()).GetCharArray());
			Assert::AreEqual(L"", ((String)_TestUriTel.GetUserInfo()).GetCharArray());
			Assert::AreEqual(L"", ((String)_TestUriTelNet.GetUserInfo()).GetCharArray());
			Assert::AreEqual(L"", ((String)_TestUriUrn.GetUserInfo()).GetCharArray());
		}

		TEST_METHOD(GetHost)
		{
			/*
			Uri _TestUriHttps = Uri("https://www.google.com:447/someFold/subfol/bla?xyz=123&jkhsdf=8ndsf#fragmentstuff");
			Uri _TestUriFtp = Uri("ftp://username:password@www.google.com/someFold/subfol/bla?xyz=123&jkhsdf=8ndsf#");
			Uri _TestUriMailTo = Uri("mailto:some@mail.com");

			Uri _TestUriNews = Uri("news:comp.infosystems.www.servers.unix");
			Uri _TestUriLdap = Uri("ldap://[2001:db8::7]/c=GB?objectClass?onex");
			Uri _TestUriTel = Uri("tel:+1-816-555-1212");
			Uri _TestUriTelNet = Uri("telnet://192.0.2.16:80/");
			Uri _TestUriUrn = Uri("urn:oasis:names:specification:docbook:dtd:xml:4.1.2");
			*/
			Assert::AreEqual(L"www.google.com", ((String)_TestUriHttps.GetHost()).GetCharArray());
			Assert::AreEqual(L"www.google.com", ((String)_TestUriFtp.GetHost()).GetCharArray());
			Assert::AreEqual(L"mail.com", ((String)_TestUriMailTo.GetHost()).GetCharArray());

			Assert::AreEqual(L"comp.infosystems.www.servers.unix", ((String)_TestUriNews.GetHost()).GetCharArray());
			Assert::AreEqual(L"[2001:db8::7]", ((String)_TestUriLdap.GetHost()).GetCharArray());
			Assert::AreEqual(L"", ((String)_TestUriTel.GetHost()).GetCharArray());
			Assert::AreEqual(L"192.0.2.16:80", ((String)_TestUriTelNet.GetHost()).GetCharArray());
			Assert::AreEqual(L"", ((String)_TestUriUrn.GetHost()).GetCharArray());
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
			Assert::AreEqual(L"someFold/subfol/bla?xyz=123&jkhsdf=8ndsf", ((String)_TestUriHttps.GetPathAndQuery()).GetCharArray());
			Assert::AreEqual(L"xomeFold/subfol/bla?xyz=123&jkhsdf=8ndsf", ((String)_TestUriFtp.GetPathAndQuery()).GetCharArray());
			Assert::AreEqual(L"", ((String)_TestUriMailTo.GetPathAndQuery()).GetCharArray());

			Assert::AreEqual(L"some/random/path", ((String)_TestUriNews.GetPathAndQuery()).GetCharArray());
			Assert::AreEqual(L"c=GB?objectClass?onex", ((String)_TestUriLdap.GetPathAndQuery()).GetCharArray());
			Assert::AreEqual(L"", ((String)_TestUriTel.GetPathAndQuery()).GetCharArray());
			Assert::AreEqual(L"some/path?query=something", ((String)_TestUriTelNet.GetPathAndQuery()).GetCharArray());
			Assert::AreEqual(L"", ((String)_TestUriUrn.GetPathAndQuery()).GetCharArray());
		}

		TEST_METHOD(GetPath)
		{
			Assert::AreEqual(L"someFold/subfol/bla", ((String)_TestUriHttps.GetPath()).GetCharArray());
			Assert::AreEqual(L"xomeFold/subfol/bla", ((String)_TestUriFtp.GetPath()).GetCharArray());
			Assert::AreEqual(L"", ((String)_TestUriMailTo.GetPath()).GetCharArray());

			Assert::AreEqual(L"some/random/path", ((String)_TestUriNews.GetPath()).GetCharArray());
			Assert::AreEqual(L"c=GB", ((String)_TestUriLdap.GetPath()).GetCharArray());
			Assert::AreEqual(L"", ((String)_TestUriTel.GetPath()).GetCharArray());
			Assert::AreEqual(L"some/path", ((String)_TestUriTelNet.GetPath()).GetCharArray());
			Assert::AreEqual(L"", ((String)_TestUriUrn.GetPath()).GetCharArray());
		}

		TEST_METHOD(GetQuery)
		{
			Assert::AreEqual(L"xyz=123&jkhsdf=8ndsf", ((String)_TestUriHttps.GetQuery()).GetCharArray());
			Assert::AreEqual(L"xyz=123&jkhsdf=8ndsf", ((String)_TestUriFtp.GetQuery()).GetCharArray());
			Assert::AreEqual(L"", ((String)_TestUriMailTo.GetQuery()).GetCharArray());

			Assert::AreEqual(L"", ((String)_TestUriNews.GetQuery()).GetCharArray());
			Assert::AreEqual(L"objectClass?onex", ((String)_TestUriLdap.GetQuery()).GetCharArray());
			Assert::AreEqual(L"", ((String)_TestUriTel.GetQuery()).GetCharArray());
			Assert::AreEqual(L"query=something", ((String)_TestUriTelNet.GetQuery()).GetCharArray());
			Assert::AreEqual(L"", ((String)_TestUriUrn.GetQuery()).GetCharArray());
		}

		TEST_METHOD(GetFragment)
		{
			Assert::AreEqual(L"fragmentstuff", ((String)_TestUriHttps.GetFragment()).GetCharArray());
			Assert::AreEqual(L"", ((String)_TestUriFtp.GetFragment()).GetCharArray());
			Assert::AreEqual(L"", ((String)_TestUriMailTo.GetFragment()).GetCharArray());

			Assert::AreEqual(L"fragmentyoyo", ((String)_TestUriNews.GetFragment()).GetCharArray());
			Assert::AreEqual(L"", ((String)_TestUriLdap.GetFragment()).GetCharArray());
			Assert::AreEqual(L"", ((String)_TestUriTel.GetFragment()).GetCharArray());
			Assert::AreEqual(L"", ((String)_TestUriTelNet.GetFragment()).GetCharArray());
			Assert::AreEqual(L"", ((String)_TestUriUrn.GetFragment()).GetCharArray());
		}
	private:
		// fields
		Uri _TestUriHttps = Uri(L"https://www.google.com:447/someFold/subfol/bla?xyz=123&jkhsdf=8ndsf#fragmentstuff");
		Uri _TestUriFtp = Uri(L"ftp://username:password@www.google.com/xomeFold/subfol/bla?xyz=123&jkhsdf=8ndsf#");
		Uri _TestUriMailTo = Uri(L"mailto:some@mail.com");

		Uri _TestUriNews = Uri(L"news:comp.infosystems.www.servers.unix/some/random/path#fragmentyoyo");
		Uri _TestUriLdap = Uri(L"ldap://[2001:db8::7]/c=GB?objectClass?onex");
		Uri _TestUriTel = Uri(L"tel:+1-816-555-1212");
		Uri _TestUriTelNet = Uri(L"telnet://192.0.2.16:80/some/path?query=something");
		Uri _TestUriUrn = Uri(L"urn:oasis:names:specification:docbook:dtd:xml:4.1.2");
	};
}
