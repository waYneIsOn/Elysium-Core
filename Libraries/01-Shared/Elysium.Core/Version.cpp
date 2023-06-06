#include "Version.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CONVERT
#include "../Elysium.Core.Template/Convert.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Elysium.Core.Template/Vector.hpp"
#endif

constexpr Elysium::Core::Version::Version()
	: _Major(Undefined), _Minor(Undefined), _Build(Undefined), _Revision(Undefined)
{ }

constexpr Elysium::Core::Version::Version(const Elysium::Core::uint16_t& Major, const Elysium::Core::uint16_t& Minor)
	: _Major(Major), _Minor(Minor), _Build(Undefined), _Revision(Undefined)
{ }

constexpr Elysium::Core::Version::Version(const Elysium::Core::uint16_t& Major, const Elysium::Core::uint16_t& Minor, const Elysium::Core::uint16_t& Build)
	: _Major(Major), _Minor(Minor), _Build(Build), _Revision(Undefined)
{ }

constexpr Elysium::Core::Version::Version(const Elysium::Core::uint16_t& Major, const Elysium::Core::uint16_t& Minor, const Elysium::Core::uint16_t& Build, const Elysium::Core::uint16_t& Revision)
	: _Major(Major), _Minor(Minor), _Build(Build), _Revision(Revision)
{ }

constexpr Elysium::Core::Version::Version(const Version & Source)
	: _Major(Source._Major), _Minor(Source._Minor), _Build(Source._Build), _Revision(Source._Revision)
{ }

constexpr Elysium::Core::Version::Version(Version && Right) noexcept
	: _Major(Undefined), _Minor(Undefined), _Build(Undefined), _Revision(Undefined)
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}

constexpr Elysium::Core::Version::~Version()
{ }

constexpr Elysium::Core::Version & Elysium::Core::Version::operator=(const Version & Other)
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

constexpr Elysium::Core::Version & Elysium::Core::Version::operator=(Version && Right) noexcept
{
	if (this != &Right)
	{
		_Major = Elysium::Core::Template::Functional::Move(Right._Major);
		_Minor = Elysium::Core::Template::Functional::Move(Right._Minor);
		_Build = Elysium::Core::Template::Functional::Move(Right._Build);
		_Revision = Elysium::Core::Template::Functional::Move(Right._Revision);

		Right._Major = Undefined;
		Right._Minor = Undefined;
		Right._Build = Undefined;
		Right._Revision = Undefined;
	}
	return *this;
}

bool Elysium::Core::Version::operator==(const Version & Other) const
{
	return Compare(Other) == 0_ui8;
}

bool Elysium::Core::Version::operator!=(const Version & Other) const
{
	return Compare(Other) != 0_ui8;
}

bool Elysium::Core::Version::operator<(const Version & Other) const
{
	return Compare(Other) < 0_ui8;
}

bool Elysium::Core::Version::operator>(const Version & Other) const
{
	return Compare(Other) > 0_ui8;
}

bool Elysium::Core::Version::operator<=(const Version & Other) const
{
	return Compare(Other) <= 0_ui8;
}

bool Elysium::Core::Version::operator>=(const Version & Other) const
{
	return Compare(Other) >= 0_ui8;
}
/*
Elysium::Core::IO::Stream & Elysium::Core::operator<<(Elysium::Core::IO::Stream & Target, const Elysium::Core::Version & Version)
{
	Target << Version._Major << Version._Minor << Version._Build << Version._Revision;
	return Target;
}
Elysium::Core::IO::Stream & Elysium::Core::operator>>(Elysium::Core::IO::Stream & Source, const Elysium::Core::Version & Version)
{
	Source >> Version._Major;
	Source >> Version._Minor;
	Source >> Version._Build;
	Source >> Version._Revision;
	return Source;
}
*/
Elysium::Core::Version Elysium::Core::Version::Parse(const Utf8String& Input)
{
	return Parse(Utf8StringView(Input));
}

