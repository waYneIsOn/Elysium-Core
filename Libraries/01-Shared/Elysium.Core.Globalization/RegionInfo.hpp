/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_GLOBALIZATION_REGIONINFO
#define ELYSIUM_CORE_GLOBALIZATION_REGIONINFO

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

namespace Elysium::Core::Globalization
{
	/// <summary>
	/// 
	/// </summary>
	class ELYSIUM_CORE_API RegionInfo final
	{
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="Culture"></param>
		RegionInfo(const Elysium::Core::int32_t Culture);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Name"></param>
		RegionInfo(const Elysium::Core::String Name);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Source"></param>
		RegionInfo(const RegionInfo& Source);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Right"></param>
		/// <returns></returns>
		RegionInfo(RegionInfo&& Right) noexcept;

		/// <summary>
		/// 
		/// </summary>
		~RegionInfo();

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Source"></param>
		/// <returns></returns>
		RegionInfo& operator=(const RegionInfo& Source);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Right"></param>
		/// <returns></returns>
		RegionInfo& operator=(RegionInfo&& Right) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const Elysium::Core::String GetDisplayName() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const Elysium::Core::String GetEnglishName() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const bool GetIsMetric() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const Elysium::Core::String GetNativeName() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const Elysium::Core::String GetThreeLetterISORegionName() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const Elysium::Core::String GetTwoLetterISORegionName() const;
	private:
		Elysium::Core::int32_t _LCID;

		static Elysium::Core::int32_t GetLocaleIdFromName(const Elysium::Core::String& Name);
	};
}
#endif
