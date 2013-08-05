#include "stdafx.h"
#include "SqlArrayTest.h"


using namespace System;
using namespace System::Text;
using namespace System::Data::SqlTypes;
using namespace Microsoft::SqlServer::Server;

namespace Jhu { namespace SqlServer { namespace Array
{
	void SqlArrayTest::Run()
	{
		//TestHeader();
		//TestFromArray();
		//TestParse();
		//TestToString();
		//TestToJaggedArray();
		//TestToMultiDArray();
		//TestReshape();
		//TestTranspose();
		//TestPermute();
		//TestGetItems();
		//TestSetItems();
		//TestGetSubarray();
		//TestGetSubarrays();
		//TestSplit();
		//TestSetSubarray();
		//TestSetSubarrays();
		//TestConvert();
		//TestEnumerators();
		//TestSVD();
		//TestFFT();
		TestInnerProduct();
	}

	bool SqlArrayTest::TestHeader()
	{

		/*
		SqlArray<Int16, ShortArray> u(gcnew array<Int16>(2) {1,2});
		array<unsigned char>^ buffer = u.ToSqlBuffer().Value;

		SqlArray<Int16, MaxArray> v;
		v.InitBuffer(buffer);

		Console::WriteLine(sizeof(SqlArrayHeader<Int16>));
		
		SqlArrayHeader<Int16> ha;
		ha.HeaderType = 1;
		ha.ColumnMajor = 1;
		ha.DataType = 0;
		ha.Rank = 31;

		ha.Length = 255;


		Int64* bb = (Int64*) &ha;
		for (int i = 0; i < sizeof(SqlArrayHeader<Int16>); i ++)
		{
			for (int j = 0; j < 8; j ++)
			{
				Console::Write((*bb & 0x8000000000000000) != 0 ? "1" : "0");
				*bb = *bb << 1;
			}
			Console::Write("|");
		}

		Console::WriteLine();
		
		
		Console::WriteLine(sizeof(SqlArrayHeader<Int32>));*/

		SqlArray<Int32, ShortArray> u = SqlArray<Int32, ShortArray>::FromString(L"[4,1,2,3]");

		Console::WriteLine(u.m_rank);
		Console::WriteLine(u.GetLengths()[0]);

		return true;
	}

	bool SqlArrayTest::TestFromArray()
	{
		Console::WriteLine("FromArray:");

		SqlArray<Double, ShortArray> u;

		array<Double>^ a = gcnew array<Double>(2);
		u = SqlArray<Double, ShortArray>::FromArray(a);
		Assert(u.m_rank == 1);
		Console::WriteLine(u.ToString());

		array<array<Double>^>^ aa = gcnew array<array<Double>^>(2);
		for (int i = 0; i < aa->Length; i++)
		{
			aa[i] = gcnew array<Double>(2);
		}
		u = SqlArray<Double, ShortArray>::FromArray(aa);
		Assert(u.m_rank == 2);
		Console::WriteLine(u.ToString());

		array<array<array<Double>^>^>^ aaa = gcnew array<array<array<Double>^>^>(2);
		for (int i = 0; i < aaa->Length; i++)
		{
			aaa[i] = gcnew array<array<Double>^>(2);
			for (int j = 0; j < aaa[i]->Length; j ++)
			{
				aaa[i][j] = gcnew array<Double>(2);
			}
		}
		u = SqlArray<Double, ShortArray>::FromArray(aaa);
		Assert(u.m_rank == 3);
		Console::WriteLine(u.ToString());

		return true;
	}

