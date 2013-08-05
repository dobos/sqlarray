//--- macros

#define GET_BUFFER_T(T, buffer, i) ((interior_ptr<T>) &(buffer)[i])

#define DATATYPEID_BYTE	1
#define DATATYPEID_INT16	2
#define DATATYPEID_INT32	3
#define DATATYPEID_INT64	4
#define DATATYPEID_SINGLE	5
#define DATATYPEID_DOUBLE	6

#define PARLIST_1(T, p) T p##0
#define PARLIST_2(T, p) PARLIST_1(T, p), T p##1
#define PARLIST_3(T, p) PARLIST_2(T, p), T p##2
#define PARLIST_4(T, p) PARLIST_3(T, p), T p##3
#define PARLIST_5(T, p) PARLIST_4(T, p), T p##4
#define PARLIST_6(T, p) PARLIST_5(T, p), T p##5
#define PARLIST_7(T, p) PARLIST_6(T, p), T p##6
#define PARLIST_8(T, p) PARLIST_7(T, p), T p##7
#define PARLIST_9(T, p) PARLIST_8(T, p), T p##8
#define PARLIST_10(T, p) PARLIST_9(T, p), T p##9

#define VARLIST_1(p) p##0
#define VARLIST_2(p) VARLIST_1(p), p##1
#define VARLIST_3(p) VARLIST_2(p), p##2
#define VARLIST_4(p) VARLIST_3(p), p##3
#define VARLIST_5(p) VARLIST_4(p), p##4
#define VARLIST_6(p) VARLIST_5(p), p##5
#define VARLIST_7(p) VARLIST_6(p), p##6
#define VARLIST_8(p) VARLIST_7(p), p##7
#define VARLIST_9(p) VARLIST_8(p), p##8
#define VARLIST_10(p) VARLIST_9(p), p##9

#define REPEAT_1(p) p
#define REPEAT_2(p) REPEAT_1(p), p
#define REPEAT_3(p) REPEAT_2(p), p
#define REPEAT_4(p) REPEAT_3(p), p
#define REPEAT_5(p) REPEAT_4(p), p
#define REPEAT_6(p) REPEAT_5(p), p
#define REPEAT_7(p) REPEAT_6(p), p
#define REPEAT_8(p) REPEAT_7(p), p
#define REPEAT_9(p) REPEAT_8(p), p
#define REPEAT_10(p) REPEAT_9(p), p

#define LAYOUTLIST_1(p, v) *p++ = v##0;
#define LAYOUTLIST_2(p, v) LAYOUTLIST_1(p, v) *p++ = v##1;
#define LAYOUTLIST_3(p, v) LAYOUTLIST_2(p, v) *p++ = v##2;
#define LAYOUTLIST_4(p, v) LAYOUTLIST_3(p, v) *p++ = v##3;
#define LAYOUTLIST_5(p, v) LAYOUTLIST_4(p, v) *p++ = v##4;
#define LAYOUTLIST_6(p, v) LAYOUTLIST_5(p, v) *p++ = v##5;
#define LAYOUTLIST_7(p, v) LAYOUTLIST_6(p, v) *p++ = v##6;
#define LAYOUTLIST_8(p, v) LAYOUTLIST_7(p, v) *p++ = v##7;
#define LAYOUTLIST_9(p, v) LAYOUTLIST_8(p, v) *p++ = v##8;
#define LAYOUTLIST_10(p, v) LAYOUTLIST_9(p, v) *p++ = v##9;

#define PRODUCTLIST_1(p) (p##0)
#define PRODUCTLIST_2(p) (PRODUCTLIST_1(p) * p##1)
#define PRODUCTLIST_3(p) (PRODUCTLIST_2(p) * p##2)
#define PRODUCTLIST_4(p) (PRODUCTLIST_3(p) * p##3)
#define PRODUCTLIST_5(p) (PRODUCTLIST_4(p) * p##4)
#define PRODUCTLIST_6(p) (PRODUCTLIST_5(p) * p##5)
#define PRODUCTLIST_7(p) (PRODUCTLIST_6(p) * p##6)
#define PRODUCTLIST_8(p) (PRODUCTLIST_7(p) * p##7)
#define PRODUCTLIST_9(p) (PRODUCTLIST_8(p) * p##8)
#define PRODUCTLIST_10(p) (PRODUCTLIST_9(p) * p##9)