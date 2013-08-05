#include "stdafx.h"
#include "SqlArrayEnumerator.h"

namespace Jhu { namespace SqlServer { namespace Array
{
	template <class T, class B>
	SqlArrayEnumerator<T, B>::SqlArrayEnumerator(SqlArray<T, B> data)
	{
		this->data = data;

		this->current = nullptr;
		this->length = data.GetLengths();
		this->currentOffset = 0;
	}

	template <class T, class B>
	Object^ SqlArrayEnumerator<T, B>::Current::get()
	{
		return Current2::get();
	}

	template <class T, class B>
	SqlIndexItemPair<T, B> SqlArrayEnumerator<T, B>::Current2::get()
	{
		return SqlIndexItemPair<T, B>(currentOffset, current, data.GetDataPointer()[currentOffset]);
	}

	template <class T, class B>
	bool SqlArrayEnumerator<T, B>::MoveNext()
	{
		if (current == nullptr)
		{
			current = gcnew array<B::IndexT>(data.m_rank);
			return data.m_length > 0;
		}

		for (B::RankT r = 0; r < current->Length; r++)
		{
			if (current[r] < length[r] - 1)
			{
				current[r]++;
				currentOffset++;
				return true;
			}
			else
			{
				if (r == data.m_rank - 1)
				{
					return false;
				}
				else
				{
					current[r] = 0;
				}
			}
		}

		throw gcnew Exception();	//**** should not reach this
	}

	template <class T, class B>
	void SqlArrayEnumerator<T, B>::Reset()
	{
		this->current = nullptr;
		this->currentOffset = 0;
	}

	template <class T, class B>
	System::Collections::IEnumerator^ SqlArrayEnumerator<T, B>::GetEnumerator()
	{
		return this;
	}

	template <class T, class B>
	System::Collections::Generic::IEnumerator<SqlIndexItemPair<T, B>>^ SqlArrayEnumerator<T, B>::GetEnumerator2()
	{
		return this;
	}

#define SPECIALIZE_SQLARRAYENUMERATOR(T) \
	template Jhu::SqlServer::Array::SqlArrayEnumerator<T, ShortArray>; \
	template Jhu::SqlServer::Array::SqlArrayEnumerator<T, MaxArray>;


	SPECIALIZE_SQLARRAYENUMERATOR(Byte)
	SPECIALIZE_SQLARRAYENUMERATOR(Int16)
	SPECIALIZE_SQLARRAYENUMERATOR(Int32)
	SPECIALIZE_SQLARRAYENUMERATOR(Int64)
	SPECIALIZE_SQLARRAYENUMERATOR(Single)
	SPECIALIZE_SQLARRAYENUMERATOR(Double)
	SPECIALIZE_SQLARRAYENUMERATOR(SqlComplex<Single>)
	SPECIALIZE_SQLARRAYENUMERATOR(SqlComplex<Double>)

}
} }