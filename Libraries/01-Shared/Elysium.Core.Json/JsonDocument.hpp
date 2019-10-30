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
			class ELYSIUM_CORE_API JsonDocument : public JsonNode
			{
			public:
				JsonDocument();
				~JsonDocument();

				const String& GetName() const override;
				const JsonNodeType GetNodeType() const override;

				//void Load(const Elysium::Core::IO::Stream& InputStream);
				//void Load(const Elysium::Core::String& Filename);
				//void LoadJson(const Elysium::Core::String& Json);

				//void Save(Elysium::Core::IO::Stream& OutputStream);
				//void Save(Elysium::Core::String& Filename);

				void WriteTo(JsonWriter& Writer) override;
			};
		}
	}
}
#endif