	bool SqlArrayTest::TestParse()
	{

		Console::WriteLine(L"Parse:");

		Console::WriteLine(SqlArray<Double,ShortArray>::FromString(L"[1,2,3]").ToString());
		Console::WriteLine(SqlArray<Double,ShortArray>::FromString(L"[[1,2][3,4][5,6]]").ToString());
		Console::WriteLine(SqlArray<Double,ShortArray>::FromString(L"[[1,2,3][4,5,6]]").ToString());
		Console::WriteLine(SqlArray<Double,ShortArray>::FromString(L"[[1,2][3,4][5,6]]").ToString());
		Console::WriteLine(SqlArray<Double,ShortArray>::FromString(L"[[[1,2][1,2]][[1,2][1,2]][[5,6][5,6]][[7,8][7,8]]]").ToString());
		array<Double>^ dd = SqlArray<Double,ShortArray>::FromString(L"[[[1,2][1,2]][[1,2][1,2]][[5,6][5,6]][[7,8][7,8]]]").ToArray();
		array<ShortArray::IndexT>^ le = SqlArray<Double,ShortArray>::FromString(L"[[[1,2][1,2]][[1,2][1,2]][[5,6][5,6]][[7,8][7,8]]]").GetLengths();
		Console::WriteLine(SqlArray<SqlComplex<Double>,ShortArray>::FromString(L"[1+2i,2+1i,3+0i]").ToString());
		Console::WriteLine(SqlArray<SqlComplex<Double>,ShortArray>::FromString(L"[36.0000 + 0.0000i,-4.0000 + 9.6569i,-4.0000 + 4.0000i,-4.0000 + 1.6569i,-4.0000 + 0.0000i,-4.0000 - 1.6569i,-4.0000 - 4.0000i,-4.0000 - 9.6569i]").ToString());

		array<Double>^ ddd = (array<Double>^)
			SqlArray<Double, ShortArray>::FromString(L"[[[1, 2][3, 4][5, 6]][[7, 8][9, 10][11, 12]]]").ToArray();

		array<ShortArray::IndexT>^ l =
			SqlArray<Double, ShortArray>::FromString(L"[[[1, 2][3, 4][5, 6]][[7, 8][9, 10][11, 12]]]").GetLengths();

		return true;
	}

	bool SqlArrayTest::TestToString()
	{
		Console::WriteLine(L"ToString:");

		SqlArray<Double,ShortArray> u =
			SqlArray<Double,ShortArray>::FromArray(SampleVector());
		Console::WriteLine(u.ToString());

		SqlArray<Double,ShortArray> v =
			SqlArray<Double,ShortArray>::FromArray(SampleMatrix());
		Console::WriteLine(v.ToString());

		SqlArray<Double,ShortArray> w =
			SqlArray<Double,ShortArray>::FromArray(SampleTensor());
		Console::WriteLine(w.ToString());

		return true;
	}

	bool SqlArrayTest::TestToJaggedArray()
	{
		Console::WriteLine("ToJaggedArray:");

		SqlArray<Double,ShortArray> u =
			SqlArray<Double,ShortArray>::FromArray(SampleVector());
		Console::WriteLine(u.ToString());
		array<Double>^ a1 = safe_cast<array<Double,1>^>(u.ToJaggedArray());

		SqlArray<Double,ShortArray> v =
			SqlArray<Double,ShortArray>::FromArray(SampleMatrix());
		Console::WriteLine(v.ToString());
		array<array<Double>^>^ a2 = safe_cast<array<array<Double>^>^>(v.ToJaggedArray());

		SqlArray<Double,ShortArray> x =
			SqlArray<Double,ShortArray>::FromArray(SampleNonRectMatrix());
		Console::WriteLine(x.ToString());
		array<array<Double>^>^ a3 = safe_cast<array<array<Double>^>^>(x.ToJaggedArray());

		SqlArray<Double,ShortArray> w =
			SqlArray<Double,ShortArray>::FromArray(SampleTensor());
		Console::WriteLine(w.ToString());
		array<array<array<Double>^>^>^ a4 = safe_cast<array<array<array<Double>^>^>^>(w.ToJaggedArray());

		SqlArray<Double,ShortArray> y =
			SqlArray<Double,ShortArray>::FromArray(SampleTensorBig());
		Console::WriteLine(y.ToString());
		array<array<array<Double>^>^>^ a5 = safe_cast<array<array<array<Double>^>^>^>(y.ToJaggedArray());

		return true;
	}

