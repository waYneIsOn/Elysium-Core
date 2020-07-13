#include "CppUnitTest.h"

#ifndef ELYSIUM_CORE_STRING
#include "../../../Libraries/01-Shared/Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_MD4
#include "../../../Libraries/01-Shared/Elysium.Core.Security.Cryptography.Algorithms/MD4.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_MD5
#include "../../../Libraries/01-Shared/Elysium.Core.Security.Cryptography.Algorithms/MD5.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../../../Libraries/01-Shared/Elysium.Core.Text/Encoding.hpp"
#endif

using namespace Elysium::Core;
using namespace Elysium::Core::Collections::Template;
using namespace Elysium::Core::Security::Cryptography;
using namespace Elysium::Core::Text;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Security::Cryptography
{
	TEST_CLASS(HashAlgorithmTest)
	{
	public:
		TEST_METHOD(MD4)
		{
			const Encoding& UsedEncoding = Encoding::ASCII();
			HashAlgorithm& Algorithm = MD4::MD4();

			//Array<byte> HashBytes1 = Hash(Algorithm, UsedEncoding.GetBytes(_Value1, 0, _Value1.GetLength()));
			Array<byte> HashBytes2 = Hash(Algorithm, UsedEncoding.GetBytes(_Value2, 0, _Value2.GetLength()));
		}

		TEST_METHOD(MD5)
		{
			const Encoding& UsedEncoding = Encoding::ASCII();
			HashAlgorithm& Algorithm = MD5::MD5();

			//Array<byte> HashBytes1 = Hash(Algorithm, UsedEncoding.GetBytes(_Value1, 0, _Value1.GetLength()));
			Array<byte> HashBytes2 = Hash(Algorithm, UsedEncoding.GetBytes(_Value2, 0, _Value2.GetLength()));
		}
	private:
		const String _Value1 = u"";
		const String _Value2 = u"bla";

		Array<byte> Hash(HashAlgorithm& Algorithm, List<byte> Bytes)
		{
			return Algorithm.ComputeHash(&Bytes[0], Bytes.GetCount());
		}
	};
}
