#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core/DateTime.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/FileStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/MemoryStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Speech/SpeechSynthesizer.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Convert.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/Thread.hpp"

#if defined ELYSIUM_CORE_OS_WINDOWS
#include "../../../Libraries/01-Shared/Elysium.Core/COMException.hpp"
#endif

using namespace Elysium::Core;
using namespace Elysium::Core::Globalization;
using namespace Elysium::Core::IO;
using namespace Elysium::Core::Speech::AudioFormat;
using namespace Elysium::Core::Speech::Synthesis;
using namespace Elysium::Core::Template::Container;
using namespace Elysium::Core::Template;
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

				Logger::WriteMessage((char*)&Voice.GetId()[0]);
				Logger::WriteMessage(" - ");
				Logger::WriteMessage((char*)&Voice.GetName()[0]);
				Logger::WriteMessage("\r\n");
			}

			VoiceInfo Voice = Synthesizer.GetVoice();
			const CultureInfo VoiceCulture = Voice.GetCulture();

			AssertExtended::AreEqual(u8"TTS_MS_EN-US_ZIRA_11.0", Voice.GetId());
			AssertExtended::AreEqual(u8"Microsoft Zira Desktop", Voice.GetName());
			Assert::AreEqual(static_cast<Elysium::Core::uint8_t>(VoiceAge::Adult), static_cast<Elysium::Core::uint8_t>(Voice.GetAge()));
			Assert::AreEqual(static_cast<Elysium::Core::uint8_t>(VoiceGender::Female), static_cast<Elysium::Core::uint8_t>(Voice.GetGender()));
			AssertExtended::AreEqual(1033_ui32, VoiceCulture.GetLCID());
		}

		TEST_METHOD(LogEventsAsynchronously)
		{
			try
			{
				const Elysium::Core::String CurrentThreadId = Elysium::Core::Template::Text::Convert<char>::ToString(Thread::GetCurrentThreadIdX());
				Logger::WriteMessage("-----\r\n");
				Logger::WriteMessage(&CurrentThreadId[0]);
				Logger::WriteMessage(" Main thread\r\n-----\r\n");

				SpeechSynthesizer Synthesizer = SpeechSynthesizer();
				Synthesizer.BookmarkReached += Delegate<void, const SpeechSynthesizer&, const BookmarkReachedEventArgs&>::Bind<&SpeechSynthesizer_OnBookmarkReached>();
				Synthesizer.PhonemeReached += Delegate<void, const SpeechSynthesizer&, const PhonemeReachedEventArgs&>::Bind<&SpeechSynthesizer_OnPhonemeReached>();
				Synthesizer.StateChanged += Delegate<void, const SpeechSynthesizer&, const StateChangedEventArgs&>::Bind<&SpeechSynthesizer_OnStateChanged>();
				Synthesizer.SpeakCompleted += Delegate<void, const SpeechSynthesizer&, const SpeakCompletedEventArgs&>::Bind<&SpeechSynthesizer_OnSpeakCompleted>();
				Synthesizer.SpeakProgress += Delegate<void, const SpeechSynthesizer&, const SpeakProgressEventArgs&>::Bind<&SpeechSynthesizer_OnSpeakProgress>();
				Synthesizer.SpeakStarted += Delegate<void, const SpeechSynthesizer&, const SpeakStartedEventArgs&>::Bind<&SpeechSynthesizer_OnSpeakStarted>();
				Synthesizer.VisemeReached += Delegate<void, const SpeechSynthesizer&, const VisemeReachedEventArgs&>::Bind<&SpeechSynthesizer_OnVisemeReached>();
				Synthesizer.VoiceChanged += Delegate<void, const SpeechSynthesizer&, const VoiceChangeEventArgs&>::Bind<&SpeechSynthesizer_OnVoiceChange>();

				Synthesizer.SpeakSsmlAsync(u8"I am speaking some text and some more stuff and so on until I'm finished and this goes on and on and on and on.");
				
				Thread::Sleep(TimeSpan::FromSeconds(1));
				Synthesizer.Pause();

				Thread::Sleep(TimeSpan::FromSeconds(3));
				Synthesizer.Resume();
				
				Synthesizer.WaitUntilDone(TimeSpan::FromSeconds(25));
			}
			catch (Elysium::Core::Runtime::InteropServices::COMException& ex)
			{
				Logger::WriteMessage("COMException: ");
				Logger::WriteMessage((char*)&ex.GetExceptionMessage()[0]);
				Assert::Fail();
			}
		}

		TEST_METHOD(LogEventsSynchronously)
		{
			try
			{
				const Elysium::Core::String CurrentThreadId = Elysium::Core::Template::Text::Convert<char>::ToString(Thread::GetCurrentThreadIdX());
				Logger::WriteMessage("-----\r\n");
				Logger::WriteMessage(&CurrentThreadId[0]);
				Logger::WriteMessage(" Main thread\r\n-----\r\n");

				SpeechSynthesizer Synthesizer = SpeechSynthesizer();
				Synthesizer.BookmarkReached += Delegate<void, const SpeechSynthesizer&, const BookmarkReachedEventArgs&>::Bind<&SpeechSynthesizer_OnBookmarkReached>();
				Synthesizer.PhonemeReached += Delegate<void, const SpeechSynthesizer&, const PhonemeReachedEventArgs&>::Bind<&SpeechSynthesizer_OnPhonemeReached>();
				Synthesizer.StateChanged += Delegate<void, const SpeechSynthesizer&, const StateChangedEventArgs&>::Bind<&SpeechSynthesizer_OnStateChanged>();
				Synthesizer.SpeakCompleted += Delegate<void, const SpeechSynthesizer&, const SpeakCompletedEventArgs&>::Bind<&SpeechSynthesizer_OnSpeakCompleted>();
				Synthesizer.SpeakProgress += Delegate<void, const SpeechSynthesizer&, const SpeakProgressEventArgs&>::Bind<&SpeechSynthesizer_OnSpeakProgress>();
				Synthesizer.SpeakStarted += Delegate<void, const SpeechSynthesizer&, const SpeakStartedEventArgs&>::Bind<&SpeechSynthesizer_OnSpeakStarted>();
				Synthesizer.VisemeReached += Delegate<void, const SpeechSynthesizer&, const VisemeReachedEventArgs&>::Bind<&SpeechSynthesizer_OnVisemeReached>();
				Synthesizer.VoiceChanged += Delegate<void, const SpeechSynthesizer&, const VoiceChangeEventArgs&>::Bind<&SpeechSynthesizer_OnVoiceChange>();
				
				//Synthesizer.SpeakSsml(u8"<speak version=\"1.0\" xmlns=\"http://www.w3.org/2001/10/synthesis\" xml:lang=\"string\"><voice name=\"en-US-JennyNeural\"><bookmark mark=\"Daytime_forecast\"/>The weather forecast for today is partly cloudy with some sun breaks. Tonight's weather will be cloudy with a 30% chance of showers<bookmark mark=\"Nighttime forecast\"/></voice></speak>");
				//Synthesizer.Speak(u8"<bookmark mark=\"Daytime forecast\"/>The weather forecast for today is partly cloudy with some sun breaks, <bookmark mark=\"Nighttime forecast\"/>Tonight's weather will be cloudy with a 30% chance of showers.");
				Synthesizer.Speak(u8"This is a simple english sentence taking a bit over five seconds to pronounce.");
			}
			catch (Elysium::Core::Runtime::InteropServices::COMException& ex)
			{
				Logger::WriteMessage("COMException: ");
				Logger::WriteMessage((char*)&ex.GetExceptionMessage()[0]);
				Assert::Fail();
			}
		}

		TEST_METHOD(SpeakEnglish)
		{
			SpeechSynthesizer Synthesizer = SpeechSynthesizer();
			Synthesizer.SetOutputToDefaultAudioDevice();

			Utf8CultureInfo EnglishUS = Utf8CultureInfo(u8"en-US", false);
			const Vector<InstalledVoice> InstalledVoices = Synthesizer.GetInstalledVoices(EnglishUS);
			Assert::IsTrue(InstalledVoices.GetLength() > 0);

			Synthesizer.SelectVoice(InstalledVoices[0].GetVoiceInfo().GetName());
			Synthesizer.SelectVoice(InstalledVoices[0].GetVoiceInfo());

			DateTime Start = DateTime::Now();
			Synthesizer.Speak(u8"This is a simple english sentence taking a bit over four seconds to pronounce.");
			TimeSpan ElapsedTime = DateTime::Now() - Start;
			Assert::IsTrue(ElapsedTime.GetTotalSeconds() > 4 && ElapsedTime.GetTotalSeconds() < 6);
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

			Utf8CultureInfo GermanGermany = Utf8CultureInfo(u8"de-DE", false);
			const Vector<InstalledVoice> InstalledVoices = Synthesizer.GetInstalledVoices(GermanGermany);
			Assert::IsTrue(InstalledVoices.GetLength() > 0);

			Synthesizer.SelectVoice(InstalledVoices[0].GetVoiceInfo().GetName());
			Synthesizer.SelectVoice(InstalledVoices[0].GetVoiceInfo());
			
			DateTime Start = DateTime::Now();
			Synthesizer.Speak(u8"Das ist ein einfacher deutscher Satz, welcher etwas mehr als sieben Sekunden zur Aussprache benötigt.");
			TimeSpan ElapsedTime = DateTime::Now() - Start;
			Assert::IsTrue(ElapsedTime.GetTotalSeconds() > 6);	// can be a bit faster than seven seconds sometimes (due to my constant code-changes)
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
		static void SpeechSynthesizer_OnBookmarkReached(const SpeechSynthesizer& Synthesizer, const BookmarkReachedEventArgs& EventArgs)
		{
			const Elysium::Core::String CurrentThreadId = Elysium::Core::Template::Text::Convert<char>::ToString(Thread::GetCurrentThreadIdX());

			Logger::WriteMessage(&CurrentThreadId[0]);
			Logger::WriteMessage(" Bookmark reached: ");
			Logger::WriteMessage((char*)&EventArgs.GetBookmark()[0]);

			//EventArgs.GetAudioPosition()

			Logger::WriteMessage("\r\n");
		}

		static void SpeechSynthesizer_OnPhonemeReached(const SpeechSynthesizer& Synthesizer, const PhonemeReachedEventArgs& EventArgs)
		{
			const Elysium::Core::String CurrentThreadId = Elysium::Core::Template::Text::Convert<char>::ToString(Thread::GetCurrentThreadIdX());

			Logger::WriteMessage(&CurrentThreadId[0]);
			Logger::WriteMessage(" Phoneme reached: ");
			switch (EventArgs.GetEmphasis())
			{
			case SynthesizerEmphasis::None:
				Logger::WriteMessage("none");
				break;
			case SynthesizerEmphasis::Stressed:
				Logger::WriteMessage("stressed");
				break;
			case SynthesizerEmphasis::Emphasized:
				Logger::WriteMessage("emphasized");
				break;
			}
			Logger::WriteMessage("\r\n");
		}

		static void SpeechSynthesizer_OnSpeakCompleted(const SpeechSynthesizer& Synthesizer, const SpeakCompletedEventArgs& EventArgs)
		{
			const Elysium::Core::String CurrentThreadId = Elysium::Core::Template::Text::Convert<char>::ToString(Thread::GetCurrentThreadIdX());

			Logger::WriteMessage(&CurrentThreadId[0]);
			Logger::WriteMessage(" Speak completed: ");
			Logger::WriteMessage("\r\n");
		}

		static void SpeechSynthesizer_OnSpeakProgress(const SpeechSynthesizer& Synthesizer, const SpeakProgressEventArgs& EventArgs)
		{
			const Elysium::Core::String CurrentThreadId = Elysium::Core::Template::Text::Convert<char>::ToString(Thread::GetCurrentThreadIdX());

			Logger::WriteMessage(&CurrentThreadId[0]);
			Logger::WriteMessage(" Speak progress: ");
			Logger::WriteMessage(&Elysium::Core::Template::Text::Convert<char>::ToString(EventArgs.GetCharacterPosition())[0]);
			Logger::WriteMessage("\r\n");
		}

		static void SpeechSynthesizer_OnSpeakStarted(const SpeechSynthesizer& Synthesizer, const SpeakStartedEventArgs& EventArgs)
		{
			const Elysium::Core::String CurrentThreadId = Elysium::Core::Template::Text::Convert<char>::ToString(Thread::GetCurrentThreadIdX());

			Logger::WriteMessage(&CurrentThreadId[0]);
			Logger::WriteMessage(" Speak started\r\n");
		}

		static void SpeechSynthesizer_OnStateChanged(const SpeechSynthesizer& Synthesizer, const StateChangedEventArgs& EventArgs)
		{
			const Elysium::Core::String CurrentThreadId = Elysium::Core::Template::Text::Convert<char>::ToString(Thread::GetCurrentThreadIdX());

			Logger::WriteMessage(&CurrentThreadId[0]);
			Logger::WriteMessage(" State changed from ");
			switch (EventArgs.GetPreviousState())
			{
			case SynthesizerState::Ready:
				Logger::WriteMessage("ready");
				break;
			case SynthesizerState::Speaking:
				Logger::WriteMessage("speaking");
				break;
			case SynthesizerState::Paused:
				Logger::WriteMessage("paused");
				break;
			}
			Logger::WriteMessage(" to ");
			switch (EventArgs.GetState())
			{
			case SynthesizerState::Ready:
				Logger::WriteMessage("ready");
				break;
			case SynthesizerState::Speaking:
				Logger::WriteMessage("speaking");
				break;
			case SynthesizerState::Paused:
				Logger::WriteMessage("paused");
				break;
			}
			Logger::WriteMessage("\r\n");
		}

		static void SpeechSynthesizer_OnVisemeReached(const SpeechSynthesizer& Synthesizer, const VisemeReachedEventArgs& EventArgs)
		{
			const Elysium::Core::String CurrentThreadId = Elysium::Core::Template::Text::Convert<char>::ToString(Thread::GetCurrentThreadIdX());

			Logger::WriteMessage(&CurrentThreadId[0]);
			Logger::WriteMessage(" Viseme reached: ");
			switch (EventArgs.GetEmphasis())
			{
			case SynthesizerEmphasis::None:
				Logger::WriteMessage("none");
				break;
			case SynthesizerEmphasis::Stressed:
				Logger::WriteMessage("stressed");
				break;
			case SynthesizerEmphasis::Emphasized:
				Logger::WriteMessage("emphasized");
				break;
			}
			Logger::WriteMessage("\r\n");
		}

		static void SpeechSynthesizer_OnVoiceChange(const SpeechSynthesizer& Synthesizer, const VoiceChangeEventArgs& EventArgs)
		{
			const Elysium::Core::String CurrentThreadId = Elysium::Core::Template::Text::Convert<char>::ToString(Thread::GetCurrentThreadIdX());

			Logger::WriteMessage(&CurrentThreadId[0]);
			Logger::WriteMessage(" Voice changed: ");
			Logger::WriteMessage((char*)&EventArgs.GetVoice().GetId()[0]);
			Logger::WriteMessage(" - ");
			Logger::WriteMessage((char*)&EventArgs.GetVoice().GetName()[0]);
			Logger::WriteMessage("\r\n");
		}
	};
}
