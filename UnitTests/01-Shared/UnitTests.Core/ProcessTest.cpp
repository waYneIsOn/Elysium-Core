#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Diagnostics/Process.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Diagnostics;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Diagnostics
{
	TEST_CLASS(ProcessTest)
	{
	public:
		TEST_METHOD(GetLocalProcessCurrent)
		{
			const Process& CurrentProcess = Process::CurrentProcess();
			const Elysium::Core::uint32_t CurrentProcessId = CurrentProcess.GetId();

			Assert::AreNotEqual((Elysium::Core::uint32_t)0, CurrentProcessId);
		}

		TEST_METHOD(GetLocalProcesses)
		{
			const Template::Container::Vector<Process> Processes = Process::GetProcesses();
			if (Processes.GetLength() == 0)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(GetLocalProcessesByName)
		{
			const Template::Container::Vector<Process> Processes = Process::GetProcessesByName(u8"explorer.exe");
			if (Processes.GetLength() == 0)
			{
				Assert::Fail();
			}

			const Process& VSPRocess = Processes[0];

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
