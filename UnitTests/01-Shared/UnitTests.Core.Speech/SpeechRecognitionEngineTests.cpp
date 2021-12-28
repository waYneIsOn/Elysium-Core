#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core/COMException.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core/DateTime.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Speech/SpeechAudioFormatInfo.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Speech/SpeechRecognitionEngine.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Speech/SpeechSynthesizer.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Globalization;
using namespace Elysium::Core::Speech::AudioFormat;
using namespace Elysium::Core::Speech::Recognition;
using namespace Elysium::Core::Speech::Synthesis;
using namespace Elysium::Core::Template::Container;
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
				const String WaveFile = u8"SpeechSynthesizerForRecognition.wav";

				// put SpeechSynthesizer in a scope so the created wave-filehandle will be released before SpeechRecognitionEngine loads it as input
				{
					SpeechSynthesizer Synthesizer = SpeechSynthesizer();

					CultureInfo EnglishUS = CultureInfo(u8"en-US", false);
					Vector<InstalledVoice> InstalledVoices = Synthesizer.GetInstalledVoices(EnglishUS);
					Assert::IsTrue(InstalledVoices.GetLength() > 0);

					SpeechAudioFormatInfo FormatInfo = SpeechAudioFormatInfo(44100, AudioBitsPerSample::Sixteen, AudioChannel::Stereo);

					Synthesizer.SelectVoice(InstalledVoices[0].GetVoiceInfo());
					Synthesizer.SetOutputToWaveFile(WaveFile, FormatInfo);
					Synthesizer.Speak(u8"Computer: Dim lights");
				}

				Grammar EnglishUsGrammar = Grammar(u8"Path");
				EnglishUsGrammar.SetName(u8"Name");

				SpeechRecognitionEngine RecognitionEngine = SpeechRecognitionEngine();
				RecognitionEngine.LoadGrammar(EnglishUsGrammar);
				RecognitionEngine.SetInputToWaveFile(WaveFile);
				RecognitionEngine.Recognize();
			}
			catch (Elysium::Core::Runtime::InteropServices::COMException& ex)
			{
				Logger::WriteMessage("COMException: ");
				Logger::WriteMessage((char*)&ex.GetExceptionMessage()[0]);
				Assert::Fail();
			}
		}
	};
}
