#pragma once

#include "macro.h"
#include "enum.h"
#include "SqlArray.h"
#include "ShortArray.h"
#include "MaxArray.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;

namespace Jhu { namespace SqlServer { namespace Array
{

	/// <summary>
	/// Implements an index/item pair.
	/// </summary>
	/// <remarks>
	/// There are three type of indexes that can be associated with an array item:
	/// <ul><li>LinearIndex: one number, the offset of the item in a continous number buffer.</li>
	///     <li>Index: The original index of an item in an array.</li>
	///     <li>CollapsedIndex: New index of a subarray, used by Split.</li></ul>
	/// </remarks>
	template <class T, class B>
	value class SqlIndexItemPair
	{
	public:
		typename B::IndexT LinearIndex;
		array<typename B::IndexT>^ Index;
		array<typename B::IndexT>^ CollapsedIndex;
		T Item;

		SqlIndexItemPair(array<typename B::IndexT>^ index, T item) : Index(index), Item(item) {};
		SqlIndexItemPair(typename B::IndexT linearIndex, T item) : LinearIndex(linearIndex), Item(item) {};
		SqlIndexItemPair(typename B::IndexT linearIndex, array<typename B::IndexT>^ index, T item) : LinearIndex(linearIndex), Index(index), Item(item) {};
		SqlIndexItemPair(array<typename B::IndexT>^ index, array<typename B::IndexT>^ collapsedIndex, T item) : Index(index), CollapsedIndex(collapsedIndex), Item(item) {};
	};

}
} }