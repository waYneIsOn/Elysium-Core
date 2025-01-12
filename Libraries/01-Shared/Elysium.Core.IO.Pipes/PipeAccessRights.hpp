/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_PIPIES_PIPEACCESSRIGHTS
#define ELYSIUM_CORE_IO_PIPIES_PIPEACCESSRIGHTS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../Elysium.Core.Template/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

namespace Elysium::Core::IO::Pipes
{
	/// <summary>
	/// Defines the access rights to use when you create access and audit rules.
	/// This enumeration supports a bitwise combination of its member values.
	/// </summary>
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class PipeAccessRights 
		: Elysium::Core::Template::System::uint32_t
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// Specifies the right to read data from the pipe. This does not include the right to read file system attributes, 
		/// extended file system attributes, or access and audit rules.
		/// </summary>
		ReadData = 1,

		/// <summary>
		/// Specifies the right to write data to a pipe. This does not include the right to write file system attributes or 
		/// extended file system attributes.
		/// </summary>
		WriteData = 2,

		/// <summary>
		/// Specifies the right to create a new pipe. Setting this right also sets the Synchronize right.
		/// </summary>
		CreateNewInstance = 4,

		/// <summary>
		/// Specifies the right to read extended file system attributes from a pipe. This does not include the right to read data, 
		/// file system attributes, or access and audit rules.
		/// </summary>
		ReadExtendedAttributes = 8,

		/// <summary>
		/// Specifies the right to write extended file system attributes to a pipe. 
		/// This does not include the right to write file attributes or data.
		/// </summary>
		WriteExtendedAttributes = 16,

		/// <summary>
		/// Specifies the right to read file system attributes from a pipe. This does not include the right to read data,
		/// extended file system attributes, or access and audit rules.
		/// </summary>
		ReadAttributes = 128,

		/// <summary>
		/// Specifies the right to write file system attributes to a pipe. This does not include the right to write data or 
		/// extended file system attributes.
		/// </summary>
		WriteAttributes = 256,

		/// <summary>
		/// Specifies the right to write to the pipe. This right includes the WriteAttributes, WriteData, and WriteExtendedAttributes rights.
		/// </summary>
		Write = 274,

		/// <summary>
		/// Specifies the right to delete a pipe.
		/// </summary>
		Delete = 65536,

		/// <summary>
		/// Specifies the right to read access and audit rules from the pipe. This does not include the right to read data, 
		/// file system attributes, or extended file system attributes.
		/// </summary>
		ReadPermissions = 131072,

		/// <summary>
		/// Specifies the right to read from the pipe. This right includes the ReadAttributes, ReadData, ReadExtendedAttributes
		/// and ReadPermissions rights.
		/// </summary>
		Read = 131209,

		/// <summary>
		/// Specifies the right to read and write from the pipe. This right includes the ReadAttributes, ReadData, ReadExtendedAttributes, 
		/// ReadPermissions, WriteAttributes, WriteData and WriteExtendedAttributes rights.
		/// </summary>
		ReadWrite = 131483,

		/// <summary>
		/// Specifies the right to change the security and audit rules that are associated with a pipe.
		/// </summary>
		ChangePermissions = 262144,

		/// <summary>
		/// Specifies the right to change the owner of a pipe. Note that owners of a pipe have full access to that resource.
		/// </summary>
		TakeOwnership = 524288,

		/// <summary>
		/// Specifies whether the application can wait for a pipe handle to synchronize with the completion of an I/O operation. 
		/// This value is automatically set when allowing access to the pipe and automatically excluded when denying access to the pipe. 
		/// The right to create a pipe requires this value. Note that if you do not explicitly set this value when you create a pipe, 
		/// the value will be set automatically for you.
		/// </summary>
		Synchronize = 1048576,

		/// <summary>
		/// Specifies the right to exert full control over a pipe, and to modify access control and audit rules.
		/// This value represents the combination of all rights in this enumeration.
		/// </summary>
		FullControl = 2032031,

		/// <summary>
		/// Specifies the right to make changes to the system access control list (SACL).
		/// </summary>
		AccessSystemSecurity = 16777216
	};
	
	inline PipeAccessRights operator|(const PipeAccessRights Left, const PipeAccessRights Right)
	{
		return static_cast<PipeAccessRights>(static_cast<int>(Left) | static_cast<int>(Right));
	}

	inline PipeAccessRights operator&(const PipeAccessRights Left, const PipeAccessRights Right)
	{
		return static_cast<PipeAccessRights>(static_cast<int>(Left) & static_cast<int>(Right));
	}
}
#endif
