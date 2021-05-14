#include "CppUnitTest.h"

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#endif

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Char.hpp"

using namespace Elysium::Core;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core
{
	TEST_CLASS(CharTest)
	{
	public:
		TEST_METHOD(LeadAndTrailBytes)
		{
			String Input = u8"\u0074\u07FF\u6045\xF0\x90\xB9\xAD";

			Assert::IsTrue(Char::IsLeadByte(Input[0]));

			Assert::IsTrue(Char::IsLeadByte(Input[1]));
			Assert::IsTrue(Char::IsTrailByte(Input[2]));

			Assert::IsTrue(Char::IsLeadByte(Input[3]));
			Assert::IsTrue(Char::IsTrailByte(Input[4]));
			Assert::IsTrue(Char::IsTrailByte(Input[5]));

			Assert::IsTrue(Char::IsLeadByte(Input[6]));
			Assert::IsTrue(Char::IsTrailByte(Input[7]));
			Assert::IsTrue(Char::IsTrailByte(Input[8]));
			Assert::IsTrue(Char::IsTrailByte(Input[9]));
		}

		TEST_METHOD(ControlCharacters)
		{
			// single byte utf-8 range
			for (size_t CodePoint = 0; CodePoint < 128; CodePoint++)
			{
				if (CodePoint < 32 || CodePoint == 127)
				{
					Assert::IsTrue(Char::IsControl(CodePoint));
				}
				else
				{
					Assert::IsFalse(Char::IsControl(CodePoint));
				}
			}

			// double byte utf-8 range
			for (size_t CodePoint = 128; CodePoint < 2048; CodePoint++)
			{
				Elysium::Core::byte* LeadByte = (Elysium::Core::byte*)&CodePoint;
				Elysium::Core::byte* TrailByte = &LeadByte[1];

				char8_t Lead = 0xC0 | (*TrailByte << 2) | (*LeadByte >> 6);
				char8_t Trail = 0x80 | (*LeadByte & 0x3F);

				if (CodePoint < 160)
				{
					Assert::IsTrue(Char::IsControl(Lead, Trail));
				}
				else
				{
					Assert::IsFalse(Char::IsControl(Lead, Trail));
				}
			}

			// triple and quad byte utf-8
			// ToDo: only requires a single test for each - no need to for a range
		}
	};
}
