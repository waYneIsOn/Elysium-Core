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
		SourceLocation(const Elysium::Core::Template::System::uint32_t Line = Elysium::Core::Template::System::Compiler::GetLine(),
			const Elysium::Core::Template::System::uint32_t Column = Elysium::Core::Template::System::Compiler::GetColumn(),
			const char8_t* File = Elysium::Core::Template::System::Compiler::GetFileName(),
			const char8_t* Function = Elysium::Core::Template::System::Compiler::GetFunctionName()) noexcept;

		~SourceLocation() noexcept;
	public:
		const SourceLocation Current(const Elysium::Core::Template::System::uint32_t Line = Elysium::Core::Template::System::Compiler::GetLine(),
			const Elysium::Core::Template::System::uint32_t Column = Elysium::Core::Template::System::Compiler::GetColumn(),
			const char8_t* File = Elysium::Core::Template::System::Compiler::GetFileName(), 
			const char8_t* Function = Elysium::Core::Template::System::Compiler::GetFunctionName()) noexcept;
	public:
		const Elysium::Core::Template::System::uint32_t GetLine() const noexcept;

		const Elysium::Core::Template::System::uint32_t GetColumn() const noexcept;

		const char8_t* GetFile() const noexcept;

		const char8_t* GetFunction() const noexcept;
	private:
		Elysium::Core::Template::System::uint32_t _Line;
		Elysium::Core::Template::System::uint32_t _Column;
		const char8_t* _File;
		const char8_t* _Function;
	};

	inline SourceLocation::SourceLocation(const Elysium::Core::Template::System::uint32_t Line, const Elysium::Core::Template::System::uint32_t Column, const char8_t* File, const char8_t* Function) noexcept
		: _Line(Line), _Column(Column), _File(File), _Function(Function)
	{ }

	inline Elysium::Core::Template::RunTimeTypeInformation::SourceLocation::~SourceLocation() noexcept
	{ }

	inline const SourceLocation SourceLocation::Current(const Elysium::Core::Template::System::uint32_t Line, const Elysium::Core::Template::System::uint32_t Column, const char8_t* File, const char8_t* Function) noexcept
	{
		return SourceLocation(Line, Column, File, Function);
	}

	inline const Elysium::Core::Template::System::uint32_t Elysium::Core::Template::RunTimeTypeInformation::SourceLocation::GetLine() const noexcept
	{
		return _Line;
	}

	inline const Elysium::Core::Template::System::uint32_t Elysium::Core::Template::RunTimeTypeInformation::SourceLocation::GetColumn() const noexcept
	{
		return _Column;
	}

	inline const char8_t* SourceLocation::GetFile() const noexcept
	{
		return _File;
	}

	inline const char8_t* SourceLocation::GetFunction() const noexcept
	{
		return _Function;
	}
}
#endif
