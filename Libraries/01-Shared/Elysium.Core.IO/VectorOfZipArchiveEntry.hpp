/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_COMPRESSION_VECTOROFZIPARCHIVEENTRY
#define ELYSIUM_CORE_IO_COMPRESSION_VECTOROFZIPARCHIVEENTRY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_COMPRESSION_ZIPARCHIVEENTRY
#include "ZipArchiveEntry.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Elysium.Core.Template/Vector.hpp"
#endif

namespace Elysium::Core::IO::Compression
{
	//template class ELYSIUM_CORE_API Elysium::Core::Template::Container::Vector<Elysium::Core::IO::Compression::ZipArchiveEntry>;

	using VectorOfZipArchiveEntry = Elysium::Core::Template::Container::Vector<Elysium::Core::IO::Compression::ZipArchiveEntry>;
}
#endif
