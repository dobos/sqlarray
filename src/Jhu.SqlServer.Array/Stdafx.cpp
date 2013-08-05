// stdafx.cpp : source file that includes just the standard includes
// Jhu.SqlServer.Array.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// This is to create a fake entry point for the module initializer.
// Normally the CRT would provide this entry point but as we don't link
// the CRT we have to provide it ourselves.
// The warning is disabled so the linker won't complain about the mismatch
// in signatures (decorated names).
#pragma warning(disable:4483)
 
 void __clrcall __identifier(".cctor")()
 {
 }

