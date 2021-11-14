#include "CppUnitTest.h"
#include "CppUnitTestFrameworkExtension.hpp"

#include "DatabaseTestBase.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Net/SocketException.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Data/DbDataReader.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Data.TdsClient/TdsConnection.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Data::Common;
using namespace Elysium::Core::Data::TdsClient;
using namespace Elysium::Core::Net::Sockets;
using namespace Elysium::Core::Text;

namespace UnitTests::Core::Data::TdsClient
{
	TEST_CLASS(MSSqlTests), DatabaseTestBase
	{
	public:
		TEST_CLASS_INITIALIZE(ClassInitialize)
		{

		}

		TEST_CLASS_CLEANUP(ClassCleanup)
		{

		}

		TEST_METHOD_INITIALIZE(Initialize)
		{

		}

		TEST_METHOD(Bla)
		{
			try
			{
				TdsConnection Connection = TdsConnection(TdsVersion::v7_0,
					u8"Application Name=Elysium Framework;Server=localhost;Database=ElysiumTest;Trusted_Connection=Yes;", 15000);
				Connection.Open();

				Connection.Close();
			}
			catch (SocketException& Ex)
			{
				LogException(Ex);
			}
		}
	private:
		static void LogException(SocketException& Ex)
		{
			Logger::WriteMessage((char*)&Ex.GetExceptionMessage()[0]);
			Assert::Fail();
		}
	};
}
