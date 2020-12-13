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
					
					for (size_t i = 0; i < Expected.GetLength(); ++i)
					{
						//Assert::IsTrue(static_cast<int32_t>(Expected[i]) == static_cast<int32_t>(Actual[i]));
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
			
				inline static Elysium::Core::Text::UTF16Encoding Utf16Encoding = Elysium::Core::Text::UTF16Encoding();
			};

			template <>
			static std::wstring ToString(const char8_t& q)
			{
				// ToDo: this is obviously incorrect!
				return std::wstring(&reinterpret_cast<const wchar_t&>(q), 1);
				/*
				Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Bytes = AssertExtended::Utf16Encoding.GetBytes(q, 0, 1);

				return std::wstring((wchar_t*)&Bytes[0], Bytes.GetLength());
				*/
			}
			/*
			template <>
			static std::wstring ToString(const Elysium::Core::String& q)
			{
				Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Bytes = AssertExtended::Utf16Encoding.GetBytes(q, 0, q.GetLength());

				return std::wstring((wchar_t*)&Bytes[0], Bytes.GetLength());
			}
			*/
		}
	}
}
#endif

