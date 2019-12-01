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

#ifndef ELYSIUM_CORE_JSON_JSONOBJECT
#include "JsonObject.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONARRAY
#include "JsonArray.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONREADEREXCEPTION
#include "JsonReaderException.hpp"
#endif

#ifndef ELYSIUM_CORE_INDEXOUTOFRANGEEXCEPTION
#include "IndexOutOfRangeException.hpp"
#endif

Elysium::Core::Json::JsonDocument::JsonDocument()
	: Elysium::Core::Json::JsonNode()
{
}
Elysium::Core::Json::JsonDocument::~JsonDocument()
{
}

const Elysium::Core::String & Elysium::Core::Json::JsonDocument::GetName() const
{
	static const Elysium::Core::String Name = u"#document";
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

void Elysium::Core::Json::JsonDocument::AddChild(JsonNode & Node)
{
	if (_Children.GetCount() > 0)
	{
		throw JsonException(u"A document can only hold one child - the root node!");
	}
	const JsonNodeType NodeType = Node.GetNodeType();
	if (NodeType != JsonNodeType::Object && NodeType != JsonNodeType::Array)
	{
		throw JsonException(u"A root node must be either object or array!");
	}
	Elysium::Core::Json::JsonNode::AddChild(Node);
}

void Elysium::Core::Json::JsonDocument::Load(const Elysium::Core::String & Filename)
{
	Elysium::Core::IO::FileStream InputStream = Elysium::Core::IO::FileStream(Filename, Elysium::Core::IO::FileMode::Open, Elysium::Core::IO::FileAccess::Read);
	Load(InputStream);
}
void Elysium::Core::Json::JsonDocument::Load(Elysium::Core::IO::Stream & InputStream)
{
	Elysium::Core::IO::StreamReader Reader = Elysium::Core::IO::StreamReader(InputStream);
	JsonTextReader JsonReader = JsonTextReader(Reader);
	Load(JsonReader);
}
void Elysium::Core::Json::JsonDocument::LoadJson(const Elysium::Core::String & Json)
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
	while (JsonReader.Read())
	{
		const JsonToken Token = JsonReader.GetToken();
		switch (Token)
		{
		case JsonToken::StartedObject:
		{
			JsonObject Node = JsonObject();
			AddChild(Node);
			Node.Load(JsonReader);
			break;
		}
		case JsonToken::StartedArray:
		{
			JsonArray Node = JsonArray();
			AddChild(Node);
			Node.Load(JsonReader);
			break;
		}
		default:
			throw JsonReaderException();
		}
	}

	const JsonToken Token = JsonReader.GetToken();
	if (Token != JsonToken::None)
	{
		throw JsonReaderException();
	}
}
