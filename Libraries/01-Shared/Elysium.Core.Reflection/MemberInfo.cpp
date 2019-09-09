#include "MemberInfo.hpp"

Elysium::Core::Reflection::MemberInfo::~MemberInfo()
{
}

const Elysium::Core::StringView Elysium::Core::Reflection::MemberInfo::GetName() const
{
	return StringView(_Name);
}

Elysium::Core::Reflection::MemberInfo::MemberInfo()
{
}
