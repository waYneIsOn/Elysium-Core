/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#define ELYSIUM_CORE_TEXT_ENCODING

#ifndef ELYSIUM_CORE_EXPORT
#include "../Elysium.Core/Export.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Text
		{
			class EXPORT Encoding
			{
			public:
				~Encoding();
			protected:
				Encoding();
				Encoding(int CodePage);
			private:
				int _CodePage;
			};
		}
	}
}
#endif
