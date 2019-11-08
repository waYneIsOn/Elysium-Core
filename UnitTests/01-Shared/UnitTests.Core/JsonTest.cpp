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
		TEST_METHOD(WriterFixedObject)
		{
			// prepare
			MemoryStream Target = MemoryStream();
			StreamWriter Writer = StreamWriter(Target);
			JsonTextWriter JsonWriter = JsonTextWriter(Writer);

			// write
			JsonWriter.WriteStartObject();
			JsonWriter.WritePropertyName(L"Yep");
			JsonWriter.WriteValue(true);
			JsonWriter.WritePropertyName(L"Nope");
			JsonWriter.WriteValue(false);
			JsonWriter.WritePropertyName(L"NullValue");
			JsonWriter.WriteNull();
			JsonWriter.WritePropertyName(L"Int");
			JsonWriter.WriteValue(5448);
			JsonWriter.WritePropertyName(L"Float");
			JsonWriter.WriteValue(13.37f);
			JsonWriter.WritePropertyName(L"Double");
			JsonWriter.WriteValue(13.37);
			JsonWriter.WritePropertyName(L"String");
			JsonWriter.WriteValue(L"SomeValue");
			JsonWriter.WritePropertyName(L"EmptyObject");
			JsonWriter.WriteStartObject();
			JsonWriter.WriteEndObject();
			JsonWriter.WritePropertyName(L"SomeObject");
			JsonWriter.WriteStartObject();
			JsonWriter.WritePropertyName(L"Property1");
			JsonWriter.WriteValue(L"Value1");
			JsonWriter.WritePropertyName(L"Property2");
			JsonWriter.WriteValue(L"Value2");
			JsonWriter.WriteEndObject();
			JsonWriter.WritePropertyName(L"EmptyArray");
			JsonWriter.WriteStartArray();
			JsonWriter.WriteEndArray();
			JsonWriter.WritePropertyName(L"IntArray");
			JsonWriter.WriteStartArray();
			JsonWriter.WriteValue(1);
			JsonWriter.WriteValue(2);
			JsonWriter.WriteValue(3);
			JsonWriter.WriteEndArray();
			JsonWriter.WritePropertyName(L"ObjectArray");
			JsonWriter.WriteStartArray();
			JsonWriter.WriteStartObject();
			JsonWriter.WritePropertyName(L"Value1");
			JsonWriter.WriteValue(5448);
			JsonWriter.WritePropertyName(L"Value2");
			JsonWriter.WriteValue(L"SomeValue");
			JsonWriter.WriteEndObject();
			JsonWriter.WriteStartObject();
			JsonWriter.WritePropertyName(L"Value1");
			JsonWriter.WriteValue(5448);
			JsonWriter.WritePropertyName(L"Value2");
			JsonWriter.WriteValue(L"SomeValue");
			JsonWriter.WriteEndObject();
			JsonWriter.WriteEndArray();
			JsonWriter.WritePropertyName(L"TwoDimensionalArray");
			JsonWriter.WriteStartArray();
			JsonWriter.WriteStartArray();
			JsonWriter.WriteEndArray();
			JsonWriter.WriteStartArray();
			JsonWriter.WriteEndArray();
			JsonWriter.WriteEndArray();
			JsonWriter.WritePropertyName(L"StringWithSpecial\"Characters");
			JsonWriter.WriteValue(L"\"\b\f\r\n\t.\\");
			JsonWriter.WriteEndObject();
			
			// check
		}
		TEST_METHOD(WriterFixedArray)
		{
			// prepare
			MemoryStream Target = MemoryStream();
			StreamWriter Writer = StreamWriter(Target);
			JsonTextWriter JsonWriter = JsonTextWriter(Writer);

			// write
			JsonWriter.WriteStartArray();
			/*
			JsonWriter.WriteValue(1);
			JsonWriter.WriteValue(2);
			JsonWriter.WriteValue(3);
			*/
			JsonWriter.WriteEndArray();

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
