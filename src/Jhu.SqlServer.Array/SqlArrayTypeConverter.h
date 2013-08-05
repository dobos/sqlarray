#pragma once

#include "macro.h"
#include "SqlArrayTypeConverterAttribute.h"
#include "SqlArrayHeader.h"
#include "SqlArray.h"

using namespace System;
using namespace System::Text;
using namespace System::Data::SqlTypes;
using namespace Microsoft::SqlServer::Server;
using namespace Jhu::SqlServer::Array::Parser;

namespace Jhu { namespace SqlServer { namespace Array
{

	/// <summary>
	/// Implements a type converter to convert between array base types.
	/// </summary>
	template <class F, class B, class T, class C>
	[Jhu::SqlServer::Array::SqlArrayTypeConverterAttribute]
	public value class SqlArrayTypeConverter
	{
	internal:
		static SqlArray<T, C> Convert(SqlArray<F, B> v);

	public:
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename C::SqlBufferT ConvertTo(typename B::SqlBufferT v);
	};
}
} }