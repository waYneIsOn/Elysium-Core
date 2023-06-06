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
		constexpr AssemblyName(const Utf8String& AssemblyName, const Version& AssemblyVersion);

		constexpr AssemblyName(const AssemblyName& Source);

		constexpr AssemblyName(AssemblyName&& Right) noexcept = delete;

		constexpr ~AssemblyName();
	public:
		constexpr AssemblyName& operator=(const AssemblyName& Source);

		constexpr AssemblyName& operator=(AssemblyName&& Right) noexcept = delete;
	public:
		bool operator==(const AssemblyName& Other) const;

		bool operator!=(const AssemblyName& Other) const;

		bool operator<(const AssemblyName& Other) const;

		bool operator>(const AssemblyName& Other) const;

		bool operator<=(const AssemblyName& Other) const;

		bool operator>=(const AssemblyName& Other) const;
	public:
		const Elysium::Core::Utf8String& GetName() const;

		const Elysium::Core::Version& GetVersion() const;
		/*
		const CultureInfo& GetCultureInfo() const;
		const String& GetFullName() const;
		*/
	private:
		Utf8String _Name;
		Version _Version;
	};
}
#endif
