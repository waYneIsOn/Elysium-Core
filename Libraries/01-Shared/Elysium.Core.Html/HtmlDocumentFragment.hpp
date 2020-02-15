/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_HTML_HTMLDOCUMENTFRAGMENT
#define ELYSIUM_CORE_HTML_HTMLDOCUMENTFRAGMENT

#ifndef ELYSIUM_CORE_HTML_HTMLNODE
#include "HtmlNode.hpp"
#endif

namespace Elysium::Core::Html
{
	class ELYSIUM_CORE_HTML_API HtmlDocumentFragment final : public HtmlNode
	{
	public:
		HtmlDocumentFragment();
		HtmlDocumentFragment(const HtmlDocumentFragment& Source) = delete;
		HtmlDocumentFragment(HtmlDocumentFragment&& Right) noexcept = delete;
		virtual ~HtmlDocumentFragment();

		HtmlDocumentFragment& operator=(const HtmlDocumentFragment& Source) = delete;
		HtmlDocumentFragment& operator=(HtmlDocumentFragment&& Right) noexcept = delete;

		virtual const String& GetName() const override;
		virtual const HtmlNodeType GetNodeType() const override;
	};
}
#endif
