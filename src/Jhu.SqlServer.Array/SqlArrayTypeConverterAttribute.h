#pragma once

#include "macro.h"

using namespace System;

namespace Jhu { namespace SqlServer { namespace Array
{

	/// <summary>
	/// Attbriute to flag the array type converted class
	/// </summary>
	public ref class SqlArrayTypeConverterAttribute : public System::Attribute
	{
	private:
		String^ m_schemaName;

	public:
		SqlArrayTypeConverterAttribute() : Attribute() { };
		property String^ SchemaName { String^ get(); void set(String^ value); };
	};
}
} }