/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_TEXT_STRINGBUILDER
#define ELYSIUM_CORE_TEXT_STRINGBUILDER

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
		namespace Text
		{
			class ELYSIUM_CORE_API StringBuilder final
			{
			public:
				StringBuilder();
				StringBuilder(const size_t Capacity);
				StringBuilder(const StringBuilder& Value);
				~StringBuilder();

				const size_t GetCapacity() const;
				virtual const size_t GetLength() const;

				void SetLength(const size_t Value);

				void Append(const Elysium::Core::String& Value);
				void Append(const ElysiumChar* Value);

				void ToString(Elysium::Core::String* Output);
			private:
				size_t _Capacity;
				ElysiumChar* _Data;
				size_t _Length;

				void Resize(size_t DesiredMinimumSize);
			};
		}
	}
}
#endif
