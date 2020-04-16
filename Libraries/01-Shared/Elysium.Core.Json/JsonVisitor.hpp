/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_JSON_JSONVISITOR
#define ELYSIUM_CORE_JSON_JSONVISITOR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_JSON_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONNODE
#include "JsonNode.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONARRAY
#include "JsonArray.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONDOCUMENT
#include "JsonDocument.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONELEMENT
#include "JsonElement.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONOBJECT
#include  "JsonObject.hpp"
#endif

namespace Elysium::Core::Json
{
	class ELYSIUM_CORE_JSON_API JsonVisitor
	{
	public:
		~JsonVisitor();

		virtual JsonNode& Visit(JsonNode& Node);
	protected:
		JsonVisitor();

		virtual JsonArray& VisitArray(JsonArray& Node);
		virtual JsonDocument& VisitDocument(JsonDocument& Node);
		virtual JsonElement& VisitElement(JsonElement& Node);
		virtual JsonObject& VisitObject(JsonObject& Node);
	};
}
#endif
