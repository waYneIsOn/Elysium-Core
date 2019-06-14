#include "Version.hpp"

#ifndef ELYSIUM_CORE_COLLECTIONS_GENERIC_LIST
#include "List.hpp"
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
Elysium::Core::Version::Version(const unsigned int & Major, const unsigned int & Minor)
	: _Major(Major), _Minor(Minor), _Build(0), _Revision(0)
{
}
Elysium::Core::Version::Version(const unsigned int & Major, const unsigned int & Minor, const unsigned int & Build)
	: _Major(Major), _Minor(Minor), _Build(Build), _Revision(0)
{
}
Elysium::Core::Version::Version(const unsigned int & Major, const unsigned int & Minor, const unsigned int & Build, const unsigned int & Revision)
	: _Major(Major), _Minor(Minor), _Build(Build), _Revision(Revision)
{
}
Elysium::Core::Version::~Version()
{
}

const unsigned int Elysium::Core::Version::GetMajor() const
{
	return _Major;
}
const unsigned int Elysium::Core::Version::GetMinor() const
{
	return _Minor;
}
const unsigned int Elysium::Core::Version::GetBuild() const
{
	return _Build;
}
const unsigned int Elysium::Core::Version::GetRevision() const
{
	return _Revision;
}

void Elysium::Core::Version::Parse(const StringView * Input, Version * Result)
{
	if (Result == nullptr)
	{
		throw ArgumentNullException(L"Result");
	}

	List<StringView> Numbers;
	Input->Split(L'.', &Numbers);

	const size_t NumberCount = Numbers.GetCount();
	if (NumberCount >= 1)
	{
		Result->_Major = wcstoul(&Numbers[0][0], nullptr, 10);
	}
	if (NumberCount >= 2)
	{
		Result->_Minor = wcstoul(&Numbers[1][0], nullptr, 10);
	}
	if (NumberCount >= 3)
	{
		Result->_Minor = wcstoul(&Numbers[2][0], nullptr, 10);
	}
	if (NumberCount >= 4)
	{
		Result->_Minor = wcstoul(&Numbers[3][0], nullptr, 10);
	}
}
Elysium::Core::Version Elysium::Core::Version::Parse(const StringView * Input)
{
	Version ParsedVersion;
	Parse(Input, &ParsedVersion);
	return ParsedVersion;
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

bool Elysium::Core::Version::operator==(const Version & Other)
{
	return Compare(Other) == 0;
}
bool Elysium::Core::Version::operator!=(const Version & Other)
{
	return Compare(Other) != 0;
}
bool Elysium::Core::Version::operator<(const Version & Other)
{
	return Compare(Other) < 0;
}
bool Elysium::Core::Version::operator>(const Version & Other)
{
	return Compare(Other) > 0;
}
bool Elysium::Core::Version::operator<=(const Version & Other)
{
	return Compare(Other) <= 0;
}
bool Elysium::Core::Version::operator>=(const Version & Other)
{
	return Compare(Other) >= 0;
}

int Elysium::Core::Version::Compare(const Version & Other)
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
