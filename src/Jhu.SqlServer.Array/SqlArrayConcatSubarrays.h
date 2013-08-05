#pragma once

#include "macro.h"
#include "enum.h"
#include "SqlArray.h"
#include "SqlArrayAttribute.h"
#include "ShortArray.h"
#include "MaxArray.h"

using namespace System;
using namespace System::Collections;
using namespace System::Text;
using namespace System::Data;
using namespace System::Data::SqlClient;
using namespace System::Data::SqlTypes;
using namespace Microsoft::SqlServer::Server;
using namespace Jhu::SqlServer::Array::Parser;

namespace Jhu { namespace SqlServer { namespace Array
{

	/// <summary>
	/// Implements a user-defined aggregate that is used to assemble arrays
	/// from subarrays
	/// </summary>
	template <class T, class B>
	[Serializable]
	[SqlUserDefinedAggregate(
		Format::UserDefined,
		IsInvariantToNulls = true,
		IsInvariantToDuplicates = false,
		IsInvariantToOrder = false,
		MaxByteSize = B::ConcatAggregateSize,
		Name=L"ConcatSubarrays")]
	public value class SqlArrayConcatSubarrays : IBinarySerialize
	{
		private: bool initialized;
		private: SqlArray<T, B> data;

		public: void Init();
		public: void Accumulate(typename ShortArray::SqlBufferT length, typename ShortArray::SqlBufferT index, typename B::SqlBufferT value);
		public: void Merge(SqlArrayConcatSubarrays group);
		public: typename B::SqlBufferT Terminate();
		public: virtual void Read(System::IO::BinaryReader^ r) = IBinarySerialize::Read;
		public: virtual void Write(System::IO::BinaryWriter^ w) = IBinarySerialize::Write;
	};

}
} }