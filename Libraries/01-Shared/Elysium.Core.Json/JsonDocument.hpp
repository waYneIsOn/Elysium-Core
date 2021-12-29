/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_JSON_JSONDOCUMENT
#define ELYSIUM_CORE_JSON_JSONDOCUMENT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_JSON_JSONNODE
#include "JSONNode.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "../Elysium.Core.IO/Stream.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONOBJECT
#include "JsonObject.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONARRAY
#include "JsonArray.hpp"
#endif

namespace Elysium::Core::Json
{
	class ELYSIUM_CORE_JSON_API JsonDocument final : public JsonNode
	{
	public:
		JsonDocument();

		JsonDocument(const JsonDocument& Source) = delete;

		JsonDocument(JsonDocument&& Right) noexcept = delete;

		virtual ~JsonDocument();
	public:
		JsonDocument& operator=(const JsonDocument& Source) = delete;

		JsonDocument& operator=(JsonDocument&& Right) noexcept = delete;
	public:
		const Elysium::Core::Utf8String& GetName() const override;

		const JsonNodeType GetNodeType() const override;

		JsonNode& GetRootNode();
	public:
		JsonObject& AddRootObject();

		JsonArray& AddRootArray();

		void Load(const Elysium::Core::Utf8String& Filename);

		void Load(Elysium::Core::IO::Stream& InputStream);

		void LoadJson(const Elysium::Core::Utf8String& Json);

		void WriteTo(JsonWriter& Writer) const override;
	protected:
		virtual void Load(JsonReader& JsonReader) override;
	};
}
#endif