	bool SqlArrayTest::TestToMultiDArray()
	{
		Console::WriteLine("ToMultiDArray:");

		SqlArray<Double,ShortArray> u =
			SqlArray<Double,ShortArray>::FromArray(SampleVector());
		Console::WriteLine(u.ToString());
		array<Double>^ a1 = safe_cast<array<Double,1>^>(u.ToMultiDArray());

		SqlArray<Double,ShortArray> v =
			SqlArray<Double,ShortArray>::FromArray(SampleMatrix());
		Console::WriteLine(v.ToString());
		array<Double,2>^ a2 = safe_cast<array<Double,2>^>(v.ToMultiDArray());

		SqlArray<Double,ShortArray> x =
			SqlArray<Double,ShortArray>::FromArray(SampleNonRectMatrix());
		Console::WriteLine(x.ToString());
		array<Double,2>^ a3 = safe_cast<array<Double,2>^>(x.ToMultiDArray());

		SqlArray<Double,ShortArray> w =
			SqlArray<Double,ShortArray>::FromArray(SampleTensor());
		Console::WriteLine(w.ToString());
		array<Double,3>^ a4 = safe_cast<array<Double,3>^>(w.ToMultiDArray());

		SqlArray<Double,ShortArray> y =
			SqlArray<Double,ShortArray>::FromArray(SampleTensorBig());
		Console::WriteLine(y.ToString());
		array<Double,3>^ a5 = safe_cast<array<Double,3>^>(y.ToMultiDArray());

		return true;
	}

	bool SqlArrayTest::TestReshape()
	{
		Console::WriteLine(L"Reshape:");

		SqlArray<Double,ShortArray> u =
			SqlArray<Double,ShortArray>::FromArray(SampleMatrix());

		u.Reshape(gcnew array<ShortArray::IndexT>(2) {9, 1});
		Console::WriteLine(u.ToString());

		u.Reshape(gcnew array<ShortArray::IndexT>(1) {9});
		Console::WriteLine(u.ToString());
		
		u.Reshape(gcnew array<ShortArray::IndexT>(2) {3, 3});
		Console::WriteLine(u.ToString());

		return true;
	}

	bool SqlArrayTest::TestTranspose()
	{
		Console::WriteLine(L"Transpose:");

		SqlArray<Double, MaxArray> M;
		M = SqlArray<Double,MaxArray>::FromArray(SampleMatrix());

		Console::WriteLine(M.ToString());
		Console::WriteLine(M.Transpose().ToString());

		M = SqlArray<Double,MaxArray>::FromArray(SampleNonRectMatrix());

		Console::WriteLine(M.ToString());
		Console::WriteLine(M.Transpose().ToString());

		return true;
	}

	bool SqlArrayTest::TestPermute()
	{
		Console::WriteLine(L"Permute:");

		SqlArray<Double,ShortArray> u =
			SqlArray<Double,ShortArray>::FromArray(SampleMatrix());
		Console::WriteLine(u.ToString());

		SqlArray<Double, ShortArray> q = u.Permute(gcnew array<ShortArray::RankT>(2) { 1, 0 });
		Console::WriteLine(q.ToString());

		SqlArray<Double,ShortArray> v =
			SqlArray<Double,ShortArray>::FromArray(SampleTensor());
		Console::WriteLine(v.ToString());

		SqlArray<Double, ShortArray> r = v.Permute(gcnew array<ShortArray::RankT>(3) { 1, 2, 0 });
		Console::WriteLine(r.ToString());

		SqlArray<Double,ShortArray> w =
			SqlArray<Double,ShortArray>::FromArray(SampleTensorBig());
		Console::WriteLine(w.ToString());

		SqlArray<Double, ShortArray> s = w.Permute(gcnew array<ShortArray::RankT>(3) { 1, 2, 0 });
		Console::WriteLine(s.ToString());

		return true;
	}

	bool SqlArrayTest::TestGetItems()
	{
		Console::WriteLine(L"GetItems:");

		SqlArray<Double,ShortArray> v;

		SqlArray<Double,ShortArray> u =
			SqlArray<Double,ShortArray>::FromArray(SampleTensorBig());

		Console::WriteLine(u.ToString());

		//---

		Console::WriteLine(u[0, 0, 0]);
		Console::WriteLine(u[1, 0, 0]);
		Console::WriteLine(u[0, 1, 0]);
		Console::WriteLine(u[0, 0, 1]);

		// ---

		Console::WriteLine(u[gcnew array<ShortArray::IndexT> { 0, 0, 0 }]);
		Console::WriteLine(u[gcnew array<ShortArray::IndexT> { 1, 0, 0 }]);
		Console::WriteLine(u[gcnew array<ShortArray::IndexT> { 0, 1, 0 }]);
		Console::WriteLine(u[gcnew array<ShortArray::IndexT> { 0, 0, 1 }]);

		// ---

		v = u.GetItems(gcnew array<array<ShortArray::IndexT>^>(4)
		{
			gcnew array<ShortArray::IndexT> { 0, 0, 0 },
			gcnew array<ShortArray::IndexT> { 1, 0, 0 },
			gcnew array<ShortArray::IndexT> { 0, 1, 0 },
			gcnew array<ShortArray::IndexT> { 0, 0, 1 }
		});

		Console::WriteLine(v.ToString());

		return true;
	}

