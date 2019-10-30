/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_REFLECTION_MODULE
#define ELYSIUM_CORE_REFLECTION_MODULE

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Reflection
		{
			class ELYSIUM_CORE_API Module
			{
			public:
				Module(const Module& Source);
				Module(Module&& Right) noexcept;
				virtual ~Module();

				Module& operator=(const Module& Source);
				Module& operator=(Module&& Right) noexcept;

				bool operator==(const Module& Other) const;
				bool operator!=(const Module& Other) const;
				bool operator<(const Module& Other) const;
				bool operator>(const Module& Other) const;
				bool operator<=(const Module& Other) const;
				bool operator>=(const Module& Other) const;

				const String& GetName() const;
			protected:
				Module();

				Elysium::Core::String _Name;
				//Assembly& _Assembly;
			};
		}
	}
}
#endif
