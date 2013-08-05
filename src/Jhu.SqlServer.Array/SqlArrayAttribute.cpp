#include "stdafx.h"
#include "macro.h"
#include "SqlArrayAttribute.h"

namespace Jhu { namespace SqlServer { namespace Array
{
	String^ SqlArrayAttribute::SchemaName::get()
	{
		return m_schemaName;
	}

	void SqlArrayAttribute::SchemaName::set(String^ value)
	{
		m_schemaName = value;
	}
}
} }