#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core/COMException.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core/DateTime.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Speech/DictationGrammar.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Speech/SpeechAudioFormatInfo.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Speech/SpeechRecognitionEngine.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Speech/SpeechSynthesizer.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Convert.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/Thread.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Globalization;
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
		TEST_METHOD(RecognizeFromWaveFile)
		{
			try
			{
				const Elysium::Core::Template::Text::String CurrentThreadId = Elysium::Core::Template::Text::Convert<char>::ToString(Thread::GetCurrentThreadIdX());
				Logger::WriteMessage("-----\r\n");
				Logger::WriteMessage(&CurrentThreadId[0]);
				Logger::WriteMessage(" Main thread\r\n-----\r\n");

				const Utf8String WaveFile = u8"SpeechSynthesizerForRecognition.wav";

				// put SpeechSynthesizer in a scope so the created wave-filehandle will be released before SpeechRecognitionEngine loads it as input
				{
					SpeechSynthesizer Synthesizer = SpeechSynthesizer();

					CultureInfo EnglishUS = CultureInfo(u8"en-US", false);
					Vector<InstalledVoice> InstalledVoices = Synthesizer.GetInstalledVoices(EnglishUS);
					Assert::IsTrue(InstalledVoices.GetLength() > 0);

					SpeechAudioFormatInfo FormatInfo = SpeechAudioFormatInfo(44100, AudioBitsPerSample::Sixteen, AudioChannel::Stereo);

					Synthesizer.SelectVoice(InstalledVoices[0].GetVoiceInfo());
					Synthesizer.SetOutputToWaveFile(WaveFile, FormatInfo);
					Synthesizer.Speak(u8"Computer, locate commander riker!");
				}

				Grammar EnglishUsGrammar = Grammar(u8"Path", u8"RuleName");
				EnglishUsGrammar.SetName(u8"Name");

				DictationGrammar DictatedGrammar = DictationGrammar(u8"Topic");

				SpeechRecognitionEngine RecognitionEngine = SpeechRecognitionEngine();
				RecognitionEngine.LoadGrammar(EnglishUsGrammar);
				//RecognitionEngine.LoadGrammar(DictatedGrammar);
				RecognitionEngine.SetInputToWaveFile(WaveFile);
				RecognitionEngine.SpeechRecognized += Delegate<void, const SpeechRecognitionEngine&, const SpeechRecognizedEventArgs&>::Bind<&SpeechRecognitionEngine_OnSpeechRecognized>();

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
		static void SpeechRecognitionEngine_OnSpeechRecognized(const SpeechRecognitionEngine& Engine, const SpeechRecognizedEventArgs& EventArgs)
		{
			const Elysium::Core::Template::Text::String CurrentThreadId = Elysium::Core::Template::Text::Convert<char>::ToString(Thread::GetCurrentThreadIdX());

			Logger::WriteMessage(&CurrentThreadId[0]);
			Logger::WriteMessage(" Speech recognized: ");
			// ...
			Logger::WriteMessage("\r\n");
		}
	};
}
