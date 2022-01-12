#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core/COMException.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core/DateTime.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/MemoryStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Speech/DictationGrammar.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Speech/SpeechAudioFormatInfo.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Speech/SpeechRecognitionEngine.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Speech/SpeechSynthesizer.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Convert.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/Thread.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Globalization;
using namespace Elysium::Core::IO;
using namespace Elysium::Core::Speech::AudioFormat;
using namespace Elysium::Core::Speech::Recognition;
using namespace Elysium::Core::Speech::Synthesis;
using namespace Elysium::Core::Template::Container;
using namespace Elysium::Core::Threading;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Speech
{
	TEST_CLASS(SpeechRecognitionEngineTests)
	{
	public:
		TEST_CLASS_INITIALIZE(OnInit)
		{
			SpeechSynthesizer Synthesizer = SpeechSynthesizer();

			CultureInfo EnglishUS = CultureInfo(u8"en-US", false);
			Vector<InstalledVoice> InstalledVoices = Synthesizer.GetInstalledVoices(EnglishUS);
			Assert::IsTrue(InstalledVoices.GetLength() > 0);

			Synthesizer.SelectVoice(InstalledVoices[0].GetVoiceInfo());

			Synthesizer.SetOutputToWaveFile(_WaveFile, _AudioFormat);
			Synthesizer.Speak(u8"Computer, locate commander riker!");

			Synthesizer.SetOutputToAudioStream(_AudioStream, _AudioFormat);
			Synthesizer.Speak(u8"Computer, locate commander riker!");
			_AudioStream.SetPosition(0);
		}

		TEST_METHOD(RecognizeDictationFromAudioStream)
		{
			try
			{
				const Elysium::Core::String CurrentThreadId = Elysium::Core::Template::Text::Convert<char>::ToString(Thread::GetCurrentThreadIdX());
				Logger::WriteMessage("-----\r\n");
				Logger::WriteMessage(&CurrentThreadId[0]);
				Logger::WriteMessage(" Main thread\r\n-----\r\n");

				DictationGrammar DictatedGrammar = DictationGrammar(); // uri=grammar:dictation rule=

				SpeechRecognitionEngine RecognitionEngine = SpeechRecognitionEngine();
				RecognitionEngine.AudioLevelUpdated += Delegate<void, const SpeechRecognitionEngine&, const AudioLevelUpdatedEventArgs&>::Bind<&SpeechRecognitionEngine_OnAudioLevelUpdated>();
				RecognitionEngine.AudioSignalProblemOccurred += Delegate<void, const SpeechRecognitionEngine&, const AudioSignalProblemOccurredEventArgs&>::Bind<&SpeechRecognitionEngine_OnAudioSignalProblemOccurred>();
				RecognitionEngine.AudioStateChanged += Delegate<void, const SpeechRecognitionEngine&, const AudioStateChangedEventArgs&>::Bind<&SpeechRecognitionEngine_OnAudioStateChanged>();
				RecognitionEngine.LoadGrammarCompleted += Delegate<void, const SpeechRecognitionEngine&, const LoadGrammarCompletedEventArgs&>::Bind<&SpeechRecognitionEngine_OnLoadGrammarCompleted>();
				RecognitionEngine.SpeechDetected += Delegate<void, const SpeechRecognitionEngine&, const SpeechDetectedEventArgs&>::Bind<&SpeechRecognitionEngine_OnSpeechDetected>();
				RecognitionEngine.SpeechHypothesized += Delegate<void, const SpeechRecognitionEngine&, const SpeechHypothesizedEventArgs&>::Bind<&SpeechRecognitionEngine_OnSpeechHypothesized>();
				RecognitionEngine.SpeechRecognized += Delegate<void, const SpeechRecognitionEngine&, const SpeechRecognizedEventArgs&>::Bind<&SpeechRecognitionEngine_OnSpeechRecognized>();
				RecognitionEngine.LoadGrammar(DictatedGrammar);
				RecognitionEngine.SetInputToAudioStream(_AudioStream, _AudioFormat);

				RecognitionEngine.Recognize();
			}
			catch (Elysium::Core::Runtime::InteropServices::COMException& ex)
			{
				Logger::WriteMessage("COMException: ");
				Logger::WriteMessage((char*)&ex.GetExceptionMessage()[0]);
				Assert::Fail();
			}
		}

		TEST_METHOD(RecognizeDictationFromWaveFile)
		{
			try
			{
				const Elysium::Core::String CurrentThreadId = Elysium::Core::Template::Text::Convert<char>::ToString(Thread::GetCurrentThreadIdX());
				Logger::WriteMessage("-----\r\n");
				Logger::WriteMessage(&CurrentThreadId[0]);
				Logger::WriteMessage(" Main thread\r\n-----\r\n");

				Grammar EnglishUsGrammar = Grammar(u8"Path", u8"RuleName");
				EnglishUsGrammar.SetName(u8"Name");

				//DictationGrammar DictatedGrammar = DictationGrammar(u8"grammar:dictation#topic");
				DictationGrammar DictatedGrammar = DictationGrammar(); // uri=grammar:dictation rule=

				SpeechRecognitionEngine RecognitionEngine = SpeechRecognitionEngine();
				RecognitionEngine.AudioLevelUpdated += Delegate<void, const SpeechRecognitionEngine&, const AudioLevelUpdatedEventArgs&>::Bind<&SpeechRecognitionEngine_OnAudioLevelUpdated>();
				RecognitionEngine.AudioSignalProblemOccurred += Delegate<void, const SpeechRecognitionEngine&, const AudioSignalProblemOccurredEventArgs&>::Bind<&SpeechRecognitionEngine_OnAudioSignalProblemOccurred>();
				RecognitionEngine.AudioStateChanged += Delegate<void, const SpeechRecognitionEngine&, const AudioStateChangedEventArgs&>::Bind<&SpeechRecognitionEngine_OnAudioStateChanged>();
				RecognitionEngine.LoadGrammarCompleted += Delegate<void, const SpeechRecognitionEngine&, const LoadGrammarCompletedEventArgs&>::Bind<&SpeechRecognitionEngine_OnLoadGrammarCompleted>();
				RecognitionEngine.SpeechDetected += Delegate<void, const SpeechRecognitionEngine&, const SpeechDetectedEventArgs&>::Bind<&SpeechRecognitionEngine_OnSpeechDetected>();
				RecognitionEngine.SpeechHypothesized += Delegate<void, const SpeechRecognitionEngine&, const SpeechHypothesizedEventArgs&>::Bind<&SpeechRecognitionEngine_OnSpeechHypothesized>();
				RecognitionEngine.SpeechRecognized += Delegate<void, const SpeechRecognitionEngine&, const SpeechRecognizedEventArgs&>::Bind<&SpeechRecognitionEngine_OnSpeechRecognized>();
				RecognitionEngine.LoadGrammar(DictatedGrammar);
				RecognitionEngine.SetInputToWaveFile(_WaveFile);

				RecognitionEngine.Recognize();
			}
			catch (Elysium::Core::Runtime::InteropServices::COMException& ex)
			{
				Logger::WriteMessage("COMException: ");
				Logger::WriteMessage((char*)&ex.GetExceptionMessage()[0]);
				Assert::Fail();
			}
		}
	private:
		inline static Elysium::Core::Speech::AudioFormat::SpeechAudioFormatInfo _AudioFormat = SpeechAudioFormatInfo(44100, AudioBitsPerSample::Sixteen, AudioChannel::Stereo);
		inline static Elysium::Core::Utf8String _WaveFile = u8"SpeechSynthesizerForRecognition.wav";
		inline static Elysium::Core::IO::MemoryStream _AudioStream = Elysium::Core::IO::MemoryStream();

		static void SpeechRecognitionEngine_OnAudioLevelUpdated(const SpeechRecognitionEngine& Engine, const AudioLevelUpdatedEventArgs& EventArgs)
		{
			const Elysium::Core::String CurrentThreadId = Elysium::Core::Template::Text::Convert<char>::ToString(Thread::GetCurrentThreadIdX());
			const Elysium::Core::uint32_t AudioLevel = EventArgs.GetAudioLevel();

			Logger::WriteMessage(&CurrentThreadId[0]);
			Logger::WriteMessage(" Audio level updated: ");
			Logger::WriteMessage(&Elysium::Core::Template::Text::Convert<char>::ToString(AudioLevel)[0]);
			Logger::WriteMessage("\r\n");
		}

		static void SpeechRecognitionEngine_OnAudioSignalProblemOccurred(const SpeechRecognitionEngine& Engine, const AudioSignalProblemOccurredEventArgs& EventArgs)
		{
			const Elysium::Core::String CurrentThreadId = Elysium::Core::Template::Text::Convert<char>::ToString(Thread::GetCurrentThreadIdX());
			const AudioSignalProblem Problem = EventArgs.GetAudioSignalProblem();

			Logger::WriteMessage(&CurrentThreadId[0]);
			Logger::WriteMessage(" Audio problem occurred: ");
			switch (Problem)
			{
			case AudioSignalProblem::None:
				Logger::WriteMessage("None ");
				break;
			case AudioSignalProblem::TooNoisy:
				Logger::WriteMessage("TooNoisy ");
				break;
			case AudioSignalProblem::NoSignal:
				Logger::WriteMessage("NoSignal ");
				break;
			case AudioSignalProblem::TooLoud:
				Logger::WriteMessage("TooLoud ");
				break;
			case AudioSignalProblem::TooSoft:
				Logger::WriteMessage("TooSoft ");
				break;
			case AudioSignalProblem::TooFast:
				Logger::WriteMessage("TooFast ");
				break;
			case AudioSignalProblem::TooSlow:
				Logger::WriteMessage("TooSlow ");
				break;
			default:
				Logger::WriteMessage("unhandled ");
				break;
			}
			Logger::WriteMessage(&Elysium::Core::Template::Text::Convert<char>::ToString(EventArgs.GetAudioLevel())[0]);
			Logger::WriteMessage("\r\n");
		}

		static void SpeechRecognitionEngine_OnAudioStateChanged(const SpeechRecognitionEngine& Engine, const AudioStateChangedEventArgs& EventArgs)
		{
			const Elysium::Core::String CurrentThreadId = Elysium::Core::Template::Text::Convert<char>::ToString(Thread::GetCurrentThreadIdX());
			const AudioState State = EventArgs.GetAudioState();

			Logger::WriteMessage(&CurrentThreadId[0]);
			Logger::WriteMessage(" Audio state changed: ");
			switch (State)
			{
			case AudioState::Stopped:
				Logger::WriteMessage("stopped");
				break;
			case AudioState::Silence:
				Logger::WriteMessage("silence");
				break;
			case AudioState::Speech:
				Logger::WriteMessage("speech");
				break;
			default:
				Logger::WriteMessage("unhandled");
				break;
			}
			Logger::WriteMessage("\r\n");
		}

		static void SpeechRecognitionEngine_OnLoadGrammarCompleted(const SpeechRecognitionEngine& Engine, const LoadGrammarCompletedEventArgs& EventArgs)
		{
			const Elysium::Core::String CurrentThreadId = Elysium::Core::Template::Text::Convert<char>::ToString(Thread::GetCurrentThreadIdX());
			
			Logger::WriteMessage(&CurrentThreadId[0]);
			Logger::WriteMessage(" Grammar loaded: ");
			//Logger::WriteMessage(...);
			Logger::WriteMessage("\r\n");
		}

		static void SpeechRecognitionEngine_OnSpeechDetected(const SpeechRecognitionEngine& Engine, const SpeechDetectedEventArgs& EventArgs)
		{
			const Elysium::Core::String CurrentThreadId = Elysium::Core::Template::Text::Convert<char>::ToString(Thread::GetCurrentThreadIdX());
			const Elysium::Core::TimeSpan& AudioPosition = EventArgs.GetAudioPosition();

			Logger::WriteMessage(&CurrentThreadId[0]);
			Logger::WriteMessage(" Speech detected: ");
			//Logger::WriteMessage((char*)&AudioPosition.ToString()[0]);
			Logger::WriteMessage("\r\n");
		}

		static void SpeechRecognitionEngine_OnSpeechHypothesized(const SpeechRecognitionEngine& Engine, const SpeechHypothesizedEventArgs& EventArgs)
		{
			const Elysium::Core::String CurrentThreadId = Elysium::Core::Template::Text::Convert<char>::ToString(Thread::GetCurrentThreadIdX());
			const Elysium::Core::Utf8String& Text = EventArgs.GetResult().GetText();

			Logger::WriteMessage(&CurrentThreadId[0]);
			Logger::WriteMessage(" Speech hypothesized: ");
			Logger::WriteMessage((char*)&Text[0]);
			Logger::WriteMessage("\r\n");
		}

		static void SpeechRecognitionEngine_OnSpeechRecognized(const SpeechRecognitionEngine& Engine, const SpeechRecognizedEventArgs& EventArgs)
		{
			const Elysium::Core::String CurrentThreadId = Elysium::Core::Template::Text::Convert<char>::ToString(Thread::GetCurrentThreadIdX());
			const Elysium::Core::Utf8String& Text = EventArgs.GetResult().GetText();

			Logger::WriteMessage(&CurrentThreadId[0]);
			Logger::WriteMessage(" Speech recognized: ");
			Logger::WriteMessage((char*)&Text[0]);
			Logger::WriteMessage("\r\n");
		}
	};
}
