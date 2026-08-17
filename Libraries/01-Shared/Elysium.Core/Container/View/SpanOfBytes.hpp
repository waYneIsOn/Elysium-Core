/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_CONTAINER_VIEW_SPANOFBYTES
#define ELYSIUM_CORE_CONTAINER_VIEW_SPANOFBYTES

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../../API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VIEW_SPAN
#include "../../../Elysium.Core.Template/Container/View/Span.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../Elysium.Core.Template/System/Primitives.hpp"
#endif

namespace Elysium::Core::Container
{
	template class ELYSIUM_CORE_API Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte>;

	using SpanOfByte = Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte>;
}
#endif
