using namespace System;
using namespace System::Resources;
using namespace System::Reflection;

namespace Jhu { namespace SqlServer { namespace Array 
{
	ref class ExceptionMessages
	{
		public: static String^ GetString(String^ id);
	};
}
} }