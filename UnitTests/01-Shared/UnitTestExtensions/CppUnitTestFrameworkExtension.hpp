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

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			// Some basic type templates are missing due from CppUnitTestAssert.h. See:
			// https://developercommunity.visualstudio.com/content/problem/338198/missing-tostring-template-specialization-for-basic.html
			// Once a fix is released, this declaration can be removed.
			template<>
			inline std::wstring ToString<int64_t>(const int64_t& t)
			{
				RETURN_WIDE_STRING(t);
			}

			class AssertExtended
			{
			public:
				static void AreEqual(const char16_t* expected, const char16_t* actual, bool ignoreCase = false, const wchar_t* message = NULL,
					const __LineInfo* pLineInfo = NULL)
				{
					mbstate_t State{};
					char Buffer[4];

					// ...
					size_t InputLength = std::char_traits<char16_t>::length(expected);
					size_t OutputLength = 1;
					for (size_t i = 0; i < InputLength; i++)
					{
						OutputLength += c16rtomb(Buffer, expected[i], &State);
					}
					
					// write bytes to list
					char* ConvertedExpected = new char[OutputLength];
					OutputLength = 0;
					for (int i = 0; i < InputLength; i++)
					{
						OutputLength += c16rtomb(&ConvertedExpected[OutputLength], expected[i], &State);
					}
					ConvertedExpected[OutputLength] = '\0';
					std::string StringExpected = std::string(ConvertedExpected);
					delete[] ConvertedExpected;

					// ...
					InputLength = std::char_traits<char16_t>::length(actual);
					OutputLength = 1;
					for (int i = 0; i < InputLength; i++)
					{
						OutputLength += c16rtomb(Buffer, actual[i], &State);
					}

					char* ConvertedActual = new char[OutputLength];
					OutputLength = 0;
					for (int i = 0; i < InputLength; i++)
					{
						OutputLength += c16rtomb(&ConvertedActual[OutputLength], actual[i], &State);
					}
					ConvertedActual[OutputLength] = '\0';
					std::string StringActual = std::string(ConvertedActual);
					delete[] ConvertedActual;

					Assert::AreEqual(StringExpected, StringActual);
				}

				static void AreEqual(const char16_t expected, const char16_t actual, bool ignoreCase = false, const wchar_t* message = NULL,
					const __LineInfo* pLineInfo = NULL)
				{
					mbstate_t State{};

					// ...
					size_t InputLength = 1;
					size_t OutputLength = 1 + c16rtomb(nullptr, expected, &State);

					char* ConvertedExpected = new char[OutputLength];
					OutputLength = 0;
					for (int i = 0; i < InputLength; i++)
					{
						OutputLength += c16rtomb(&ConvertedExpected[OutputLength], expected, &State);
					}
					ConvertedExpected[OutputLength] = '\0';
					std::string StringExpected = std::string(ConvertedExpected);
					delete[] ConvertedExpected;

					// ...
					InputLength = 1;
					OutputLength = 1 + c16rtomb(nullptr, actual, &State);

					char* ConvertedActual = new char[OutputLength];
					OutputLength = 0;
					for (int i = 0; i < InputLength; i++)
					{
						OutputLength += c16rtomb(&ConvertedActual[OutputLength], actual, &State);
					}
					ConvertedActual[OutputLength] = '\0';
					std::string StringActual = std::string(ConvertedActual);
					delete[] ConvertedActual;

					Assert::AreEqual(StringExpected, StringActual);
				}
			};
		}
	}
}
#endif

