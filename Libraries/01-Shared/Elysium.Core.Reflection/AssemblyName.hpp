/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_REFLECTION_ASSEMBLYNAME
#define ELYSIUM_CORE_REFLECTION_ASSEMBLYNAME

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_VERSION
#include "../Elysium.Core/Version.hpp"
#endif

namespace Elysium::Core::Reflection
{
	class ELYSIUM_CORE_API AssemblyName final
	{
	public:
		AssemblyName();
		AssemblyName(const String& AssemblyName, const String& CodeBase, const Version& AssemblyVersion);
		AssemblyName(const AssemblyName& Source);
		AssemblyName(AssemblyName&& Right) noexcept;
		~AssemblyName();

		AssemblyName& operator=(const AssemblyName& Source);
		AssemblyName& operator=(AssemblyName&& Right) noexcept;

		bool operator==(const AssemblyName& Other) const;
		bool operator!=(const AssemblyName& Other) const;
		bool operator<(const AssemblyName& Other) const;
		bool operator>(const AssemblyName& Other) const;
		bool operator<=(const AssemblyName& Other) const;
		bool operator>=(const AssemblyName& Other) const;

		const String& GetCodeBase() const;
		const String& GetName() const;
		const Version& GetVersion() const;
		/*
		const CultureInfo& GetCultureInfo() const;
		const String& GetFullName() const;
		*/
	private:
		String _Name;
		String _CodeBase;	// Location (Folder)
		Version _Version;
	};
}
#endif
