/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_JSON_JSONNODE
#define ELYSIUM_CORE_JSON_JSONNODE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "../Elysium.Core/List.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONNODETYPE
#include "JSONNodeType.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONREADER
#include "JsonReader.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONWRITER
#include "JsonWriter.hpp"
#endif

namespace Elysium::Core::Json
{
	class ELYSIUM_CORE_JSON_API JsonNode
	{
	public:
		virtual ~JsonNode();

		virtual const Elysium::Core::Utf8String& GetName() const = 0;
		virtual const JsonNodeType GetNodeType() const = 0;
		virtual const JsonNode* GetParentNode() const;
		
		virtual const Elysium::Core::size GetChildCount();

		virtual JsonNode& GetChild(Elysium::Core::size Index);
		virtual void RemoveChild(JsonNode& Node);

		virtual void WriteTo(JsonWriter& Writer) const = 0;
	protected:
		JsonNode();

		JsonNode* _ParentNode;
#pragma warning(disable : 4251)	// _Children don't get exposed directly so I can simply ignore the warning
		Collections::Template::List<JsonNode*> _Children;
#pragma warning(default : 4251)

		virtual void AddChild(JsonNode& Node);

		virtual void Load(JsonReader& JsonReader) = 0;
	};
}
#endif
