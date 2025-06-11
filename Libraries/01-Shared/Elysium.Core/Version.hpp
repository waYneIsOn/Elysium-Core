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

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Version final
	{
	public:
		constexpr Version() noexcept
			: _Major(Undefined), _Minor(Undefined), _Build(Undefined), _Revision(Undefined)
		{ }

		constexpr Version(const Elysium::Core::uint16_t& Major, const Elysium::Core::uint16_t& Minor) noexcept
			: _Major(Major), _Minor(Minor), _Build(Undefined), _Revision(Undefined)
		{ }

		constexpr Version(const Elysium::Core::uint16_t& Major, const Elysium::Core::uint16_t& Minor, const Elysium::Core::uint16_t& Build) noexcept
			: _Major(Major), _Minor(Minor), _Build(Build), _Revision(0xFFFF)
		{ }

		constexpr Version(const Elysium::Core::uint16_t& Major, const Elysium::Core::uint16_t& Minor, const Elysium::Core::uint16_t& Build, const Elysium::Core::uint16_t& Revision) noexcept
			: _Major(Major), _Minor(Minor), _Build(Build), _Revision(Revision)
		{ }

		constexpr Version(const Version& Source) noexcept
			: _Major(Source._Major), _Minor(Source._Minor), _Build(Source._Build), _Revision(Source._Revision)
		{ }

		constexpr Version(Version&& Right) noexcept
			: _Major(0xFFFF), _Minor(0xFFFF), _Build(0xFFFF), _Revision(0xFFFF)
		{
			*this = Elysium::Core::Template::Functional::Move(Right);
		}

		constexpr ~Version() noexcept = default;
	public:
		constexpr Version& operator=(const Version& Other)
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

		constexpr Version& operator=(Version&& Right) noexcept
		{
			if (this != &Right)
			{
				_Major = Elysium::Core::Template::Functional::Move(Right._Major);
				_Minor = Elysium::Core::Template::Functional::Move(Right._Minor);
				_Build = Elysium::Core::Template::Functional::Move(Right._Build);
				_Revision = Elysium::Core::Template::Functional::Move(Right._Revision);

				Right._Major = 0xFFFF;
				Right._Minor = 0xFFFF;
				Right._Build = 0xFFFF;
				Right._Revision = 0xFFFF;
			}
			return *this;
		}
	public:
		constexpr bool operator==(const Version& Other) const
		{
			return Compare(Other) == 0_ui8;
		}

		constexpr bool operator!=(const Version& Other) const
		{
			return Compare(Other) != 0_ui8;
		}

		constexpr bool operator<(const Version& Other) const
		{
			return Compare(Other) < 0_ui8;
		}

		constexpr bool operator>(const Version& Other) const
		{
			return Compare(Other) > 0_ui8;
		}

		constexpr bool operator<=(const Version& Other) const
		{
			return Compare(Other) <= 0_ui8;
		}

		constexpr bool operator>=(const Version& Other) const
		{
			return Compare(Other) >= 0_ui8;
		}
		/*
		friend Elysium::Core::IO::Stream& operator<<(Elysium::Core::IO::Stream& Target, const Elysium::Core::Version& Version);
		friend Elysium::Core::IO::Stream& operator>>(Elysium::Core::IO::Stream& Source, const Elysium::Core::Version& Version);
		*/
	public:
		constexpr const Elysium::Core::uint16_t GetMajor() const
		{
			return _Major;
		}

		constexpr const Elysium::Core::uint16_t GetMinor() const
		{
			return _Minor;
		}

		constexpr const Elysium::Core::uint16_t GetBuild() const
		{
			return _Build;
		}

		constexpr const Elysium::Core::uint16_t GetRevision() const
		{
			return _Revision;
		}
	public:
		static Version Parse(const Utf8String& Input);
		
		static Version Parse(const Utf8StringView Input);
	public:
		const Utf8String ToString();
	private:
		constexpr const Elysium::Core::uint8_t Compare(const Version& Other) const
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
	private:
		inline static constexpr Elysium::Core::uint16_t const Undefined = -1_ui16;

		inline static constexpr Elysium::Core::Utf8String::ConstCharacter Delimiter = u8'.';
	private:
		Elysium::Core::uint16_t _Major;
		Elysium::Core::uint16_t _Minor;
		Elysium::Core::uint16_t _Build;
		Elysium::Core::uint16_t _Revision;
	};
}
#endif
