#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#ifndef ELYSIUM_CORE_INTEGER
#include "../../../Libraries/01-Shared/Elysium.Core/Integer.hpp"
#endif

using namespace Elysium::Core;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core
{
	TEST_CLASS(IntegerTest)
	{
	public:
		TEST_METHOD(Size)
		{
			//Assert::AreEqual((size_t)1, sizeof(Elysium::Core::Byte));
			//Assert::AreEqual((size_t)1, sizeof(Elysium::Core::SByte));

			Assert::AreEqual((size_t)2, sizeof(Elysium::Core::UInt16));
			Assert::AreEqual((size_t)2, sizeof(Elysium::Core::Int16));

			Assert::AreEqual((size_t)4, sizeof(Elysium::Core::UInt32));
			Assert::AreEqual((size_t)4, sizeof(Elysium::Core::Int32));

			Assert::AreEqual((size_t)8, sizeof(Elysium::Core::UInt64));
			Assert::AreEqual((size_t)8, sizeof(Elysium::Core::Int64));
		}

		TEST_METHOD(StaticMethods)
		{
			// unsigned
			AssertExtended::AreEqual((Elysium::Core::uint16_t)0, Elysium::Core::UInt16::GetMinValue());
			AssertExtended::AreEqual((Elysium::Core::uint16_t)65535, Elysium::Core::UInt16::GetMaxValue());

			Assert::AreEqual((Elysium::Core::uint32_t)0, Elysium::Core::UInt32::GetMinValue());
			Assert::AreEqual((Elysium::Core::uint32_t)4294967295, Elysium::Core::UInt32::GetMaxValue());

			Assert::AreEqual((Elysium::Core::uint64_t)0, Elysium::Core::UInt64::GetMinValue());
			Assert::AreEqual((Elysium::Core::uint64_t)18446744073709551615, Elysium::Core::UInt64::GetMaxValue());

			// signed
			Assert::AreEqual((Elysium::Core::int16_t)-32768, Elysium::Core::Int16::GetMinValue());
			Assert::AreEqual((Elysium::Core::int16_t)32767, Elysium::Core::Int16::GetMaxValue());

			Assert::AreEqual((Elysium::Core::int32_t)-2147483648, Elysium::Core::Int32::GetMinValue());
			Assert::AreEqual((Elysium::Core::int32_t)2147483647, Elysium::Core::Int32::GetMaxValue());

			Assert::AreEqual((Elysium::Core::int64_t)-9223372036854775808, Elysium::Core::Int64::GetMinValue());
			Assert::AreEqual((Elysium::Core::int64_t)9223372036854775807, Elysium::Core::Int64::GetMaxValue());
		}
		
		TEST_METHOD(Operators)
		{
			// underflow via subtraction
			Elysium::Core::UInt16 UnsignedShortMin = 0;
			try
			{
				UnsignedShortMin = UnsignedShortMin - 1;
				Assert::Fail();
			}
			catch (Elysium::Core::OverflowException& ex)
			{ }
			try
			{
				UnsignedShortMin -= 1;
				Assert::Fail();
			}
			catch (Elysium::Core::OverflowException& ex)
			{ }
			try
			{
				UnsignedShortMin--;
				Assert::Fail();
			}
			catch (Elysium::Core::OverflowException& ex)
			{ }
			try
			{
				--UnsignedShortMin;
				Assert::Fail();
			}
			catch (Elysium::Core::OverflowException& ex)
			{ }

			// overflow via addition
			Elysium::Core::UInt16 UnsignedShortMax = 65535;
			try
			{
				UnsignedShortMax = UnsignedShortMax + 1;
				Assert::Fail();
			}
			catch (Elysium::Core::OverflowException& ex)
			{ }
			try
			{
				UnsignedShortMax += 1;
				Assert::Fail();
			}
			catch (Elysium::Core::OverflowException& ex)
			{ }
			try
			{
				UnsignedShortMax++;
				Assert::Fail();
			}
			catch (Elysium::Core::OverflowException& ex)
			{ }
			try
			{
				++UnsignedShortMax;
				Assert::Fail();
			}
			catch (Elysium::Core::OverflowException& ex)
			{ }

			Elysium::Core::Int16 SignedShortMinusOne = -1;
			try
			{
				SignedShortMinusOne = SignedShortMinusOne * Elysium::Core::Int16::GetMinValue();
				Assert::Fail();
			}
			catch (Elysium::Core::OverflowException& ex)
			{ }
			try
			{
				SignedShortMinusOne *= Elysium::Core::Int16::GetMinValue();
				Assert::Fail();
			}
			catch (Elysium::Core::OverflowException& ex)
			{ }
		}
	};
}