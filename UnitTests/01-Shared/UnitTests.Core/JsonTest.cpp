#include "CppUnitTest.h"

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#include "CppUnitTestFrameworkExtension.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../../../Libraries/01-Shared/Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STRINGWRITER
#include "../../../Libraries/01-Shared/Elysium.Core.IO/StringWriter.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONDOCUMENT
#include "../../../Libraries/01-Shared/Elysium.Core.Json/JsonDocument.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONTEXTWRITER
#include "../../../Libraries/01-Shared/Elysium.Core.Json/JsonTextWriter.hpp"
#endif

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Elysium::Core;
using namespace Elysium::Core::IO;
using namespace Elysium::Core::Json;
using namespace Elysium::Core::Text;

namespace UnitTestsCore
{
	TEST_CLASS(Core_Json)
	{
	public:
		TEST_METHOD(WriterFixedObject)
		{
			// prepare
			StringBuilder Target = StringBuilder();
			StringWriter Writer = StringWriter(Target);
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
			JsonWriter.WritePropertyName(L"StringWithSpecial\"Characters üñîcødé");
			//JsonWriter.WriteValue(L"\"\b\f\r\n\t\\foo\x02\x0F\x1fbar.?äüö");	// c++ interprets \x1fba as a single character so we need to actually use "" as seen in the next line
			JsonWriter.WriteValue(L"\"\b\f\r\n\t\\foo\x02\x0F\x1f""bar.?äüö");
			JsonWriter.WriteEndObject();

			// check
			Assert::AreEqual(L"{\r\n\t\"Yep\": true,\r\n\t\"Nope\": false,\r\n\t\"NullValue\": null,\r\n\t\"Int\": 5448,\r\n\t\"Float\": 13.370000,\r\n\t\"Double\": 13.370000,\r\n\t\"String\": \"SomeValue\",\r\n\t\"EmptyObject\": {},\r\n\t\"SomeObject\": {\r\n\t\t\"Property1\": \"Value1\",\r\n\t\t\"Property2\": \"Value2\"\r\n\t},\r\n\t\"EmptyArray\": [],\r\n\t\"IntArray\": [\r\n\t\t1,\r\n\t\t2,\r\n\t\t3\r\n\t],\r\n\t\"ObjectArray\": [{\r\n\t\t\t\"Value1\": 5448,\r\n\t\t\t\"Value2\": \"SomeValue\"\r\n\t\t}, {\r\n\t\t\t\"Value1\": 5448,\r\n\t\t\t\"Value2\": \"SomeValue\"\r\n\t\t}],\r\n\t\"TwoDimensionalArray\": [[], []],\r\n\t\"StringWithSpecial\\\\\\\"Characters üñîcødé\": \"\\\\\\\"\\\\b\\\\f\\\\r\\\\n\\\\t\\\\\\\\foo\\u0002\\u0015\\u0031bar.?äüö\"\r\n}",
				Target.ToString().GetCharArray());
		}
		TEST_METHOD(WriterFixedArray)
		{
			// prepare
			StringBuilder Target = StringBuilder();
			StringWriter Writer = StringWriter(Target);
			JsonTextWriter JsonWriter = JsonTextWriter(Writer);

			// write
			JsonWriter.WriteStartArray();
			JsonWriter.WriteValue(L"Value1");
			JsonWriter.WriteValue(L"Value2");
			JsonWriter.WriteValue(L"Value3");
			JsonWriter.WriteEndArray();

			// check
			Assert::AreEqual(L"[\r\n\t\"Value1\",\r\n\t\"Value2\",\r\n\t\"Value3\"\r\n]", Target.ToString().GetCharArray());
		}
		TEST_METHOD(WriterFromDocument)
		{
			// prepare
			StringBuilder Target = StringBuilder();
			StringWriter Writer = StringWriter(Target);
			JsonTextWriter JsonWriter = JsonTextWriter(Writer);

			JsonDocument Document = JsonDocument();

			// write
			Document.WriteTo(JsonWriter);

			// check
		}

		TEST_METHOD(ReaderFixedObject)
		{

		}
		TEST_METHOD(ReaderFixedArray)
		{

		}
		TEST_METHOD(ReaderToDocument)
		{

		}
	};
}
