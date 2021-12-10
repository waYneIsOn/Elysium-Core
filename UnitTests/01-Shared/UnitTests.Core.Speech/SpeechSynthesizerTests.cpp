#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core/DateTime.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Speech/SpeechSynthesizer.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Globalization;
using namespace Elysium::Core::Speech::Synthesis;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Reflection
{
	TEST_CLASS(SpeechSynthesizerTests)
	{
	public:
		TEST_METHOD(CheckUsedVoice)
		{
			SpeechSynthesizer Synthesizer = SpeechSynthesizer();

			VoiceInfo Voice = Synthesizer.GetVoice();
			AssertExtended::AreEqual(u8"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Speech\\Voices\\Tokens\\TTS_MS_EN-US_ZIRA_11.0", Voice.GetId());
			AssertExtended::AreEqual(u8"Microsoft Zira Desktop", Voice.GetName());
			Assert::AreEqual(static_cast<Elysium::Core::uint8_t>(VoiceAge::Adult), static_cast<Elysium::Core::uint8_t>(Voice.GetAge()));
			Assert::AreEqual(static_cast<Elysium::Core::uint8_t>(VoiceGender::Female), static_cast<Elysium::Core::uint8_t>(Voice.GetGender()));

			const CultureInfo VoiceCulture = Voice.GetCulture();
			Assert::AreEqual(409, VoiceCulture.GetLCID());

			DateTime Start = DateTime::Now();
			Synthesizer.Speak(u8"Look at you, hacker: a pathetic creature of meat and bone, panting and sweating as you run through my corridors. How can you challenge a perfect immortal machine?");
			TimeSpan ElapsedTime = DateTime::Now() - Start;
			Assert::IsTrue(ElapsedTime.GetTotalSeconds() > 10);
		}
	};
}
