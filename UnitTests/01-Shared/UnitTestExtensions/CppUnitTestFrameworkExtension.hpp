#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#define MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT
#include <CppUnitTestAssert.h>
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

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	class AssertExtended
	{
	public:
		inline static void AreEqual(const Elysium::Core::uint8_t Expected, const Elysium::Core::uint8_t Actual)
		{
			Assert::IsTrue(Expected == Actual);
		}

		inline static void AreEqual(const Elysium::Core::uint16_t Expected, const Elysium::Core::uint16_t Actual)
		{
			Assert::IsTrue(Expected == Actual);
		}

		inline static void AreEqual(const Elysium::Core::uint32_t Expected, const Elysium::Core::uint32_t Actual)
		{
			Assert::IsTrue(Expected == Actual);
		}

		inline static void AreEqual(const Elysium::Core::uint64_t Expected, const Elysium::Core::uint64_t Actual)
		{
			Assert::IsTrue(Expected == Actual);
		}

		inline static void AreEqual(const Elysium::Core::int8_t Expected, const Elysium::Core::int8_t Actual)
		{
			Assert::IsTrue(Expected == Actual);
		}

		inline static void AreEqual(const Elysium::Core::int16_t Expected, const Elysium::Core::int16_t Actual)
		{
			Assert::IsTrue(Expected == Actual);
		}

		inline static void AreEqual(const Elysium::Core::int64_t Expected, const Elysium::Core::int64_t Actual)
		{
			Assert::IsTrue(Expected == Actual);
		}
		/*
		inline static void AreEqual(const char Expected, const char Actual)
		{
			Assert::IsTrue(Expected == Actual);
		}
		*/
		inline static void AreEqual(const char8_t Expected, const char8_t Actual)
		{
			Assert::IsTrue(Expected == Actual);
		}

		inline static void AreEqual(const char16_t Expected, const char16_t Actual)
		{
			Assert::IsTrue(Expected == Actual);
		}

		inline static void AreEqual(const char32_t Expected, const char32_t Actual)
		{
			Assert::IsTrue(Expected == Actual);
		}

		inline static void AreEqual(const wchar_t Expected, const wchar_t Actual)
		{
			Assert::IsTrue(Expected == Actual);
		}

		inline static void AreEqual(const Elysium::Core::String& Expected, const Elysium::Core::String& Actual, bool ignoreCase = false, const wchar_t* message = NULL, const __LineInfo* pLineInfo = NULL)
		{
			// length can actually differ but actual's length must be at least the same length as expected's
			Assert::IsTrue(Actual.GetLength() >= Expected.GetLength());

			for (Elysium::Core::size i = 0; i < Expected.GetLength(); ++i)
			{
				Elysium::Core::String::ConstCharacterReference ExpectedChar = Expected[i];
				Elysium::Core::String::ConstCharacterReference ActualChar = Actual[i];

				Assert::AreEqual(ExpectedChar, ActualChar);
			}
		}

		inline static void AreEqual(const Elysium::Core::Utf8String& Expected, const Elysium::Core::Utf8String& Actual, bool ignoreCase = false, const wchar_t* message = NULL, const __LineInfo* pLineInfo = NULL)
		{
			// length can actually differ but actual's length must be at least the same length as expected's
			Assert::IsTrue(Actual.GetLength() >= Expected.GetLength());

			for (Elysium::Core::size i = 0; i < Expected.GetLength(); ++i)
			{
				Elysium::Core::Utf8String::ConstCharacterReference ExpectedChar = Expected[i];
				Elysium::Core::Utf8String::ConstCharacterReference ActualChar = Actual[i];

				AssertExtended::AreEqual(ExpectedChar, ActualChar);
			}
		}

		inline static void AreEqual(const Elysium::Core::Utf16String& Expected, const Elysium::Core::Utf16String& Actual, bool ignoreCase = false, const wchar_t* message = NULL, const __LineInfo* pLineInfo = NULL)
		{
			// length can actually differ but actual's length must be at least the same length as expected's
			Assert::IsTrue(Actual.GetLength() >= Expected.GetLength());

			for (Elysium::Core::size i = 0; i < Expected.GetLength(); ++i)
			{
				Elysium::Core::Utf16String::ConstCharacterReference ExpectedChar = Expected[i];
				Elysium::Core::Utf16String::ConstCharacterReference ActualChar = Actual[i];

				AssertExtended::AreEqual(ExpectedChar, ActualChar);
			}
		}

		inline static void AreEqual(const Elysium::Core::Utf32String& Expected, const Elysium::Core::Utf32String& Actual, bool ignoreCase = false, const wchar_t* message = NULL, const __LineInfo* pLineInfo = NULL)
		{
			// length can actually differ but actual's length must be at least the same length as expected's
			Assert::IsTrue(Actual.GetLength() >= Expected.GetLength());

			for (Elysium::Core::size i = 0; i < Expected.GetLength(); ++i)
			{
				Elysium::Core::Utf32String::ConstCharacterReference ExpectedChar = Expected[i];
				Elysium::Core::Utf32String::ConstCharacterReference ActualChar = Actual[i];

				AssertExtended::AreEqual(ExpectedChar, ActualChar);
			}
		}

		inline static void AreEqual(const Elysium::Core::WideString& Expected, const Elysium::Core::WideString& Actual, bool ignoreCase = false, const wchar_t* message = NULL, const __LineInfo* pLineInfo = NULL)
		{
			//Assert::AreEqual(Expected.GetLength(), Actual.GetLength());

			for (Elysium::Core::size i = 0; i < Expected.GetLength(); ++i)
			{
				Elysium::Core::WideString::ConstCharacterReference ExpectedChar = Expected[i];
				Elysium::Core::WideString::ConstCharacterReference ActualChar = Actual[i];

				AssertExtended::AreEqual(ExpectedChar, ActualChar);
			}
		}

		inline static Elysium::Core::Text::UTF16Encoding& Utf16Encoding()
		{
			static Elysium::Core::Text::UTF16Encoding Utf16Encoding = Elysium::Core::Text::UTF16Encoding();
			return Utf16Encoding;
		}
	};

	template <>
	inline static std::wstring ToString(const char8_t& q)
	{
		Elysium::Core::Container::VectorOfByte Bytes = AssertExtended::Utf16Encoding().GetBytes(&q, 1, 1);

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
#endif

