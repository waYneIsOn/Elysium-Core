#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Version.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Literals.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Move.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core
{
	TEST_CLASS(VersionTests)
	{
	public:
		TEST_METHOD(CopyAndMoveTests)
		{
			constexpr const Elysium::Core::Version Source = Elysium::Core::Version(21, 34);
			Assert::AreEqual(21_ui16, Source.GetMajor());
			Assert::AreEqual(34_ui16, Source.GetMinor());
			Assert::AreEqual(0xFFFF_ui16, Source.GetRevision());
			Assert::AreEqual(0xFFFF_ui16, Source.GetBuild());

			// ...
			Elysium::Core::Version Copied = Source;	// musn't be constexpr or later on even a "moved object" will get copied
			Assert::AreEqual(21_ui16, Source.GetMajor());
			Assert::AreEqual(34_ui16, Source.GetMinor());
			Assert::AreEqual(0xFFFF_ui16, Source.GetRevision());
			Assert::AreEqual(0xFFFF_ui16, Source.GetBuild());

			Assert::AreEqual(21_ui16, Copied.GetMajor());
			Assert::AreEqual(34_ui16, Copied.GetMinor());
			Assert::AreEqual(0xFFFF_ui16, Copied.GetRevision());
			Assert::AreEqual(0xFFFF_ui16, Copied.GetBuild());

			Elysium::Core::Version CopiedThroughConstructor = Elysium::Core::Version(Source); // musn't be constexpr or later on even a "moved object" will get copied
			Assert::AreEqual(21_ui16, Copied.GetMajor());
			Assert::AreEqual(34_ui16, Copied.GetMinor());
			Assert::AreEqual(0xFFFF_ui16, Copied.GetRevision());
			Assert::AreEqual(0xFFFF_ui16, Copied.GetBuild());

			Assert::AreEqual(21_ui16, CopiedThroughConstructor.GetMajor());
			Assert::AreEqual(34_ui16, CopiedThroughConstructor.GetMinor());
			Assert::AreEqual(0xFFFF_ui16, CopiedThroughConstructor.GetRevision());
			Assert::AreEqual(0xFFFF_ui16, CopiedThroughConstructor.GetBuild());

			// ...
			Elysium::Core::Version Moved = Elysium::Core::Template::Functional::Move(Copied);
			Assert::AreEqual(0_ui16, Copied.GetMajor());
			Assert::AreEqual(0_ui16, Copied.GetMinor());
			Assert::AreEqual(0xFFFF_ui16, Copied.GetRevision());
			Assert::AreEqual(0xFFFF_ui16, Copied.GetBuild());
			
			Assert::AreEqual(21_ui16, Moved.GetMajor());
			Assert::AreEqual(34_ui16, Moved.GetMinor());
			Assert::AreEqual(0xFFFF_ui16, Moved.GetRevision());
			Assert::AreEqual(0xFFFF_ui16, Moved.GetBuild());

			Elysium::Core::Version MovedThroughConstructor = 
				Elysium::Core::Version(Elysium::Core::Template::Functional::Move(CopiedThroughConstructor));
			Assert::AreEqual(0_ui16, CopiedThroughConstructor.GetMajor());
			Assert::AreEqual(0_ui16, CopiedThroughConstructor.GetMinor());
			Assert::AreEqual(0xFFFF_ui16, CopiedThroughConstructor.GetRevision());
			Assert::AreEqual(0xFFFF_ui16, CopiedThroughConstructor.GetBuild());

			Assert::AreEqual(21_ui16, MovedThroughConstructor.GetMajor());
			Assert::AreEqual(34_ui16, MovedThroughConstructor.GetMinor());
			Assert::AreEqual(0xFFFF_ui16, MovedThroughConstructor.GetRevision());
			Assert::AreEqual(0xFFFF_ui16, MovedThroughConstructor.GetBuild());
		}

		TEST_METHOD(StringRepresentationsTests)
		{
			/*
			const Elysium::Core::Utf8String Zero = static_cast<Elysium::Core::Utf8String>(_Zero);
			const Elysium::Core::Utf8String Two = static_cast<Elysium::Core::Utf8String>(_Two);
			const Elysium::Core::Utf8String Three = static_cast<Elysium::Core::Utf8String>(_Three);
			const Elysium::Core::Utf8String Four = static_cast<Elysium::Core::Utf8String>(_Four);
			*/
			bool bla = false;
		}
	private:
		static constexpr const Elysium::Core::Version _Zero = Elysium::Core::Version();
		static constexpr const Elysium::Core::Version _Two = Elysium::Core::Version(1, 3);
		static constexpr const Elysium::Core::Version _Three = Elysium::Core::Version(1, 3, 25);
		static constexpr const Elysium::Core::Version _Four = Elysium::Core::Version(1, 3, 25, 1337);
	};
}
