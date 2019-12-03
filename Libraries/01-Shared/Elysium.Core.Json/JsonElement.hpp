/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_JSON_JSONELEMENT
#define ELYSIUM_CORE_JSON_JSONELEMENT

#ifndef ELYSIUM_CORE_JSON_JSONNODE
#include "JsonNode.hpp"
#endif

#ifndef _VARIANT_
#include <variant>
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Json
		{
			class ELYSIUM_CORE_JSON_API JsonElement final : public JsonNode
			{
				friend class JsonDocument;
				friend class JsonObject;
				friend class JsonArray;
			public:
				JsonElement(const JsonElement& Source) = delete;
				JsonElement(JsonElement&& Right) noexcept = delete;
				~JsonElement();

				JsonElement& operator=(const JsonElement& Source) = delete;
				JsonElement& operator=(JsonElement&& Right) noexcept = delete;

				const String& GetName() const override;
				virtual const JsonNodeType GetNodeType() const override;

				const String& GetValueAsString() const;

				virtual void WriteTo(JsonWriter& Writer) const override;
			protected:
				virtual void Load(JsonReader& JsonReader) override;
			private:
				JsonElement(const String& Name, const String& Value);
				JsonElement(const String& Name, const int32_t Value);
				JsonElement(const String& Name, const float Value);
				JsonElement(const String& Name, const double Value);
				JsonElement(const String& Name, const bool Value);
				JsonElement(const String& Name);

				String _Name;
				JsonNodeType _Type;
				std::variant<bool, int32_t, float, double, String, void*> _Value;
			};
		}
	}
}
#endif
