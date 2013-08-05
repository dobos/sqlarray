#pragma once

#include "macro.h"

using namespace System;

namespace Jhu { namespace SqlServer { namespace Array
{

	/// <summary>
	/// Used to flag classes that export SQL CLR functions
	/// </summary>
	public ref class SqlArrayAttribute : public System::Attribute
	{
	private:
		String^ m_schemaName;

	public:
		SqlArrayAttribute() : Attribute() { };
		property String^ SchemaName { String^ get(); void set(String^ value); };
	};
}
} }