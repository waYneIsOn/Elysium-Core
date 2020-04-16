/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_HTML_HTMLNODE
#define ELYSIUM_CORE_HTML_HTMLNODE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_HTML_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_HTML_HTMLNODETYPE
#include "HtmlNodeType.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "../Elysium.Core/List.hpp"
#endif

namespace Elysium::Core::Html
{
	class ELYSIUM_CORE_HTML_API HtmlNode
	{
	public:
		virtual ~HtmlNode();

		virtual const String& GetName() const = 0;
		virtual const HtmlNodeType GetNodeType() const = 0;
		virtual const HtmlNode* GetParentNode() const;

		virtual const size_t GetChildCount();

		virtual HtmlNode& GetChild(size_t Index);
		virtual void RemoveChild(HtmlNode& Node);

		//virtual void WriteTo(HtmlWriter& Writer) const = 0;
	protected:
		HtmlNode();

		HtmlNode* _ParentNode;
		Collections::Template::List<HtmlNode*> _Children;

		virtual void AddChild(HtmlNode& Node);

		//virtual void Load(HtmlReader& HtmlReader) = 0;
	};
}
#endif
