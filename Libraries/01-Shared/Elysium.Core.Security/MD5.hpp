/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_MD5
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_MD5

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_HASHALGORITHM
#include "HashAlgorithm.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Security
		{
			namespace Cryptography
			{
				class ELYSIUM_CORE_API MD5 : public HashAlgorithm
				{
				public:
					~MD5();
				protected:
					MD5();
				};
			}
		}
	}
}
#endif
