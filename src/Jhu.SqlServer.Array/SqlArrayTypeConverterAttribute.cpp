#include "stdafx.h"
#include "macro.h"
#include "SqlArrayTypeConverterAttribute.h"

namespace Jhu { namespace SqlServer { namespace Array
{
	String^ SqlArrayTypeConverterAttribute::SchemaName::get()
	{
		return m_schemaName;
	}

	void SqlArrayTypeConverterAttribute::SchemaName::set(String^ value)
	{
		m_schemaName = value;
	}
}
} }