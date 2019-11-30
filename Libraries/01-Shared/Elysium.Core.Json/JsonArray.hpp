/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_JSON_JSONARRAY
#define ELYSIUM_CORE_JSON_JSONARRAY

#ifndef ELYSIUM_CORE_JSON_JSONNODE
#include "JSONNode.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Json
		{
			class ELYSIUM_CORE_JSON_API JsonArray final : public JsonNode
			{
			public:
				JsonArray();
				JsonArray(const String & Name);
				~JsonArray();

				const String& GetName() const override;
				virtual const JsonNodeType GetNodeType() const override;

				virtual void WriteTo(JsonWriter& Writer) const override;
			private:
				String _Name;
			};
		}
	}
}
#endif
