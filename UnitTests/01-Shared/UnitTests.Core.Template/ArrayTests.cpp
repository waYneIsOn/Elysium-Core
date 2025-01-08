#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Array.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Container
{
	TEST_CLASS(ArrayTests)
	{
	public:
		TEST_METHOD(Iterators)
		{
			Elysium::Core::Template::Container::Array<Elysium::Core::Template::System::uint8_t, 3> Instance = { 0, 1, 2 };
			for (Elysium::Core::Template::Container::Array<Elysium::Core::Template::System::uint8_t, 3>::FIterator Iterator = Instance.GetBegin();
				Iterator != Instance.GetEnd(); ++Iterator)
			{
				(*Iterator) = 128;
			}

			Assert::AreEqual(128_ui8, Instance[0]);
			Assert::AreEqual(128_ui8, Instance[1]);
			Assert::AreEqual(128_ui8, Instance[2]);

			Instance[0] = 0;
			Instance[0] = 1;
			Instance[0] = 2;

			const Elysium::Core::Template::Container::Array<Elysium::Core::Template::System::uint8_t, 3>& ConstReference = Instance;
			for (Elysium::Core::Template::Container::Array<Elysium::Core::Template::System::uint8_t, 3>::ConstIterator Iterator = ConstReference.GetBegin();
				Iterator != ConstReference.GetEnd(); ++Iterator)
			{
				//(*Iterator) = 128;
			}
		}
	};
}