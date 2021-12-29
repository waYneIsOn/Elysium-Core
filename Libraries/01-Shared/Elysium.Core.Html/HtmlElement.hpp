/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_HTML_HTMLELEMENT
#define ELYSIUM_CORE_HTML_HTMLELEMENT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_HTML_HTMLNODE
#include "HtmlNode.hpp"
#endif

namespace Elysium::Core::Html
{
	// Element, EntityReference, Entity, DocumentType(?), Notation(?)
	class ELYSIUM_CORE_HTML_API HtmlElement final : public HtmlNode
	{
		friend class HtmlDocument;
	private:
		HtmlElement(const HtmlNodeType NodeType, const Utf8String& Value);

		HtmlElement(const Utf8String& Name, const HtmlNodeType NodeType, const Utf8String& Value);
	public:
		HtmlElement(const HtmlElement& Source) = delete;

		HtmlElement(HtmlElement&& Right) noexcept = delete;

		virtual ~HtmlElement();
	public:
		HtmlElement& operator=(const HtmlElement& Source) = delete;

		HtmlElement& operator=(HtmlElement&& Right) noexcept = delete;
	public:
		virtual const Utf8String& GetName() const override;

		virtual const HtmlNodeType GetNodeType() const override;

		const Utf8String& GetValue() const;
	private:
		Utf8String _Name;
		HtmlNodeType _Type;
		Utf8String _Value;
	};
}
#endif