	bool SqlArrayTest::TestSetItems()
	{
		Console::WriteLine(L"SetItems:");

		SqlArray<Double,ShortArray> u(gcnew array<ShortArray::IndexT>(3) {3, 3, 4});

		Console::WriteLine(u.ToString());

		u.SetItems(gcnew array<array<ShortArray::IndexT>^>(4)
			{
				gcnew array<ShortArray::IndexT> { 0, 0, 0 },
				gcnew array<ShortArray::IndexT> { 1, 0, 0 },
				gcnew array<ShortArray::IndexT> { 0, 1, 0 },
				gcnew array<ShortArray::IndexT> { 0, 0, 1 }
			},
				gcnew array<Double>(4) { 1, 2, 3, 4});

		Console::WriteLine(u.ToString());

		return true;
	}

	bool SqlArrayTest::TestGetSubarray()
	{
		Console::WriteLine(L"GetSubArray:");

		SqlArray<Double, ShortArray> u, v;

		u =	SqlArray<Double,ShortArray>::FromArray(SampleMatrix());
		Console::WriteLine(u.ToString());

		v = u.GetSubarray(gcnew array<ShortArray::IndexT>(2) {0, 1},
					   gcnew array<ShortArray::IndexT>(2) {1, 2}, true);
		Console::WriteLine(v.ToString());

		v =	u.GetSubarray(gcnew array<ShortArray::IndexT>(2) {0, 0},
					   gcnew array<ShortArray::IndexT>(2) {2, 1}, true);
		Console::WriteLine(v.ToString());

		u = SqlArray<Double,ShortArray>::FromArray(SampleTensorBig());
		Console::WriteLine(u.ToString());

		v = u.GetSubarray(gcnew array<ShortArray::IndexT>(3) {0, 0, 0},
					   gcnew array<ShortArray::IndexT>(3) {1, 3, 3}, true);
		Console::WriteLine(v.ToString());

		v = u.GetSubarray(gcnew array<ShortArray::IndexT>(3) {0, 0, 0},
					   gcnew array<ShortArray::IndexT>(3) {1, 3, 2}, false);
		Console::WriteLine(v.ToString());

		return true;
	}

	bool SqlArrayTest::TestGetSubarrays()
	{
		Console::WriteLine(L"GetSubArrays:");

		SqlArray<Double, ShortArray> u, v;

		array<array<ShortArray::IndexT>^>^ off = gcnew array<array<ShortArray::IndexT>^>(3)
			{ gcnew array<ShortArray::IndexT>(3) {0, 0, 0},
			  gcnew array<ShortArray::IndexT>(3) {1, 1, 1},
			  gcnew array<ShortArray::IndexT>(3) {0, 1, 0}
			};

		u = SqlArray<Double, ShortArray>::FromArray(SampleTensorBig());
		Console::WriteLine(u.ToString());

		v = u.GetSubarrays(off, gcnew array<ShortArray::IndexT>(3) {2,2,2}, false);
		Console::WriteLine(v.ToString());

		return true;
	}

	bool SqlArrayTest::TestSplit()
	{
		Console::WriteLine(L"Split:");

		SqlArray<Double, ShortArray> u = SqlArray<Double, ShortArray>::FromString("[[[1,2,3,4],[3,4,5,6]],[[5,6,7,8],[7,8,9,0]]]");
		Console::WriteLine(u.ToString());

		SqlArraySliceEnumerator<Double, ShortArray>^ en = gcnew SqlArraySliceEnumerator<Double, ShortArray>(u);

		en->Offset = gcnew array<ShortArray::IndexT>(3) { 0, 0, 0 };
		en->Length = gcnew array<ShortArray::IndexT>(3) { 4, 1, 1 };
		en->Collapse = true;

		for each (SqlIndexItemPair<SqlArray<Double, ShortArray>, ShortArray> it in en)
		{
			SqlArray<ShortArray::IndexT, ShortArray> ci = SqlArray<ShortArray::IndexT, ShortArray>::FromArray(it.CollapsedIndex);
			SqlArray<ShortArray::IndexT, ShortArray> i = SqlArray<ShortArray::IndexT, ShortArray>::FromArray(it.Index);
			Console::WriteLine(L"{0} {1} {2}", it.Item.ToString(), i.ToString(), ci.ToString());
		}

		return true;
	}

