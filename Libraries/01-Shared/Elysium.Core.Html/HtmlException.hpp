/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_HTML_HTMLEXCEPTION
#define ELYSIUM_CORE_HTML_HTMLEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_HTML_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "../Elysium.Core/Exception.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

namespace Elysium::Core::Html
{
	class ELYSIUM_CORE_HTML_API HtmlException : public Exception
	{
	public:
		HtmlException();

		HtmlException(Elysium::Core::Utf8String&& Message);

		virtual ~HtmlException();
	};
}
#endif
