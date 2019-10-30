#include "CppUnitTest.h"

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#include "CppUnitTestFrameworkExtension.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_MEMORYSTREAM
#include "../../../Libraries/01-Shared/Elysium.Core.IO/MemoryStream.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAMWRITER
#include "../../../Libraries/01-Shared/Elysium.Core.IO/StreamWriter.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONDOCUMENT
#include "../../../Libraries/01-Shared/Elysium.Core.Json/JsonDocument.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONTEXTWRITER
#include "../../../Libraries/01-Shared/Elysium.Core.Json/JsonTextWriter.hpp"
#endif

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Elysium::Core::IO;
using namespace Elysium::Core::Json;

namespace UnitTestsCore
{
	TEST_CLASS(Core_Json)
	{
	public:
		TEST_METHOD(WriterFixed)
		{
			// prepare
			MemoryStream Target = MemoryStream();
			StreamWriter Writer = StreamWriter(Target);
			JsonTextWriter JsonWriter = JsonTextWriter(Writer);

			// write
			JsonWriter.WriteStartObject();
			JsonWriter.WritePropertyName(L"Int");
			JsonWriter.WriteValue(5448);
			JsonWriter.WritePropertyName(L"Float");
			JsonWriter.WriteValue(13.37);
			JsonWriter.WriteEndObject();

			// check
		}
		TEST_METHOD(WriterFromDocument)
		{
			// prepare
			MemoryStream Target = MemoryStream();
			StreamWriter Writer = StreamWriter(Target);
			JsonTextWriter JsonWriter = JsonTextWriter(Writer);

			JsonDocument Document = JsonDocument();

			// write
			Document.WriteTo(JsonWriter);

			// check
		}
	};
}
