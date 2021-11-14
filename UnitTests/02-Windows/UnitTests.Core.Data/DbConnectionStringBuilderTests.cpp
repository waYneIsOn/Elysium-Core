#include "CppUnitTest.h"
#include "CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Data.TdsClient/TdsConnectionStringBuilder.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Data::TdsClient;
using namespace Elysium::Core::Text;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Data::Common
{
	TEST_CLASS(DbConnectionStringBuilderTests)
	{
	public:
		TEST_METHOD(BuildTdsFromMethods)
		{
			TdsConnectionStringBuilder Builder = TdsConnectionStringBuilder();
			Builder.SetServer(u8"127.0.0.1,1337");
			Builder.SetDatabase(u8"master");
			Builder.SetIsTrustedConnection(true);

			AssertExtended::AreEqual(u8"Trusted_Connection=Yes;Server=127.0.0.1,1337;Database=master;", Builder.GetConnectionString());
		}

		TEST_METHOD(BuildTdsFromStrings)
		{
			TdsConnectionStringBuilder Builder = TdsConnectionStringBuilder();
			Builder.SetConnectionString(u8"Application Name=Elysium Framework;Server=localhost;Database=ElysiumTest;Trusted_Connection=Yes;");

			AssertExtended::AreEqual(u8"localhost", Builder[u8"Server"]);
		}
	};
}
