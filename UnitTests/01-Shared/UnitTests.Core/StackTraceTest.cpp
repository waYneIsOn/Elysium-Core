#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Diagnostics/StackTrace.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Convert.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Utf16.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Diagnostics;
using namespace Elysium::Core::Diagnostics::Container;
using namespace Elysium::Core::Template::Text;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Diagnostics
{
	TEST_CLASS(StackTraceTest)
	{
	public:
		TEST_METHOD(PrintCurrent)
		{
			PrintStackTrace(StackTrace());
		}

		TEST_METHOD(PrintException)
		{
			Assert::Fail(L"not implemented yet");
			/*
			try
			{
				throw Exception();
			}
			catch (const Exception& ex)
			{
				//PrintStackTrace(ex.GetStackTrace());
			}
			*/
		}

		TEST_METHOD(PrintRecursion)
		{
			RecursiveMethod(0, 50, 3);
			RecursiveMethod(0, 50, 100);
		}
	private:
		void RecursiveMethod(uint32_t Depth, const uint32_t MaxRecursion, const uint32_t FramesToCapture)
		{
			if (Depth > MaxRecursion)
			{
				PrintStackTrace(StackTrace(FramesToCapture));
				return;
			}

			RecursiveMethod(++Depth, MaxRecursion, FramesToCapture);
		}

		void PrintStackTrace(const StackTrace& Instance)
		{
			/*
			const Utf8String StringifiedInstance = Instance.ToUtf8String();
			Logger::WriteMessage(&Template::Text::Unicode::Utf16::SafeToWideString(&StringifiedInstance[0], StringifiedInstance.GetLength())[0]);
			*/
			VectorOfStackFrame StackFrames = Instance.GetFrames();
			for (Elysium::Core::size i = 0; i < StackFrames.GetLength(); i++)
			{
				const StackFrame& CurrentFrame = StackFrames[i];

				const Utf8String& FileName = CurrentFrame.GetFileName();
				const Elysium::Core::String LineNumber = Convert<char>::ToString(CurrentFrame.GetLineNumber());
				const Elysium::Core::String ColumnNumber = Convert<char>::ToString(CurrentFrame.GetColumnNumber());

				Logger::WriteMessage("at ");
				Logger::WriteMessage((char*)&FileName[0]);
				Logger::WriteMessage("(...)");
				Logger::WriteMessage(": line ");
				Logger::WriteMessage(&LineNumber[0]);
				Logger::WriteMessage("\r\n");
			}
			Logger::WriteMessage("-------------------------------\r\n");
		}
	};
}
