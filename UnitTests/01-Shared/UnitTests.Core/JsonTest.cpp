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

#ifndef ELYSIUM_CORE_IO_STRINGREADER
#include "../../../Libraries/01-Shared/Elysium.Core.IO/StringReader.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONDOCUMENT
#include "../../../Libraries/01-Shared/Elysium.Core.Json/JsonDocument.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONOBJECT
#include "../../../Libraries/01-Shared/Elysium.Core.Json/JsonObject.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONARRAY
#include "../../../Libraries/01-Shared/Elysium.Core.Json/JsonArray.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONELEMENT
#include "../../../Libraries/01-Shared/Elysium.Core.Json/JsonElement.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONTEXTWRITER
#include "../../../Libraries/01-Shared/Elysium.Core.Json/JsonTextWriter.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONTEXTREADER
#include "../../../Libraries/01-Shared/Elysium.Core.Json/JsonTextReader.hpp"
#endif

#ifndef UNITTESTS_CORE_JSON_CHANGINGJSONVISITOR
#include "ChangingJsonVisitor.hpp"
#endif

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Elysium::Core;
using namespace Elysium::Core::IO;
using namespace Elysium::Core::Json;
using namespace Elysium::Core::Text;

namespace UnitTests::Core
{
	TEST_CLASS(JsonTests)
	{
	public:
		TEST_METHOD(WriteObject)
		{
			// prepare
			StringBuilder Target = StringBuilder();
			StringWriter Writer = StringWriter(Target);
			JsonTextWriter JsonWriter = JsonTextWriter(Writer);

			// write
			JsonWriter.WriteStartObject();
			JsonWriter.WritePropertyName(u8"Yep");
			JsonWriter.WriteValue(true);
			JsonWriter.WritePropertyName(u8"Nope");
			JsonWriter.WriteValue(false);
			JsonWriter.WritePropertyName(u8"NullValue");
			JsonWriter.WriteNull();
			JsonWriter.WritePropertyName(u8"Int");
			JsonWriter.WriteValue(-5448);
			JsonWriter.WritePropertyName(u8"Float");
			JsonWriter.WriteValue(13.37f);
			JsonWriter.WritePropertyName(u8"Double");
			JsonWriter.WriteValue(13.37);
			JsonWriter.WritePropertyName(u8"String");
			JsonWriter.WriteValue(u8"SomeValue");
			JsonWriter.WritePropertyName(u8"EmptyObject");
			JsonWriter.WriteStartObject();
			JsonWriter.WriteEndObject();
			JsonWriter.WritePropertyName(u8"SomeObject");
			JsonWriter.WriteStartObject();
			JsonWriter.WritePropertyName(u8"Property1");
			JsonWriter.WriteValue(u8"Value1");
			JsonWriter.WritePropertyName(u8"Property2");
			JsonWriter.WriteValue(u8"Value2");
			JsonWriter.WriteEndObject();
			JsonWriter.WritePropertyName(u8"EmptyArray");
			JsonWriter.WriteStartArray();
			JsonWriter.WriteEndArray();
			JsonWriter.WritePropertyName(u8"IntArray");
			JsonWriter.WriteStartArray();
			JsonWriter.WriteValue(1);
			JsonWriter.WriteValue(2);
			JsonWriter.WriteValue(3);
			JsonWriter.WriteEndArray();
			JsonWriter.WritePropertyName(u8"ObjectArray");
			JsonWriter.WriteStartArray();
			JsonWriter.WriteStartObject();
			JsonWriter.WritePropertyName(u8"Value1");
			JsonWriter.WriteValue(5448);
			JsonWriter.WritePropertyName(u8"Value2");
			JsonWriter.WriteValue(u8"SomeValue");
			JsonWriter.WriteEndObject();
			JsonWriter.WriteStartObject();
			JsonWriter.WritePropertyName(u8"Value1");
			JsonWriter.WriteValue(5448);
			JsonWriter.WritePropertyName(u8"Value2");
			JsonWriter.WriteValue(u8"SomeValue");
			JsonWriter.WriteEndObject();
			JsonWriter.WriteEndArray();
			JsonWriter.WritePropertyName(u8"TwoDimensionalArray");
			JsonWriter.WriteStartArray();
			JsonWriter.WriteStartArray();
			JsonWriter.WriteEndArray();
			JsonWriter.WriteStartArray();
			JsonWriter.WriteEndArray();
			JsonWriter.WriteEndArray();
			JsonWriter.WritePropertyName(u8"StringWithSpecial\"Characters üñîcødé");
			//JsonWriter.WriteValue(u8"\"\b\f\r\n\t\\foo\x02\x0F\x1fbar.?äüö");	// c++ interprets \x1fba as a single character so we need to actually use "" as seen in the next line
			JsonWriter.WriteValue(u8"\"\b\f\r\n\t\\foo\x02\x0F\x1f""bar.?äüö");
			JsonWriter.WriteEndObject();

			// check
			Assert::AreEqual(u8"{\r\n\t\"Yep\": true,\r\n\t\"Nope\": false,\r\n\t\"NullValue\": null,\r\n\t\"Int\": -5448,\r\n\t\"Float\": 13.370000,\r\n\t\"Double\": 13.370000,\r\n\t\"String\": \"SomeValue\",\r\n\t\"EmptyObject\": {},\r\n\t\"SomeObject\": {\r\n\t\t\"Property1\": \"Value1\",\r\n\t\t\"Property2\": \"Value2\"\r\n\t},\r\n\t\"EmptyArray\": [],\r\n\t\"IntArray\": [\r\n\t\t1,\r\n\t\t2,\r\n\t\t3\r\n\t],\r\n\t\"ObjectArray\": [{\r\n\t\t\t\"Value1\": 5448,\r\n\t\t\t\"Value2\": \"SomeValue\"\r\n\t\t}, {\r\n\t\t\t\"Value1\": 5448,\r\n\t\t\t\"Value2\": \"SomeValue\"\r\n\t\t}],\r\n\t\"TwoDimensionalArray\": [[], []],\r\n\t\"StringWithSpecial\\\\\\\"Characters üñîcødé\": \"\\\\\\\"\\\\b\\\\f\\\\r\\\\n\\\\t\\\\\\\\foo\\u0002\\u0015\\u0031bar.?äüö\"\r\n}",
				Target.ToString().GetCharArray());
		}
		TEST_METHOD(WriteArray)
		{
			// prepare
			StringBuilder Target = StringBuilder();
			StringWriter Writer = StringWriter(Target);
			JsonTextWriter JsonWriter = JsonTextWriter(Writer);

			// write
			JsonWriter.WriteStartArray();
			JsonWriter.WriteValue(u8"Value1");
			JsonWriter.WriteValue(u8"Value2");
			JsonWriter.WriteValue(u8"Value3");
			JsonWriter.WriteEndArray();

			// check
			Assert::AreEqual(u8"[\r\n\t\"Value1\",\r\n\t\"Value2\",\r\n\t\"Value3\"\r\n]", Target.ToString().GetCharArray());
		}

		TEST_METHOD(ReadObject)
		{
			// prepare
			String Source = u8"{\r\n\t\"Yep\": true,\r\n\t\"Nope\": false,\r\n\t\"NullValue\": null,\r\n\t\"Int\": -5448,\r\n\t\"Float\": 13.370000,\r\n\t\"Double\": 13.370000,\r\n\t\"String\": \"SomeValue\",\r\n\t\"EmptyObject\": {},\r\n\t\"SomeObject\": {\r\n\t\t\"Property1\": \"Value1\",\r\n\t\t\"Property2\": \"Value2\"\r\n\t},\r\n\t\"EmptyArray\": [],\r\n\t\"IntArray\": [\r\n\t\t1,\r\n\t\t2,\r\n\t\t3\r\n\t],\r\n\t\"ObjectArray\": [{\r\n\t\t\t\"Value1\": 5448,\r\n\t\t\t\"Value2\": \"SomeValue\"\r\n\t\t}, {\r\n\t\t\t\"Value1\": 5448,\r\n\t\t\t\"Value2\": \"SomeValue\"\r\n\t\t}],\r\n\t\"TwoDimensionalArray\": [[], []],\r\n\t\"StringWithSpecial\\\\\\\"Characters üñîcødé\": \"\\\\\\\"\\\\b\\\\f\\\\r\\\\n\\\\t\\\\\\\\foo\\u0002\\u0015\\u0031bar.?äüö\"\r\n}";
			StringReader Reader = StringReader(Source);
			JsonTextReader JsonReader = JsonTextReader(Reader);
			
			// read & check
			Assert::AreEqual((uint32_t)JsonToken::None, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::StartedObject, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"Yep", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::Boolean, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"true", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"Nope", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::Boolean, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"false", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"NullValue", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::Null, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"null", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"Int", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::Integer, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"-5448", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"Float", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::Float, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"13.370000", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"Double", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::Float, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"13.370000", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"String", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::String, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"SomeValue", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"EmptyObject", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::StartedObject, (uint32_t)JsonReader.GetToken());
			//AssertExtended::AreEqual("SomeValue", JsonReader.GetNodeValue().GetCharArray());	// ToDo: reset _CurrentNodeValue

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::EndedObject, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"SomeObject", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::StartedObject, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"Property1", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::String, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"Value1", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"Property2", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::String, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"Value2", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::EndedObject, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"EmptyArray", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::StartedArray, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::EndedArray, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"IntArray", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::StartedArray, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::Integer, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"1", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::Integer, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"2", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::Integer, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"3", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::EndedArray, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"ObjectArray", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::StartedArray, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::StartedObject, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"Value1", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::Integer, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"5448", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"Value2", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::String, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"SomeValue", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::EndedObject, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::StartedObject, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"Value1", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::Integer, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"5448", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"Value2", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::String, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"SomeValue", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::EndedObject, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::EndedArray, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"TwoDimensionalArray", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::StartedArray, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::StartedArray, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::EndedArray, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::StartedArray, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::EndedArray, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::EndedArray, (uint32_t)JsonReader.GetToken());
			
			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"StringWithSpecial\\\\\\\"Characters üñîcødé", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::String, (uint32_t)JsonReader.GetToken());
			Assert::AreEqual(u8"\\\\\\\"\\\\b\\\\f\\\\r\\\\n\\\\t\\\\\\\\foo\\u0002\\u0015\\u0031bar.?äüö", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::EndedObject, (uint32_t)JsonReader.GetToken());

