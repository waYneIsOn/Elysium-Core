/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_HTML_HTMLNODETYPE
#define ELYSIUM_CORE_HTML_HTMLNODETYPE

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Html
{
	// Represents HTML Tags
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class HtmlNodeType : uint32_t
#elif defined(__ANDROID__)
	enum class HtmlNodeType
#else
#error "undefined os"
#endif
	{
		Document = 0,
		Comment = 1,	// <!--...-->
		DocumentType = 2,	// <!DOCTYPE>
		Root,	// <html>
		Head,	// <head>
		Meta,	// <meta>
		Body,	// <body>
		Footer,	// <footer>

		Hyperlink ,	// <a>
		Abbreviation,	// <abbr>
		Acronym,	// <acronym>
		Address,	// <address>
		Applet,	// <applet>
		Area,	// <area>
		Article,
		Aside,
		Audio,
		Base,
		BaseFont,
		BDI,
		BDO,

		BoldText,
		BigText,
		ImportantText,	// <strong>
		EmphasizedText,	// <em>
		CursiveText,	// <i>
		MarkedText,		// <mark>
		PreformattedText,	// <pre>
		UnderlinedText,	// <u>
		InsertedText,	// <ins>
		DeletedText,	// <del>

		DescriptionList,	// <dl>
		DescriptionListValue,	// <dd>
		DescriptionListTerm,	// <dt>

		BlockQuote,
		SingleLineBreak,	// <br>
		Button,
		Canvas,
		Caption,
		Center,
		Cite,
		Code,
		Column,
		ColumnGroup,
		Data,
		DataList,
		Details,
		DefiningInstanceTerm,
		Dialog,
		DirectoryList,
		Div,
		Embed,
		FieldSet,
		FieldSetCaption,	// <legend>
		FigureCaption,
		Figure,
		Font,
		Form,
		Frame,
		FrameSet,
		Heading1,
		Heading2,
		Heading3,
		Heading4,
		Heading5,
		Heading6,
		Header,
		HR,
		InlineFrame,
		Image,
		Input,
		KeyboardInput,
		Label,
		ListItem,
		Link,
		Main,
		ImageMap,
		Meter,
		NavigationLink,
		NoFrames,
		NoScript,
		Object,
		OrderedList,
		OptGroup,
		Option,
		Output,
		Paragraph,
		Parameter,
		Picture,
		Progress,
		ShortQuotation,
		RP,
		RT,
		Ruby,
		S,
		Sample,
		Script,
		Section,
		Select,
		Small, 
		Source,
		Span,
		Strike,
		Strong,
		Style,
		Sub,
		Summary,
		Sup,
		SVG,
		Table,
		TableBody,
		TableCell,
		Template,
		TextArea,
		TableFooterGroup,
		TableHeader,
		TableHeaderGroup,
		Time,
		Title,
		TableRow,
		Track,
		TeletypeText,
		UnorderedList,
		Variable,
		Video,
		PossibleLineBreak,	// <wbr>
	};
}
#endif
