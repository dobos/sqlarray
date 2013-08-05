#include "stdafx.h"
#include "macro.h"
#include "Lapack.h"
#include "ShortArray.h"
#include "MaxArray.h"

namespace Jhu { namespace SqlServer { namespace Array
{
	template <class T, class B>
	void Lapack<T, B>::Svd(SqlArray<T, B> data, SqlArray<T, B>% s, SqlArray<T, B>% U, SqlArray<T, B>% Vt)
	{
		char jobu = 'S';
        char jobvt = 'S';

		array<B::IndexT>^ length = data.GetLengths();
		int m = length[0];
		int n = length[1];

        int lda = m;
		s = SqlArray<T, B>(gcnew array<B::IndexT>(1) { Math::Max(1, Math::Min(m, n)) });
		U = SqlArray<T, B>(gcnew array<B::IndexT>(2) { m, Math::Min(m, n) });
        int ldu = m;
		Vt = SqlArray<T, B>(gcnew array<B::IndexT>(2) { Math::Min(m, n), m });
		int ldvt = Math::Min(m, n);
        int info = 0;

		pin_ptr<T> pd = data.GetDataPointer();
		pin_ptr<T> ps = s.GetDataPointer();
		pin_ptr<T> pU = U.GetDataPointer();
		pin_ptr<T> pVt = Vt.GetDataPointer();

		LapackWrapper<T>::Svd(jobu, jobvt, m, n,
            (IntPtr) pd, lda, (IntPtr) ps, (IntPtr) pU, ldu, (IntPtr) pVt, ldvt,
            info);

        //Vt = Vt.Transpose();
	}

	template <>
	void LapackWrapper<Single>::Svd(char jobu, char jobvt, int m, int n, IntPtr pd, int lda, IntPtr ps, IntPtr pU, int ldu, IntPtr pVt, int ldvt, int% info)
	{
		sgesvd(jobu, jobvt, m, n,
            (IntPtr) pd, lda, (IntPtr) ps, (IntPtr) pU, ldu, (IntPtr) pVt, ldvt,
            info);
	}

	template <>
	void LapackWrapper<Double>::Svd(char jobu, char jobvt, int m, int n, IntPtr pd, int lda, IntPtr ps, IntPtr pU, int ldu, IntPtr pVt, int ldvt, int% info)
	{
		dgesvd(jobu, jobvt, m, n,
            (IntPtr) pd, lda, (IntPtr) ps, (IntPtr) pU, ldu, (IntPtr) pVt, ldvt,
            info);
	}

	template <>
	void LapackWrapper<SqlComplex<Single>>::Svd(char jobu, char jobvt, int m, int n, IntPtr pd, int lda, IntPtr ps, IntPtr pU, int ldu, IntPtr pVt, int ldvt, int% info)
	{
		cgesvd(jobu, jobvt, m, n,
            (IntPtr) pd, lda, (IntPtr) ps, (IntPtr) pU, ldu, (IntPtr) pVt, ldvt,
            info);
	}

	template <>
	void LapackWrapper<SqlComplex<Double>>::Svd(char jobu, char jobvt, int m, int n, IntPtr pd, int lda, IntPtr ps, IntPtr pU, int ldu, IntPtr pVt, int ldvt, int% info)
	{
		zgesvd(jobu, jobvt, m, n,
            (IntPtr) pd, lda, (IntPtr) ps, (IntPtr) pU, ldu, (IntPtr) pVt, ldvt,
            info);
	}

	template Jhu::SqlServer::Array::Lapack<Single, ShortArray>;
	template Jhu::SqlServer::Array::Lapack<Single, MaxArray>;
	template Jhu::SqlServer::Array::Lapack<Double, ShortArray>;
	template Jhu::SqlServer::Array::Lapack<Double, MaxArray>;
	template Jhu::SqlServer::Array::Lapack<SqlComplex<Single>, ShortArray>;
	template Jhu::SqlServer::Array::Lapack<SqlComplex<Single>, MaxArray>;
	template Jhu::SqlServer::Array::Lapack<SqlComplex<Double>, ShortArray>;
	template Jhu::SqlServer::Array::Lapack<SqlComplex<Double>, MaxArray>;

}
} }