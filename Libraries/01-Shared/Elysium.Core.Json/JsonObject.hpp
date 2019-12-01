/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_JSON_JSONOBJECT
#define ELYSIUM_CORE_JSON_JSONOBJECT

#ifndef ELYSIUM_CORE_JSON_JSONNODE
#include "JSONNode.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Json
		{
			class ELYSIUM_CORE_JSON_API JsonObject final : public JsonNode
			{
				friend class JsonDocument;
			public:
				JsonObject();
				JsonObject(const String& Name);
				~JsonObject();

				const String& GetName() const override;
				virtual const JsonNodeType GetNodeType() const override;

				virtual void WriteTo(JsonWriter& Writer) const override;
			protected:
				virtual void Load(JsonReader& JsonReader) override;
			private:
				String _Name;
			};
		}
	}
}
#endif
