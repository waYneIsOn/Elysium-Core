/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_WEB_MIMETYPEMAP
#define ELYSIUM_CORE_WEB_MIMETYPEMAP

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_WEB_API
#include "API.hpp"
#endif

namespace Elysium::Core::Web
{
	class ELYSIUM_CORE_WEB_API MimeTypeMap final
	{
	public:
		MimeTypeMap() = delete;
		MimeTypeMap(const MimeTypeMap& Source) = delete;
		MimeTypeMap(MimeTypeMap&& Right) = delete;
		~MimeTypeMap() = delete;
	private:
	};
}
#endif
