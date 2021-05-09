/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_COMPRESSION_GZIPSTREAM_LISTOFZIPARCHIVEENTRY
#define ELYSIUM_CORE_IO_COMPRESSION_GZIPSTREAM_LISTOFZIPARCHIVEENTRY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_COMPRESSION_ZIPARCHIVEENTRY
#include "ZipArchiveEntry.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "List.hpp"
#endif

template class ELYSIUM_CORE_API Elysium::Core::Collections::Template::List<Elysium::Core::IO::Compression::ZipArchiveEntry>;
#endif
