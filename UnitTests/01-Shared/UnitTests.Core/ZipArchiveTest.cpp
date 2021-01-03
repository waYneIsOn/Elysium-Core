#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core/Array.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/FileStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/ZipArchive.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Text/Encoding.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Collections::Template;
using namespace Elysium::Core::IO;
using namespace Elysium::Core::IO::Compression;
using namespace Elysium::Core::Text;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::IO::Compression
{
	TEST_CLASS(ZipArchiveTests)
	{
	public:
		TEST_METHOD(ReadMinimalisticArchive)
		{
			Array<byte> Bytes = { 0x50, 0x4B, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
			FileStream MinimalisticArchive = FileStream(u8"MinimalisticArchive.zip", FileMode::Create, FileAccess::ReadWrite, FileShare::None);
			MinimalisticArchive.Write(&Bytes[0], Bytes.GetLength());
			MinimalisticArchive.SetPosition(0);

			ZipArchive Archive = ZipArchive(MinimalisticArchive, ZipArchiveMode::Read, false, Encoding::UTF8());
			Assert::AreEqual((size_t)0, Archive.GetEntries().GetCount());
		}

		TEST_METHOD(ReadArchive)
		{
			FileStream MinimalisticArchive = FileStream(u8"UT.zip", FileMode::Open, FileAccess::Read, FileShare::None);

			ZipArchive Archive = ZipArchive(MinimalisticArchive, ZipArchiveMode::Read, false, Encoding::UTF8());
			const Elysium::Core::Collections::Template::List<ZipArchiveEntry> Entries = Archive.GetEntries();
			Assert::AreEqual((size_t)5, Entries.GetCount());

			ZipArchiveEntry& Entry1 = Entries[0];
			const String& FullName1 = Entry1.GetFullName();
			AssertExtended::AreEqual(u8"UT/", &FullName1[0]);

			ZipArchiveEntry& Entry2 = Entries[1];
			const String& FullName2 = Entry2.GetFullName();
			AssertExtended::AreEqual(u8"UT/Compression/", &FullName2[0]);

			ZipArchiveEntry& Entry3 = Entries[2];
			const String& FullName3 = Entry3.GetFullName();
			AssertExtended::AreEqual(u8"UT/Compression/Zip/", &FullName3[0]);

			ZipArchiveEntry& Entry4 = Entries[3];
			const String& FullName4 = Entry4.GetFullName();
			AssertExtended::AreEqual(u8"UT/Compression/Zip/dok1.txt", &FullName4[0]);

			ZipArchiveEntry& Entry5 = Entries[4];
			const String& FullName5 = Entry5.GetFullName();
			AssertExtended::AreEqual(u8"UT/Compression/Zip/dok2.txt", &FullName5[0]);
			
			ReadOnlyStream Entry5DataStream = Entry5.Open();
			FileStream TargetStream = FileStream(u8"dok2.txt", FileMode::Create, FileAccess::ReadWrite, FileShare::None);
			Entry5DataStream.CopyTo(TargetStream);
			Assert::AreEqual(static_cast<size_t>(21), TargetStream.GetLength());

			Array<byte> Buffer = Array<byte>(TargetStream.GetLength());
			TargetStream.SetPosition(0);
			size_t BytesRead = TargetStream.Read(&Buffer[0], Buffer.GetLength());

			String Data = Encoding::UTF8().GetString(&Buffer[0], Buffer.GetLength());
			AssertExtended::AreEqual(u8"some other utf-8 text", &Data[0]);
		}

		TEST_METHOD(ReadMultiFileArchive)
		{
			Assert::Fail();
		}

		TEST_METHOD(ReadEncryptedArchive)
		{
			Assert::Fail();
		}
	};
}