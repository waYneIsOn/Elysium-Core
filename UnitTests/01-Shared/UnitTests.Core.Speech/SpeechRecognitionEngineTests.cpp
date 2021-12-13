#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core/DateTime.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Speech/SpeechRecognitionEngine.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Speech::Recognition;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Speech
{
	TEST_CLASS(SpeechRecognitionEngineTests)
	{
	public:
		TEST_METHOD(Bla)
		{
			SpeechRecognitionEngine RecognitionEngine = SpeechRecognitionEngine();
			RecognitionEngine.Test();
		}
	};
}
