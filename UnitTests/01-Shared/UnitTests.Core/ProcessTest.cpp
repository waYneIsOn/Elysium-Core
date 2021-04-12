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
		TEST_METHOD(GetLocalProcessCurrent)
		{
			Process CurrentProcess = Process::GetCurrentProcess();
			const Elysium::Core::uint32_t CurrentProcessId = CurrentProcess.GetId();

			Assert::AreNotEqual((Elysium::Core::uint32_t)0, CurrentProcessId);
		}

		TEST_METHOD(GetLocalProcesses)
		{
			Array<Process> Processes = Process::GetProcesses();
			if (Processes.GetLength() == 0)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(GetLocalProcessesByName)
		{
			Array<Process> Processes = Process::GetProcessesByName(u8"explorer.exe");
			if (Processes.GetLength() == 0)
			{
				Assert::Fail();
			}

			Process& VSPRocess = Processes[0];

			int slkjsdf = 45;
		}

		TEST_METHOD(StartAndKillNotepad)
		{
			ProcessStartInfo StartInfo = ProcessStartInfo();
			StartInfo.SetFileName(u8"C:\\Windows\\System32\\notepad.exe");

			Process Notepad = Process();
			Notepad.Start(StartInfo);
			Notepad.Kill(false);
			if (!Notepad.GetHasExited())
			{
				Assert::Fail();
			}
		}
	};
}
