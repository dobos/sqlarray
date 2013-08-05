#pragma once

#include "macro.h"
#include "enum.h"
#include "SqlArray.h"
#include "ShortArray.h"
#include "MaxArray.h"
#include "SqlIndexItemPair.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;

namespace Jhu { namespace SqlServer { namespace Array
{

	/// <remarks>
	/// Enumerates the items of an array and returns index/value pairs
	/// to serialize into a SQL table
	/// </remarks>
	template <class T, class B>
	ref class SqlArrayItemEnumerator
		: public System::Collections::Generic::IEnumerator<SqlIndexItemPair<T, B>>,
		  public System::Collections::Generic::IEnumerable<SqlIndexItemPair<T, B>>
	{
	private:
		typename B::IndexT current;
		SqlArray<T, B> data;
		array<array<typename B::IndexT>^>^ indexes;

	public:
		SqlArrayItemEnumerator(SqlArray<T, B> data, array<array<typename B::IndexT>^>^ indexes);
		~SqlArrayItemEnumerator() {};

		virtual property Object^ Current { Object^ get() = System::Collections::IEnumerator::Current::get; };
		virtual property SqlIndexItemPair<T, B> Current2 { SqlIndexItemPair<T, B> get() = System::Collections::Generic::IEnumerator<SqlIndexItemPair<T, typename B>>::Current::get; };
		virtual bool MoveNext();
		virtual void Reset();

		virtual System::Collections::IEnumerator^ GetEnumerator() = System::Collections::IEnumerable::GetEnumerator;
		virtual System::Collections::Generic::IEnumerator<SqlIndexItemPair<T, B>>^ GetEnumerator2() = System::Collections::Generic::IEnumerable<SqlIndexItemPair<T, B>>::GetEnumerator;

	};

}
} }