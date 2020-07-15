#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#ifndef ELYSIUM_CORE_INTEGER
#include "../../../Libraries/01-Shared/Elysium.Core/Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_FLOAT
#include "../../../Libraries/01-Shared/Elysium.Core/Float.hpp"
#endif

using namespace Elysium::Core;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core
{
	TEST_CLASS(NumericTest)
	{
	public:
		TEST_METHOD(Size)
		{
			Assert::AreEqual(static_cast<size_t>(2), sizeof(Elysium::Core::UInt16));
			Assert::AreEqual(static_cast<size_t>(2), sizeof(Elysium::Core::Int16));

			Assert::AreEqual(static_cast<size_t>(4), sizeof(Elysium::Core::UInt32));
			Assert::AreEqual(static_cast<size_t>(4), sizeof(Elysium::Core::Int32));

			Assert::AreEqual(static_cast<size_t>(8), sizeof(Elysium::Core::UInt64));
			Assert::AreEqual(static_cast<size_t>(8), sizeof(Elysium::Core::Int64));

			Assert::AreEqual(static_cast<size_t>(4), sizeof(Elysium::Core::Single));

			Assert::AreEqual(static_cast<size_t>(8), sizeof(Elysium::Core::Double));
		}

		TEST_METHOD(StaticMethods)
		{
			// unsigned
			AssertExtended::AreEqual(static_cast<Elysium::Core::uint16_t>(0), Elysium::Core::UInt16::GetMinValue());
			AssertExtended::AreEqual(static_cast<Elysium::Core::uint16_t>(65535), Elysium::Core::UInt16::GetMaxValue());
			Assert::IsFalse(Elysium::Core::UInt16::GetIsSigned());

			Assert::AreEqual(static_cast<Elysium::Core::uint32_t>(0), Elysium::Core::UInt32::GetMinValue());
			Assert::AreEqual(static_cast<Elysium::Core::uint32_t>(4294967295), Elysium::Core::UInt32::GetMaxValue());
			Assert::IsFalse(Elysium::Core::UInt32::GetIsSigned());

			Assert::AreEqual(static_cast<Elysium::Core::uint64_t>(0), Elysium::Core::UInt64::GetMinValue());
			Assert::AreEqual(static_cast<Elysium::Core::uint64_t>(18446744073709551615), Elysium::Core::UInt64::GetMaxValue());
			Assert::IsFalse(Elysium::Core::UInt64::GetIsSigned());

			// signed
			Assert::AreEqual(static_cast<Elysium::Core::int16_t>(-32768), Elysium::Core::Int16::GetMinValue());
			Assert::AreEqual(static_cast<Elysium::Core::int16_t>(32767), Elysium::Core::Int16::GetMaxValue());
			Assert::IsTrue(Elysium::Core::Int16::GetIsSigned());

			Assert::AreEqual(static_cast<Elysium::Core::int32_t>(-2147483647 - 1), Elysium::Core::Int32::GetMinValue());
			Assert::AreEqual(static_cast<Elysium::Core::int32_t>(2147483647), Elysium::Core::Int32::GetMaxValue());
			Assert::IsTrue(Elysium::Core::Int32::GetIsSigned());

			Assert::AreEqual(static_cast<Elysium::Core::int64_t>(-9223372036854775807 - 1), Elysium::Core::Int64::GetMinValue());
			Assert::AreEqual(static_cast<Elysium::Core::int64_t>(9223372036854775807), Elysium::Core::Int64::GetMaxValue());
			Assert::IsTrue(Elysium::Core::Int64::GetIsSigned());

			Assert::AreEqual(static_cast<float>(1.175494351e-38), Elysium::Core::Single::GetMinValue());
			Assert::AreEqual(static_cast<float>(3.40282347e+38), Elysium::Core::Single::GetMaxValue());
			Assert::IsTrue(Elysium::Core::Single::GetIsSigned());

			Assert::AreEqual(static_cast<double>(2.22507385850720138e-308), Elysium::Core::Double::GetMinValue());
			Assert::AreEqual(static_cast<double>(1.79769313486231571e+308), Elysium::Core::Double::GetMaxValue());
			Assert::IsTrue(Elysium::Core::Double::GetIsSigned());
		}
		
		TEST_METHOD(Overflow)
		{
			// underflow via subtraction
			Elysium::Core::UInt16 UnsignedShortMin = 0;
			try
			{
				UnsignedShortMin = UnsignedShortMin - 1;
				Assert::Fail();
			}
			catch (Elysium::Core::OverflowException&)
			{ }
			try
			{
				UnsignedShortMin -= 1;
				Assert::Fail();
			}
			catch (Elysium::Core::OverflowException&)
			{ }
			try
			{
				UnsignedShortMin--;
				Assert::Fail();
			}
			catch (Elysium::Core::OverflowException&)
			{ }
			try
			{
				--UnsignedShortMin;
				Assert::Fail();
			}
			catch (Elysium::Core::OverflowException&)
			{ }

			// overflow via addition
			Elysium::Core::UInt16 UnsignedShortMax = 65535;
			try
			{
				UnsignedShortMax = UnsignedShortMax + 1;
				Assert::Fail();
			}
			catch (Elysium::Core::OverflowException&)
			{ }
			try
			{
				UnsignedShortMax += 1;
				Assert::Fail();
			}
			catch (Elysium::Core::OverflowException&)
			{ }
			try
			{
				UnsignedShortMax++;
				Assert::Fail();
			}
			catch (Elysium::Core::OverflowException&)
			{ }
			try
			{
				++UnsignedShortMax;
				Assert::Fail();
			}
			catch (Elysium::Core::OverflowException&)
			{ }

			Elysium::Core::Int16 SignedShortMinusOne = -1;
			try
			{
				SignedShortMinusOne = SignedShortMinusOne * Elysium::Core::Int16::GetMinValue();
				Assert::Fail();
			}
			catch (Elysium::Core::OverflowException&)
			{ }
			try
			{
				SignedShortMinusOne *= Elysium::Core::Int16::GetMinValue();
				Assert::Fail();
			}
			catch (Elysium::Core::OverflowException&)
			{ }

			/*
			
			remaining:
			/
			/=

			*/
		}

		TEST_METHOD(AssigmentOperators)
		{
			Elysium::Core::Int32 Value1 = -25;
			Assert::AreEqual(static_cast<Elysium::Core::int32_t>(-25), static_cast<Elysium::Core::int32_t>(Value1));

			Value1 += 25;
			Assert::AreEqual(static_cast<Elysium::Core::int32_t>(0), static_cast<Elysium::Core::int32_t>(Value1));

			Value1 -= 12;
			Assert::AreEqual(static_cast<Elysium::Core::int32_t>(-12), static_cast<Elysium::Core::int32_t>(Value1));

			Value1 *= -1;
			Assert::AreEqual(static_cast<Elysium::Core::int32_t>(12), static_cast<Elysium::Core::int32_t>(Value1));

			Value1 %= 3;
			Assert::AreEqual(static_cast<Elysium::Core::int32_t>(0), static_cast<Elysium::Core::int32_t>(Value1));

			Value1 = 1;
			Value1 <<= 8;
			Assert::AreEqual(static_cast<Elysium::Core::int32_t>(256), static_cast<Elysium::Core::int32_t>(Value1));

			Value1 >>= 1;
			Assert::AreEqual(static_cast<Elysium::Core::int32_t>(128), static_cast<Elysium::Core::int32_t>(Value1));

			//Value1 /= 2;
			//Assert::AreEqual(static_cast<Elysium::Core::int32_t>(6), static_cast<Elysium::Core::int32_t>(Value1));

			/*

			remaining:
			/=

			&=
			|=
			^=

			*/
		}

		TEST_METHOD(ComparisonOperators)
		{
			Elysium::Core::Int16 Value1 = -25;
			Elysium::Core::Int16 Value2 = 32;

			Assert::IsFalse(Value1 == Value2);
			Assert::IsTrue(Value1 != Value2);
			Assert::IsTrue(Value1 < Value2);
			Assert::IsFalse(Value1 > Value2);
			Assert::IsTrue(Value1 <= Value2);
			Assert::IsFalse(Value1 >= Value2);
		}

		TEST_METHOD(LogicalOperators)
		{
			Elysium::Core::Int16 Value1 = -25;
			Elysium::Core::Int16 Value2 = -25;
			Elysium::Core::Int16 Value3 = 32;
			Elysium::Core::Int16 Value4 = 32;

			Assert::IsFalse((Value1 == Value2) && (Value3 > Value4));
			Assert::IsTrue((Value1 == Value2) || (Value3 > Value4));
			Assert::IsTrue(!((Value1 == Value2) && (Value3 > Value4)));
		}

		TEST_METHOD(BitwiseOperators)
		{
			Elysium::Core::Int32 Value = 1;

			Value = Value << 2;
			Assert::AreEqual(static_cast<Elysium::Core::int32_t>(4), static_cast<Elysium::Core::int32_t>(Value));

			Value = Value >> 1;
			Assert::AreEqual(static_cast<Elysium::Core::int32_t>(2), static_cast<Elysium::Core::int32_t>(Value));
			/*

			remaining:
			&
			|
			^
			~

			*/
		}
	};
}