Elysium::Core::Version Elysium::Core::Version::Parse(const Utf8StringView Input)
{
	Template::Container::Vector<Utf8StringView> Numbers = Input.Split(Delimiter);

	const Elysium::Core::size NumberCount = Numbers.GetLength();
	if (NumberCount > 0)
	{
		return Version(Elysium::Core::Template::Text::Convert<char8_t>::ToUInt16(&Numbers[0][0], Numbers[0].GetLength(), 10), 0);
	}
	if (NumberCount > 1)
	{
		return Version(
			Elysium::Core::Template::Text::Convert<char8_t>::ToUInt16(&Numbers[0][0], Numbers[0].GetLength(), 10),
			Elysium::Core::Template::Text::Convert<char8_t>::ToUInt16(&Numbers[1][0], Numbers[1].GetLength(), 10)
		);
	}
	if (NumberCount > 2)
	{
		return Version(
			Elysium::Core::Template::Text::Convert<char8_t>::ToUInt16(&Numbers[0][0], Numbers[0].GetLength(), 10),
			Elysium::Core::Template::Text::Convert<char8_t>::ToUInt16(&Numbers[1][0], Numbers[1].GetLength(), 10),
			Elysium::Core::Template::Text::Convert<char8_t>::ToUInt16(&Numbers[2][0], Numbers[2].GetLength(), 10)
		);
	}
	if (NumberCount > 3)
	{
		return Version(
			Elysium::Core::Template::Text::Convert<char8_t>::ToUInt16(&Numbers[0][0], Numbers[0].GetLength(), 10),
			Elysium::Core::Template::Text::Convert<char8_t>::ToUInt16(&Numbers[1][0], Numbers[1].GetLength(), 10),
			Elysium::Core::Template::Text::Convert<char8_t>::ToUInt16(&Numbers[2][0], Numbers[2].GetLength(), 10),
			Elysium::Core::Template::Text::Convert<char8_t>::ToUInt16(&Numbers[3][0], Numbers[3].GetLength(), 10)
		);
	}
	else
	{
		return Version();
	}
}

const Elysium::Core::uint16_t Elysium::Core::Version::GetMajor() const
{
	return _Major;
}

const Elysium::Core::uint16_t Elysium::Core::Version::GetMinor() const
{
	return _Minor;
}

const Elysium::Core::uint16_t Elysium::Core::Version::GetBuild() const
{
	return _Build;
}

const Elysium::Core::uint16_t Elysium::Core::Version::GetRevision() const
{
	return _Revision;
}

const Elysium::Core::Utf8String Elysium::Core::Version::ToString()
{
	Elysium::Core::size DelimiterLength = Elysium::Core::Utf8String::CharacterTraits::MinimumByteLength;

	const Elysium::Core::Utf8String Major = Elysium::Core::Template::Text::Convert<char8_t>::ToString(_Major);
	const Elysium::Core::size MajorLength = Major.GetLength();

	const Elysium::Core::Utf8String Minor = Elysium::Core::Template::Text::Convert<char8_t>::ToString(_Minor);
	const Elysium::Core::size MinorLength = Minor.GetLength();

	if (_Build != Undefined)
	{
		DelimiterLength += Elysium::Core::Utf8String::CharacterTraits::MinimumByteLength;
	}
	const Elysium::Core::Utf8String Build = DelimiterLength == Elysium::Core::Utf8String::CharacterTraits::MinimumByteLength * 2 ?
		Elysium::Core::Utf8String() : Elysium::Core::Template::Text::Convert<char8_t>::ToString(_Build);
	const Elysium::Core::size BuildLength = Build.GetLength();

	if (_Revision != Undefined)
	{
		DelimiterLength += Elysium::Core::Utf8String::CharacterTraits::MinimumByteLength;
	}
	const Elysium::Core::Utf8String Revision = DelimiterLength == Elysium::Core::Utf8String::CharacterTraits::MinimumByteLength * 3 ?
		Elysium::Core::Utf8String() : Elysium::Core::Template::Text::Convert<char8_t>::ToString(_Revision);
	const Elysium::Core::size RevisionLength = Revision.GetLength();

	const Elysium::Core::size RequiredLength = DelimiterLength + MajorLength + MinorLength + BuildLength + RevisionLength;

	Elysium::Core::Utf8String Result = Elysium::Core::Utf8String(RequiredLength);
	Elysium::Core::size ResultIndex = 0;
	for (Elysium::Core::size i = 0; i < MajorLength; i++)
	{
		Result[ResultIndex++] = Major[i];
	}
	Result[ResultIndex++] = Delimiter;
	for (Elysium::Core::size i = 0; i < MinorLength; i++)
	{
		Result[ResultIndex++] = Minor[i];
	}
	if (DelimiterLength > Elysium::Core::Utf8String::CharacterTraits::MinimumByteLength)
	{
		Result[ResultIndex++] = Delimiter;
		for (Elysium::Core::size i = 0; i < BuildLength; i++)
		{
			Result[ResultIndex++] = Build[i];
		}
	}
	if (DelimiterLength > Elysium::Core::Utf8String::CharacterTraits::MinimumByteLength * 2)
	{
		Result[ResultIndex++] = Delimiter;
		for (Elysium::Core::size i = 0; i < RevisionLength; i++)
		{
			Result[ResultIndex++] = Revision[i];
		}
	}

	return Result;
}

const Elysium::Core::uint8_t Elysium::Core::Version::Compare(const Version & Other) const
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
