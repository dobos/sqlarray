#pragma once

#include "macro.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace System::Data::SqlTypes;
using namespace Microsoft::SqlServer::Server;

namespace Jhu { namespace SqlServer { namespace Array
{
	public enum class ArrayLoadMethod
	{
		HeaderOnly,
		AllData
	};
}
} }