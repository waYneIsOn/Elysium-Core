#include "CppUnitTest.h"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Speech/SpeechSynthesizer.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Speech::Synthesis;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Reflection
{
	TEST_CLASS(SpeechSynthesizerTests)
	{
	public:
		TEST_METHOD(Bla)
		{
			SpeechSynthesizer Synthesizer = SpeechSynthesizer();
			Synthesizer.Speak(u8"some spoken text");
		}
	};
}
