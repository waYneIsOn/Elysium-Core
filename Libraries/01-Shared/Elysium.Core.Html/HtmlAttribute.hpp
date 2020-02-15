/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_HTML_HTMLATTRIBUTE
#define ELYSIUM_CORE_HTML_HTMLATTRIBUTE

#ifndef ELYSIUM_CORE_HTML_HTMLNODE
#include "HtmlNode.hpp"
#endif

namespace Elysium::Core::Html
{
	class ELYSIUM_CORE_HTML_API HtmlAttribute final : public HtmlNode
	{
	public:
		HtmlAttribute(const HtmlAttribute& Source) = delete;
		HtmlAttribute(HtmlAttribute&& Right) noexcept = delete;
		virtual ~HtmlAttribute();

		HtmlAttribute& operator=(const HtmlAttribute& Source) = delete;
		HtmlAttribute& operator=(HtmlAttribute&& Right) noexcept = delete;

		virtual const String& GetName() const override;
		virtual const HtmlNodeType GetNodeType() const override;
		const String& GetValue() const;
	private:
		HtmlAttribute(const String& Name, const String& Value);

		String _Name;
		String _Value;
	};
}
#endif
