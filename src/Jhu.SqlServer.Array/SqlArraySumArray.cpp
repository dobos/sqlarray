#include "stdafx.h"
#include "SqlArraySumArray.h"

namespace Jhu {
	namespace SqlServer {
		namespace Array
		{

			template <class T, class B>
			void SqlArraySumArray<T, B>::Init()
			{
				initialized = false;
			}

			template <class T, class B>
			void SqlArraySumArray<T, B>::Accumulate(typename B::SqlBufferT value)
			{
				SqlArray<T, B> item = SqlArray<T, B>(value);

				if (!initialized)
				{
					array<B::IndexT>^ lens = item.GetLengths();

					initialized = true;
					count = 0;
					sum = SqlArray<T, B>::Zeros(lens);
				}

				if (sum.m_length != item.m_length)
				{
					throw gcnew SqlArrayException(ExceptionMessages::GetString(L"IncompatibleShape"));
				}

				interior_ptr<T> dp = item.GetDataPointer();
				interior_ptr<T> sp = sum.GetDataPointer();

				for (B::IndexT i = 0; i < sum.m_length; i++)
				{
					sp[i] += dp[i];
				}

				count++;
			}

			template <class T, class B>
			void SqlArraySumArray<T, B>::Merge(SqlArraySumArray group)
			{
				if (group.initialized)
				{
					// Merge two arrays by adding values
					// This will cause problems with duplicate rows
					interior_ptr<T> sp = group.sum.GetDataPointer();
					interior_ptr<T> dp = sum.GetDataPointer();

					for (B::IndexT i = 0; i < sum.m_length; i++)
					{
						dp[i] += sp[i];
					}

					count += group.count;
				}
			}

			template <class T, class B>
			typename B::SqlBufferT SqlArraySumArray<T, B>::Terminate()
			{
				return sum.ToSqlBuffer();
			}

			template <class T, class B>
			void SqlArraySumArray<T, B>::Read(System::IO::BinaryReader^ r)
			{
				count = r->ReadInt64();

				array<B::BufferT>^ buffer = gcnew array<B::BufferT>((int)r->BaseStream->Length - 1);
				r->Read(buffer, 0, buffer->Length);
				sum.InitBuffer(buffer);
			}

			template <class T, class B>
			void SqlArraySumArray<T, B>::Write(System::IO::BinaryWriter^ w)
			{
				w->Write(count);
				w->Write(sum.m_buffer);
			}

#define SPECIALIZE_SqlArraySumArray(T) \
	template Jhu::SqlServer::Array::SqlArraySumArray<T, ShortArray>; \
	template Jhu::SqlServer::Array::SqlArraySumArray<T, MaxArray>;


			SPECIALIZE_SqlArraySumArray(Byte)
				SPECIALIZE_SqlArraySumArray(Int16)
				SPECIALIZE_SqlArraySumArray(Int32)
				SPECIALIZE_SqlArraySumArray(Int64)
				SPECIALIZE_SqlArraySumArray(Single)
				SPECIALIZE_SqlArraySumArray(Double)
				SPECIALIZE_SqlArraySumArray(SqlComplex<Single>)
				SPECIALIZE_SqlArraySumArray(SqlComplex<Double>)
		}
	}
}