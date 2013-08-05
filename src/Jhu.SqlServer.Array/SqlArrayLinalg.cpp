#include "stdafx.h"
#include "macro.h"
#include "ShortArray.h"
#include "MaxArray.h"
#include "SqlArrayAttribute.h"
#include "SqlArray.h"
#include "SqlArrayLinalg.h"
#include "Lapack.h"

namespace Jhu { namespace SqlServer { namespace Array
{
	template <class T, class B>
	System::Collections::IEnumerable^ SqlArrayLinalg<T, B>::SVD(typename B::SqlBufferT data)
	{
		SqlArray<T, B> s, U, Vt;

		Lapack<T, B>::Svd(
			SqlArray<T, B>(data, ArrayLoadMethod::AllData),
			s, U, Vt);

		array<array<SqlArray<T, B>>^>^ r = gcnew array<array<SqlArray<T, B>>^>(1);
		r[0] = gcnew array<SqlArray<T, B>>(3) { s, U, Vt };

		return r;
	}

	template <class T, class B>
	void SqlArrayLinalg<T, B>::SVD_FillRow(System::Object ^o, typename B::SqlBufferT %s, typename B::SqlBufferT %U, typename B::SqlBufferT %Vt)
	{
		array<SqlArray<T, B>>^ r = safe_cast<array<SqlArray<T, B>>^>(o);

		s = r[0].ToSqlBuffer();
		U = r[1].ToSqlBuffer();
		Vt = r[2].ToSqlBuffer();
	}

	template SqlArrayLinalg<Double, ShortArray>;
	template SqlArrayLinalg<Double, MaxArray>;
}
} }