#include "ProcessModule.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

constexpr Elysium::Core::Diagnostics::ProcessModule::ProcessModule(Elysium::Core::Template::Text::String<char8_t>&& Name, Elysium::Core::Template::Text::String<char8_t>&& FileName, void* BaseAddress, void* EntryPoint, Elysium::Core::Template::System::uint32_t SizeOfImage, Elysium::Core::Template::System::uint32_t Id) noexcept
	: _Name(Name), _FileName(FileName), _BaseAddress(BaseAddress), _EntryPoint(EntryPoint), _SizeOfImage(SizeOfImage), _Id(Id)
{ }

constexpr Elysium::Core::Diagnostics::ProcessModule::ProcessModule()
	: _Name(), _FileName(), _BaseAddress(), _EntryPoint(), _SizeOfImage(), _Id()
{ }

constexpr Elysium::Core::Diagnostics::ProcessModule::ProcessModule(const ProcessModule& Source)
	: _Name(Source._Name), _FileName(Source._FileName), _BaseAddress(Source._BaseAddress), _EntryPoint(Source._EntryPoint), _SizeOfImage(Source._SizeOfImage), _Id(Source._Id)
{ }

constexpr Elysium::Core::Diagnostics::ProcessModule::ProcessModule(ProcessModule&& Right) noexcept
	: _Name(), _FileName(), _BaseAddress(), _EntryPoint(), _SizeOfImage(), _Id()
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}

constexpr Elysium::Core::Diagnostics::ProcessModule::~ProcessModule()
{ }

constexpr Elysium::Core::Diagnostics::ProcessModule& Elysium::Core::Diagnostics::ProcessModule::operator=(const ProcessModule & Source)
{
	if (this != &Source)
	{
		_Name = Source._Name;
		_FileName = Source._FileName;
		_BaseAddress = Source._BaseAddress;
		_EntryPoint = Source._EntryPoint;
		_SizeOfImage = Source._SizeOfImage;
		_Id = Source._Id;
	}

	return *this;
}

constexpr Elysium::Core::Diagnostics::ProcessModule& Elysium::Core::Diagnostics::ProcessModule::operator=(ProcessModule&& Right) noexcept
{
	if (this != &Right)
	{
		_Name = Elysium::Core::Template::Functional::Move(Right._Name);
		_FileName = Elysium::Core::Template::Functional::Move(Right._FileName);
		_BaseAddress = Elysium::Core::Template::Functional::Move(Right._BaseAddress);
		_EntryPoint = Elysium::Core::Template::Functional::Move(Right._EntryPoint);
		_SizeOfImage = Elysium::Core::Template::Functional::Move(Right._SizeOfImage);
		_Id = Elysium::Core::Template::Functional::Move(Right._Id);

		Right._BaseAddress = nullptr;
		Right._EntryPoint = nullptr;
		Right._SizeOfImage = 0;
		Right._Id = 0;
	}

	return *this;
}

const Elysium::Core::Template::Text::String<char8_t> Elysium::Core::Diagnostics::ProcessModule::GetModuleName() const
{
	return _Name;
}

const Elysium::Core::Template::Text::String<char8_t> Elysium::Core::Diagnostics::ProcessModule::GetFileName() const
{
	return _FileName;
}

const void* Elysium::Core::Diagnostics::ProcessModule::GetBaseAddress() const
{
	return _BaseAddress;
}

const void* Elysium::Core::Diagnostics::ProcessModule::GetEntryPoint() const
{
	return _EntryPoint;
}

const Elysium::Core::Template::System::uint32_t Elysium::Core::Diagnostics::ProcessModule::GetSizeOfImage() const
{
	return _SizeOfImage;
}

const Elysium::Core::Template::System::uint32_t Elysium::Core::Diagnostics::ProcessModule::GetId() const
{
	return _Id;
}
