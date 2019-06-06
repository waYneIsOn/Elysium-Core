#include "Version.hpp"

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "NotImplementedException.hpp"
#endif

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

void Elysium::Core::Version::Parse(const String & Input, Version * Result)
{
	//Input.Split('.');
	throw NotImplementedException();
}
Elysium::Core::Version Elysium::Core::Version::Parse(const String & Input)
{
	throw NotImplementedException();
}

Elysium::Core::Version & Elysium::Core::Version::operator=(const Version & Value)
{
	if (&Value != this)
	{
		_Major = Value._Major;
		_Minor = Value._Minor;
		_Build = Value._Build;
		_Revision = Value._Revision;
	}

	return *this;
}