	bool SqlArrayTest::TestSetSubarray()
	{
		Console::WriteLine(L"GetSubArray:");

		SqlArray<Double, ShortArray> u;
		u =	SqlArray<Double,ShortArray>::FromArray(SampleMatrix());
		Console::WriteLine(u.ToString());

		u.SetSubarray(
			gcnew array<ShortArray::IndexT>(2) { 1, 1 },
			SqlArray<Double, ShortArray>::FromArray(gcnew array<Double,2>(1,1) { {99} })
		);
		Console::WriteLine(u.ToString());

		u.SetSubarray(
			gcnew array<ShortArray::IndexT>(2) { 0, 1 },
			SqlArray<Double, ShortArray>::FromArray(gcnew array<Double,2>(1,3) { {0, 0, 0} })
		);
		Console::WriteLine(u.ToString());

		u.SetSubarray(
			gcnew array<ShortArray::IndexT>(2) { 1, 0 },
			SqlArray<Double, ShortArray>::FromArray(gcnew array<Double,2>(3,1) { {-1},{-1},{-1} })
		);
		Console::WriteLine(u.ToString());

		// ---

		u = SqlArray<Double,ShortArray>::FromArray(SampleTensorBig());
		Console::WriteLine(u.ToString());

		u.SetSubarray(
			gcnew array<ShortArray::IndexT>(3) { 1, 1, 1 },
			SqlArray<Double, ShortArray>::FromArray(gcnew array<Double,3>(2,2,2) {{{-1, -2},{-3, -4}},{{-5, -6},{-7, -8}}})
		);
		Console::WriteLine(u.ToString());


		Console::WriteLine(u.GetSubarray(
			gcnew array<ShortArray::IndexT>(3) { 1, 1, 1 },
			gcnew array<ShortArray::IndexT>(3) { 2, 2, 2 },
			false).ToString());

		return true;
	}

	bool SqlArrayTest::TestSetSubarrays()
	{
		Console::WriteLine(L"SetSubArrays:");

		SqlArray<Double, ShortArray> u, v;

		array<array<ShortArray::IndexT>^>^ off = gcnew array<array<ShortArray::IndexT>^>(3)
			{ gcnew array<ShortArray::IndexT>(2) {0, 0},
			  gcnew array<ShortArray::IndexT>(2) {1, 1},
			  gcnew array<ShortArray::IndexT>(2) {2, 2}
			};

		u = SqlArray<Double, ShortArray>(gcnew array<ShortArray::IndexT>(2) {5, 5});
		Console::WriteLine(u.ToString());

		v = SqlArray<Double, ShortArray>::FromString("[[[1, 2, 3], [1, 2, 3]], [[1, 2, 3], [1, 2, 3]]]");
		Console::WriteLine(v.ToString());

		u.SetSubarrays(off, v);
		Console::WriteLine(u.ToString());

		return true;

	}

	bool SqlArrayTest::TestConvert()
	{
		SqlArray<Double, ShortArray> u = SqlArray<Double, ShortArray>::FromString("[1,2,3,4,5,6,7,8]");
		SqlArray<Double, MaxArray> v = SqlArrayTypeConverter<Double, ShortArray, Double, MaxArray>::Convert(u);

		Console::WriteLine(u.ToString());
		Console::WriteLine(v.ToString());

		return true;
	}

