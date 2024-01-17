#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Diagnostics/Process.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Diagnostics/ProcessModule.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Convert.hpp"

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
			const Process CurrentProcess = Process::CurrentProcess();
			const Elysium::Core::uint32_t CurrentProcessId = CurrentProcess.GetId();

			Assert::AreNotEqual((Elysium::Core::uint32_t)0, CurrentProcessId);

			const Template::Text::String<char8_t> ProcessName = CurrentProcess.GetProcessName();
			Logger::WriteMessage((char*)&ProcessName[0]);
			Logger::WriteMessage("\r\n");

			//const ProcessModule MainModule = CurrentProcess.GetMainModule();

			const Template::Container::Vector<ProcessModule>& Modules = CurrentProcess.GetModules();
			for (Template::Container::Vector<ProcessModule>::ConstIterator Iterator = Modules.GetBegin(); Iterator != Modules.GetEnd(); ++Iterator)
			{
				const ProcessModule& CurrentModule = *Iterator;

				const Template::Text::String<char8_t> ModuleName = CurrentModule.GetModuleName();
				Logger::WriteMessage("\t");
				Logger::WriteMessage((char*)&ModuleName[0]);
				Logger::WriteMessage(" - ");

				const void* ModuleBaseAddress = CurrentModule.GetBaseAddress();
				const Template::System::size Address =
					reinterpret_cast<const Template::System::size>(ModuleBaseAddress);
				Template::Text::String BaseAddress = Template::Text::Convert<char>::ToString(Address);
				Logger::WriteMessage(&BaseAddress[0]);
				Logger::WriteMessage("\r\n");
			}
		}

		TEST_METHOD(GetLocalProcesses)
		{
			const Template::Container::Vector<Process> Processes = Process::GetProcesses();
			if (Processes.GetLength() == 0)
			{
				Assert::Fail();
			}
			
			for (Template::Container::Vector<Process>::ConstIterator Iterator = Processes.GetBegin(); Iterator != Processes.GetEnd(); ++Iterator)
			{
				const Template::Text::String<char8_t> ProcessName = (*Iterator).GetProcessName();
				Logger::WriteMessage((char*)&ProcessName[0]);
				Logger::WriteMessage("\r\n");
			}
		}

		TEST_METHOD(GetLocalProcessesByName)
		{
			const Template::Container::Vector<Process> Processes = Process::GetProcesses(u8"explorer.exe");
			if (Processes.GetLength() == 0)
			{
				Assert::Fail(L"process not found");
			}

			const Process& FirstProcess = Processes[0];
			const Template::Text::String<char8_t> ProcessName = FirstProcess.GetProcessName();
			Logger::WriteMessage((char*)&ProcessName[0]);
			Logger::WriteMessage("\r\n");
		}

		TEST_METHOD(StartAndCloseNotepad)
		{
			try
			{
				ProcessStartInfo StartInfo = ProcessStartInfo();
				StartInfo.SetFileName(u8"C:\\Windows\\System32\\notepad.exe");

				Process Notepad = Process::Start(StartInfo);
				bool Closed = Notepad.CloseMainWindow();

				if (!Notepad.GetHasExited())
				{
					Assert::Fail();
				}
			}
			catch (const Elysium::Core::Template::Exceptions::SystemException& ex)
			{
				Template::Text::String ErrorCode = Template::Text::Convert<char>::ToString(ex.GetErrorCode());

				Logger::WriteMessage((char*)&ex.GetExceptionMessage()[0]);
				Logger::WriteMessage(" - ");
				Logger::WriteMessage(&ErrorCode[0]);
				Logger::WriteMessage("\r\n");
				Logger::WriteMessage((char*)&ex.GetStackTrace()[0]);
				Logger::WriteMessage("\r\n");
				Assert::Fail();
			}
		}

		TEST_METHOD(StartAndKillNotepad)
		{
			try
			{
				ProcessStartInfo StartInfo = ProcessStartInfo();
				StartInfo.SetFileName(u8"C:\\Windows\\System32\\notepad.exe");

				Process Notepad = Process::Start(StartInfo);
				Notepad.Kill(false);

				if (!Notepad.GetHasExited())
				{
					Assert::Fail();
				}
			}
			catch (const Elysium::Core::Template::Exceptions::SystemException& ex)
			{
				Template::Text::String ErrorCode = Template::Text::Convert<char>::ToString(ex.GetErrorCode());

				Logger::WriteMessage((char*)&ex.GetExceptionMessage()[0]);
				Logger::WriteMessage(" - ");
				Logger::WriteMessage(&ErrorCode[0]);
				Logger::WriteMessage("\r\n");
				Logger::WriteMessage((char*)&ex.GetStackTrace()[0]);
				Logger::WriteMessage("\r\n");
				Assert::Fail();
			}
		}
	};
}
