#include "KeySizes.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Security::Cryptography::KeySizes::KeySizes(Elysium::Core::uint32_t MinimumSize, Elysium::Core::uint32_t MaximumSize, Elysium::Core::uint32_t SkipSize)
	: _MinimumSize(MinimumSize), _MaximumSize(MaximumSize), _SkipSize(SkipSize)
{ }

Elysium::Core::Security::Cryptography::KeySizes::~KeySizes()
{ }

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