	bool SqlArrayTest::TestEnumerators()
	{
		Console::WriteLine("Enumerators");

		SqlArray<Double, ShortArray> u = SqlArray<Double, ShortArray>::FromArray(SampleTensorBig());
		Console::WriteLine(u.ToString());
		
/*		for each (SqlIndexItemPair<Double, ShortArray> i in SqlArrayLinearEnumerator<Double, ShortArray>(u))
		{
			Console::WriteLine(L"{0} {1}", i.Index, i.Item);
		}

		u = SqlArray<Double, ShortArray>::FromString(L"[[[1, 2][3, 4][5, 6]][[7, 8][9, 10][11, 12]]]");
		Console::WriteLine(u.ToString());
		
		for each (SqlIndexItemPair<Double, ShortArray> i in SqlArrayLinearEnumerator<Double, ShortArray>(u))
		{
			Console::WriteLine(L"{0} {1}", i.Index, i.Item);
		}*/

		u = SqlArray<Double, ShortArray>::FromArray(SampleTensorBig());
		Console::WriteLine(u.ToString());

		SqlArraySliceEnumerator<Double, ShortArray>^ en =
			gcnew SqlArraySliceEnumerator<Double, ShortArray>(u);
		en->Offset = gcnew array<ShortArray::IndexT>(3);
		en->Length = gcnew array<ShortArray::IndexT>(3) {2,2,1};
		en->Collapse = true;

		for each (SqlIndexItemPair<SqlArray<Double, ShortArray>, ShortArray> p in en)
		{
			Console::WriteLine(L"{0} {1} {2} {3}", p.Index[0], p.Index[1], p.Index[2], p.Item.ToString());
		}

		return true;
	}

	bool SqlArrayTest::TestSVD()
	{
		Console::WriteLine(L"SVD:");

		SqlArray<Double, MaxArray> M;
		M = SqlArray<Double,MaxArray>::FromArray(SampleMatrix());
		Console::WriteLine(M.ToString());


		SqlArray<Double, MaxArray> s, U, Vt;

		Lapack<Double, MaxArray>::Svd(M, s, U, Vt);

		Console::WriteLine(M.ToString());
		Console::WriteLine(s.ToString());
		Console::WriteLine(U.ToString());
		Console::WriteLine(Vt.ToString());

		return true;
	}

	bool SqlArrayTest::TestFFT()
	{
		return true;
	}

	bool SqlArrayTest::TestInnerProduct()
	{

		Console::WriteLine(L"Inner product:");

		SqlArray<Double, MaxArray> a = SqlArray<Double, MaxArray>::FromArray(gcnew array<Double>(3){1, 2, 3});
		SqlArray<Double, MaxArray> b = SqlArray<Double, MaxArray>::FromArray(gcnew array<Double,2>(2, 3){{1, 2, 3}, {4, 5, 6}});
		SqlArray<Double, MaxArray> c = SqlArray<Double, MaxArray>::FromArray(SampleMatrix());

		

		Console::WriteLine(a.ToString());
		Console::WriteLine(b.ToString());
		Console::WriteLine(c.ToString());
		
		Console::WriteLine(SqlArray<Double, MaxArray>::InnerProduct(a, c).ToString());
		Console::WriteLine(SqlArray<Double, MaxArray>::InnerProduct(b, c).ToString());

		Console::WriteLine();

		a = SqlArray<Double, MaxArray>::FromString("[[1,2,3],[4,5,6],[7,8,9]]");
		b = SqlArray<Double, MaxArray>::FromString("[[7,4,5],[6,7,3],[4,8,9]]");
		Console::WriteLine(SqlArray<Double, MaxArray>::InnerProduct(a, b).ToString());

		return true;
	}

	// ---

	array<Double>^ SqlArrayTest::SampleVector()
	{
		return gcnew array<Double>(5) { 1,2,3,4,5 };
	}

	array<Double,2>^ SqlArrayTest::SampleMatrix()
	{
		return gcnew array<Double,2>(3,3) { {1,2,3},{4,5,6},{7,8,9} };
	}

	array<Double,2>^ SqlArrayTest::SampleNonRectMatrix()
	{
		return gcnew array<Double,2>(5,3) { {1,2,3},{4,5,6},{7,8,9},{10,11,12},{13,14,15} };
	}

	array<Double,3>^ SqlArrayTest::SampleTensor()
	{
		return gcnew array<Double,3>(2,2,2) { {{1,2},{3,4,}},{{5,6,},{7,8}} };
	}

	array<Double,3>^ SqlArrayTest::SampleTensorBig()
	{
		return gcnew array<Double,3>(3,3,4) {{{1,2,3,4},{5,6,7,8},{9,10,11,12}},
											{{13,14,15,16},{17,18,19,20},{21,22,23,24}},
											{{25,26,27,28},{29,30,31,32},{33,34,35,36}}};
	}

	// ---
	void SqlArrayTest::Assert(bool condition)
	{
		if (!condition)
		{
			throw gcnew Exception("Assertation fault.");
		}
	}

}
} }