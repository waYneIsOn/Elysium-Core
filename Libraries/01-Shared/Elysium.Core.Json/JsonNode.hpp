/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_JSON_JSONNODE
#define ELYSIUM_CORE_JSON_JSONNODE

#ifndef ELYSIUM_CORE_JSON_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONNODETYPE
#include "JSONNodeType.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONWRITER
#include "JsonWriter.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_GENERIC_LIST
#include "../Elysium.Core/List.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Json
		{
			class ELYSIUM_CORE_JSON_API JsonNode
			{
			public:
				virtual ~JsonNode();

				virtual const String& GetName() const = 0;
				virtual const JsonNodeType GetNodeType() const = 0;
				virtual const JsonNode* GetParentNode() const;

				virtual void AddChild(JsonNode& Node);
				virtual void RemoveChild(JsonNode& Node);

				virtual void WriteTo(JsonWriter& Writer) const = 0;
			protected:
				JsonNode();

				JsonNode* _ParentNode;
				Collections::Generic::List<const JsonNode*> _Children;
			};
		}
	}
}
#endif
