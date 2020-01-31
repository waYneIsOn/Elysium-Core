/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef UNITTESTS_CORE_JSON_ASSERTJSONVISITOR
#define UNITTESTS_CORE_JSON_ASSERTJSONVISITOR

#ifndef ELYSIUM_CORE_JSON_JSONVISITOR
#include "../../../Libraries/01-Shared/Elysium.Core.Json/JsonVisitor.hpp"
#endif

using namespace Elysium::Core::Json;

namespace UnitTests::Core::Json
{
	class AssertJsonVisitor : JsonVisitor
	{
	public:
		AssertJsonVisitor();
		~AssertJsonVisitor();

		virtual JsonNode& Visit(JsonNode& Node) override;
	protected:
		virtual JsonArray& VisitArray(JsonArray& Node) override;
		virtual JsonDocument& VisitDocument(JsonDocument& Node) override;
		virtual JsonElement& VisitElement(JsonElement& Node) override;
		virtual JsonObject& VisitObject(JsonObject& Node) override;
	};
}
#endif
