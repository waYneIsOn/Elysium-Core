#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core/VectorOfByte.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/DeflateStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/FileStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/ZipArchive.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Text/Encoding.hpp"

using namespace Elysium::Core;
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
			Elysium::Core::Container::VectorOfByte Bytes = { 0x50, 0x4B, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
			FileStream MinimalisticArchive = FileStream(u8"MinimalisticArchive.zip", FileMode::Create, FileAccess::Read | FileAccess::Write, FileShare::None);
			MinimalisticArchive.Write(&Bytes[0], Bytes.GetLength());
			MinimalisticArchive.SetPosition(0);

			ZipArchive Archive = ZipArchive(MinimalisticArchive, ZipArchiveMode::Read, false, Encoding::UTF8());
			Assert::AreEqual((Elysium::Core::size)0, Archive.GetEntries().GetLength());
		}

		TEST_METHOD(ReadArchive)
		{
			FileStream MinimalisticArchive = FileStream(u8"UT.zip", FileMode::Open, FileAccess::Read, FileShare::None);

			ZipArchive Archive = ZipArchive(MinimalisticArchive, ZipArchiveMode::Read, false, Encoding::UTF8());
			Elysium::Core::Template::Container::Vector<ZipArchiveEntry> Entries = Archive.GetEntries();
			Assert::AreEqual((Elysium::Core::size)6, Entries.GetLength());

			ZipArchiveEntry& Entry1 = Entries[0];
			const Elysium::Core::Utf8String& FullName1 = Entry1.GetFullName();
			AssertExtended::AreEqual(u8"UT/", &FullName1[0]);

			ZipArchiveEntry& Entry2 = Entries[1];
			const Elysium::Core::Utf8String& FullName2 = Entry2.GetFullName();
			AssertExtended::AreEqual(u8"UT/Compression/", &FullName2[0]);

			ZipArchiveEntry& Entry3 = Entries[2];
			const Elysium::Core::Utf8String& FullName3 = Entry3.GetFullName();
			AssertExtended::AreEqual(u8"UT/Compression/Zip/", &FullName3[0]);

			ZipArchiveEntry& Entry4 = Entries[3];
			const Elysium::Core::Utf8String& FullName4 = Entry4.GetFullName();
			AssertExtended::AreEqual(u8"UT/Compression/Zip/dok1.txt", &FullName4[0]);

			ZipArchiveEntry& Entry5 = Entries[4];
			const Elysium::Core::Utf8String& FullName5 = Entry5.GetFullName();
			AssertExtended::AreEqual(u8"UT/Compression/Zip/dok2.txt", &FullName5[0]);

			ZipArchiveEntry& Entry6 = Entries[5];
			const Elysium::Core::Utf8String& FullName6 = Entry6.GetFullName();
			AssertExtended::AreEqual(u8"UT/Compression/Zip/Lorem ipsum.txt", &FullName6[0]);
			/*
			ReadOnlyStream Entry5Stream = Entry5.Open();
			FileStream Entry5File = FileStream(Entry5.GetName(), FileMode::Create, FileAccess::Write, FileShare::None);
			Entry5Stream.CopyTo(Entry5File);
			*/
			ReadOnlyStream Entry6Stream = Entry6.Open();
			DeflateStream DecStream = DeflateStream(Entry6Stream, CompressionMode::Decompress, true);
			FileStream Entry6File = FileStream(&Entry6.GetName()[0], FileMode::Create, FileAccess::Write, FileShare::None);
			DecStream.CopyTo(Entry6File);



			/*
			Elysium::Core::size BytesRead = Entry6Stream.Read(&Buffer[0], Buffer.GetLength());
			Assert::AreEqual(Entry6Stream.GetLength(), BytesRead);
			*/

			/*
			FileStream TargetStream = FileStream(u8"Lorem ipsum decompressed.txt", FileMode::Create, FileAccess::ReadWrite, FileShare::None);
			Entry6Stream.CopyTo(TargetStream);
			Assert::AreEqual(static_cast<Elysium::Core::size>(10323), TargetStream.GetLength());

			Elysium::Core::Container::VectorOfByte Buffer = Elysium::Core::Container::VectorOfByte(TargetStream.GetLength());
			Buffer.Clear();
			TargetStream.SetPosition(0);
			Elysium::Core::size BytesRead = TargetStream.Read(&Buffer[0], Buffer.GetLength());
			Assert::AreEqual(TargetStream.GetLength(), BytesRead);

			String Content = Encoding::UTF8().GetString(&Buffer[0], Buffer.GetLength());
			//AssertExtended::AreEqual(u8"some other utf-8 text", &Content[0]);
			*/
			int sdgf = 45;
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