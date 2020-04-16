/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

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
	public:
		HtmlElement(const HtmlElement& Source) = delete;
		HtmlElement(HtmlElement&& Right) noexcept = delete;
		virtual ~HtmlElement();

		HtmlElement& operator=(const HtmlElement& Source) = delete;
		HtmlElement& operator=(HtmlElement&& Right) noexcept = delete;

		virtual const String& GetName() const override;
		virtual const HtmlNodeType GetNodeType() const override;
		const String& GetValue() const;
	private:
		HtmlElement(const HtmlNodeType NodeType, const String& Value);
		HtmlElement(const String& Name, const HtmlNodeType NodeType, const String& Value);

		String _Name;
		HtmlNodeType _Type;
		String _Value;
	};
}
#endif
