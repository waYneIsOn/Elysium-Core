/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CHAIN
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CHAIN

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::X509Certificates
{
	class ELYSIUM_CORE_API X509Chain sealed
	{
	public:
		X509Chain();
		~X509Chain();
	};
}
#endif
