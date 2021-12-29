/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_JSON_JSONELEMENT
#define ELYSIUM_CORE_JSON_JSONELEMENT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_JSON_JSONNODE
#include "JsonNode.hpp"
#endif

#ifndef _VARIANT_
#include <variant>
#endif

namespace Elysium::Core::Json
{
	class ELYSIUM_CORE_JSON_API JsonElement final : public JsonNode
	{
		friend class JsonDocument;
		friend class JsonObject;
		friend class JsonArray;
	public:
		JsonElement(const JsonElement& Source) = delete;
		JsonElement(JsonElement&& Right) noexcept = delete;
		virtual ~JsonElement();

		JsonElement& operator=(const JsonElement& Source) = delete;
		JsonElement& operator=(JsonElement&& Right) noexcept = delete;

		const Utf8String& GetName() const override;
		virtual const JsonNodeType GetNodeType() const override;

		const bool IsNull() const;
		const Utf8String& GetValueAsString() const;
		const int32_t GetValueAsInt32() const;
		const float GetValueAsSingle() const;
		const bool GetValueAsBoolean() const;

		void SetValue(const Utf8String& Value);
		void SetValue(const int32_t Value);
		void SetValue(const float Value);
		void SetValue(const bool Value);

		virtual void WriteTo(JsonWriter& Writer) const override;
	protected:
		virtual void Load(JsonReader& JsonReader) override;
	private:
		JsonElement(const Utf8String& Name, const Utf8String& Value);
		JsonElement(const Utf8String& Name, const int32_t Value);
		JsonElement(const Utf8String& Name, const float Value);
		JsonElement(const Utf8String& Name, const double Value);
		JsonElement(const Utf8String& Name, const bool Value);
		JsonElement(const Utf8String& Name);

		Elysium::Core::Utf8String _Name;
		JsonNodeType _Type;
#pragma warning(disable : 4251)	// _Value doesn't get exposed directly so I can simply ignore the warning
		std::variant<bool, Elysium::Core::int32_t, float, double, Elysium::Core::Utf8String, void*> _Value;
#pragma warning(default : 4251)
	};
}
#endif
