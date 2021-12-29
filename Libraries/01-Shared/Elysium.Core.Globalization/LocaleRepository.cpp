#include "LocaleRepository.hpp"

#if defined ELYSIUM_CORE_OS_REQUIRES_FALLBACK_ON_GLOBALIZATION
const Elysium::Core::int32_t Elysium::Core::Globalization::Internal::Fallback::LocaleRepository::GetIdFromName(const Elysium::Core::Utf8String& Name)
{
	throw 1;
}

const Elysium::Core::Utf8String Elysium::Core::Globalization::Internal::Fallback::LocaleRepository::GetNameFromId(const Elysium::Core::int32_t Name)
{
	throw 1;
}
#endif
