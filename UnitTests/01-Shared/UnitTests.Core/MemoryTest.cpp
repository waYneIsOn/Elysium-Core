#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Memory.hpp"

using namespace Elysium::Core;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core
{
	TEST_CLASS(MemoryTest)
	{
	public:
		TEST_METHOD(NonConstTest)
		{
			Elysium::Core::uint32_t Data[256];
			for (Elysium::Core::uint32_t i = 0; i < 256; i++)
			{
				Data[i] = i;
			}

			Elysium::Core::Memory<Elysium::Core::uint32_t> Memory = Elysium::Core::Memory<Elysium::Core::uint32_t>(Data[128], 27);
			Elysium::Core::Span<Elysium::Core::uint32_t> Span = Memory.GetSpan();

			Span[0] = 27_ui32;
			Assert::AreEqual(27_ui32, Span[0]);

			for (Elysium::Core::uint32_t i = 1; i < Span.GetLength(); i++)
			{
				Assert::AreEqual(i + 128, Span[i]);
			}
		}

		TEST_METHOD(ConstTest)
		{
			Elysium::Core::uint32_t Data[256];
			for (Elysium::Core::uint32_t i = 0; i < 256; i++)
			{
				Data[i] = i;
			}

			const Elysium::Core::Memory<Elysium::Core::uint32_t> Memory = Elysium::Core::Memory<Elysium::Core::uint32_t>(Data[128], 27);
			const Elysium::Core::Span<Elysium::Core::uint32_t> Span = Memory.GetSpan();
			for (Elysium::Core::uint32_t i = 0; i < Span.GetLength(); i++)
			{
				Assert::AreEqual(i + 128, Span[i]);
			}
		}
	};
}
