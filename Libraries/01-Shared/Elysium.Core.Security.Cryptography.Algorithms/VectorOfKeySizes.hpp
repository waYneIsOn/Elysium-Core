/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_VECTOROFKEYSIZES
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_VECTOROFKEYSIZES

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Elysium.Core.Template/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_KEYSIZES
#include "KeySizes.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Container
{
	template class ELYSIUM_CORE_SECURITY_API Elysium::Core::Template::Container::Vector<KeySizes>;

	using VectorOfKeySizes = Elysium::Core::Template::Container::Vector<KeySizes>;
}
#endif
