#include "CppUnitTest.h"
/*
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
			Assert::AreEqual("://", Uri::SchemeDelimiter.c_str());

			Assert::AreEqual("file", Uri::UriSchemeFile.c_str());
			Assert::AreEqual("ftp", Uri::UriSchemeFtp.c_str());
			Assert::AreEqual("gopher", Uri::UriSchemeGopher.c_str());
			Assert::AreEqual("http", Uri::UriSchemeHttp.c_str());
			Assert::AreEqual("https", Uri::UriSchemeHttps.c_str());
			Assert::AreEqual("irc", Uri::UriSchemeIrc.c_str());
			Assert::AreEqual("ldap", Uri::UriSchemeLdap.c_str());
			Assert::AreEqual("mailto", Uri::UriSchemeMailto.c_str());
			Assert::AreEqual("net.pipe", Uri::UriSchemeNetPipe.c_str());
			Assert::AreEqual("net.tcp", Uri::UriSchemeNetTcp.c_str());
			Assert::AreEqual("news", Uri::UriSchemeNews.c_str());
			Assert::AreEqual("nntp", Uri::UriSchemeNntp.c_str());
			Assert::AreEqual("wss", Uri::UriSchemeSecureWebSocket.c_str());
			Assert::AreEqual("tel", Uri::UriSchemeTel.c_str());
			Assert::AreEqual("telnet", Uri::UriSchemeTelNet.c_str());
			Assert::AreEqual("urn", Uri::UriSchemeUrn.c_str());
			Assert::AreEqual("ws", Uri::UriSchemeWebSocket.c_str());
		}

		TEST_METHOD(GetAbsoluteUri)
		{
			Assert::AreEqual("https://www.google.com:447/someFold/subfol/bla?xyz=123&jkhsdf=8ndsf#fragmentstuff", ((string)_TestUriHttps.GetAbsoluteUri()).c_str());
			Assert::AreEqual("ftp://username:password@www.google.com/xomeFold/subfol/bla?xyz=123&jkhsdf=8ndsf#", ((string)_TestUriFtp.GetAbsoluteUri()).c_str());
			Assert::AreEqual("mailto:some@mail.com", ((string)_TestUriMailTo.GetAbsoluteUri()).c_str());

			Assert::AreEqual("news:comp.infosystems.www.servers.unix/some/random/path#fragmentyoyo", ((string)_TestUriNews.GetAbsoluteUri()).c_str());
			Assert::AreEqual("ldap://[2001:db8::7]/c=GB?objectClass?onex", ((string)_TestUriLdap.GetAbsoluteUri()).c_str());
			Assert::AreEqual("tel:+1-816-555-1212", ((string)_TestUriTel.GetAbsoluteUri()).c_str());
			Assert::AreEqual("telnet://192.0.2.16:80/some/path?query=something", ((string)_TestUriTelNet.GetAbsoluteUri()).c_str());
			Assert::AreEqual("urn:oasis:names:specification:docbook:dtd:xml:4.1.2", ((string)_TestUriUrn.GetAbsoluteUri()).c_str());
		}

		TEST_METHOD(GetSchema)
		{
			Assert::AreEqual("https", ((string)_TestUriHttps.GetSchema()).c_str());
			Assert::AreEqual("ftp", ((string)_TestUriFtp.GetSchema()).c_str());
			Assert::AreEqual("mailto", ((string)_TestUriMailTo.GetSchema()).c_str());

			Assert::AreEqual("news", ((string)_TestUriNews.GetSchema()).c_str());
			Assert::AreEqual("ldap", ((string)_TestUriLdap.GetSchema()).c_str());
			Assert::AreEqual("tel", ((string)_TestUriTel.GetSchema()).c_str());
			Assert::AreEqual("telnet", ((string)_TestUriTelNet.GetSchema()).c_str());
			Assert::AreEqual("urn", ((string)_TestUriUrn.GetSchema()).c_str());
		}

		TEST_METHOD(GetAuthorities)
		{
			Assert::AreEqual("www.google.com:447", ((string)_TestUriHttps.GetAuthority()).c_str());
			Assert::AreEqual("username:password@www.google.com", ((string)_TestUriFtp.GetAuthority()).c_str());
			Assert::AreEqual("some@mail.com", ((string)_TestUriMailTo.GetAuthority()).c_str());

			Assert::AreEqual("comp.infosystems.www.servers.unix", ((string)_TestUriNews.GetAuthority()).c_str());
			Assert::AreEqual("[2001:db8::7]", ((string)_TestUriLdap.GetAuthority()).c_str());
			Assert::AreEqual("+1-816-555-1212", ((string)_TestUriTel.GetAuthority()).c_str());
			Assert::AreEqual("192.0.2.16:80", ((string)_TestUriTelNet.GetAuthority()).c_str());
			Assert::AreEqual("oasis:names:specification:docbook:dtd:xml:4.1.2", ((string)_TestUriUrn.GetAuthority()).c_str());
		}

		TEST_METHOD(GetUserInfo)
		{
			Assert::AreEqual("", ((string)_TestUriHttps.GetUserInfo()).c_str());
			Assert::AreEqual("username:password", ((string)_TestUriFtp.GetUserInfo()).c_str());
			Assert::AreEqual("some", ((string)_TestUriMailTo.GetUserInfo()).c_str());

			Assert::AreEqual("", ((string)_TestUriNews.GetUserInfo()).c_str());
			Assert::AreEqual("", ((string)_TestUriLdap.GetUserInfo()).c_str());
			Assert::AreEqual("", ((string)_TestUriTel.GetUserInfo()).c_str());
			Assert::AreEqual("", ((string)_TestUriTelNet.GetUserInfo()).c_str());
			Assert::AreEqual("", ((string)_TestUriUrn.GetUserInfo()).c_str());
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
			*-/
			Assert::AreEqual("www.google.com", ((string)_TestUriHttps.GetHost()).c_str());
			Assert::AreEqual("www.google.com", ((string)_TestUriFtp.GetHost()).c_str());
			Assert::AreEqual("mail.com", ((string)_TestUriMailTo.GetHost()).c_str());

			Assert::AreEqual("comp.infosystems.www.servers.unix", ((string)_TestUriNews.GetHost()).c_str());
			Assert::AreEqual("[2001:db8::7]", ((string)_TestUriLdap.GetHost()).c_str());
			Assert::AreEqual("", ((string)_TestUriTel.GetHost()).c_str());
			Assert::AreEqual("192.0.2.16:80", ((string)_TestUriTelNet.GetHost()).c_str());
			Assert::AreEqual("", ((string)_TestUriUrn.GetHost()).c_str());
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
			Assert::AreEqual("someFold/subfol/bla?xyz=123&jkhsdf=8ndsf", ((string)_TestUriHttps.GetPathAndQuery()).c_str());
			Assert::AreEqual("xomeFold/subfol/bla?xyz=123&jkhsdf=8ndsf", ((string)_TestUriFtp.GetPathAndQuery()).c_str());
			Assert::AreEqual("", ((string)_TestUriMailTo.GetPathAndQuery()).c_str());

			Assert::AreEqual("some/random/path", ((string)_TestUriNews.GetPathAndQuery()).c_str());
			Assert::AreEqual("c=GB?objectClass?onex", ((string)_TestUriLdap.GetPathAndQuery()).c_str());
			Assert::AreEqual("", ((string)_TestUriTel.GetPathAndQuery()).c_str());
			Assert::AreEqual("some/path?query=something", ((string)_TestUriTelNet.GetPathAndQuery()).c_str());
			Assert::AreEqual("", ((string)_TestUriUrn.GetPathAndQuery()).c_str());
		}

		TEST_METHOD(GetPath)
		{
			Assert::AreEqual("someFold/subfol/bla", ((string)_TestUriHttps.GetPath()).c_str());
			Assert::AreEqual("xomeFold/subfol/bla", ((string)_TestUriFtp.GetPath()).c_str());
			Assert::AreEqual("", ((string)_TestUriMailTo.GetPath()).c_str());

			Assert::AreEqual("some/random/path", ((string)_TestUriNews.GetPath()).c_str());
			Assert::AreEqual("c=GB", ((string)_TestUriLdap.GetPath()).c_str());
			Assert::AreEqual("", ((string)_TestUriTel.GetPath()).c_str());
			Assert::AreEqual("some/path", ((string)_TestUriTelNet.GetPath()).c_str());
			Assert::AreEqual("", ((string)_TestUriUrn.GetPath()).c_str());
		}

		TEST_METHOD(GetQuery)
		{
			Assert::AreEqual("xyz=123&jkhsdf=8ndsf", ((string)_TestUriHttps.GetQuery()).c_str());
			Assert::AreEqual("xyz=123&jkhsdf=8ndsf", ((string)_TestUriFtp.GetQuery()).c_str());
			Assert::AreEqual("", ((string)_TestUriMailTo.GetQuery()).c_str());

			Assert::AreEqual("", ((string)_TestUriNews.GetQuery()).c_str());
			Assert::AreEqual("objectClass?onex", ((string)_TestUriLdap.GetQuery()).c_str());
			Assert::AreEqual("", ((string)_TestUriTel.GetQuery()).c_str());
			Assert::AreEqual("query=something", ((string)_TestUriTelNet.GetQuery()).c_str());
			Assert::AreEqual("", ((string)_TestUriUrn.GetQuery()).c_str());
		}

		TEST_METHOD(GetFragment)
		{
			Assert::AreEqual("fragmentstuff", ((string)_TestUriHttps.GetFragment()).c_str());
			Assert::AreEqual("", ((string)_TestUriFtp.GetFragment()).c_str());
			Assert::AreEqual("", ((string)_TestUriMailTo.GetFragment()).c_str());

			Assert::AreEqual("fragmentyoyo", ((string)_TestUriNews.GetFragment()).c_str());
			Assert::AreEqual("", ((string)_TestUriLdap.GetFragment()).c_str());
			Assert::AreEqual("", ((string)_TestUriTel.GetFragment()).c_str());
			Assert::AreEqual("", ((string)_TestUriTelNet.GetFragment()).c_str());
			Assert::AreEqual("", ((string)_TestUriUrn.GetFragment()).c_str());
		}
	private:
		// fields
		Uri _TestUriHttps = Uri("https://www.google.com:447/someFold/subfol/bla?xyz=123&jkhsdf=8ndsf#fragmentstuff");
		Uri _TestUriFtp = Uri("ftp://username:password@www.google.com/xomeFold/subfol/bla?xyz=123&jkhsdf=8ndsf#");
		Uri _TestUriMailTo = Uri("mailto:some@mail.com");

		Uri _TestUriNews = Uri("news:comp.infosystems.www.servers.unix/some/random/path#fragmentyoyo");
		Uri _TestUriLdap = Uri("ldap://[2001:db8::7]/c=GB?objectClass?onex");
		Uri _TestUriTel = Uri("tel:+1-816-555-1212");
		Uri _TestUriTelNet = Uri("telnet://192.0.2.16:80/some/path?query=something");
		Uri _TestUriUrn = Uri("urn:oasis:names:specification:docbook:dtd:xml:4.1.2");
	};
}
*/