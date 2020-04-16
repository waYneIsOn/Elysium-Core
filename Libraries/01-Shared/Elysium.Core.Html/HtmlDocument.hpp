/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_HTML_HTMLDOCUMENT
#define ELYSIUM_CORE_HTML_HTMLDOCUMENT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_HTML_HTMLNODE
#include "HtmlNode.hpp"
#endif

#ifndef ELYSIUM_CORE_HTML_HTMLELEMENT
#include "HtmlElement.hpp"
#endif

namespace Elysium::Core::Html
{
	class ELYSIUM_CORE_HTML_API HtmlDocument final : public HtmlNode
	{
	public:
		HtmlDocument();
		HtmlDocument(const HtmlDocument& Source) = delete;
		HtmlDocument(HtmlDocument&& Right) noexcept = delete;
		virtual ~HtmlDocument();

		HtmlDocument& operator=(const HtmlDocument& Source) = delete;
		HtmlDocument& operator=(HtmlDocument&& Right) noexcept = delete;

		virtual const String& GetName() const override;
		virtual const HtmlNodeType GetNodeType() const override;
		HtmlElement& GetRootNode();
	private:
		HtmlElement _RootNode;
	};
}
#endif
