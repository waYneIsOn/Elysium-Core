/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

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

namespace Elysium::Core::Html
{
	class ELYSIUM_CORE_HTML_API HtmlException : public Exception
	{
	public:
		HtmlException();
		HtmlException(String&& Message);
		virtual ~HtmlException();
	};
}
#endif
