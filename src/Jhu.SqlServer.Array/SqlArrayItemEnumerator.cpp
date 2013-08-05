#include "stdafx.h"
#include "SqlArrayItemEnumerator.h"

namespace Jhu { namespace SqlServer { namespace Array
{
	template <class T, class B>
	SqlArrayItemEnumerator<T, B>::SqlArrayItemEnumerator(SqlArray<T, B> data, array<array<typename B::IndexT>^>^ indexes)
	{
		this->data = data;
		this->indexes = indexes;
		this->current = -1;
	}

	template <class T, class B>
	Object^ SqlArrayItemEnumerator<T, B>::Current::get()
	{
		return Current2::get();
	}

	template <class T, class B>
	SqlIndexItemPair<T, B> SqlArrayItemEnumerator<T, B>::Current2::get()
	{
		return SqlIndexItemPair<T, B>(current, indexes[current], data[indexes[current]]);
	}

	template <class T, class B>
	bool SqlArrayItemEnumerator<T, B>::MoveNext()
	{
		current++;
		return (current < indexes->Length);
	}

	template <class T, class B>
	void SqlArrayItemEnumerator<T, B>::Reset()
	{
		this->current = -1;
	}

	template <class T, class B>
	System::Collections::IEnumerator^ SqlArrayItemEnumerator<T, B>::GetEnumerator()
	{
		return this;
	}

	template <class T, class B>
	System::Collections::Generic::IEnumerator<SqlIndexItemPair<T, B>>^ SqlArrayItemEnumerator<T, B>::GetEnumerator2()
	{
		return this;
	}

#define SPECIALIZE_SQLARRAYITEMENUMERATOR(T) \
	template Jhu::SqlServer::Array::SqlArrayItemEnumerator<T, ShortArray>; \
	template Jhu::SqlServer::Array::SqlArrayItemEnumerator<T, MaxArray>;


	SPECIALIZE_SQLARRAYITEMENUMERATOR(Byte)
	SPECIALIZE_SQLARRAYITEMENUMERATOR(Int16)
	SPECIALIZE_SQLARRAYITEMENUMERATOR(Int32)
	SPECIALIZE_SQLARRAYITEMENUMERATOR(Int64)
	SPECIALIZE_SQLARRAYITEMENUMERATOR(Single)
	SPECIALIZE_SQLARRAYITEMENUMERATOR(Double)
	SPECIALIZE_SQLARRAYITEMENUMERATOR(SqlComplex<Single>)
	SPECIALIZE_SQLARRAYITEMENUMERATOR(SqlComplex<Double>)

}
} }