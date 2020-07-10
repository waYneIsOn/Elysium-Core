#include "CppUnitTest.h"

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_MD4
#include "../../../Libraries/01-Shared/Elysium.Core.Security.Cryptography.Algorithms/MD4.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_MD5
#include "../../../Libraries/01-Shared/Elysium.Core.Security.Cryptography.Algorithms/MD5.hpp"
#endif

using namespace Elysium::Core::Security::Cryptography;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Security::Cryptography
{
	TEST_CLASS(HashAlgorithmTest)
	{
	public:
		TEST_METHOD(MD4)
		{
		}

		TEST_METHOD(MD5)
		{
		}
	};
}
