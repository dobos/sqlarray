#include "stdafx.h"
#include "ExceptionMessages.h"

namespace Jhu { namespace SqlServer { namespace Array 
{
	String^ ExceptionMessages::GetString(String^ id)
	{
		ResourceManager^ rm = gcnew ResourceManager(
			"JhuSqlServerArray.ExceptionMessages",
			Assembly::GetExecutingAssembly());

		ResourceSet^ rs = rm->GetResourceSet(System::Threading::Thread::CurrentThread->CurrentCulture,
			false, false);

		return rm->GetString(id);
	}
}
} }