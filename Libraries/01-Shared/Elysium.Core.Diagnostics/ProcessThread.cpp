#include "ProcessThread.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

constexpr Elysium::Core::Diagnostics::ProcessThread::ProcessThread(const Elysium::Core::Template::System::uint32_t Id, const Elysium::Core::Template::System::uint32_t OwnerProcessId, const Elysium::Core::Template::System::int32_t BasePriority, const Elysium::Core::Template::System::int32_t CurrentPriority) noexcept
	: _Id(Id), _OwnerProcessId(OwnerProcessId), _BasePriority(BasePriority), _CurrentPriority(CurrentPriority)
{ }

constexpr Elysium::Core::Diagnostics::ProcessThread::ProcessThread()
	: _Id(), _OwnerProcessId(), _BasePriority(), _CurrentPriority()
{ }

constexpr Elysium::Core::Diagnostics::ProcessThread::ProcessThread(const ProcessThread& Source)
	: _Id(Source._Id), _OwnerProcessId(Source._OwnerProcessId), _BasePriority(Source._BasePriority), _CurrentPriority(Source._CurrentPriority)
{ }

constexpr Elysium::Core::Diagnostics::ProcessThread::ProcessThread(ProcessThread&& Right) noexcept
	: _Id(), _OwnerProcessId(), _BasePriority(), _CurrentPriority()
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}

constexpr Elysium::Core::Diagnostics::ProcessThread::~ProcessThread()
{ }

constexpr Elysium::Core::Diagnostics::ProcessThread& Elysium::Core::Diagnostics::ProcessThread::operator=(const ProcessThread& Source)
{
	if (this != &Source)
	{
		_Id = Source._Id;
		_OwnerProcessId = Source._OwnerProcessId;
		_BasePriority = Source._BasePriority;
		_CurrentPriority = Source._CurrentPriority;
	}

	return *this;
}

constexpr Elysium::Core::Diagnostics::ProcessThread& Elysium::Core::Diagnostics::ProcessThread::operator=(ProcessThread&& Right) noexcept
{
	if (this != &Right)
	{
		_Id = Elysium::Core::Template::Functional::Move(Right._Id);
		_OwnerProcessId = Elysium::Core::Template::Functional::Move(Right._OwnerProcessId);
		_BasePriority = Elysium::Core::Template::Functional::Move(Right._BasePriority);
		_CurrentPriority = Elysium::Core::Template::Functional::Move(Right._CurrentPriority);

		Right._Id = 0;
		Right._OwnerProcessId = 0;
		Right._BasePriority = 0;
		Right._CurrentPriority = 0;
	}

	return *this;
}

const Elysium::Core::Template::System::uint32_t Elysium::Core::Diagnostics::ProcessThread::GetId() const
{
	return _Id;
}

const Elysium::Core::Template::System::uint32_t Elysium::Core::Diagnostics::ProcessThread::GetOwnedProcessId() const
{
	return _OwnerProcessId;
}

const Elysium::Core::Template::System::int32_t Elysium::Core::Diagnostics::ProcessThread::GetBasePriority() const
{
	return _BasePriority;
}

const Elysium::Core::Template::System::int32_t Elysium::Core::Diagnostics::ProcessThread::GetCurrentPriority() const
{
	return _CurrentPriority;
}
