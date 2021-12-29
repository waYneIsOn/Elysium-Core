/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_HTML_HTMLATTRIBUTE
#define ELYSIUM_CORE_HTML_HTMLATTRIBUTE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_HTML_HTMLNODE
#include "HtmlNode.hpp"
#endif

namespace Elysium::Core::Html
{
	class ELYSIUM_CORE_HTML_API HtmlAttribute final : public HtmlNode
	{
	private:
		HtmlAttribute(const Elysium::Core::Utf8String & Name, const Elysium::Core::Utf8String & Value);
	public:
		HtmlAttribute(const HtmlAttribute& Source) = delete;

		HtmlAttribute(HtmlAttribute&& Right) noexcept = delete;

		virtual ~HtmlAttribute();
	public:
		HtmlAttribute& operator=(const HtmlAttribute& Source) = delete;

		HtmlAttribute& operator=(HtmlAttribute&& Right) noexcept = delete;
	public:
		virtual const Elysium::Core::Utf8String& GetName() const override;

		virtual const HtmlNodeType GetNodeType() const override;

		const Elysium::Core::Utf8String& GetValue() const;
	private:
		Elysium::Core::Utf8String _Name;
		Elysium::Core::Utf8String _Value;
	};
}
#endif
