/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_RUNTIMETYPEINFORMATION_SOURCELOCATION
#define ELYSIUM_CORE_TEMPLATE_RUNTIMETYPEINFORMATION_SOURCELOCATION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_COMPILER
#include "../Compiler.hpp"
#endif

namespace Elysium::Core::Template::RunTimeTypeInformation
{
	class SourceLocation
	{
	public:
		constexpr SourceLocation(const Elysium::Core::Template::System::uint32_t Line = Elysium::Core::Template::System::Compiler::GetLine(),
			const Elysium::Core::Template::System::uint32_t Column = Elysium::Core::Template::System::Compiler::GetColumn(),
			const char* File = Elysium::Core::Template::System::Compiler::GetFileName(),
			const char* Function = Elysium::Core::Template::System::Compiler::GetFunctionName()) noexcept;

		constexpr SourceLocation(const SourceLocation& Source) = delete;

		constexpr SourceLocation(SourceLocation&& Source) noexcept = delete;

		constexpr ~SourceLocation() noexcept;
	public:
		SourceLocation& operator=(const SourceLocation& Source) = delete;

		SourceLocation& operator=(SourceLocation&& Right) noexcept = delete;
	public:
		static constexpr const SourceLocation Current(
			const Elysium::Core::Template::System::uint32_t Line = Elysium::Core::Template::System::Compiler::GetLine(),
			const Elysium::Core::Template::System::uint32_t Column = Elysium::Core::Template::System::Compiler::GetColumn(),
			const char* File = Elysium::Core::Template::System::Compiler::GetFileName(),
			const char* Function = Elysium::Core::Template::System::Compiler::GetFunctionName()) noexcept;
	public:
		constexpr const Elysium::Core::Template::System::uint32_t GetLine() const noexcept;

		constexpr const Elysium::Core::Template::System::uint32_t GetColumn() const noexcept;

		constexpr const char* GetFile() const noexcept;

		constexpr const char* GetFunction() const noexcept;
	private:
		const Elysium::Core::Template::System::uint32_t _Line;
		const Elysium::Core::Template::System::uint32_t _Column;
		const char* _File;
		const char* _Function;
	};

	inline constexpr  SourceLocation::SourceLocation(const Elysium::Core::Template::System::uint32_t Line, const Elysium::Core::Template::System::uint32_t Column, const char* File, const char* Function) noexcept
		: _Line(Line), _Column(Column), _File(File), _Function(Function)
	{ }

	inline constexpr Elysium::Core::Template::RunTimeTypeInformation::SourceLocation::~SourceLocation() noexcept
	{ }

	inline constexpr const SourceLocation SourceLocation::Current(const Elysium::Core::Template::System::uint32_t Line, const Elysium::Core::Template::System::uint32_t Column, const char* File, const char* Function) noexcept
	{
		return SourceLocation(Line, Column, File, Function);
	}

	inline constexpr const Elysium::Core::Template::System::uint32_t Elysium::Core::Template::RunTimeTypeInformation::SourceLocation::GetLine() const noexcept
	{
		return _Line;
	}

	inline constexpr const Elysium::Core::Template::System::uint32_t Elysium::Core::Template::RunTimeTypeInformation::SourceLocation::GetColumn() const noexcept
	{
		return _Column;
	}

	inline constexpr const char* SourceLocation::GetFile() const noexcept
	{
		return _File;
	}

	inline constexpr const char* SourceLocation::GetFunction() const noexcept
	{
		return _Function;
	}
}
#endif
