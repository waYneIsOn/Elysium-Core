/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef UNITTESTS_CORE_JSON_CHANGINGJSONVISITOR
#define UNITTESTS_CORE_JSON_CHANGINGJSONVISITOR

#ifndef ELYSIUM_CORE_JSON_JSONVISITOR
#include "../../../Libraries/01-Shared/Elysium.Core.Json/JsonVisitor.hpp"
#endif

namespace UnitTests::Core::Json
{
	class ChangingJsonVisitor : Elysium::Core::Json::JsonVisitor
	{
	public:
		ChangingJsonVisitor();
		~ChangingJsonVisitor();

		virtual Elysium::Core::Json::JsonNode& Visit(Elysium::Core::Json::JsonNode& Node) override;
	protected:
		virtual Elysium::Core::Json::JsonArray& VisitArray(Elysium::Core::Json::JsonArray& Node) override;
		virtual Elysium::Core::Json::JsonDocument& VisitDocument(Elysium::Core::Json::JsonDocument& Node) override;
		virtual Elysium::Core::Json::JsonElement& VisitElement(Elysium::Core::Json::JsonElement& Node) override;
		virtual Elysium::Core::Json::JsonObject& VisitObject(Elysium::Core::Json::JsonObject& Node) override;
	};
}
#endif
