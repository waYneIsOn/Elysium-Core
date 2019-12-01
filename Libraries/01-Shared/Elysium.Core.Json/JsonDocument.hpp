/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_JSON_JSONDOCUMENT
#define ELYSIUM_CORE_JSON_JSONDOCUMENT

#ifndef ELYSIUM_CORE_JSON_JSONNODE
#include "JSONNode.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "../Elysium.Core.IO/Stream.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Json
		{
			class ELYSIUM_CORE_JSON_API JsonDocument final : public JsonNode
			{
			public:
				JsonDocument();
				~JsonDocument();

				const String& GetName() const override;
				const JsonNodeType GetNodeType() const override;
				JsonNode& GetRootNode();

				virtual void AddChild(JsonNode& Node) override;

				void Load(const Elysium::Core::String& Filename);
				void Load(Elysium::Core::IO::Stream& InputStream);
				void LoadJson(const Elysium::Core::String& Json);

				void WriteTo(JsonWriter& Writer) const override;
			protected:
				virtual void Load(JsonReader& JsonReader) override;
			};
		}
	}
}
#endif
