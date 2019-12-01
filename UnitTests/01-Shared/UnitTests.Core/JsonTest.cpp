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
		TEST_METHOD(WriteObject)
		{
			// prepare
			StringBuilder Target = StringBuilder();
			StringWriter Writer = StringWriter(Target);
			JsonTextWriter JsonWriter = JsonTextWriter(Writer);

			// write
			JsonWriter.WriteStartObject();
			JsonWriter.WritePropertyName(u"Yep");
			JsonWriter.WriteValue(true);
			JsonWriter.WritePropertyName(u"Nope");
			JsonWriter.WriteValue(false);
			JsonWriter.WritePropertyName(u"NullValue");
			JsonWriter.WriteNull();
			JsonWriter.WritePropertyName(u"Int");
			JsonWriter.WriteValue(-5448);
			JsonWriter.WritePropertyName(u"Float");
			JsonWriter.WriteValue(13.37f);
			JsonWriter.WritePropertyName(u"Double");
			JsonWriter.WriteValue(13.37);
			JsonWriter.WritePropertyName(u"String");
			JsonWriter.WriteValue(u"SomeValue");
			JsonWriter.WritePropertyName(u"EmptyObject");
			JsonWriter.WriteStartObject();
			JsonWriter.WriteEndObject();
			JsonWriter.WritePropertyName(u"SomeObject");
			JsonWriter.WriteStartObject();
			JsonWriter.WritePropertyName(u"Property1");
			JsonWriter.WriteValue(u"Value1");
			JsonWriter.WritePropertyName(u"Property2");
			JsonWriter.WriteValue(u"Value2");
			JsonWriter.WriteEndObject();
			JsonWriter.WritePropertyName(u"EmptyArray");
			JsonWriter.WriteStartArray();
			JsonWriter.WriteEndArray();
			JsonWriter.WritePropertyName(u"IntArray");
			JsonWriter.WriteStartArray();
			JsonWriter.WriteValue(1);
			JsonWriter.WriteValue(2);
			JsonWriter.WriteValue(3);
			JsonWriter.WriteEndArray();
			JsonWriter.WritePropertyName(u"ObjectArray");
			JsonWriter.WriteStartArray();
			JsonWriter.WriteStartObject();
			JsonWriter.WritePropertyName(u"Value1");
			JsonWriter.WriteValue(5448);
			JsonWriter.WritePropertyName(u"Value2");
			JsonWriter.WriteValue(u"SomeValue");
			JsonWriter.WriteEndObject();
			JsonWriter.WriteStartObject();
			JsonWriter.WritePropertyName(u"Value1");
			JsonWriter.WriteValue(5448);
			JsonWriter.WritePropertyName(u"Value2");
			JsonWriter.WriteValue(u"SomeValue");
			JsonWriter.WriteEndObject();
			JsonWriter.WriteEndArray();
			JsonWriter.WritePropertyName(u"TwoDimensionalArray");
			JsonWriter.WriteStartArray();
			JsonWriter.WriteStartArray();
			JsonWriter.WriteEndArray();
			JsonWriter.WriteStartArray();
			JsonWriter.WriteEndArray();
			JsonWriter.WriteEndArray();
			JsonWriter.WritePropertyName(u"StringWithSpecial\"Characters üñîcødé");
			//JsonWriter.WriteValue(u"\"\b\f\r\n\t\\foo\x02\x0F\x1fbar.?äüö");	// c++ interprets \x1fba as a single character so we need to actually use "" as seen in the next line
			JsonWriter.WriteValue(u"\"\b\f\r\n\t\\foo\x02\x0F\x1f""bar.?äüö");
			JsonWriter.WriteEndObject();

			// check
			AssertExtended::AreEqual(u"{\r\n\t\"Yep\": true,\r\n\t\"Nope\": false,\r\n\t\"NullValue\": null,\r\n\t\"Int\": -5448,\r\n\t\"Float\": 13.370000,\r\n\t\"Double\": 13.370000,\r\n\t\"String\": \"SomeValue\",\r\n\t\"EmptyObject\": {},\r\n\t\"SomeObject\": {\r\n\t\t\"Property1\": \"Value1\",\r\n\t\t\"Property2\": \"Value2\"\r\n\t},\r\n\t\"EmptyArray\": [],\r\n\t\"IntArray\": [\r\n\t\t1,\r\n\t\t2,\r\n\t\t3\r\n\t],\r\n\t\"ObjectArray\": [{\r\n\t\t\t\"Value1\": 5448,\r\n\t\t\t\"Value2\": \"SomeValue\"\r\n\t\t}, {\r\n\t\t\t\"Value1\": 5448,\r\n\t\t\t\"Value2\": \"SomeValue\"\r\n\t\t}],\r\n\t\"TwoDimensionalArray\": [[], []],\r\n\t\"StringWithSpecial\\\\\\\"Characters üñîcødé\": \"\\\\\\\"\\\\b\\\\f\\\\r\\\\n\\\\t\\\\\\\\foo\\u0002\\u0015\\u0031bar.?äüö\"\r\n}",
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
			JsonWriter.WriteValue(u"Value1");
			JsonWriter.WriteValue(u"Value2");
			JsonWriter.WriteValue(u"Value3");
			JsonWriter.WriteEndArray();

			// check
			AssertExtended::AreEqual(u"[\r\n\t\"Value1\",\r\n\t\"Value2\",\r\n\t\"Value3\"\r\n]", Target.ToString().GetCharArray());
		}

		TEST_METHOD(ReadObject)
		{
			// prepare
			String Source = u"{\r\n\t\"Yep\": true,\r\n\t\"Nope\": false,\r\n\t\"NullValue\": null,\r\n\t\"Int\": -5448,\r\n\t\"Float\": 13.370000,\r\n\t\"Double\": 13.370000,\r\n\t\"String\": \"SomeValue\",\r\n\t\"EmptyObject\": {},\r\n\t\"SomeObject\": {\r\n\t\t\"Property1\": \"Value1\",\r\n\t\t\"Property2\": \"Value2\"\r\n\t},\r\n\t\"EmptyArray\": [],\r\n\t\"IntArray\": [\r\n\t\t1,\r\n\t\t2,\r\n\t\t3\r\n\t],\r\n\t\"ObjectArray\": [{\r\n\t\t\t\"Value1\": 5448,\r\n\t\t\t\"Value2\": \"SomeValue\"\r\n\t\t}, {\r\n\t\t\t\"Value1\": 5448,\r\n\t\t\t\"Value2\": \"SomeValue\"\r\n\t\t}],\r\n\t\"TwoDimensionalArray\": [[], []],\r\n\t\"StringWithSpecial\\\\\\\"Characters üñîcødé\": \"\\\\\\\"\\\\b\\\\f\\\\r\\\\n\\\\t\\\\\\\\foo\\u0002\\u0015\\u0031bar.?äüö\"\r\n}";
			StringReader Reader = StringReader(Source);
			JsonTextReader JsonReader = JsonTextReader(Reader);
			
			// read & check
			Assert::AreEqual((uint32_t)JsonToken::None, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::StartedObject, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"Yep", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::Boolean, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"true", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"Nope", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::Boolean, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"false", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"NullValue", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::Null, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"null", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"Int", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::Integer, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"-5448", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"Float", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::Float, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"13.370000", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"Double", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::Float, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"13.370000", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"String", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::String, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"SomeValue", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"EmptyObject", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::StartedObject, (uint32_t)JsonReader.GetToken());
			//AssertExtended::AreEqual(u"SomeValue", JsonReader.GetNodeValue().GetCharArray());	// ToDo: reset _CurrentNodeValue

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::EndedObject, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"SomeObject", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::StartedObject, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"Property1", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::String, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"Value1", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"Property2", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::String, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"Value2", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::EndedObject, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"EmptyArray", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::StartedArray, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::EndedArray, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"IntArray", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::StartedArray, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::Integer, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"1", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::Integer, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"2", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::Integer, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"3", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::EndedArray, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"ObjectArray", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::StartedArray, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::StartedObject, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"Value1", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::Integer, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"5448", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"Value2", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::String, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"SomeValue", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::EndedObject, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::StartedObject, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"Value1", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::Integer, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"5448", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"Value2", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::String, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"SomeValue", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::EndedObject, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::EndedArray, (uint32_t)JsonReader.GetToken());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::PropertyName, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"TwoDimensionalArray", JsonReader.GetNodeValue().GetCharArray());

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
			AssertExtended::AreEqual(u"StringWithSpecial\\\\\\\"Characters üñîcødé", JsonReader.GetNodeValue().GetCharArray());

			Assert::IsTrue(JsonReader.Read());
			Assert::AreEqual((uint32_t)JsonToken::String, (uint32_t)JsonReader.GetToken());
			AssertExtended::AreEqual(u"\\\\\\\"\\\\b\\\\f\\\\r\\\\n\\\\t\\\\\\\\foo\\u0002\\u0015\\u0031bar.?äüö", JsonReader.GetNodeValue().GetCharArray());

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
				String Source = u"[\r\n\t\"Value1\",\r\n\t\"Value2\",\r\n\t\"Value3\"\r\n]";
				StringReader Reader = StringReader(Source);
				JsonTextReader JsonReader = JsonTextReader(Reader);

				// read & check
				Assert::AreEqual((uint32_t)JsonToken::None, (uint32_t)JsonReader.GetToken());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::StartedArray, (uint32_t)JsonReader.GetToken());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::String, (uint32_t)JsonReader.GetToken());
				AssertExtended::AreEqual(u"Value1", JsonReader.GetNodeValue().GetCharArray());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::String, (uint32_t)JsonReader.GetToken());
				AssertExtended::AreEqual(u"Value2", JsonReader.GetNodeValue().GetCharArray());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::String, (uint32_t)JsonReader.GetToken());
				AssertExtended::AreEqual(u"Value3", JsonReader.GetNodeValue().GetCharArray());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::EndedArray, (uint32_t)JsonReader.GetToken());

				Assert::IsFalse(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::None, (uint32_t)JsonReader.GetToken());
			}

			// test: int array
			{
				// prepare
				String Source = u"[\r\n\t12,\r\n\t2,\r\n\t3453\r\n]";
				StringReader Reader = StringReader(Source);
				JsonTextReader JsonReader = JsonTextReader(Reader);

				// read & check
				Assert::AreEqual((uint32_t)JsonToken::None, (uint32_t)JsonReader.GetToken());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::StartedArray, (uint32_t)JsonReader.GetToken());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::Integer, (uint32_t)JsonReader.GetToken());
				AssertExtended::AreEqual(u"12", JsonReader.GetNodeValue().GetCharArray());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::Integer, (uint32_t)JsonReader.GetToken());
				AssertExtended::AreEqual(u"2", JsonReader.GetNodeValue().GetCharArray());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::Integer, (uint32_t)JsonReader.GetToken());
				AssertExtended::AreEqual(u"3453", JsonReader.GetNodeValue().GetCharArray());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::EndedArray, (uint32_t)JsonReader.GetToken());

				Assert::IsFalse(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::None, (uint32_t)JsonReader.GetToken());
			}

			// test: float array
			{
				// prepare
				String Source = u"[\r\n\t1.2,\r\n\t2.3,\r\n\t3453.0\r\n]";
				StringReader Reader = StringReader(Source);
				JsonTextReader JsonReader = JsonTextReader(Reader);
				
				// read & check
				Assert::AreEqual((uint32_t)JsonToken::None, (uint32_t)JsonReader.GetToken());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::StartedArray, (uint32_t)JsonReader.GetToken());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::Float, (uint32_t)JsonReader.GetToken());
				AssertExtended::AreEqual(u"1.2", JsonReader.GetNodeValue().GetCharArray());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::Float, (uint32_t)JsonReader.GetToken());
				AssertExtended::AreEqual(u"2.3", JsonReader.GetNodeValue().GetCharArray());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::Float, (uint32_t)JsonReader.GetToken());
				AssertExtended::AreEqual(u"3453.0", JsonReader.GetNodeValue().GetCharArray());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::EndedArray, (uint32_t)JsonReader.GetToken());

				Assert::IsFalse(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::None, (uint32_t)JsonReader.GetToken());
			}

			// test: bool array
			{
				// prepare
				String Source = u"[\r\n\tfalse,\r\n\ttrue,\r\n\tnull\r\n]";
				StringReader Reader = StringReader(Source);
				JsonTextReader JsonReader = JsonTextReader(Reader);

				// read & check
				Assert::AreEqual((uint32_t)JsonToken::None, (uint32_t)JsonReader.GetToken());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::StartedArray, (uint32_t)JsonReader.GetToken());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::Boolean, (uint32_t)JsonReader.GetToken());
				AssertExtended::AreEqual(u"false", JsonReader.GetNodeValue().GetCharArray());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::Boolean, (uint32_t)JsonReader.GetToken());
				AssertExtended::AreEqual(u"true", JsonReader.GetNodeValue().GetCharArray());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::Null, (uint32_t)JsonReader.GetToken());
				AssertExtended::AreEqual(u"null", JsonReader.GetNodeValue().GetCharArray());

				Assert::IsTrue(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::EndedArray, (uint32_t)JsonReader.GetToken());

				Assert::IsFalse(JsonReader.Read());
				Assert::AreEqual((uint32_t)JsonToken::None, (uint32_t)JsonReader.GetToken());
			}

			// test: empty array
			{
				// prepare
				String Source = u"[]";
				//String Source = u"[ ]";
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
				JsonObject Root = JsonObject();
				JsonElement Yep = JsonElement(u"Yep", true);
				JsonElement Nope = JsonElement(u"Nope", false);
				JsonElement NullValue = JsonElement(u"NullValue");
				JsonElement Int = JsonElement(u"Int", -5448);
				JsonElement Float = JsonElement(u"Float", 13.370000f);
				JsonElement Double = JsonElement(u"Double", 13.370000);
				JsonElement String = JsonElement(u"String", Elysium::Core::String(u"SomeValue"));
				JsonObject EmptyObject = JsonObject(u"EmptyObject");
				JsonObject SomeObject = JsonObject(u"SomeObject");
				JsonElement Property1 = JsonElement(u"Property1", Elysium::Core::String(u"Value1"));
				JsonElement Property2 = JsonElement(u"Property2", Elysium::Core::String(u"Value2"));
				JsonArray EmptyArray = JsonArray(u"EmptyArray");
				JsonArray IntArray = JsonArray(u"IntArray");
				JsonElement IntArrayValue1 = JsonElement(Elysium::Core::String(), 1);
				JsonElement IntArrayValue2 = JsonElement(Elysium::Core::String(), 2);
				JsonElement IntArrayValue3 = JsonElement(Elysium::Core::String(), 3);
				JsonArray ObjectArray = JsonArray(u"ObjectArray");
				JsonObject ObjectArrayObject1 = JsonObject();
				JsonElement ObjectArrayObject1Value1 = JsonElement(u"Value1", 5448);
				JsonElement ObjectArrayObject1Value2 = JsonElement(u"Value2", Elysium::Core::String(u"SomeValue"));
				JsonObject ObjectArrayObject2 = JsonObject();
				JsonElement ObjectArrayObject2Value1 = JsonElement(u"Value1", 5448);
				JsonElement ObjectArrayObject2Value2 = JsonElement(u"Value2", Elysium::Core::String(u"SomeValue"));
				JsonArray TwoDimensionalArray = JsonArray(u"TwoDimensionalArray");
				JsonArray TwoDimensionalArray1 = JsonArray();
				JsonArray TwoDimensionalArray2 = JsonArray();
				JsonElement SpecialCharacterString = JsonElement(u"StringWithSpecial\"Characters üñîcødé", Elysium::Core::String(u"\"\b\f\r\n\t\\foo\x02\x0F\x1f""bar.?äüö"));

				Document.AddChild(Root);
				Root.AddChild(Yep);
				Root.AddChild(Nope);
				Root.AddChild(NullValue);
				Root.AddChild(Int);
				Root.AddChild(Float);
				Root.AddChild(Double);
				Root.AddChild(String);
				Root.AddChild(EmptyObject);
				Root.AddChild(SomeObject);
				SomeObject.AddChild(Property1);
				SomeObject.AddChild(Property2);
				Root.AddChild(EmptyArray);
				Root.AddChild(IntArray);
				IntArray.AddChild(IntArrayValue1);
				IntArray.AddChild(IntArrayValue2);
				IntArray.AddChild(IntArrayValue3);
				Root.AddChild(ObjectArray);
				ObjectArray.AddChild(ObjectArrayObject1);
				ObjectArrayObject1.AddChild(ObjectArrayObject1Value1);
				ObjectArrayObject1.AddChild(ObjectArrayObject1Value2);
				ObjectArray.AddChild(ObjectArrayObject2);
				ObjectArrayObject2.AddChild(ObjectArrayObject2Value1);
				ObjectArrayObject2.AddChild(ObjectArrayObject2Value2);
				Root.AddChild(TwoDimensionalArray);
				TwoDimensionalArray.AddChild(TwoDimensionalArray1);
				TwoDimensionalArray.AddChild(TwoDimensionalArray2);
				Root.AddChild(SpecialCharacterString);

				// write
				Document.WriteTo(JsonWriter);

				// check
				AssertExtended::AreEqual(u"{\r\n\t\"Yep\": true,\r\n\t\"Nope\": false,\r\n\t\"NullValue\": null,\r\n\t\"Int\": -5448,\r\n\t\"Float\": 13.370000,\r\n\t\"Double\": 13.370000,\r\n\t\"String\": \"SomeValue\",\r\n\t\"EmptyObject\": {},\r\n\t\"SomeObject\": {\r\n\t\t\"Property1\": \"Value1\",\r\n\t\t\"Property2\": \"Value2\"\r\n\t},\r\n\t\"EmptyArray\": [],\r\n\t\"IntArray\": [\r\n\t\t1,\r\n\t\t2,\r\n\t\t3\r\n\t],\r\n\t\"ObjectArray\": [{\r\n\t\t\t\"Value1\": 5448,\r\n\t\t\t\"Value2\": \"SomeValue\"\r\n\t\t}, {\r\n\t\t\t\"Value1\": 5448,\r\n\t\t\t\"Value2\": \"SomeValue\"\r\n\t\t}],\r\n\t\"TwoDimensionalArray\": [[], []],\r\n\t\"StringWithSpecial\\\\\\\"Characters üñîcødé\": \"\\\\\\\"\\\\b\\\\f\\\\r\\\\n\\\\t\\\\\\\\foo\\u0002\\u0015\\u0031bar.?äüö\"\r\n}",
					Target.ToString().GetCharArray());
			}

			// test 2
			{
				// prepare
				StringBuilder Target = StringBuilder();
				StringWriter Writer = StringWriter(Target);
				JsonTextWriter JsonWriter = JsonTextWriter(Writer);

				JsonDocument Document = JsonDocument();
				JsonArray Root = JsonArray();
				JsonElement Value1 = JsonElement(Elysium::Core::String(), Elysium::Core::String(u"Value1"));
				JsonElement Value2 = JsonElement(Elysium::Core::String(), Elysium::Core::String(u"Value2"));
				JsonElement Value3 = JsonElement(Elysium::Core::String(), Elysium::Core::String(u"Value3"));

				Document.AddChild(Root);
				Root.AddChild(Value1);
				Root.AddChild(Value2);
				Root.AddChild(Value3);

				// write
				Document.WriteTo(JsonWriter);

				// check
				AssertExtended::AreEqual(u"[\r\n\t\"Value1\",\r\n\t\"Value2\",\r\n\t\"Value3\"\r\n]", Target.ToString().GetCharArray());
			}
		}
		TEST_METHOD(DocumentFromReader)
		{
			// test 1
			{
				/*
				// prepare
				String Source = u"{\r\n\t\"Yep\": true,\r\n\t\"Nope\": false,\r\n\t\"NullValue\": null,\r\n\t\"Int\": -5448,\r\n\t\"Float\": 13.370000,\r\n\t\"Double\": 13.370000,\r\n\t\"String\": \"SomeValue\",\r\n\t\"EmptyObject\": {},\r\n\t\"SomeObject\": {\r\n\t\t\"Property1\": \"Value1\",\r\n\t\t\"Property2\": \"Value2\"\r\n\t},\r\n\t\"EmptyArray\": [],\r\n\t\"IntArray\": [\r\n\t\t1,\r\n\t\t2,\r\n\t\t3\r\n\t],\r\n\t\"ObjectArray\": [{\r\n\t\t\t\"Value1\": 5448,\r\n\t\t\t\"Value2\": \"SomeValue\"\r\n\t\t}, {\r\n\t\t\t\"Value1\": 5448,\r\n\t\t\t\"Value2\": \"SomeValue\"\r\n\t\t}],\r\n\t\"TwoDimensionalArray\": [[], []],\r\n\t\"StringWithSpecial\\\\\\\"Characters üñîcødé\": \"\\\\\\\"\\\\b\\\\f\\\\r\\\\n\\\\t\\\\\\\\foo\\u0002\\u0015\\u0031bar.?äüö\"\r\n}";
				JsonDocument Document = JsonDocument();
				Document.LoadJson(Source);

				// read & check
				*/
			}

			// test 2
			{
				// prepare
				String Source = u"[\r\n\t\"Value1\",\r\n\t\"Value2\",\r\n\t\"Value3\"\r\n]";
				JsonDocument Document = JsonDocument();
				Document.LoadJson(Source);

				// read & check
				JsonArray& RootNode = static_cast<JsonArray&>(Document.GetRootNode());
				JsonElement& Element1 = static_cast<JsonElement&>(RootNode.GetChild(0));
				AssertExtended::AreEqual(u"Value1", Element1.GetValueAsString().GetCharArray());

				JsonElement& Element2 = static_cast<JsonElement&>(RootNode.GetChild(1));
				AssertExtended::AreEqual(u"Value2", Element2.GetValueAsString().GetCharArray());

				JsonElement& Element3 = static_cast<JsonElement&>(RootNode.GetChild(2));
				AssertExtended::AreEqual(u"Value3", Element3.GetValueAsString().GetCharArray());

				int x = 34;
			}
		}
	};
}
