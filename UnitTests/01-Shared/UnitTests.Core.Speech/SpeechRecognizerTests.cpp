#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core/DateTime.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Speech/SpeechRecognizer.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Speech::Recognition;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Reflection
{
	TEST_CLASS(SpeechRecognizerTests)
	{
	public:
		TEST_METHOD(Bla)
		{
			SpeechRecognizer Recognizer = SpeechRecognizer();
		}
	};
}
