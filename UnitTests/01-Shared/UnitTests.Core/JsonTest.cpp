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
			JsonWriter.WritePropertyName(L"Bool1");
			JsonWriter.WriteValue(true);
			JsonWriter.WritePropertyName(L"Bool2");
			JsonWriter.WriteValue(false);
			JsonWriter.WritePropertyName(L"Float");
			JsonWriter.WriteValue(13.37f);
			JsonWriter.WritePropertyName(L"Double");
			JsonWriter.WriteValue(13.37);
			JsonWriter.WritePropertyName(L"String");
			JsonWriter.WriteValue(L"SomeValue");

			// ToDo: this results in invalid json
			JsonWriter.WritePropertyName(L"IntArray");
			JsonWriter.WriteStartArray();
			JsonWriter.WriteValue(1);
			JsonWriter.WriteValue(2);
			JsonWriter.WriteValue(3);
			JsonWriter.WriteEndArray();
			
			JsonWriter.WritePropertyName(L"SomeObject");
			JsonWriter.WriteStartObject();
			JsonWriter.WritePropertyName(L"Property1");
			JsonWriter.WriteValue(L"Value1");
			JsonWriter.WritePropertyName(L"Property2");
			JsonWriter.WriteValue(L"Value2");
			JsonWriter.WritePropertyName(L"Property3");
			JsonWriter.WriteStartArray();
			/*
			// ToDo: this results in invalid json
			JsonWriter.WriteStartArray();
			JsonWriter.WriteEndArray();
			JsonWriter.WriteStartArray();
			JsonWriter.WriteEndArray();
			*/
			JsonWriter.WriteEndArray();
			JsonWriter.WriteEndObject();
			/*
			// ToDo: this results in invalid json - can there even be an empty object or should it be null?
			JsonWriter.WritePropertyName(L"SomeEmptyObject");
			JsonWriter.WriteStartObject();
			JsonWriter.WriteEndObject();
			*/
			JsonWriter.WritePropertyName(L"NullValue");
			JsonWriter.WriteNull();
			JsonWriter.WritePropertyName(L"String");
			JsonWriter.WriteValue(L"SomeValue");
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
