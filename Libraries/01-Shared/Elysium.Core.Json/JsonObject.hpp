/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_JSON_JSONOBJECT
#define ELYSIUM_CORE_JSON_JSONOBJECT

#ifdef _MSC_VER
#pragma once
#endif

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
	private:
		JsonObject();
		JsonObject(const Elysium::Core::Utf8String& Name);
	public:
		JsonObject(const JsonObject& Source) = delete;
		JsonObject(JsonObject&& Right) noexcept = delete;
		virtual ~JsonObject();

		JsonObject& operator=(const JsonObject& Source) = delete;
		JsonObject& operator=(JsonObject&& Right) noexcept = delete;

		const Elysium::Core::Utf8String& GetName() const override;
		virtual const JsonNodeType GetNodeType() const override;

		virtual void WriteTo(JsonWriter& Writer) const override;

		JsonElement& AddElement(const Elysium::Core::Utf8String& Name, const Elysium::Core::Utf8String& Value);
		JsonElement& AddElement(const Elysium::Core::Utf8String& Name, const int32_t Value);
		JsonElement& AddElement(const Elysium::Core::Utf8String& Name, const float Value);
		JsonElement& AddElement(const Elysium::Core::Utf8String& Name, const double Value);
		JsonElement& AddElement(const Elysium::Core::Utf8String& Name, const bool Value);
		JsonElement& AddElement(const Elysium::Core::Utf8String& Name);

		JsonObject& AddObject(const Elysium::Core::Utf8String& Name);

		JsonArray& AddArray(const Elysium::Core::Utf8String& Name);
	protected:
		virtual void Load(JsonReader& JsonReader) override;
	private:
		Elysium::Core::Utf8String _Name;
	};
}
#endif
