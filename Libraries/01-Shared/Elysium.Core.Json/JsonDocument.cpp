#include "JsonDocument.hpp"

#ifndef ELYSIUM_CORE_IO_FILESTREAM
#include "../Elysium.Core.IO/FileStream.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAMREADER
#include "../Elysium.Core.IO/StreamReader.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STRINGREADER
#include "../Elysium.Core.IO/StringReader.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONTEXTREADER
#include "JsonTextReader.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONREADEREXCEPTION
#include "JsonReaderException.hpp"
#endif

#ifndef ELYSIUM_CORE_INDEXOUTOFRANGEEXCEPTION
#include "../Elysium.Core/IndexOutOfRangeException.hpp"
#endif

Elysium::Core::Json::JsonDocument::JsonDocument()
	: Elysium::Core::Json::JsonNode()
{ }

Elysium::Core::Json::JsonDocument::~JsonDocument()
{ }

const Elysium::Core::Utf8String & Elysium::Core::Json::JsonDocument::GetName() const
{
	static const Elysium::Core::Utf8String Name = u8"#document";
	return Name;
}

const Elysium::Core::Json::JsonNodeType Elysium::Core::Json::JsonDocument::GetNodeType() const
{
	return JsonNodeType::Document;
}

Elysium::Core::Json::JsonNode & Elysium::Core::Json::JsonDocument::GetRootNode()
{
	if (_Children.GetCount() == 0)
	{
		throw IndexOutOfRangeException();
	}
	return *_Children[0];
}

Elysium::Core::Json::JsonObject & Elysium::Core::Json::JsonDocument::AddRootObject()
{
	if (_Children.GetCount() > 0)
	{	// ToDo: InvalidOperationException
		throw JsonException(u8"A document can only hold one child - the root node!");
	}
	// ToDo: having the elements scattered around memory obviously isn't good
	JsonObject* OwnedObject = new JsonObject();
	Elysium::Core::Json::JsonNode::AddChild(*OwnedObject);
	return *OwnedObject;
}

Elysium::Core::Json::JsonArray & Elysium::Core::Json::JsonDocument::AddRootArray()
{
	if (_Children.GetCount() > 0)
	{	// ToDo: InvalidOperationException
		throw JsonException(u8"A document can only hold one child - the root node!");
	}
	// ToDo: having the elements scattered around memory obviously isn't good
	JsonArray* OwnedArray = new JsonArray();
	Elysium::Core::Json::JsonNode::AddChild(*OwnedArray);
	return *OwnedArray;
}

void Elysium::Core::Json::JsonDocument::Load(const Elysium::Core::Utf8String & Filename)
{
	Elysium::Core::IO::FileStream InputStream = Elysium::Core::IO::FileStream(Filename, Elysium::Core::IO::FileMode::Open, Elysium::Core::IO::FileAccess::Read);
	Load(InputStream);
}

void Elysium::Core::Json::JsonDocument::Load(Elysium::Core::IO::Stream & InputStream)
{
	Elysium::Core::IO::StreamReader Reader = Elysium::Core::IO::StreamReader(InputStream, Elysium::Core::Text::Encoding::UTF8());
	JsonTextReader JsonReader = JsonTextReader(Reader);
	Load(JsonReader);
}

void Elysium::Core::Json::JsonDocument::LoadJson(const Elysium::Core::Utf8String & Json)
{
	Elysium::Core::IO::StringReader Reader = Elysium::Core::IO::StringReader(Json);
	JsonTextReader JsonReader = JsonTextReader(Reader);
	Load(JsonReader);
}

void Elysium::Core::Json::JsonDocument::WriteTo(JsonWriter & Writer) const
{
	for (int i = 0; i < _Children.GetCount(); i++)
	{
		_Children[i]->WriteTo(Writer);
	}
}

void Elysium::Core::Json::JsonDocument::Load(JsonReader & JsonReader)
{
	if (!JsonReader.Read())
	{	// there was nothing to read ergo: emtpy document
		return;
	}

	const JsonToken Token = JsonReader.GetToken();
	switch (Token)
	{
	case JsonToken::StartedObject:
	{
		JsonObject* Node = new JsonObject();
		AddChild(*Node);
		Node->Load(JsonReader);
		break;
	}
	case JsonToken::StartedArray:
	{
		JsonArray* Node = new JsonArray();
		AddChild(*Node);
		Node->Load(JsonReader);
		break;
	}
	default:
		throw JsonReaderException();
	}

	JsonReader.Read();
	if (JsonReader.GetToken() != JsonToken::None)
	{
		throw JsonReaderException();
	}
}
