#include "CppUnitTest.h"

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#include "CppUnitTestFrameworkExtension.hpp"
#endif

#include "../../../Libraries/01-Shared/Elysium.Core.IO/FileStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/IOException.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/MemoryStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/OSCompressionStream.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::IO;
using namespace Elysium::Core::IO::Compression;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::IO::Compression
{
	TEST_CLASS(OSCompressionStreamTests)
	{
	public:
		/*
		TEST_METHOD(CompressAndDecompress)
		{
			Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Data = { 0x00, 0x27, 0x45, 0x00, 0x27, 0x45, 0x00, 0x27, 0x45, };

			FileStream BaseStream = FileStream(u8"OSCompressionStream_Compress.compr", FileMode::Create);

			{
				OSCompressionStream CompressionStream = OSCompressionStream(BaseStream, OSCompressionAlgorithm::LZMS, CompressionMode::Compress, true);
				CompressionStream.Write((Elysium::Core::byte*)&Data[0], Data.GetLength());
				CompressionStream.Flush();
			}

			{
				Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Buffer = Elysium::Core::Collections::Template::Array<Elysium::Core::byte>(Data.GetLength());

				BaseStream.SetPosition(0);

				OSCompressionStream DecompressionStream = OSCompressionStream(BaseStream, OSCompressionAlgorithm::LZMS, CompressionMode::Decompress, true);
				const size_t BytesRead = DecompressionStream.Read(&Buffer[0], Buffer.GetLength());
			}
		}
		*/
	};
}