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
	/// Enumerates the columns of an array and returns column index/value pairs
	/// to serialize into a SQL table
	/// </remarks>
	template <class T, class B>
	ref class SqlArrayMatrixEnumerator
		: public System::Collections::Generic::IEnumerator<SqlIndexItemPair<array<T>^, B>>,
		  public System::Collections::Generic::IEnumerable<SqlIndexItemPair<array<T>^, B>>
	{
	private:

		typename B::IndexT current;
		SqlArray<T, B> data;
		array<typename B::IndexT>^ dataLength;

	public:
		SqlArrayMatrixEnumerator(SqlArray<T, B> data);
		~SqlArrayMatrixEnumerator() {};

		virtual property Object^ Current { Object^ get() = System::Collections::IEnumerator::Current::get; };
		virtual property SqlIndexItemPair<array<T>^, B> Current2 { SqlIndexItemPair<array<T>^, B> get() = System::Collections::Generic::IEnumerator<SqlIndexItemPair<array<T>^, B>>::Current::get; };
		virtual bool MoveNext();
		virtual void Reset();

		virtual System::Collections::IEnumerator^ GetEnumerator() = System::Collections::IEnumerable::GetEnumerator;
		virtual System::Collections::Generic::IEnumerator<SqlIndexItemPair<array<T>^, B>>^ GetEnumerator2() = System::Collections::Generic::IEnumerable<SqlIndexItemPair<array<T>^, B>>::GetEnumerator;

	};

}
} }