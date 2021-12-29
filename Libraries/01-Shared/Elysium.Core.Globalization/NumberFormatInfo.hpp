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
		const Utf8String GetCurrencyDecimalSeparator() const;
		const Utf8String GetCurrencyGroupSeparator() const;
		const Elysium::Core::int32_t GetCurrencyNegativePattern() const;
		const Elysium::Core::int32_t GetCurrencyPositivePattern() const;
		const Utf8String GetCurrencySymbol() const;
		const DigitShapes GetDigitSubstitution() const;
		const bool GetIsReadOnly() const;
		const Utf8String GetNaNSymbol() const;
		const Utf8String GetNegativeInfinitySymbol() const;
		const Utf8String GetNegativeSign() const;
		const Elysium::Core::int32_t GetNumberDecimalDigits() const;
		const Utf8String GetNumberDecimalSeparator() const;
		const Utf8String GetNumberGroupSeparator() const;
		const Elysium::Core::int32_t GetPercentDecimalDigits() const;
		const Utf8String GetPercentDecimalSeparator() const;
		const Utf8String GetPercentGroupSeparator() const;
		const Elysium::Core::int32_t GetPercentNegativePattern() const;
		const Elysium::Core::int32_t GetPercentPositivePattern() const;
		const Utf8String GetPercentSymbol() const;
		const Utf8String GetPerMilleSymbol() const;
		const Utf8String GetPositiveInfinitySymbol() const;
		const Utf8String GetPositiveSign() const;

		void SetCurrencyDecimalDigits(const Elysium::Core::int32_t Value);
		void SetCurrencyDecimalSeparator(const Utf8String& Value);
		void SetCurrencyGroupSeparator(const Utf8String& Value);
		void SetCurrencyNegativePattern(const Elysium::Core::int32_t Value);
		void SetCurrencyPositivePattern(const Elysium::Core::int32_t Value);
		void SetCurrencySymbol(const Utf8String& Value);
		void SetDigitSubstitution(const DigitShapes Value);
		void SetNaNSymbol(const Utf8String& Value);
		void SetNegativeInfinitySymbol(const Utf8String& Value);
		void SetNegativeSign(const Utf8String& Value);
		void SetNumberDecimalDigits(const Elysium::Core::int32_t Value);
		void SetNumberDecimalSeparator(const Utf8String& Value);
		void SetNumberGroupSeparator(const Utf8String& Value);
		void SetPercentDecimalDigits(const Elysium::Core::int32_t Value);
		void SetPercentDecimalSeparator(const Utf8String& Value);
		void SetPercentGroupSeparator(const Utf8String& Value);
		void SetPercentNegativePattern(const Elysium::Core::int32_t Value);
		void SetPercentPositivePattern(const Elysium::Core::int32_t Value);
		void SetPercentSymbol(const Utf8String& Value);
		void SetPerMilleSymbol(const Utf8String& Value);
		void SetPositiveInfinitySymbol(const Utf8String& Value);
		void SetPositiveSign(const Utf8String& Value);

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
