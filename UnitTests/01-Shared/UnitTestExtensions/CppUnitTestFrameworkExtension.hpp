#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#define MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT
#include <CppUnitTestAssert.h>
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

#ifndef ELYSIUM_CORE_TEXT_UTF16ENCODING
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Text/UTF16Encoding.hpp"
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
				static void AreEqual(const Elysium::Core::String& Expected, const Elysium::Core::String& Actual, bool ignoreCase = false, const wchar_t* message = NULL, const __LineInfo* pLineInfo = NULL)
				{
					//Assert::AreEqual(Expected.GetLength(), Actual.GetLength());

					for (Elysium::Core::size i = 0; i < Expected.GetLength(); ++i)
					{
						char8_t ExpectedChar = Expected[i];
						char8_t ActualChar = Actual[i];

						Assert::AreEqual(ExpectedChar, ActualChar);
						//Assert::AreEqual(Expected[i], Actual[i]);
					}
				}

				static void AreEqual(const Elysium::Core::WideString& Expected, const Elysium::Core::WideString& Actual, bool ignoreCase = false, const wchar_t* message = NULL, const __LineInfo* pLineInfo = NULL)
				{
					//Assert::AreEqual(Expected.GetLength(), Actual.GetLength());

					for (Elysium::Core::size i = 0; i < Expected.GetLength(); ++i)
					{
						char8_t ExpectedChar = Expected[i];
						char8_t ActualChar = Actual[i];

						Assert::AreEqual(ExpectedChar, ActualChar);
						//Assert::AreEqual(Expected[i], Actual[i]);
					}
				}

				static void AreEqual(const Elysium::Core::Utf8String& Expected, const Elysium::Core::Utf8String& Actual, bool ignoreCase = false, const wchar_t* message = NULL, const __LineInfo* pLineInfo = NULL)
				{
					//Assert::AreEqual(Expected.GetLength(), Actual.GetLength());

					for (Elysium::Core::size i = 0; i < Expected.GetLength(); ++i)
					{
						char8_t ExpectedChar = Expected[i];
						char8_t ActualChar = Actual[i];

						Assert::AreEqual(ExpectedChar, ActualChar);
						//Assert::AreEqual(Expected[i], Actual[i]);
					}
				}

				static void AreEqual(const Elysium::Core::Utf16String& Expected, const Elysium::Core::Utf16String& Actual, bool ignoreCase = false, const wchar_t* message = NULL, const __LineInfo* pLineInfo = NULL)
				{
					//Assert::AreEqual(Expected.GetLength(), Actual.GetLength());

					for (Elysium::Core::size i = 0; i < Expected.GetLength(); ++i)
					{
						char8_t ExpectedChar = Expected[i];
						char8_t ActualChar = Actual[i];

						Assert::AreEqual(ExpectedChar, ActualChar);
						//Assert::AreEqual(Expected[i], Actual[i]);

						//Assert::IsTrue(static_cast<uint16_t>(Expected[i]) == static_cast<uint16_t>(Actual[i]));
					}
				}

				static void AreEqual(const Elysium::Core::Utf32String& Expected, const Elysium::Core::Utf32String& Actual, bool ignoreCase = false, const wchar_t* message = NULL, const __LineInfo* pLineInfo = NULL)
				{
					//Assert::AreEqual(Expected.GetLength(), Actual.GetLength());

					for (Elysium::Core::size i = 0; i < Expected.GetLength(); ++i)
					{
						char8_t ExpectedChar = Expected[i];
						char8_t ActualChar = Actual[i];

						Assert::AreEqual(ExpectedChar, ActualChar);
						//Assert::AreEqual(Expected[i], Actual[i]);

						//::IsTrue(static_cast<uint32_t>(Expected[i]) == static_cast<uint32_t>(Actual[i]));
					}
				}

				static void AreEqual(const Elysium::Core::uint8_t Expected, const Elysium::Core::uint8_t Actual)
				{
					Assert::IsTrue(Expected == Actual);
				}

				static void AreEqual(const Elysium::Core::uint16_t Expected, const Elysium::Core::uint16_t Actual)
				{
					Assert::IsTrue(Expected == Actual);
				}

				static void AreEqual(const Elysium::Core::uint32_t Expected, const Elysium::Core::uint32_t Actual)
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
			
				inline static Elysium::Core::Text::UTF16Encoding Utf16Encoding = Elysium::Core::Text::UTF16Encoding();
			};

			template <>
			static std::wstring ToString(const char8_t& q)
			{
				Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Bytes = AssertExtended::Utf16Encoding.GetBytes(&q, 1, 1);

				return std::wstring((wchar_t*)&Bytes[0], Bytes.GetLength());
			}
			/*
			template <>
			static std::wstring ToString(const Elysium::Core::Utf8String& q)
			{
				Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Bytes = AssertExtended::Utf16Encoding.GetBytes(q, 0, q.GetLength());

				return std::wstring((wchar_t*)&Bytes[0], Bytes.GetLength());
			}
			*/
		}
	}
}
#endif

