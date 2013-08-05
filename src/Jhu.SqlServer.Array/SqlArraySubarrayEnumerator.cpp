#include "stdafx.h"
#include "SqlArraySubarrayEnumerator.h"

namespace Jhu { namespace SqlServer { namespace Array
{

	template <class T, class B>
	array<typename B::IndexT>^ SqlArraySubarrayEnumerator<T, B>::Length::get()
	{
		return length;
	}

	template <class T, class B>
	void SqlArraySubarrayEnumerator<T, B>::Length::set(array<typename B::IndexT>^ value)
	{
		length = value;

		if (length->Length != dataLength->Length)
		{
			throw gcnew ArgumentOutOfRangeException();	//***
		}
	}

	template <class T, class B>
	bool SqlArraySubarrayEnumerator<T, B>::Collapse::get()
	{
		return collapse;
	}

	template <class T, class B>
	void SqlArraySubarrayEnumerator<T, B>::Collapse::set(bool value)
	{
		collapse = value;
	}

	template <class T, class B>
	SqlArraySubarrayEnumerator<T, B>::SqlArraySubarrayEnumerator(SqlArray<T, B> data, array<array<typename B::IndexT>^>^ indexes)
	{
		this->data = data;
		this->dataLength = data.GetLengths();

		this->indexes = indexes;
		this->current = -1;
	}

	template <class T, class B>
	Object^ SqlArraySubarrayEnumerator<T, B>::Current::get()
	{
		return Current2::get();
	}

	template <class T, class B>
	SqlIndexItemPair<SqlArray<T, B>, B> SqlArraySubarrayEnumerator<T, B>::Current2::get()
	{
		return SqlIndexItemPair<SqlArray<T, B>, B>(current, indexes[current], data.GetSubarray(indexes[current], length, collapse));
	}

	template <class T, class B>
	bool SqlArraySubarrayEnumerator<T, B>::MoveNext()
	{
		current++;
		return (current < indexes->Length);
	}

	template <class T, class B>
	void SqlArraySubarrayEnumerator<T, B>::Reset()
	{
		this->current = -1;
	}

	template <class T, class B>
	System::Collections::IEnumerator^ SqlArraySubarrayEnumerator<T, B>::GetEnumerator()
	{
		return this;
	}

	template <class T, class B>
	System::Collections::Generic::IEnumerator<SqlIndexItemPair<SqlArray<T, B>, B>>^ SqlArraySubarrayEnumerator<T, B>::GetEnumerator2()
	{
		return this;
	}

#define SPECIALIZE_SQLARRAYSUBARRAYENUMERATOR(T) \
	template Jhu::SqlServer::Array::SqlArraySubarrayEnumerator<T, ShortArray>; \
	template Jhu::SqlServer::Array::SqlArraySubarrayEnumerator<T, MaxArray>;


	SPECIALIZE_SQLARRAYSUBARRAYENUMERATOR(Byte)
	SPECIALIZE_SQLARRAYSUBARRAYENUMERATOR(Int16)
	SPECIALIZE_SQLARRAYSUBARRAYENUMERATOR(Int32)
	SPECIALIZE_SQLARRAYSUBARRAYENUMERATOR(Int64)
	SPECIALIZE_SQLARRAYSUBARRAYENUMERATOR(Single)
	SPECIALIZE_SQLARRAYSUBARRAYENUMERATOR(Double)
	SPECIALIZE_SQLARRAYSUBARRAYENUMERATOR(SqlComplex<Single>)
	SPECIALIZE_SQLARRAYSUBARRAYENUMERATOR(SqlComplex<Double>)

}
} }