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

	/// <summary>
	/// Enumerates the slices of an array and returns offset/value pairs
	/// to serialize into a SQL table
	/// </summary>
	/// <remarks>Used by the slit function</remarks>
	template <class T, class B>
	ref class SqlArraySliceEnumerator
		: public System::Collections::Generic::IEnumerator<SqlIndexItemPair<SqlArray<T, B>, B>>,
		  public System::Collections::Generic::IEnumerable<SqlIndexItemPair<SqlArray<T, B>, B>>
	{
	private:

		array<typename B::IndexT>^ offset;
		array<typename B::IndexT>^ length;
		bool collapse;

		array<typename B::IndexT>^ current;
		array<typename B::IndexT>^ start;
		SqlArray<T, B> data;
		array<typename B::IndexT>^ dataLength;
		array<typename B::IndexT>^ slices;

	public:
		property array<typename B::IndexT>^ Offset { typename array<typename B::IndexT>^ get(); void set(array<typename B::IndexT>^); };
		property array<typename B::IndexT>^ Length { typename array<typename B::IndexT>^ get(); void set(array<typename B::IndexT>^); };
		property bool Collapse { typename bool get(); void set(bool); };

		SqlArraySliceEnumerator(SqlArray<T, B> data);
		~SqlArraySliceEnumerator() {};

		virtual property Object^ Current { Object^ get() = System::Collections::IEnumerator::Current::get; };
		virtual property SqlIndexItemPair<SqlArray<T, B>, B> Current2 { SqlIndexItemPair<SqlArray<T, B>, B> get() = System::Collections::Generic::IEnumerator<SqlIndexItemPair<SqlArray<T, B>, B>>::Current::get; };
		virtual bool MoveNext();
		virtual void Reset();

		virtual System::Collections::IEnumerator^ GetEnumerator() = System::Collections::IEnumerable::GetEnumerator;
		virtual System::Collections::Generic::IEnumerator<SqlIndexItemPair<SqlArray<T, B>, B>>^ GetEnumerator2() = System::Collections::Generic::IEnumerable<SqlIndexItemPair<SqlArray<T, B>, B>>::GetEnumerator;

	};

}
} }