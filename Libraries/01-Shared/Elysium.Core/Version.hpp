/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_VERSION
#define ELYSIUM_CORE_VERSION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_STRINGVIEW
#include "StringView.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "../Elysium.Core.IO/Stream.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Version final
	{
	public:
		constexpr Version() noexcept;

		constexpr Version(const Elysium::Core::Template::System::uint16_t& Major, const Elysium::Core::Template::System::uint16_t& Minor) noexcept;

		constexpr Version(const Elysium::Core::Template::System::uint16_t& Major, const Elysium::Core::Template::System::uint16_t& Minor,
			const Elysium::Core::Template::System::uint16_t& Build) noexcept;

		constexpr Version(const Elysium::Core::Template::System::uint16_t& Major, const Elysium::Core::Template::System::uint16_t& Minor,
			const Elysium::Core::Template::System::uint16_t& Build, const Elysium::Core::Template::System::uint16_t& Revision) noexcept;

		constexpr Version(const Version& Source) noexcept;

		constexpr Version(Version&& Right) noexcept;

		constexpr ~Version() noexcept = default;
	public:
		constexpr Version& operator=(const Version& Other) noexcept;

		constexpr Version& operator=(Version&& Right) noexcept;
	public:
		constexpr bool operator==(const Version& Other) const noexcept;

		constexpr bool operator!=(const Version& Other) const noexcept;

		constexpr bool operator<(const Version& Other) const noexcept;

		constexpr bool operator>(const Version& Other) const noexcept;

		constexpr bool operator<=(const Version& Other) const noexcept;

		constexpr bool operator>=(const Version& Other) const noexcept;
	public:
		/*
		friend Elysium::Core::IO::Stream& operator<<(Elysium::Core::IO::Stream& Target, const Elysium::Core::Version& Version);

		friend Elysium::Core::IO::Stream& operator>>(Elysium::Core::IO::Stream& Source, const Elysium::Core::Version& Version);
		*/
	public:
		constexpr const Elysium::Core::Template::System::uint16_t GetMajor() const noexcept;

		constexpr const Elysium::Core::Template::System::uint16_t GetMinor() const noexcept;

		constexpr const Elysium::Core::Template::System::uint16_t GetBuild() const noexcept;

		constexpr const Elysium::Core::Template::System::uint16_t GetRevision() const noexcept;
	public:
		static Version Parse(Elysium::Core::Utf8String::ConstCharacterPointer Input);

		static Version Parse(const Elysium::Core::Utf8StringView Input);
	public:
		Elysium::Core::Utf8String ToString() const;

		Elysium::Core::Utf8String ToString(const Elysium::Core::Template::System::uint8_t Fields) const;
	private:
		constexpr const Elysium::Core::uint8_t Compare(const Version& Other) const noexcept;
	private:
		inline static constexpr Elysium::Core::Template::System::uint16_t const Undefined = -1_ui16;

		inline static constexpr Elysium::Core::Utf8String::ConstCharacter Delimiter = u8'.';
	private:
		Elysium::Core::Template::System::uint16_t _Major;
		Elysium::Core::Template::System::uint16_t _Minor;
		Elysium::Core::Template::System::uint16_t _Build;
		Elysium::Core::Template::System::uint16_t _Revision;
	};

	inline constexpr Elysium::Core::Version::Version() noexcept
		: _Major(0), _Minor(0), _Build(Undefined), _Revision(Undefined)
	{	}

	inline constexpr Elysium::Core::Version::Version(const Elysium::Core::Template::System::uint16_t& Major, const Elysium::Core::Template::System::uint16_t& Minor) noexcept
		: _Major(Major), _Minor(Minor), _Build(Undefined), _Revision(Undefined)
	{	}

	inline constexpr Elysium::Core::Version::Version(const Elysium::Core::Template::System::uint16_t& Major, const Elysium::Core::Template::System::uint16_t& Minor, const Elysium::Core::Template::System::uint16_t& Build) noexcept
		: _Major(Major), _Minor(Minor), _Build(Build), _Revision(Undefined)
	{	}

	inline constexpr Elysium::Core::Version::Version(const Elysium::Core::Template::System::uint16_t& Major, const Elysium::Core::Template::System::uint16_t& Minor, const Elysium::Core::Template::System::uint16_t& Build, const Elysium::Core::Template::System::uint16_t& Revision) noexcept
		: _Major(Major), _Minor(Minor), _Build(Build), _Revision(Revision)
	{	}

	inline constexpr Elysium::Core::Version::Version(const Version& Source) noexcept
		: _Major(Source._Major), _Minor(Source._Minor), _Build(Source._Build), _Revision(Source._Revision)
	{	}

	inline constexpr Elysium::Core::Version::Version(Version&& Right) noexcept
		: _Major(0), _Minor(0), _Build(Undefined), _Revision(Undefined)
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}

	inline constexpr Version& Elysium::Core::Version::operator=(const Version& Other) noexcept
	{
		if (this != &Other)
		{
			_Major = Other._Major;
			_Minor = Other._Minor;
			_Build = Other._Build;
			_Revision = Other._Revision;
		}
		return *this;
	}

	inline constexpr Version& Elysium::Core::Version::operator=(Version&& Right) noexcept
	{
		if (this != &Right)
		{
			_Major = Elysium::Core::Template::Functional::Move(Right._Major);
			_Minor = Elysium::Core::Template::Functional::Move(Right._Minor);
			_Build = Elysium::Core::Template::Functional::Move(Right._Build);
			_Revision = Elysium::Core::Template::Functional::Move(Right._Revision);

			Right._Major = 0;
			Right._Minor = 0;
			Right._Build = Undefined;
			Right._Revision = Undefined;
		}
		return *this;
	}

	inline constexpr bool Elysium::Core::Version::operator==(const Version& Other) const noexcept
	{
		return Compare(Other) == 0_ui8;
	}

	inline constexpr bool Elysium::Core::Version::operator!=(const Version& Other) const noexcept
	{
		return Compare(Other) != 0_ui8;
	}

	inline constexpr bool Elysium::Core::Version::operator<(const Version& Other) const noexcept
	{
		return Compare(Other) < 0_ui8;
	}

	inline constexpr bool Elysium::Core::Version::operator>(const Version& Other) const noexcept
	{
		return Compare(Other) > 0_ui8;
	}

	inline constexpr bool Elysium::Core::Version::operator<=(const Version& Other) const noexcept
	{
		return Compare(Other) <= 0_ui8;
	}

	inline constexpr bool Elysium::Core::Version::operator>=(const Version& Other) const noexcept
	{
		return Compare(Other) >= 0_ui8;
	}

	inline constexpr const Elysium::Core::Template::System::uint16_t Elysium::Core::Version::GetMajor() const noexcept
	{
		return _Major;
	}

	inline constexpr const Elysium::Core::Template::System::uint16_t Elysium::Core::Version::GetMinor() const noexcept
	{
		return _Minor;
	}

	inline constexpr const Elysium::Core::Template::System::uint16_t Elysium::Core::Version::GetBuild() const noexcept
	{
		return _Build;
	}

	inline constexpr const Elysium::Core::Template::System::uint16_t Elysium::Core::Version::GetRevision() const noexcept
	{
		return _Revision;
	}

	inline constexpr const Elysium::Core::uint8_t Elysium::Core::Version::Compare(const Version& Other) const noexcept
	{
		if (this == &Other)
		{
			return 0;
		}

		if (_Major != Other._Major)
		{
			if (_Major > Other._Major)
			{
				return 1;
			}
			else
			{
				return -1;
			}
		}

		if (_Minor != Other._Minor)
		{
			if (_Minor > Other._Minor)
			{
				return 1;
			}
			else
			{
				return -1;
			}
		}

		if (_Build != Other._Build)
		{
			if (_Build > Other._Build)
			{
				return 1;
			}
			else
			{
				return -1;
			}
		}

		if (_Revision != Other._Revision)
		{
			if (_Revision > Other._Revision)
			{
				return 1;
			}
			else
			{
				return -1;
			}
		}

		return 0;
	}
}
#endif
