#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core/List.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/FileStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/GZipStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Math/MathHelper.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Collections::Generic;
using namespace Elysium::Core::IO;
using namespace Elysium::Core::IO::Compression;
using namespace Elysium::Core::Math;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsCore
{
	TEST_CLASS(Core_IO_Compression_GZipStream)
	{
	public:
		TEST_METHOD(Read)
		{
			const size_t BufferSize = 8192;
			byte Buffer[8192];
			size_t BytesRead = 0;

			FileStream FS = FileStream(L"test.lz77", FileMode::Open, FileAccess::Read, FileShare::None);
			GZipStream DecompressionStream = GZipStream(FS, CompressionMode::Decompress);
			BytesRead = DecompressionStream.Read(&Buffer[0], BufferSize);


			/*
			for (size_t i = 0; i < TotalBuffer.GetCount(); i++)
			{
				Logger::WriteMessage(std::to_string((int)TotalBuffer[i]).c_str());
			}
			*/

			//ZipFileStream.SetPosition(1440);
			//Assert::AreEqual(ZipFileStream.GetLength(), TotalBuffer.GetCount());
		}
	};
}