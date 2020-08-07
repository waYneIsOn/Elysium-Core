#pragma once

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#define MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT
#include <CppUnitTestAssert.h>
#endif

#ifndef _XSTRING_
#include <xstring>
#endif

#ifndef _UCHAR
#include <uchar.h>
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/String.hpp"
#endif

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			class AssertExtended
			{
			public:
				static void AreEqual(const Elysium::Core::String& Expected, const Elysium::Core::String& Actual, bool ignoreCase = false,
					const wchar_t* message = NULL, const __LineInfo* pLineInfo = NULL)
				{
					Assert::AreEqual(Expected.GetLength(), Actual.GetLength());
					
					for (size_t i = 0; i < Expected.GetLength(); ++i)
					{
						char e = Expected[i];
						char a = Actual[i];

						Assert::AreEqual(Expected[i], Actual[i]);
					}
				}

				static void AreEqual(const unsigned short Expected, const unsigned short Actual)
				{
					Assert::IsTrue(Expected == Actual);
				}

				static void AreEqual(const Elysium::Core::uint64_t Expected, const Elysium::Core::uint64_t Actual)
				{
					Assert::IsTrue(Expected == Actual);
				}

				static void AreEqual(const Elysium::Core::int64_t Expected, const Elysium::Core::int64_t Actual)
				{
					Assert::IsTrue(Expected == Actual);
				}
			};
		}
	}
}
#endif

