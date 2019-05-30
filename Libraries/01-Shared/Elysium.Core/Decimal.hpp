/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DECIMAL
#define ELYSIUM_CORE_DECIMAL

#ifndef ELYSIUM_CORE_EXPORT
#include "Export.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "Byte.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		class EXPORT Decimal final
		{
		public:
			Decimal();
			Decimal(const float& Value);
			Decimal(const double& Value);
			Decimal(const __int64& HighPart, const __int64& LowPart);
			Decimal(const Decimal& Value);
			~Decimal();

			const __int64* GetHighPart() const;
			const __int64* GetLowPart() const;
		private:
			byte _Data[16];
		};
	}
}
#endif
