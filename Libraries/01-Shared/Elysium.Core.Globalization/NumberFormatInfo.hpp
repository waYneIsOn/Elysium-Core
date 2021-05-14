/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_GLOBALIZATION_NUMBERFORMATINFO
#define ELYSIUM_CORE_GLOBALIZATION_NUMBERFORMATINFO

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_GLOBALIZATION_DIGITSHAPES
#include "DigitShapes.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

namespace Elysium::Core::Globalization
{
	class ELYSIUM_CORE_API NumberFormatInfo final
	{
	public:
		NumberFormatInfo();
		NumberFormatInfo(const Elysium::Core::int32_t Culture, const bool ReadOnly);
		NumberFormatInfo(const NumberFormatInfo& Source);
		NumberFormatInfo(NumberFormatInfo&& Right) noexcept;
		~NumberFormatInfo();

		NumberFormatInfo& operator=(const NumberFormatInfo& Source);
		NumberFormatInfo& operator=(NumberFormatInfo&& Right) noexcept;

		static const NumberFormatInfo GetCurrentInfo();
		static const NumberFormatInfo GetInvariantInfo();

		const Elysium::Core::int32_t GetCurrencyDecimalDigits() const;
		const String GetCurrencyDecimalSeparator() const;
		const String GetCurrencyGroupSeparator() const;
		const Elysium::Core::int32_t GetCurrencyNegativePattern() const;
		const Elysium::Core::int32_t GetCurrencyPositivePattern() const;
		const String GetCurrencySymbol() const;
		const DigitShapes GetDigitSubstitution() const;
		const bool GetIsReadOnly() const;
		const String GetNaNSymbol() const;
		const String GetNegativeInfinitySymbol() const;
		const String GetNegativeSign() const;
		const Elysium::Core::int32_t GetNumberDecimalDigits() const;
		const String GetNumberDecimalSeparator() const;
		const String GetNumberGroupSeparator() const;
		const Elysium::Core::int32_t GetPercentDecimalDigits() const;
		const String GetPercentDecimalSeparator() const;
		const String GetPercentGroupSeparator() const;
		const Elysium::Core::int32_t GetPercentNegativePattern() const;
		const Elysium::Core::int32_t GetPercentPositivePattern() const;
		const String GetPercentSymbol() const;
		const String GetPerMilleSymbol() const;
		const String GetPositiveInfinitySymbol() const;
		const String GetPositiveSign() const;

		void SetCurrencyDecimalDigits(const Elysium::Core::int32_t Value);
		void SetCurrencyDecimalSeparator(const String& Value);
		void SetCurrencyGroupSeparator(const String& Value);
		void SetCurrencyNegativePattern(const Elysium::Core::int32_t Value);
		void SetCurrencyPositivePattern(const Elysium::Core::int32_t Value);
		void SetCurrencySymbol(const String& Value);
		void SetDigitSubstitution(const DigitShapes Value);
		void SetNaNSymbol(const String& Value);
		void SetNegativeInfinitySymbol(const String& Value);
		void SetNegativeSign(const String& Value);
		void SetNumberDecimalDigits(const Elysium::Core::int32_t Value);
		void SetNumberDecimalSeparator(const String& Value);
		void SetNumberGroupSeparator(const String& Value);
		void SetPercentDecimalDigits(const Elysium::Core::int32_t Value);
		void SetPercentDecimalSeparator(const String& Value);
		void SetPercentGroupSeparator(const String& Value);
		void SetPercentNegativePattern(const Elysium::Core::int32_t Value);
		void SetPercentPositivePattern(const Elysium::Core::int32_t Value);
		void SetPercentSymbol(const String& Value);
		void SetPerMilleSymbol(const String& Value);
		void SetPositiveInfinitySymbol(const String& Value);
		void SetPositiveSign(const String& Value);

		//static const NumberFormatInfo& GetCurrentInfo();
		//static const NumberFormatInfo& GetInvariantInfo();
	private:
		Elysium::Core::int32_t _LCID;
		bool _IsReadOnly;

		/*
		Elysium::Core::int32_t _CurrencyDecimalDigits;
		String _CurrencyDecimalSeparator;
		String _CurrencyGroupSeparator;
		//int* _CurrencyGroupSizes;
		Elysium::Core::int32_t _CurrencyNegativePattern;
		Elysium::Core::int32_t _CurrencyPositivePattern;
		String _CurrencySymbol;
		DigitShapes _DigitSubstitution;
		bool _IsReadOnly;
		String _NaNSymbol;
		//String* _NativeDigits;
		String _NegativeInfinitySymbol;
		String _NegativeSign;
		Elysium::Core::int32_t _NumberDecimalDigits;
		String _NumberDecimalSeparator;
		String _NumberGroupSeparator;
		//int* _NumberGroupSizes;
		//int _NumberNegativePattern;
		Elysium::Core::int32_t _PercentDecimalDigits;
		String _PercentDecimalSeparator;
		String _PercentGroupSeparator;
		//int* _PercentGroupSizes;
		Elysium::Core::int32_t _PercentNegativePattern;
		Elysium::Core::int32_t _PercentPositivePattern;
		String _PercentSymbol;
		String _PerMilleSymbol;
		String _PositiveInfinitySymbol;
		String _PositiveSign;

		static NumberFormatInfo _InvariantInfo;
		*/
	};
}
#endif
