#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Diagnostics/Process.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Collections::Template;
using namespace Elysium::Core::Diagnostics;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Diagnostics
{
	TEST_CLASS(ProcessTest)
	{
	public:
		TEST_METHOD(CheckCurrentProcess)
		{
			//Process CurrentProcess = Process::GetCurrentProcess();
			//const Elysium::Core::uint32_t CurrentProcessId = CurrentProcess.GetId();
			
			Process Process = Process::GetProcessById(19068);
			const Elysium::Core::uint32_t Id = Process.GetId();

			int lkjsdf = 35;
			Assert::Fail();
		}

		TEST_METHOD(StartAndCloseNotepad)
		{
			Process Notepad = Process();
			Notepad.GetStartInfo().SetFileName(u8"C:\\Windows\\System32\\notepad.exe");
			Notepad.GetStartInfo().SetWindowStyle(ProcessWindowStyle::Maximized);
			Notepad.Start();
			Notepad.CloseMainWindow();
			Notepad.Close();
			if (!Notepad.GetHasExited())
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(StartAndKillNotepad)
		{
			Process Notepad = Process();
			Notepad.GetStartInfo().SetFileName(u8"C:\\Windows\\System32\\notepad.exe");
			Notepad.Start();
			Notepad.Kill(false);
			if (!Notepad.GetHasExited())
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(StartAndKillProgramDependantOnUserSettings)
		{
			Assert::Fail();
		}
	};
}
