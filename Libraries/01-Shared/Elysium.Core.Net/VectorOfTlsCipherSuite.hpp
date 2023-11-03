/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SECURITY_CONTAINER_VECTOROFTLSCIPHERSUITE
#define ELYSIUM_CORE_NET_SECURITY_CONTAINER_VECTOROFTLSCIPHERSUITE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_NET_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Elysium.Core.Template/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SECURITY_TLSCIPHERSUITE
#include "TlsCipherSuite.hpp"
#endif

namespace Elysium::Core::Net::Security::Container
{
	template class ELYSIUM_CORE_NET_API Elysium::Core::Template::Container::Vector<TlsCipherSuite>;

	using VectorOfTlsCipherSuite = Elysium::Core::Template::Container::Vector<TlsCipherSuite>;
}
#endif
