/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_LEMPELZIV_LZ77
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_LEMPELZIV_LZ77

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::LempelZiv
{
	template<class T>
	class LZ77
	{
		using ConstPointer = const T*;
	public:
		static void Compress(ConstPointer Input, const Elysium::Core::Template::System::size Length)
		{
			Elysium::Core::Template::System::size RemainingBufferLength = 0;

			while (RemainingBufferLength > 0)
			{
				bool DictionaryMatchFound = false;
				if(DictionaryMatchFound)
				{

				}
				else
				{

				}
			}
		}
	private:
		Elysium::Core::Template::System::uint8_t _BufferSize = 63;
		Elysium::Core::Template::System::uint16_t _DictionarySize = 32767;
	};
}
#endif
