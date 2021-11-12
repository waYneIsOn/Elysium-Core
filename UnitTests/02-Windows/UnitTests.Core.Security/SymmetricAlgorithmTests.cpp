#include "CppUnitTest.h"

#include "../../../Libraries/01-Shared/Elysium.Core/String.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Security.Cryptography.Primitives/DES.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Text/Encoding.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Collections::Template;
using namespace Elysium::Core::Security::Cryptography;
using namespace Elysium::Core::Text;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Security::Cryptography
{
	TEST_CLASS(SymmetricAlgorithmTests)
	{
	public:
		TEST_METHOD(DESTest)
		{
			DES DESProvider = DES();
			DESProvider.Test();
		}
	};
}
