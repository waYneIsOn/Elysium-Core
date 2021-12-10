#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core/DateTime.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Speech/SpeechSynthesizer.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Globalization;
using namespace Elysium::Core::Speech::Synthesis;
using namespace Elysium::Core::Template::Container;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Reflection
{
	TEST_CLASS(SpeechSynthesizerTests)
	{
	public:
		TEST_METHOD(CheckVoices)
		{
			SpeechSynthesizer Synthesizer = SpeechSynthesizer();
			Vector<InstalledVoice> AllInstalledVoices = Synthesizer.GetInstalledVoices();
			Assert::IsTrue(AllInstalledVoices.GetLength() > 0);
			
			for (Elysium::Core::size i = 0; i < AllInstalledVoices.GetLength(); i++)
			{
				const bool Enabled = AllInstalledVoices[i].GetEnabled();
				const VoiceInfo& Voice = AllInstalledVoices[i].GetVoiceInfo();

				//Logger::WriteMessage(AllInstalledVoices[i].GetVoiceInfo().GetId());
			}

			VoiceInfo Voice = Synthesizer.GetVoice();
			const CultureInfo VoiceCulture = Voice.GetCulture();

			AssertExtended::AreEqual(u8"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Speech\\Voices\\Tokens\\TTS_MS_EN-US_ZIRA_11.0", Voice.GetId());
			AssertExtended::AreEqual(u8"Microsoft Zira Desktop", Voice.GetName());
			Assert::AreEqual(static_cast<Elysium::Core::uint8_t>(VoiceAge::Adult), static_cast<Elysium::Core::uint8_t>(Voice.GetAge()));
			Assert::AreEqual(static_cast<Elysium::Core::uint8_t>(VoiceGender::Female), static_cast<Elysium::Core::uint8_t>(Voice.GetGender()));
			Assert::AreEqual(1033, VoiceCulture.GetLCID());
			/*
			DateTime Start = DateTime::Now();
			Synthesizer.Speak(u8"Look at you, hacker: a pathetic creature of meat and bone, panting and sweating as you run through my corridors. How can you challenge a perfect immortal machine?");
			TimeSpan ElapsedTime = DateTime::Now() - Start;
			Assert::IsTrue(ElapsedTime.GetTotalSeconds() > 10);
			*/
		}

		TEST_METHOD(SpeakEnglish)
		{
			SpeechSynthesizer Synthesizer = SpeechSynthesizer();

			CultureInfo EnglishUS = CultureInfo(u8"en-US", false);
			Vector<InstalledVoice> InstalledVoices = Synthesizer.GetInstalledVoices(EnglishUS);
			Assert::IsTrue(InstalledVoices.GetLength() > 0);

			Synthesizer.SelectVoice(InstalledVoices[0].GetVoiceInfo().GetName());
			Synthesizer.SelectVoice(InstalledVoices[0].GetVoiceInfo());

			DateTime Start = DateTime::Now();
			Synthesizer.Speak(u8"This is a simple english sentence taking a bit over five seconds to pronounce.");
			TimeSpan ElapsedTime = DateTime::Now() - Start;
			Assert::IsTrue(ElapsedTime.GetTotalSeconds() > 5);
		}

		TEST_METHOD(SpeakGerman)
		{
			SpeechSynthesizer Synthesizer = SpeechSynthesizer();

			CultureInfo GermanGermany = CultureInfo(u8"de-DE", false);
			Vector<InstalledVoice> InstalledVoices = Synthesizer.GetInstalledVoices(GermanGermany);
			Assert::IsTrue(InstalledVoices.GetLength() > 0);

			Synthesizer.SelectVoice(InstalledVoices[0].GetVoiceInfo().GetName());
			Synthesizer.SelectVoice(InstalledVoices[0].GetVoiceInfo());
			
			DateTime Start = DateTime::Now();
			Synthesizer.Speak(u8"Das ist ein einfacher deutscher Satz, welcher etwas mehr als sieben Sekunden zur Aussprache benötigt.");
			TimeSpan ElapsedTime = DateTime::Now() - Start;
			Assert::IsTrue(ElapsedTime.GetTotalSeconds() > 7);
		}

		TEST_METHOD(SpeakSsml)
		{
			SpeechSynthesizer Synthesizer = SpeechSynthesizer();

			DateTime Start = DateTime::Now();
			Synthesizer.SpeakSsml(u8"<speak version=\"1.0\" xmlns=\"http://www.w3.org/2001/10/synthesis\" xml:lang=\"en-US\"><say-as type=\"date:mdy\"> 1/29/2009 </say-as></speak>");
			TimeSpan ElapsedTime = DateTime::Now() - Start;
			Assert::IsTrue(ElapsedTime.GetTotalSeconds() > 3);
		}
	};
}
