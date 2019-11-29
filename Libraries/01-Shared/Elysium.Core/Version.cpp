#include "Version.hpp"

#ifndef ELYSIUM_CORE_COLLECTIONS_GENERIC_LIST
#include "List.hpp"
#endif

#ifndef ELYSIUM_CORE_CONVERT
#include "Convert.hpp"
#endif

#ifndef ELYSIUM_CORE_ARGUMENTNULLEXCEPTION
#include "ArgumentNullException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "NotImplementedException.hpp"
#endif

using namespace Elysium::Core::Collections::Generic;

Elysium::Core::Version::Version()
	: _Major(0), _Minor(0), _Build(0), _Revision(0)
{
}
Elysium::Core::Version::Version(const uint32_t & Major, const uint32_t & Minor)
	: _Major(Major), _Minor(Minor), _Build(0), _Revision(0)
{
}
Elysium::Core::Version::Version(const uint32_t & Major, const uint32_t & Minor, const uint32_t & Build)
	: _Major(Major), _Minor(Minor), _Build(Build), _Revision(0)
{
}
Elysium::Core::Version::Version(const uint32_t & Major, const uint32_t & Minor, const uint32_t & Build, const uint32_t & Revision)
	: _Major(Major), _Minor(Minor), _Build(Build), _Revision(Revision)
{
}
Elysium::Core::Version::Version(const Version & Source)
	: _Major(Source._Major), _Minor(Source._Minor), _Build(Source._Build), _Revision(Source._Revision)
{
}
Elysium::Core::Version::Version(Version && Right) noexcept
	: _Major(0), _Minor(0), _Build(0), _Revision(0)
{
	*this = std::move(Right);
}
Elysium::Core::Version::~Version()
{
}

Elysium::Core::Version & Elysium::Core::Version::operator=(const Version & Other)
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
Elysium::Core::Version & Elysium::Core::Version::operator=(Version && Right) noexcept
{
	if (this != &Right)
	{
		_Major = std::move(Right._Major);
		_Minor = std::move(Right._Minor);
		_Build = std::move(Right._Build);
		_Revision = std::move(Right._Revision);
	}
	return *this;
}

bool Elysium::Core::Version::operator==(const Version & Other) const
{
	return Compare(Other) == 0;
}
bool Elysium::Core::Version::operator!=(const Version & Other) const
{
	return Compare(Other) != 0;
}
bool Elysium::Core::Version::operator<(const Version & Other) const
{
	return Compare(Other) < 0;
}
bool Elysium::Core::Version::operator>(const Version & Other) const
{
	return Compare(Other) > 0;
}
bool Elysium::Core::Version::operator<=(const Version & Other) const
{
	return Compare(Other) <= 0;
}
bool Elysium::Core::Version::operator>=(const Version & Other) const
{
	return Compare(Other) >= 0;
}

Elysium::Core::IO::Stream & Elysium::Core::operator<<(Elysium::Core::IO::Stream & Target, const Version & Version)
{
	Target << Version._Major << Version._Minor << Version._Build << Version._Revision;
	return Target;
}
Elysium::Core::IO::Stream & Elysium::Core::operator>>(Elysium::Core::IO::Stream & Source, const Version & Version)
{
	Source >> Version._Major;
	Source >> Version._Minor;
	Source >> Version._Build;
	Source >> Version._Revision;
	return Source;
}

const uint32_t Elysium::Core::Version::GetMajor() const
{
	return _Major;
}
const uint32_t Elysium::Core::Version::GetMinor() const
{
	return _Minor;
}
const uint32_t Elysium::Core::Version::GetBuild() const
{
	return _Build;
}
const uint32_t Elysium::Core::Version::GetRevision() const
{
	return _Revision;
}

void Elysium::Core::Version::Parse(const StringView & Input, Version & Result)
{
	List<StringView> Numbers;
	Input.Split(u'.', Numbers);

	const size_t NumberCount = Numbers.GetCount();
	if (NumberCount >= 1)
	{
		Result._Major = Elysium::Core::Convert::ToInt32(&Numbers[0][0], 10);
		//Result._Major = wcstoul(&Numbers[0][0], nullptr, 10);
	}
	if (NumberCount >= 2)
	{
		Result._Major = Elysium::Core::Convert::ToInt32(&Numbers[1][0], 10);
		//Result._Minor = wcstoul(&Numbers[1][0], nullptr, 10);
	}
	if (NumberCount >= 3)
	{
		Result._Major = Elysium::Core::Convert::ToInt32(&Numbers[2][0], 10);
		//Result._Minor = wcstoul(&Numbers[2][0], nullptr, 10);
	}
	if (NumberCount >= 4)
	{
		Result._Major = Elysium::Core::Convert::ToInt32(&Numbers[3][0], 10);
		//Result._Minor = wcstoul(&Numbers[3][0], nullptr, 10);
	}
}
Elysium::Core::Version Elysium::Core::Version::Parse(const StringView & Input)
{
	Version ParsedVersion;
	Parse(Input, ParsedVersion);
	return ParsedVersion;
}

uint32_t Elysium::Core::Version::Compare(const Version & Other) const
{
	if (this != &Other)
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
