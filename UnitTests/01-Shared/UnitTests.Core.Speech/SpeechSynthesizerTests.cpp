#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core/DateTime.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/FileStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/MemoryStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Speech/SpeechSynthesizer.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/Thread.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Globalization;
using namespace Elysium::Core::IO;
using namespace Elysium::Core::Speech::AudioFormat;
using namespace Elysium::Core::Speech::Synthesis;
using namespace Elysium::Core::Template::Container;
using namespace Elysium::Core::Threading;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Speech
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

				Logger::WriteMessage((char*)&AllInstalledVoices[i].GetVoiceInfo().GetId()[0]);
				Logger::WriteMessage("\r\n");
			}

			VoiceInfo Voice = Synthesizer.GetVoice();
			const CultureInfo VoiceCulture = Voice.GetCulture();

			AssertExtended::AreEqual(u8"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Speech\\Voices\\Tokens\\TTS_MS_EN-US_ZIRA_11.0", Voice.GetId());
			AssertExtended::AreEqual(u8"Microsoft Zira Desktop", Voice.GetName());
			Assert::AreEqual(static_cast<Elysium::Core::uint8_t>(VoiceAge::Adult), static_cast<Elysium::Core::uint8_t>(Voice.GetAge()));
			Assert::AreEqual(static_cast<Elysium::Core::uint8_t>(VoiceGender::Female), static_cast<Elysium::Core::uint8_t>(Voice.GetGender()));
			Assert::AreEqual(1033, VoiceCulture.GetLCID());
		}

		TEST_METHOD(CheckEventVoiceChanged)
		{
			SpeechSynthesizer Synthesizer = SpeechSynthesizer();
			Synthesizer.VoiceChanged += Delegate<void, const SpeechSynthesizer&, const VoiceChangeEventArgs&>::Bind<&SpeechSynthesizer_OnVoiceChange>();

			CultureInfo EnglishUS = CultureInfo(u8"en-US", false);
			Vector<InstalledVoice> EnglishVoices = Synthesizer.GetInstalledVoices(EnglishUS);
			Assert::IsTrue(EnglishVoices.GetLength() > 0);

			CultureInfo GermanGermany = CultureInfo(u8"de-DE", false);
			Vector<InstalledVoice> GermanVoices = Synthesizer.GetInstalledVoices(GermanGermany);
			Assert::IsTrue(GermanVoices.GetLength() > 0);

			Synthesizer.SelectVoice(GermanVoices[0].GetVoiceInfo());
			Synthesizer.SelectVoice(EnglishVoices[0].GetVoiceInfo());
		}

		TEST_METHOD(SpeakEnglish)
		{
			SpeechSynthesizer Synthesizer = SpeechSynthesizer();
			Synthesizer.SetOutputToDefaultAudioDevice();

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

		TEST_METHOD(SpeakEnglishAsync)
		{
			SpeechSynthesizer Synthesizer = SpeechSynthesizer();
			Synthesizer.SetOutputToDefaultAudioDevice();
			
			DateTime Start = DateTime::Now();
			Synthesizer.SpeakAsync(u8"This is a simple english sentence taking a bit over seven seconds to pronounce due to interruption.");			
			
			Thread::Sleep(TimeSpan::FromSeconds(1));
			Synthesizer.Pause();

			Thread::Sleep(TimeSpan::FromSeconds(3));
			Synthesizer.Resume();

			Synthesizer.WaitUntilDone(TimeSpan::FromSeconds(25));
			TimeSpan ElapsedTime = DateTime::Now() - Start;
			Assert::IsTrue(ElapsedTime.GetTotalSeconds() > 7 && ElapsedTime.GetTotalSeconds() < 9);
		}

		TEST_METHOD(SpeakGerman)
		{
			SpeechSynthesizer Synthesizer = SpeechSynthesizer();
			Synthesizer.SetOutputToDefaultAudioDevice();

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
			Synthesizer.SetOutputToDefaultAudioDevice();

			DateTime Start = DateTime::Now();
			Synthesizer.SpeakSsml(u8"<speak version=\"1.0\" xmlns=\"http://www.w3.org/2001/10/synthesis\" xml:lang=\"en-US\"><say-as type=\"date:mdy\">1/29/2009</say-as></speak>");
			TimeSpan ElapsedTime = DateTime::Now() - Start;
			Assert::IsTrue(ElapsedTime.GetTotalSeconds() > 3);
		}

		TEST_METHOD(SpeakSsmlAsync)
		{
			SpeechSynthesizer Synthesizer = SpeechSynthesizer();
			Synthesizer.SetOutputToDefaultAudioDevice();

			DateTime Start = DateTime::Now();
			Synthesizer.SpeakSsmlAsync(u8"<speak version=\"1.0\" xmlns=\"http://www.w3.org/2001/10/synthesis\" xml:lang=\"en-US\"><say-as type=\"date:mdy\">1/29/2009</say-as></speak>");
			
			Thread::Sleep(TimeSpan::FromSeconds(1));
			Synthesizer.Pause();

			Thread::Sleep(TimeSpan::FromSeconds(3));
			Synthesizer.Resume();

			Synthesizer.WaitUntilDone(TimeSpan::FromSeconds(25));
			TimeSpan ElapsedTime = DateTime::Now() - Start;
			Assert::IsTrue(ElapsedTime.GetTotalSeconds() > 5 && ElapsedTime.GetTotalSeconds() < 7);
		}

		TEST_METHOD(SpeakToStreams)
		{
			SpeechSynthesizer Synthesizer = SpeechSynthesizer();
			SpeechAudioFormatInfo FormatInfo = SpeechAudioFormatInfo(44100, AudioBitsPerSample::Sixteen, AudioChannel::Stereo);
			
			MemoryStream TargetStream = MemoryStream();
			Synthesizer.SetOutputToAudioStream(TargetStream, FormatInfo);
			Synthesizer.Speak(u8"Look at you, hacker: a pathetic creature of meat and bone, panting and sweating as you run through my corridors. How can you challenge a perfect immortal machine?");
			Assert::AreEqual(1919028_ui64, TargetStream.GetLength());
			/*
			FileStream TargetWaveStream = FileStream(u8"SpeechSynthesizer.wav", FileMode::Create, FileAccess::Write, FileShare::None);
			Synthesizer.SetOutputToWaveStream(TargetWaveStream);
			Synthesizer.Speak(u8"Look at you, hacker: a pathetic creature of meat and bone, panting and sweating as you run through my corridors. How can you challenge a perfect immortal machine?");
			//Assert::AreEqual(TargetStream.GetLength(), TargetWaveStream.GetLength());
			*/
			FileStream TargetFileStream = FileStream(u8"SpeechSynthesizer.saf", FileMode::Create, FileAccess::Write, FileShare::None);
			Synthesizer.SetOutputToAudioStream(TargetFileStream, FormatInfo);
			Synthesizer.Speak(u8"Look at you, hacker: a pathetic creature of meat and bone, panting and sweating as you run through my corridors. How can you challenge a perfect immortal machine?");
			Assert::AreEqual(TargetStream.GetLength(), TargetFileStream.GetLength());
		}

		TEST_METHOD(SpeakToWaveFiles)
		{
			SpeechAudioFormatInfo FormatInfo = SpeechAudioFormatInfo(44100, AudioBitsPerSample::Sixteen, AudioChannel::Stereo);

			SpeechSynthesizer Synthesizer1 = SpeechSynthesizer();
			Synthesizer1.SetOutputToWaveFile(u8"SpeechSynthesizer1.wav", FormatInfo);
			Synthesizer1.SpeakAsync(u8"This file is called SpeechSynthesizer1 dot wav");
			Synthesizer1.SpeakSsmlAsync(u8"<speak version=\"1.0\" xmlns=\"http://www.w3.org/2001/10/synthesis\" xml:lang=\"en-US\"><say-as type=\"date:mdy\">1/29/2009</say-as></speak>");

			SpeechSynthesizer Synthesizer2 = SpeechSynthesizer();
			Synthesizer2.SetOutputToWaveFile(u8"SpeechSynthesizer2.wav", FormatInfo);
			Synthesizer2.Speak(u8"This file is called SpeechSynthesizer2 dot wav");

			Synthesizer1.WaitUntilDone(TimeSpan::FromSeconds(1));
		}
	private:
		static void SpeechSynthesizer_OnVoiceChange(const SpeechSynthesizer&, const VoiceChangeEventArgs&)
		{
			bool bla = false;
		}
	};
}
