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

#ifndef ELYSIUM_CORE_INTEGER
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Integer.hpp"
#endif

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			
			// User should provide a specialization of below ToString() template to use equality asserts in test code.
			// std::wstring ToString(const Q& q) is used for converting type Q in  user readable std::wstring value. 
			// Converted value is emitted in Assert failure message. Specialization for basic types has been provided below.
			template <> 
			static std::wstring ToString(const char8_t& q) 
			{
				return L"Bla";
				//static_assert(false, "Test writer must define specialization of ToString<const Q& q> for your class "__FUNCSIG__".");
			}
			
			class AssertExtended
			{
			public:
				static void AreEqual(const Elysium::Core::String& Expected, const Elysium::Core::String& Actual, bool ignoreCase = false, const wchar_t* message = NULL, const __LineInfo* pLineInfo = NULL)
				{
					Assert::AreEqual(Expected.GetLength(), Actual.GetLength());
					
					for (size_t i = 0; i < Expected.GetLength(); ++i)
					{
						char8_t e = Expected[i];
						char8_t a = Actual[i];

						//AreEqual(Expected[i], Actual[i]);
					}

					// ToDo:
					Assert::Fail();
				}

				static void AreEqual(const char8_t Expected, const char8_t Actual, bool ignoreCase = false, const wchar_t* message = NULL, const __LineInfo* pLineInfo = NULL)
				{
					// ToDo:
					Assert::Fail();

					//Assert::AreEqual((char)Expected, (char)Actual);
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

