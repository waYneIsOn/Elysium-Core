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
		TEST_METHOD(HashMD4)
		{
			const Encoding& UsedEncoding = Encoding::ASCII();
			MD4 Algorithm = MD4();

			Array<byte> Bytes2 = UsedEncoding.GetBytes(_Value2, 0, _Value2.GetLength());

			//Array<byte> HashBytes1 = Hash(Algorithm, UsedEncoding.GetBytes(_Value1, 0, _Value1.GetLength()));
			Array<byte> HashBytes2 = Hash(Algorithm, Bytes2);
		}

		TEST_METHOD(HashMD5)
		{
			const Encoding& UsedEncoding = Encoding::ASCII();
			MD5 Algorithm = MD5();

			Array<byte> Bytes2 = UsedEncoding.GetBytes(_Value2, 0, _Value2.GetLength());

			//Array<byte> HashBytes1 = Hash(Algorithm, UsedEncoding.GetBytes(_Value1, 0, _Value1.GetLength()));
			Array<byte> HashBytes2 = Hash(Algorithm, Bytes2);
		}
	private:
		const String _Value1 = u8"";
		const String _Value2 = u8"bla";

		Array<byte> Hash(HashAlgorithm& Algorithm, Array<byte>& Bytes)
		{
			return Algorithm.ComputeHash(&Bytes[0], Bytes.GetLength());
		}
	};
}
