/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

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

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Elysium.Core.Template/Vector.hpp"
#endif

namespace Elysium::Core::Html
{
	class ELYSIUM_CORE_HTML_API HtmlNode
	{
	public:
		virtual ~HtmlNode();
	public:
		virtual const Utf8String& GetName() const = 0;

		virtual const HtmlNodeType GetNodeType() const = 0;

		virtual const HtmlNode* GetParentNode() const;

		virtual const Elysium::Core::size GetChildCount();

		virtual HtmlNode& GetChild(Elysium::Core::size Index);

		virtual void RemoveChild(HtmlNode& Node);

		//virtual void WriteTo(HtmlWriter& Writer) const = 0;
	protected:
		HtmlNode();

		HtmlNode* _ParentNode;
		Elysium::Core::Template::Container::Vector<HtmlNode*> _Children;

		virtual void AddChild(HtmlNode& Node);

		//virtual void Load(HtmlReader& HtmlReader) = 0;
	};
}
#endif
