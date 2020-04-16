/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_GLOBALIZATION_NUMBERFORMATINFO
#define ELYSIUM_CORE_GLOBALIZATION_NUMBERFORMATINFO

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_GLOBALIZATION_DIGITSHAPES
#include "DigitShapes.hpp"
#endif

namespace Elysium::Core::Globalization
{
	class ELYSIUM_CORE_API NumberFormatInfo final
	{
	public:
		NumberFormatInfo();
		//NumberFormatInfo(const NumberFormatInfo& Source);
		//NumberFormatInfo(NumberFormatInfo&& Right) noexcept;
		~NumberFormatInfo();

		//NumberFormatInfo& operator=(const NumberFormatInfo& Source);
		//NumberFormatInfo& operator=(NumberFormatInfo&& Right) noexcept;

		const int GetCurrencyDecimalDigits() const;
		const String& GetCurrencyDecimalSeparator() const;
		const String& GetCurrencyGroupSeparator() const;
		const int GetCurrencyNegativePattern() const;
		const int GetCurrencyPositivePattern() const;
		const String& GetCurrencySymbol() const;
		const DigitShapes GetDigitSubstitution() const;
		const bool GetIsReadOnly() const;
		const String& GetNaNSymbol() const;
		const String& GetNegativeInfinitySymbol() const;
		const String& GetNegativeSign() const;
		const int GetNumberDecimalDigits() const;
		const String& GetNumberDecimalSeparator() const;
		const String& GetNumberGroupSeparator() const;
		const int GetPercentDecimalDigits() const;
		const String& GetPercentDecimalSeparator() const;
		const String& GetPercentGroupSeparator() const;
		const int GetPercentNegativePattern() const;
		const int GetPercentPositivePattern() const;
		const String& GetPercentSymbol() const;
		const String& GetPerMilleSymbol() const;
		const String& GetPositiveInfinitySymbol() const;
		const String& GetPositiveSign() const;

		void SetCurrencyDecimalDigits(const int Value);
		void SetCurrencyDecimalSeparator(const String& Value);
		void SetCurrencyGroupSeparator(const String& Value);
		void SetCurrencyNegativePattern(const int Value);
		void SetCurrencyPositivePattern(const int Value);
		void SetCurrencySymbol(const String& Value);
		void SetDigitSubstitution(const DigitShapes Value);
		void SetNaNSymbol(const String& Value);
		void SetNegativeInfinitySymbol(const String& Value);
		void SetNegativeSign(const String& Value);
		void SetNumberDecimalDigits(const int Value);
		void SetNumberDecimalSeparator(const String& Value);
		void SetNumberGroupSeparator(const String& Value);
		void SetPercentDecimalDigits(const int Value);
		void SetPercentDecimalSeparator(const String& Value);
		void SetPercentGroupSeparator(const String& Value);
		void SetPercentNegativePattern(const int Value);
		void SetPercentPositivePattern(const int Value);
		void SetPercentSymbol(const String& Value);
		void SetPerMilleSymbol(const String& Value);
		void SetPositiveInfinitySymbol(const String& Value);
		void SetPositiveSign(const String& Value);

		//static const NumberFormatInfo& GetCurrentInfo();
		static const NumberFormatInfo& GetInvariantInfo();
	private:
		int _CurrencyDecimalDigits;
		String _CurrencyDecimalSeparator;
		String _CurrencyGroupSeparator;
		//int* _CurrencyGroupSizes;
		int _CurrencyNegativePattern;
		int _CurrencyPositivePattern;
		String _CurrencySymbol;
		DigitShapes _DigitSubstitution;
		bool _IsReadOnly;
		String _NaNSymbol;
		//String* _NativeDigits;
		String _NegativeInfinitySymbol;
		String _NegativeSign;
		int _NumberDecimalDigits;
		String _NumberDecimalSeparator;
		String _NumberGroupSeparator;
		//int* _NumberGroupSizes;
		//int _NumberNegativePattern;
		int _PercentDecimalDigits;
		String _PercentDecimalSeparator;
		String _PercentGroupSeparator;
		//int* _PercentGroupSizes;
		int _PercentNegativePattern;
		int _PercentPositivePattern;
		String _PercentSymbol;
		String _PerMilleSymbol;
		String _PositiveInfinitySymbol;
		String _PositiveSign;

		static NumberFormatInfo _InvariantInfo;
	};
}
#endif
