#include "KeySizes.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::Security::Cryptography::KeySizes::KeySizes(Elysium::Core::uint32_t MinimumSize, Elysium::Core::uint32_t MaximumSize, Elysium::Core::uint32_t SkipSize)
	: _MinimumSize(MinimumSize), _MaximumSize(MaximumSize), _SkipSize(SkipSize)
{ }
Elysium::Core::Security::Cryptography::KeySizes::KeySizes(const KeySizes & Source)
	: _MinimumSize(Source._MinimumSize), _MaximumSize(Source._MaximumSize), _SkipSize(Source._SkipSize)
{ }
Elysium::Core::Security::Cryptography::KeySizes::KeySizes(KeySizes && Right) noexcept
	: _MinimumSize(0), _MaximumSize(0), _SkipSize(0)
{
	*this = std::move(Right);
}
Elysium::Core::Security::Cryptography::KeySizes::~KeySizes()
{ }

Elysium::Core::Security::Cryptography::KeySizes & Elysium::Core::Security::Cryptography::KeySizes::operator=(const KeySizes & Source)
{
	if (this != &Source)
	{
		_MinimumSize = Source._MinimumSize;
		_MaximumSize = Source._MaximumSize;
		_SkipSize = Source._SkipSize;
	}
	return *this;
}
Elysium::Core::Security::Cryptography::KeySizes & Elysium::Core::Security::Cryptography::KeySizes::operator=(KeySizes && Right) noexcept
{
	if (this != &Right)
	{
		_MinimumSize = std::move(Right._MinimumSize);
		_MaximumSize = std::move(Right._MaximumSize);
		_SkipSize = std::move(Right._SkipSize);
	}
	return *this;
}

const Elysium::Core::uint32_t Elysium::Core::Security::Cryptography::KeySizes::GetMinimumSize() const
{
	return _MinimumSize;
}
const Elysium::Core::uint32_t Elysium::Core::Security::Cryptography::KeySizes::GetMaximumSize() const
{
	return _MaximumSize;
}
const Elysium::Core::uint32_t Elysium::Core::Security::Cryptography::KeySizes::GetSkipSize() const
{
	return _SkipSize;
}

Elysium::Core::Security::Cryptography::KeySizes::KeySizes()
	: _MinimumSize(0), _MaximumSize(0), _SkipSize(0)
{ }
