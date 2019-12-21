/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_JSON_JSONARRAY
#define ELYSIUM_CORE_JSON_JSONARRAY

#ifndef ELYSIUM_CORE_JSON_JSONNODE
#include "JsonNode.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONELEMENT
#include "JsonElement.hpp"
#endif

namespace Elysium::Core::Json
{
	class JsonObject;

	class ELYSIUM_CORE_JSON_API JsonArray final : public JsonNode
	{
		friend class JsonDocument;
		friend class JsonObject;
	public:
		JsonArray(const JsonArray& Source) = delete;
		JsonArray(JsonArray&& Right) noexcept = delete;
		~JsonArray();

		JsonArray& operator=(const JsonArray& Source) = delete;
		JsonArray& operator=(JsonArray&& Right) noexcept = delete;

		const String& GetName() const override;
		virtual const JsonNodeType GetNodeType() const override;

		virtual void WriteTo(JsonWriter& Writer) const override;
				
		JsonElement& AddElement(const String& Value);
		JsonElement& AddElement(const int32_t Value);
		JsonElement& AddElement(const float Value);
		JsonElement& AddElement(const double Value);
		JsonElement& AddElement(const bool Value);
		JsonElement& AddElement();

		JsonObject& AddObject();

		JsonArray& AddArray();
	protected:
		virtual void Load(JsonReader& JsonReader) override;
	private:
		JsonArray();
		JsonArray(const String & Name);

		String _Name;
	};
}
#endif