			Assert::IsFalse(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::None, (uint32_t)JsonReader.GetToken());
		}
		TEST_METHOD(ReadArray)
		{
			// test: string array
			{
				// prepare
				String Source = u8"[\r\n\t\"Value1\",\r\n\t\"Value2\",\r\n\t\"Value3\"\r\n]";
				StringReader Reader = StringReader(Source);
				JsonTextReader JsonReader = JsonTextReader(Reader);

				// read & check
				Assert::AreEqual((uint32_t)JsonToken::None, (uint32_t)JsonReader.GetToken());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::StartedArray, (uint32_t)JsonReader.GetToken());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::String, (uint32_t)JsonReader.GetToken());
				Assert::AreEqual(u8"Value1", JsonReader.GetNodeValue().GetCharArray());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::String, (uint32_t)JsonReader.GetToken());
				Assert::AreEqual(u8"Value2", JsonReader.GetNodeValue().GetCharArray());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::String, (uint32_t)JsonReader.GetToken());
				Assert::AreEqual(u8"Value3", JsonReader.GetNodeValue().GetCharArray());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::EndedArray, (uint32_t)JsonReader.GetToken());

				Assert::IsFalse(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::None, (uint32_t)JsonReader.GetToken());
			}

			// test: int array
			{
				// prepare
				String Source = u8"[\r\n\t12,\r\n\t2,\r\n\t3453\r\n]";
				StringReader Reader = StringReader(Source);
				JsonTextReader JsonReader = JsonTextReader(Reader);

				// read & check
				Assert::AreEqual((uint32_t)JsonToken::None, (uint32_t)JsonReader.GetToken());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::StartedArray, (uint32_t)JsonReader.GetToken());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::Integer, (uint32_t)JsonReader.GetToken());
				Assert::AreEqual(u8"12", JsonReader.GetNodeValue().GetCharArray());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::Integer, (uint32_t)JsonReader.GetToken());
				Assert::AreEqual(u8"2", JsonReader.GetNodeValue().GetCharArray());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::Integer, (uint32_t)JsonReader.GetToken());
				Assert::AreEqual(u8"3453", JsonReader.GetNodeValue().GetCharArray());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::EndedArray, (uint32_t)JsonReader.GetToken());

				Assert::IsFalse(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::None, (uint32_t)JsonReader.GetToken());
			}

			// test: float array
			{
				// prepare
				String Source = u8"[\r\n\t1.2,\r\n\t2.3,\r\n\t3453.0\r\n]";
				StringReader Reader = StringReader(Source);
				JsonTextReader JsonReader = JsonTextReader(Reader);
				
				// read & check
				Assert::AreEqual((uint32_t)JsonToken::None, (uint32_t)JsonReader.GetToken());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::StartedArray, (uint32_t)JsonReader.GetToken());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::Float, (uint32_t)JsonReader.GetToken());
				Assert::AreEqual(u8"1.2", JsonReader.GetNodeValue().GetCharArray());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::Float, (uint32_t)JsonReader.GetToken());
				Assert::AreEqual(u8"2.3", JsonReader.GetNodeValue().GetCharArray());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::Float, (uint32_t)JsonReader.GetToken());
				Assert::AreEqual(u8"3453.0", JsonReader.GetNodeValue().GetCharArray());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::EndedArray, (uint32_t)JsonReader.GetToken());

				Assert::IsFalse(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::None, (uint32_t)JsonReader.GetToken());
			}

			// test: bool array
			{
				// prepare
				String Source = u8"[\r\n\tfalse,\r\n\ttrue,\r\n\tnull\r\n]";
				StringReader Reader = StringReader(Source);
				JsonTextReader JsonReader = JsonTextReader(Reader);

				// read & check
				Assert::AreEqual((uint32_t)JsonToken::None, (uint32_t)JsonReader.GetToken());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::StartedArray, (uint32_t)JsonReader.GetToken());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::Boolean, (uint32_t)JsonReader.GetToken());
				Assert::AreEqual(u8"false", JsonReader.GetNodeValue().GetCharArray());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::Boolean, (uint32_t)JsonReader.GetToken());
				Assert::AreEqual(u8"true", JsonReader.GetNodeValue().GetCharArray());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::Null, (uint32_t)JsonReader.GetToken());
				Assert::AreEqual(u8"null", JsonReader.GetNodeValue().GetCharArray());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::EndedArray, (uint32_t)JsonReader.GetToken());

				Assert::IsFalse(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::None, (uint32_t)JsonReader.GetToken());
			}

			// test: empty array
			{
				// prepare
				String Source = u8"[]";
				//String Source = u8"[ ]";
				StringReader Reader = StringReader(Source);
				JsonTextReader JsonReader = JsonTextReader(Reader);

				// read & check
				Assert::AreEqual((uint32_t)JsonToken::None, (uint32_t)JsonReader.GetToken());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::StartedArray, (uint32_t)JsonReader.GetToken());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::EndedArray, (uint32_t)JsonReader.GetToken());

				Assert::IsFalse(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::None, (uint32_t)JsonReader.GetToken());
			}
		}

		TEST_METHOD(DocumentToWriter)
		{
			// test 1
			{
				// prepare
				StringBuilder Target = StringBuilder();
				StringWriter Writer = StringWriter(Target);
				JsonTextWriter JsonWriter = JsonTextWriter(Writer);

				JsonDocument Document = JsonDocument();
				JsonObject& Root = Document.AddRootObject();
				Root.AddElement(u8"Yep", true);
				Root.AddElement(u8"Nope", false);
				Root.AddElement(u8"NullValue");
				Root.AddElement(u8"Int", -5448);
				Root.AddElement(u8"Float", 13.370000f);
				Root.AddElement(u8"Double", 13.370000);
				Root.AddElement(u8"String", Elysium::Core::String(u8"SomeValue"));
				Root.AddObject(u8"EmptyObject");
				JsonObject& SomeObject = Root.AddObject(u8"SomeObject");
				SomeObject.AddElement(u8"Property1", Elysium::Core::String(u8"Value1"));
				SomeObject.AddElement(u8"Property2", Elysium::Core::String(u8"Value2"));
				Root.AddArray(u8"EmptyArray");
				JsonArray& IntArray = Root.AddArray(u8"IntArray");
				IntArray.AddElement(1);
				IntArray.AddElement(2);
				IntArray.AddElement(3);
				JsonArray& ObjectArray = Root.AddArray(u8"ObjectArray");
				JsonObject& ObjectArrayObject1 = ObjectArray.AddObject();
				ObjectArrayObject1.AddElement(u8"Value1", 5448);
				ObjectArrayObject1.AddElement(u8"Value2", Elysium::Core::String(u8"SomeValue"));
				JsonObject& ObjectArrayObject2 = ObjectArray.AddObject();
				ObjectArrayObject2.AddElement(u8"Value1", 5448);
				ObjectArrayObject2.AddElement(u8"Value2", Elysium::Core::String(u8"SomeValue"));
				JsonArray& TwoDimensionalArray = Root.AddArray(u8"TwoDimensionalArray");
				TwoDimensionalArray.AddArray();
				TwoDimensionalArray.AddArray();
				Root.AddElement(u8"StringWithSpecial\"Characters üñîcødé", Elysium::Core::String(u8"\"\b\f\r\n\t\\foo\x02\x0F\x1f""bar.?äüö"));
				
				// write
				Document.WriteTo(JsonWriter);

				// check
				Assert::AreEqual(u8"{\r\n\t\"Yep\": true,\r\n\t\"Nope\": false,\r\n\t\"NullValue\": null,\r\n\t\"Int\": -5448,\r\n\t\"Float\": 13.370000,\r\n\t\"Double\": 13.370000,\r\n\t\"String\": \"SomeValue\",\r\n\t\"EmptyObject\": {},\r\n\t\"SomeObject\": {\r\n\t\t\"Property1\": \"Value1\",\r\n\t\t\"Property2\": \"Value2\"\r\n\t},\r\n\t\"EmptyArray\": [],\r\n\t\"IntArray\": [\r\n\t\t1,\r\n\t\t2,\r\n\t\t3\r\n\t],\r\n\t\"ObjectArray\": [{\r\n\t\t\t\"Value1\": 5448,\r\n\t\t\t\"Value2\": \"SomeValue\"\r\n\t\t}, {\r\n\t\t\t\"Value1\": 5448,\r\n\t\t\t\"Value2\": \"SomeValue\"\r\n\t\t}],\r\n\t\"TwoDimensionalArray\": [[], []],\r\n\t\"StringWithSpecial\\\\\\\"Characters üñîcødé\": \"\\\\\\\"\\\\b\\\\f\\\\r\\\\n\\\\t\\\\\\\\foo\\u0002\\u0015\\u0031bar.?äüö\"\r\n}",
					Target.ToString().GetCharArray());
			}

			// test 2
			{
				// prepare
				StringBuilder Target = StringBuilder();
				StringWriter Writer = StringWriter(Target);
				JsonTextWriter JsonWriter = JsonTextWriter(Writer);

				JsonDocument Document = JsonDocument();
				JsonArray& Root = Document.AddRootArray();
				Root.AddElement(Elysium::Core::String(u8"Value1"));
				Root.AddElement(Elysium::Core::String(u8"Value2"));
				Root.AddElement(Elysium::Core::String(u8"Value3"));

				// write
				Document.WriteTo(JsonWriter);

				// check
				Assert::AreEqual(u8"[\r\n\t\"Value1\",\r\n\t\"Value2\",\r\n\t\"Value3\"\r\n]", Target.ToString().GetCharArray());
			}
		}
		TEST_METHOD(DocumentFromReader)
		{
			// test 1: object
			{
				// prepare
				String Source = u8"{\r\n\t\"Yep\": true,\r\n\t\"Nope\": false,\r\n\t\"NullValue\": null,\r\n\t\"Int\": -5448,\r\n\t\"Float\": 13.370000,\r\n\t\"String\": \"SomeValue\",\r\n\t\"EmptyObject\": {},\r\n\t\"SomeObject\": {\r\n\t\t\"Property1\": \"Value1\",\r\n\t\t\"Property2\": \"Value2\"\r\n\t},\r\n\t\"EmptyArray\": [],\r\n\t\"IntArray\": [\r\n\t\t1,\r\n\t\t2,\r\n\t\t3\r\n\t],\r\n\t\"ObjectArray\": [{\r\n\t\t\t\"Value1\": 5448,\r\n\t\t\t\"Value2\": \"SomeValue\"\r\n\t\t}, {\r\n\t\t\t\"Value1\": 5448,\r\n\t\t\t\"Value2\": \"SomeValue\"\r\n\t\t}],\r\n\t\"TwoDimensionalArray\": [[], []],\r\n\t\"StringWithSpecial\\\\\\\"Characters üñîcødé\": \"\\\\\\\"\\\\b\\\\f\\\\r\\\\n\\\\t\\\\\\\\foo\\u0002\\u0015\\u0031bar.?äüö\"\r\n}";
				JsonDocument Document = JsonDocument();
				Document.LoadJson(Source);
				
				// read & check
				JsonObject& RootNode = static_cast<JsonObject&>(Document.GetRootNode());
				Assert::AreEqual((uint32_t)JsonNodeType::Object, (uint32_t)RootNode.GetNodeType());

				JsonElement& Yep = static_cast<JsonElement&>(RootNode.GetChild(0));
				Assert::AreEqual(u8"Yep", Yep.GetName().GetCharArray());
				Assert::AreEqual(true, Yep.GetValueAsBoolean());

				JsonElement& Nope = static_cast<JsonElement&>(RootNode.GetChild(1));
				Assert::AreEqual(u8"Nope", Nope.GetName().GetCharArray());
				Assert::AreEqual(false, Nope.GetValueAsBoolean());

				JsonElement& NullValue = static_cast<JsonElement&>(RootNode.GetChild(2));
				Assert::AreEqual(u8"NullValue", NullValue.GetName().GetCharArray());
				Assert::IsTrue(NullValue.IsNull());

				JsonElement& Int = static_cast<JsonElement&>(RootNode.GetChild(3));
				Assert::AreEqual(u8"Int", Int.GetName().GetCharArray());
				Assert::AreEqual(-5448, Int.GetValueAsInt32());

				JsonElement& Float = static_cast<JsonElement&>(RootNode.GetChild(4));
				Assert::AreEqual(u8"Float", Float.GetName().GetCharArray());
				Assert::AreEqual(13.370000f, Float.GetValueAsSingle());

				JsonElement& String = static_cast<JsonElement&>(RootNode.GetChild(5));
				Assert::AreEqual(u8"String", String.GetName().GetCharArray());
				Assert::AreEqual(u8"SomeValue", String.GetValueAsString().GetCharArray());

				JsonObject& EmptyObject = static_cast<JsonObject&>(RootNode.GetChild(6));
				Assert::AreEqual((uint32_t)JsonNodeType::Object, (uint32_t)EmptyObject.GetNodeType());
				Assert::AreEqual(u8"EmptyObject", EmptyObject.GetName().GetCharArray());

				JsonObject& SomeObject = static_cast<JsonObject&>(RootNode.GetChild(7));
				Assert::AreEqual((uint32_t)JsonNodeType::Object, (uint32_t)SomeObject.GetNodeType());
				Assert::AreEqual(u8"SomeObject", SomeObject.GetName().GetCharArray());

				JsonElement& SomeObjectProperty1 = static_cast<JsonElement&>(SomeObject.GetChild(0));
				Assert::AreEqual(u8"Property1", SomeObjectProperty1.GetName().GetCharArray());
				Assert::AreEqual(u8"Value1", SomeObjectProperty1.GetValueAsString().GetCharArray());

				JsonElement& SomeObjectProperty2 = static_cast<JsonElement&>(SomeObject.GetChild(1));
				Assert::AreEqual(u8"Property2", SomeObjectProperty2.GetName().GetCharArray());
				Assert::AreEqual(u8"Value2", SomeObjectProperty2.GetValueAsString().GetCharArray());
				
				JsonArray& EmptyArray = static_cast<JsonArray&>(RootNode.GetChild(8));
				Assert::AreEqual((uint32_t)JsonNodeType::Array, (uint32_t)EmptyArray.GetNodeType());
				
				JsonArray& IntArray = static_cast<JsonArray&>(RootNode.GetChild(9));
				Assert::AreEqual((uint32_t)JsonNodeType::Array, (uint32_t)IntArray.GetNodeType());

				JsonElement& IntArrayValue1 = static_cast<JsonElement&>(IntArray.GetChild(0));
				Assert::IsNull(IntArrayValue1.GetName().GetCharArray());
				Assert::AreEqual(1, IntArrayValue1.GetValueAsInt32());

				JsonElement& IntArrayValue2 = static_cast<JsonElement&>(IntArray.GetChild(1));
				Assert::IsNull(IntArrayValue2.GetName().GetCharArray());
				Assert::AreEqual(2, IntArrayValue2.GetValueAsInt32());

				JsonElement& IntArrayValue3 = static_cast<JsonElement&>(IntArray.GetChild(2));
				Assert::IsNull(IntArrayValue3.GetName().GetCharArray());
				Assert::AreEqual(3, IntArrayValue3.GetValueAsInt32());

				JsonArray& ObjectArray = static_cast<JsonArray&>(RootNode.GetChild(10));
				Assert::AreEqual((uint32_t)JsonNodeType::Array, (uint32_t)ObjectArray.GetNodeType());

				JsonObject& ObjectArrayObject1 = static_cast<JsonObject&>(ObjectArray.GetChild(0));
				Assert::AreEqual((uint32_t)JsonNodeType::Object, (uint32_t)ObjectArrayObject1.GetNodeType());

				JsonElement& ObjectArrayObject1Value1 = static_cast<JsonElement&>(ObjectArrayObject1.GetChild(0));
				Assert::AreEqual(u8"Value1", ObjectArrayObject1Value1.GetName().GetCharArray());
				Assert::AreEqual(5448, ObjectArrayObject1Value1.GetValueAsInt32());

				JsonElement& ObjectArrayObject1Value2 = static_cast<JsonElement&>(ObjectArrayObject1.GetChild(1));
				Assert::AreEqual(u8"Value2", ObjectArrayObject1Value2.GetName().GetCharArray());
				Assert::AreEqual(u8"SomeValue", ObjectArrayObject1Value2.GetValueAsString().GetCharArray());

				JsonObject& ObjectArrayObject2 = static_cast<JsonObject&>(ObjectArray.GetChild(1));
				Assert::AreEqual((uint32_t)JsonNodeType::Object, (uint32_t)ObjectArrayObject2.GetNodeType());

				JsonElement& ObjectArrayObject2Value1 = static_cast<JsonElement&>(ObjectArrayObject2.GetChild(0));
				Assert::AreEqual(u8"Value1", ObjectArrayObject2Value1.GetName().GetCharArray());
				Assert::AreEqual(5448, ObjectArrayObject2Value1.GetValueAsInt32());

				JsonElement& ObjectArrayObject2Value2 = static_cast<JsonElement&>(ObjectArrayObject2.GetChild(1));
				Assert::AreEqual(u8"Value2", ObjectArrayObject2Value2.GetName().GetCharArray());
				Assert::AreEqual(u8"SomeValue", ObjectArrayObject2Value2.GetValueAsString().GetCharArray());

				JsonArray& TwoDimensionalArray = static_cast<JsonArray&>(RootNode.GetChild(11));
				Assert::AreEqual((uint32_t)JsonNodeType::Array, (uint32_t)TwoDimensionalArray.GetNodeType());

				JsonArray& TwoDimensionalArrayArray1 = static_cast<JsonArray&>(TwoDimensionalArray.GetChild(0));
				Assert::AreEqual((uint32_t)JsonNodeType::Array, (uint32_t)TwoDimensionalArrayArray1.GetNodeType());

				JsonArray& TwoDimensionalArrayArray2 = static_cast<JsonArray&>(TwoDimensionalArray.GetChild(1));
				Assert::AreEqual((uint32_t)JsonNodeType::Array, (uint32_t)TwoDimensionalArrayArray2.GetNodeType());

				JsonElement& StringWithSpecialCharacters = static_cast<JsonElement&>(RootNode.GetChild(12));
				Assert::AreEqual(u8"StringWithSpecial\\\\\\\"Characters üñîcødé", StringWithSpecialCharacters.GetName().GetCharArray());
				Assert::AreEqual(u8"\\\\\\\"\\\\b\\\\f\\\\r\\\\n\\\\t\\\\\\\\foo\\u0002\\u0015\\u0031bar.?äüö", StringWithSpecialCharacters.GetValueAsString().GetCharArray());
			}

			// test 2: string array
			{
				// prepare
				String Source = u8"[\r\n\t\"Value1\",\r\n\t\"Value2\",\r\n\t\"Value3\"\r\n]";
				JsonDocument Document = JsonDocument();
				Document.LoadJson(Source);

				// read & check
				JsonArray& RootNode = static_cast<JsonArray&>(Document.GetRootNode());
				Assert::AreEqual((uint32_t)JsonNodeType::Array, (uint32_t)RootNode.GetNodeType());

				JsonElement& Element1 = static_cast<JsonElement&>(RootNode.GetChild(0));
				Assert::AreEqual(u8"Value1", Element1.GetValueAsString().GetCharArray());

				JsonElement& Element2 = static_cast<JsonElement&>(RootNode.GetChild(1));
				Assert::AreEqual(u8"Value2", Element2.GetValueAsString().GetCharArray());

				JsonElement& Element3 = static_cast<JsonElement&>(RootNode.GetChild(2));
				Assert::AreEqual(u8"Value3", Element3.GetValueAsString().GetCharArray());
			}

			// test 3: numeric array
			{
				// prepare
				String Source = u8"[\r\n\t1.2,\r\n\t2.3,\r\n\t3453.0\r\n]";
				JsonDocument Document = JsonDocument();
				Document.LoadJson(Source);

				// read & check
				JsonArray& RootNode = static_cast<JsonArray&>(Document.GetRootNode());
				Assert::AreEqual((uint32_t)JsonNodeType::Array, (uint32_t)RootNode.GetNodeType());

				JsonElement& Element1 = static_cast<JsonElement&>(RootNode.GetChild(0));
				Assert::AreEqual(1.2f, Element1.GetValueAsSingle());

				JsonElement& Element2 = static_cast<JsonElement&>(RootNode.GetChild(1));
				Assert::AreEqual(2.3f, Element2.GetValueAsSingle());

				JsonElement& Element3 = static_cast<JsonElement&>(RootNode.GetChild(2));
				Assert::AreEqual(3453.0f, Element3.GetValueAsSingle());
			}
			
			// test 4: bool array
			{
				// prepare
				String Source = u8"[\r\n\tfalse,\r\n\ttrue,\r\n\tnull\r\n]";
				JsonDocument Document = JsonDocument();
				Document.LoadJson(Source);

				// read & check
				JsonArray& RootNode = static_cast<JsonArray&>(Document.GetRootNode());
				Assert::AreEqual((uint32_t)JsonNodeType::Array, (uint32_t)RootNode.GetNodeType());

				JsonElement& Element1 = static_cast<JsonElement&>(RootNode.GetChild(0));
				Assert::AreEqual(false, Element1.GetValueAsBoolean());

				JsonElement& Element2 = static_cast<JsonElement&>(RootNode.GetChild(1));
				Assert::AreEqual(true, Element2.GetValueAsBoolean());

				JsonElement& Element3 = static_cast<JsonElement&>(RootNode.GetChild(2));
				Assert::IsTrue(Element3.IsNull());
			}
			
			// test 5: empty array
			{
				// prepare
				String Source = u8"[]";
				JsonDocument Document = JsonDocument();
				Document.LoadJson(Source);

				// read & check
				JsonArray& RootNode = static_cast<JsonArray&>(Document.GetRootNode());
				Assert::AreEqual((uint32_t)JsonNodeType::Array, (uint32_t)RootNode.GetNodeType());
			}
		}

		TEST_METHOD(Visitor)
		{
			// prepare
			String Source = u8"{\r\n\t\"Yep\": true,\r\n\t\"Nope\": false,\r\n\t\"NullValue\": null,\r\n\t\"Int\": -5448,\r\n\t\"Float\": 13.370000,\r\n\t\"String\": \"SomeValue\",\r\n\t\"EmptyObject\": {},\r\n\t\"SomeObject\": {\r\n\t\t\"Property1\": \"Value1\",\r\n\t\t\"Property2\": \"Value2\"\r\n\t},\r\n\t\"EmptyArray\": [],\r\n\t\"IntArray\": [\r\n\t\t1,\r\n\t\t2,\r\n\t\t3\r\n\t],\r\n\t\"ObjectArray\": [{\r\n\t\t\t\"Value1\": 5448,\r\n\t\t\t\"Value2\": \"SomeValue\"\r\n\t\t}, {\r\n\t\t\t\"Value1\": 5448,\r\n\t\t\t\"Value2\": \"SomeValue\"\r\n\t\t}],\r\n\t\"TwoDimensionalArray\": [[], []],\r\n\t\"StringWithSpecial\\\\\\\"Characters üñîcødé\": \"\\\\\\\"\\\\b\\\\f\\\\r\\\\n\\\\t\\\\\\\\foo\\u0002\\u0015\\u0031bar.?äüö\"\r\n}";
			JsonDocument Document = JsonDocument();
			Document.LoadJson(Source);

			UnitTests::Core::Json::ChangingJsonVisitor Visitor = UnitTests::Core::Json::ChangingJsonVisitor();
			Visitor.Visit(static_cast<JsonNode&>(Document));

			// read & check
			JsonObject& RootNode = static_cast<JsonObject&>(Document.GetRootNode());
			Assert::AreEqual((uint32_t)JsonNodeType::Object, (uint32_t)RootNode.GetNodeType());

			JsonElement& Yep = static_cast<JsonElement&>(RootNode.GetChild(0));
			Assert::AreEqual(u8"Yep", Yep.GetName().GetCharArray());
			Assert::AreEqual(false, Yep.GetValueAsBoolean());

			JsonElement& Nope = static_cast<JsonElement&>(RootNode.GetChild(1));
			Assert::AreEqual(u8"Nope", Nope.GetName().GetCharArray());
			Assert::AreEqual(true, Nope.GetValueAsBoolean());

			JsonElement& NullValue = static_cast<JsonElement&>(RootNode.GetChild(2));
			Assert::AreEqual(u8"NullValue", NullValue.GetName().GetCharArray());
			Assert::IsTrue(NullValue.IsNull());

			JsonElement& Int = static_cast<JsonElement&>(RootNode.GetChild(3));
			Assert::AreEqual(u8"Int", Int.GetName().GetCharArray());
			Assert::AreEqual(5448, Int.GetValueAsInt32());

			JsonElement& Float = static_cast<JsonElement&>(RootNode.GetChild(4));
			Assert::AreEqual(u8"Float", Float.GetName().GetCharArray());
			Assert::AreEqual(-13.370000f, Float.GetValueAsSingle());

			JsonElement& String = static_cast<JsonElement&>(RootNode.GetChild(5));
			Assert::AreEqual(u8"String", String.GetName().GetCharArray());
			Assert::AreEqual(u8"SomeValue", String.GetValueAsString().GetCharArray());

			JsonObject& EmptyObject = static_cast<JsonObject&>(RootNode.GetChild(6));
			Assert::AreEqual((uint32_t)JsonNodeType::Object, (uint32_t)EmptyObject.GetNodeType());
			Assert::AreEqual(u8"EmptyObject", EmptyObject.GetName().GetCharArray());

			JsonObject& SomeObject = static_cast<JsonObject&>(RootNode.GetChild(7));
			Assert::AreEqual((uint32_t)JsonNodeType::Object, (uint32_t)SomeObject.GetNodeType());
			Assert::AreEqual(u8"SomeObject", SomeObject.GetName().GetCharArray());

			JsonElement& SomeObjectProperty1 = static_cast<JsonElement&>(SomeObject.GetChild(0));
			Assert::AreEqual(u8"Property1", SomeObjectProperty1.GetName().GetCharArray());
			Assert::AreEqual(u8"Value1", SomeObjectProperty1.GetValueAsString().GetCharArray());

			JsonElement& SomeObjectProperty2 = static_cast<JsonElement&>(SomeObject.GetChild(1));
			Assert::AreEqual(u8"Property2", SomeObjectProperty2.GetName().GetCharArray());
			Assert::AreEqual(u8"Value2", SomeObjectProperty2.GetValueAsString().GetCharArray());

			JsonArray& EmptyArray = static_cast<JsonArray&>(RootNode.GetChild(8));
			Assert::AreEqual((uint32_t)JsonNodeType::Array, (uint32_t)EmptyArray.GetNodeType());

			JsonArray& IntArray = static_cast<JsonArray&>(RootNode.GetChild(9));
			Assert::AreEqual((uint32_t)JsonNodeType::Array, (uint32_t)IntArray.GetNodeType());

			JsonElement& IntArrayValue1 = static_cast<JsonElement&>(IntArray.GetChild(0));
			Assert::IsNull(IntArrayValue1.GetName().GetCharArray());
			Assert::AreEqual(-1, IntArrayValue1.GetValueAsInt32());

			JsonElement& IntArrayValue2 = static_cast<JsonElement&>(IntArray.GetChild(1));
			Assert::IsNull(IntArrayValue2.GetName().GetCharArray());
			Assert::AreEqual(-2, IntArrayValue2.GetValueAsInt32());

			JsonElement& IntArrayValue3 = static_cast<JsonElement&>(IntArray.GetChild(2));
			Assert::IsNull(IntArrayValue3.GetName().GetCharArray());
			Assert::AreEqual(-3, IntArrayValue3.GetValueAsInt32());

			JsonArray& ObjectArray = static_cast<JsonArray&>(RootNode.GetChild(10));
			Assert::AreEqual((uint32_t)JsonNodeType::Array, (uint32_t)ObjectArray.GetNodeType());

			JsonObject& ObjectArrayObject1 = static_cast<JsonObject&>(ObjectArray.GetChild(0));
			Assert::AreEqual((uint32_t)JsonNodeType::Object, (uint32_t)ObjectArrayObject1.GetNodeType());

			JsonElement& ObjectArrayObject1Value1 = static_cast<JsonElement&>(ObjectArrayObject1.GetChild(0));
			Assert::AreEqual(u8"Value1", ObjectArrayObject1Value1.GetName().GetCharArray());
			Assert::AreEqual(-5448, ObjectArrayObject1Value1.GetValueAsInt32());

			JsonElement& ObjectArrayObject1Value2 = static_cast<JsonElement&>(ObjectArrayObject1.GetChild(1));
			Assert::AreEqual(u8"Value2", ObjectArrayObject1Value2.GetName().GetCharArray());
			Assert::AreEqual(u8"SomeValue", ObjectArrayObject1Value2.GetValueAsString().GetCharArray());

			JsonObject& ObjectArrayObject2 = static_cast<JsonObject&>(ObjectArray.GetChild(1));
			Assert::AreEqual((uint32_t)JsonNodeType::Object, (uint32_t)ObjectArrayObject2.GetNodeType());

			JsonElement& ObjectArrayObject2Value1 = static_cast<JsonElement&>(ObjectArrayObject2.GetChild(0));
			Assert::AreEqual(u8"Value1", ObjectArrayObject2Value1.GetName().GetCharArray());
			Assert::AreEqual(-5448, ObjectArrayObject2Value1.GetValueAsInt32());

			JsonElement& ObjectArrayObject2Value2 = static_cast<JsonElement&>(ObjectArrayObject2.GetChild(1));
			Assert::AreEqual(u8"Value2", ObjectArrayObject2Value2.GetName().GetCharArray());
			Assert::AreEqual(u8"SomeValue", ObjectArrayObject2Value2.GetValueAsString().GetCharArray());

			JsonArray& TwoDimensionalArray = static_cast<JsonArray&>(RootNode.GetChild(11));
			Assert::AreEqual((uint32_t)JsonNodeType::Array, (uint32_t)TwoDimensionalArray.GetNodeType());

			JsonArray& TwoDimensionalArrayArray1 = static_cast<JsonArray&>(TwoDimensionalArray.GetChild(0));
			Assert::AreEqual((uint32_t)JsonNodeType::Array, (uint32_t)TwoDimensionalArrayArray1.GetNodeType());

			JsonArray& TwoDimensionalArrayArray2 = static_cast<JsonArray&>(TwoDimensionalArray.GetChild(1));
			Assert::AreEqual((uint32_t)JsonNodeType::Array, (uint32_t)TwoDimensionalArrayArray2.GetNodeType());

			JsonElement& StringWithSpecialCharacters = static_cast<JsonElement&>(RootNode.GetChild(12));
			Assert::AreEqual(u8"StringWithSpecial\\\\\\\"Characters üñîcødé", StringWithSpecialCharacters.GetName().GetCharArray());
			Assert::AreEqual(u8"\\\\\\\"\\\\b\\\\f\\\\r\\\\n\\\\t\\\\\\\\foo\\u0002\\u0015\\u0031bar.?äüö", StringWithSpecialCharacters.GetValueAsString().GetCharArray());
		}
	};
}
