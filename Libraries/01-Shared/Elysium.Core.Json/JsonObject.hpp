/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_JSON_JSONOBJECT
#define ELYSIUM_CORE_JSON_JSONOBJECT

#ifndef ELYSIUM_CORE_JSON_JSONNODE
#include "JsonNode.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONELEMENT
#include "JsonElement.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONARRAY
#include "JsonArray.hpp"
#endif

namespace Elysium::Core::Json
{
	class ELYSIUM_CORE_JSON_API JsonObject final : public JsonNode
	{
		friend class JsonDocument;
		friend class JsonArray;
	public:
		JsonObject(const JsonObject& Source) = delete;
		JsonObject(JsonObject&& Right) noexcept = delete;
		~JsonObject();

		JsonObject& operator=(const JsonObject& Source) = delete;
		JsonObject& operator=(JsonObject&& Right) noexcept = delete;

		const String& GetName() const override;
		virtual const JsonNodeType GetNodeType() const override;

		virtual void WriteTo(JsonWriter& Writer) const override;

		JsonElement& AddElement(const String& Name, const String& Value);
		JsonElement& AddElement(const String& Name, const int32_t Value);
		JsonElement& AddElement(const String& Name, const float Value);
		JsonElement& AddElement(const String& Name, const double Value);
		JsonElement& AddElement(const String& Name, const bool Value);
		JsonElement& AddElement(const String& Name);

		JsonObject& AddObject(const String& Name);

		JsonArray& AddArray(const String& Name);
	protected:
		virtual void Load(JsonReader& JsonReader) override;
	private:
		JsonObject();
		JsonObject(const String& Name);

		String _Name;
	};
}
#endif
