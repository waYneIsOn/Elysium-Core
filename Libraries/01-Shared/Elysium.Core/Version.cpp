#include "Version.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CONVERT
#include "../Elysium.Core.Template/Text/Convert.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Elysium.Core.Template/Vector.hpp"
#endif

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

Elysium::Core::Version Elysium::Core::Version::Parse(Elysium::Core::Utf8String::ConstCharacterPointer Input)
{
	return Parse(Elysium::Core::Utf8StringView(Input));
}

Elysium::Core::Version Elysium::Core::Version::Parse(const Elysium::Core::Utf8StringView Input)
{
	Elysium::Core::Template::Container::Vector<Utf8StringView> Numbers = Input.Split(Delimiter);

	const Elysium::Core::Template::System::size NumberCount = Numbers.GetLength();
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

Elysium::Core::Utf8String Elysium::Core::Version::ToString() const
{
	Elysium::Core::Template::System::size DelimiterLength = Elysium::Core::Utf8String::CharacterTraits::MinimumByteLength;

	const Elysium::Core::Utf8String Major = Elysium::Core::Template::Text::Convert<char8_t>::ToString(_Major);
	const Elysium::Core::Template::System::size MajorLength = Major.GetLength();

	const Elysium::Core::Utf8String Minor = Elysium::Core::Template::Text::Convert<char8_t>::ToString(_Minor);
	const Elysium::Core::Template::System::size MinorLength = Minor.GetLength();

	if (_Build != Undefined)
	{
		DelimiterLength += Elysium::Core::Utf8String::CharacterTraits::MinimumByteLength;
	}
	const Elysium::Core::Utf8String Build = DelimiterLength == Elysium::Core::Utf8String::CharacterTraits::MinimumByteLength * 2 ?
		Elysium::Core::Utf8String() : Elysium::Core::Template::Text::Convert<char8_t>::ToString(_Build);
	const Elysium::Core::Template::System::size BuildLength = Build.GetLength();

	if (_Revision != Undefined)
	{
		DelimiterLength += Elysium::Core::Utf8String::CharacterTraits::MinimumByteLength;
	}
	const Elysium::Core::Utf8String Revision = DelimiterLength == Elysium::Core::Utf8String::CharacterTraits::MinimumByteLength * 3 ?
		Elysium::Core::Utf8String() : Elysium::Core::Template::Text::Convert<char8_t>::ToString(_Revision);
	const Elysium::Core::Template::System::size RevisionLength = Revision.GetLength();

	const Elysium::Core::Template::System::size RequiredLength = DelimiterLength + MajorLength + MinorLength + BuildLength + RevisionLength;

	Elysium::Core::Utf8String Result = Elysium::Core::Utf8String(RequiredLength);
	Elysium::Core::Template::System::size ResultIndex = 0;
	for (Elysium::Core::Template::System::size i = 0; i < MajorLength; i++)
	{
		Result[ResultIndex++] = Major[i];
	}
	Result[ResultIndex++] = Delimiter;
	for (Elysium::Core::Template::System::size i = 0; i < MinorLength; i++)
	{
		Result[ResultIndex++] = Minor[i];
	}
	if (DelimiterLength > Elysium::Core::Utf8String::CharacterTraits::MinimumByteLength)
	{
		Result[ResultIndex++] = Delimiter;
		for (Elysium::Core::Template::System::size i = 0; i < BuildLength; i++)
		{
			Result[ResultIndex++] = Build[i];
		}
	}
	if (DelimiterLength > Elysium::Core::Utf8String::CharacterTraits::MinimumByteLength * 2)
	{
		Result[ResultIndex++] = Delimiter;
		for (Elysium::Core::Template::System::size i = 0; i < RevisionLength; i++)
		{
			Result[ResultIndex++] = Revision[i];
		}
	}

	return Result;
}

Elysium::Core::Utf8String Elysium::Core::Version::ToString(const Elysium::Core::Template::System::uint8_t Fields) const
{
	if (Fields == 0 || Fields > 4)
	{
		return Elysium::Core::Utf8String();
	}

	


	return Elysium::Core::Utf8String();
}
