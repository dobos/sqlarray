#pragma once

#include "macro.h"
#include "SqlArray.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Jhu { namespace SqlServer { namespace Array
{
	template <class T, class B>
	ref class Lapack
	{
	private:

	public:
		
		static void Svd(SqlArray<T, B> data, SqlArray<T, B>% s, SqlArray<T, B>% U, SqlArray<T, B>% Vt);

	};

    [DllImport("libacml_mp_dll.dll", EntryPoint = "sgesvd")]
    extern "C" void _cdecl sgesvd(char jobu, char jobvt, int m, int n, IntPtr a, int lda, IntPtr sing, IntPtr u, int ldu, IntPtr vt, int ldvt, int% info);

	[DllImport("libacml_mp_dll.dll", EntryPoint = "dgesvd")]
    extern "C" void _cdecl dgesvd(char jobu, char jobvt, int m, int n, IntPtr a, int lda, IntPtr sing, IntPtr u, int ldu, IntPtr vt, int ldvt, int% info);

	[DllImport("libacml_mp_dll.dll", EntryPoint = "cgesvd")]
    extern "C" void _cdecl cgesvd(char jobu, char jobvt, int m, int n, IntPtr a, int lda, IntPtr sing, IntPtr u, int ldu, IntPtr vt, int ldvt, int% info);

	[DllImport("libacml_mp_dll.dll", EntryPoint = "zgesvd")]
    extern "C" void _cdecl zgesvd(char jobu, char jobvt, int m, int n, IntPtr a, int lda, IntPtr sing, IntPtr u, int ldu, IntPtr vt, int ldvt, int% info);

	template <class T>
	ref class LapackWrapper
	{
	public:
		static void Svd(char jobu, char jobvt, int m, int n, IntPtr pd, int lda, IntPtr ps, IntPtr pU, int ldu, IntPtr pVt, int ldvt, int% info);
	};

}
} }