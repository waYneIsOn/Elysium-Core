#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Literals.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Primitives.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Utility/IntegerSequence.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Utility
{
	TEST_CLASS(IntegerSequenceTests)
	{
	public:
		TEST_METHOD(LengthTests)
		{
			constexpr const Elysium::Core::Template::System::size UInt8SequenceLength = _UInt8Sequence.Length;
			constexpr const Elysium::Core::Template::System::size Int8SequenceLength = _Int8Sequence.Length;

			Assert::AreEqual(4_ui64, UInt8SequenceLength);
			Assert::AreEqual(3_ui64, Int8SequenceLength);
		}

		TEST_METHOD(FirstTests)
		{
			constexpr const Elysium::Core::Template::System::uint8_t UInt8SequenceFirst = _UInt8Sequence.First;
			constexpr const Elysium::Core::Template::System::int8_t Int8SequenceFirst = _Int8Sequence.First;

			Assert::AreEqual(3_ui8, UInt8SequenceFirst);
			Assert::AreEqual(255_i8, Int8SequenceFirst);
		}

		TEST_METHOD(LastTests)
		{
			constexpr const Elysium::Core::Template::System::uint8_t UInt8SequenceLast = _UInt8Sequence.Last;
			constexpr const Elysium::Core::Template::System::int8_t Int8SequenceLast = _Int8Sequence.Last;

			Assert::AreEqual(0_ui8, UInt8SequenceLast);
			Assert::AreEqual(1_i8, Int8SequenceLast);
		}

		TEST_METHOD(GetAtTests)
		{
			using Sequence = typename Elysium::Core::Template::Utility::IntegerSequence<Elysium::Core::Template::System::uint64_t, 4, 5, 6>;

			// invalid indices (index out of range)
			//constexpr const Elysium::Core::Template::System::uint8_t UInt8SequenceElement4 = _UInt8Sequence.GetAt<4>();
			//constexpr const Elysium::Core::Template::System::int8_t Int8SequenceElement3 = _Int8Sequence.GetAt<3>();
			//constexpr const Elysium::Core::Template::System::uint8_t SequenceElement3 = Sequence::GetAt<3>();

			// valid indices
			constexpr const Elysium::Core::Template::System::uint8_t UInt8SequenceElement0 = _UInt8Sequence.GetAt<0>();
			constexpr const Elysium::Core::Template::System::uint8_t UInt8SequenceElement1 = _UInt8Sequence.GetAt<1>();
			constexpr const Elysium::Core::Template::System::uint8_t UInt8SequenceElement2 = _UInt8Sequence.GetAt<2>();
			constexpr const Elysium::Core::Template::System::uint8_t UInt8SequenceElement3 = _UInt8Sequence.GetAt<3>();

			Assert::AreEqual(3_ui8, UInt8SequenceElement0);
			Assert::AreEqual(2_ui8, UInt8SequenceElement1);
			Assert::AreEqual(1_ui8, UInt8SequenceElement2);
			Assert::AreEqual(0_ui8, UInt8SequenceElement3);

			constexpr const Elysium::Core::Template::System::int8_t Int8SequenceElement0 = _Int8Sequence.GetAt<0>();
			constexpr const Elysium::Core::Template::System::int8_t Int8SequenceElement1 = _Int8Sequence.GetAt<1>();
			constexpr const Elysium::Core::Template::System::int8_t Int8SequenceElement2 = _Int8Sequence.GetAt<2>();

			Assert::AreEqual(255_i8, Int8SequenceElement0);
			Assert::AreEqual(0_i8, Int8SequenceElement1);
			Assert::AreEqual(1_i8, Int8SequenceElement2);

			// ...
			constexpr const Elysium::Core::Template::System::uint8_t SequenceElement0 = Sequence::GetAt<0>();
			constexpr const Elysium::Core::Template::System::uint8_t SequenceElement1 = Sequence::GetAt<1>();
			constexpr const Elysium::Core::Template::System::uint8_t SequenceElement2 = Sequence::GetAt<2>();

			Assert::AreEqual(4_ui8, SequenceElement0);
			Assert::AreEqual(5_ui8, SequenceElement1);
			Assert::AreEqual(6_ui8, SequenceElement2);
		}
	private:
		static constexpr const Elysium::Core::Template::Utility::IntegerSequence _UInt8Sequence =
			Elysium::Core::Template::Utility::IntegerSequence<Elysium::Core::Template::System::uint8_t, 3, 2, 1, 0>();
		static constexpr const Elysium::Core::Template::Utility::IntegerSequence _Int8Sequence =
			Elysium::Core::Template::Utility::IntegerSequence<Elysium::Core::Template::System::int8_t, -1, 0, 1>();
	};
}
