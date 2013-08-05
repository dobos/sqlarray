--- Basic array operations

-- From SQL scalars
DECLARE @a varbinary(100) = FloatArray.Vector_5(1, 2, 3, 4, 5)
PRINT FloatArray.ToString(@a)

-- From string using the parser
DECLARE @a varbinary(100) = FloatArray.Parse('[[1, 2],[3, 4],[5, 6]]')
PRINT FloatArray.ToString(@a)

-- Get single item

DECLARE @a varbinary(100) = FloatArray.Parse('[[1, 2],[3, 4],[5, 6]]')
SELECT FloatArray.Item_2(@a, 1, 2)

-- Get all items in a table
---- index as array + item as scalar

DECLARE @a varbinary(100) = FloatArray.Parse('[[1, 2],[3, 4],[5, 6]]')
SELECT * FROM FloatArray.ToTable(@a) t

---- organized in a big table
DECLARE @a varbinary(100) = FloatArray.Parse('[[1, 2],[3, 4],[5, 6]]')
SELECT SmallIntArray.ToString(t.i), t.v FROM FloatArray.ToTable(@a) t

DECLARE @a varbinary(100) = FloatArray.Parse('[1, 2, 3, 4, 5, 6]')
SELECT * FROM FloatArray.ToTable_1(@a) t

DECLARE @a varbinary(500) = FloatArray.Parse('[[1, 2],[3, 4],[5, 6],[7, 8],[9, 10]]')
SELECT * FROM FloatArray.ToTable_2(@a) t

DECLARE @a varbinary(500) = FloatArray.Parse('[[[1, 2],[3, 4],[5, 6]],[[7, 8],[9, 10],[11, 12]]]')
SELECT * FROM FloatArray.ToTable(@a) t

DECLARE @a varbinary(500) = FloatArray.Parse('[[[1, 2],[3, 4],[5, 6]],[[7, 8],[9, 10],[11, 12]]]')
SELECT * FROM FloatArray.ToTable_3(@a) t

DECLARE @a varbinary(500) = FloatArray.Parse('[[[[1, 2],[3, 4],[5, 6]],[[7, 8],[9, 10],[11, 12]]],[[[1, 2],[3, 4],[5, 6]],[[7, 8],[9, 10],[11, 12]]]]')
SELECT * FROM FloatArray.ToTable_4(@a) t

DECLARE @a varbinary(500) = FloatArray.Parse('[[1, 2],[3, 4],[5, 6],[7, 8],[9, 10]]')
SELECT * FROM FloatArray.MatrixToTable_2(@a) t

DECLARE @a varbinary(500) = FloatArray.Parse('[[1, 2, 9],[3, 4, 8],[5, 6, 7],[7, 8, 6],[9, 10, 5]]')
SELECT * FROM FloatArray.MatrixToTable_3(@a) t

DECLARE @a varbinary(500) = FloatArray.Parse('[[1, 2, 9, 7],[3, 4, 8, 5],[5, 6, 7, 3],[7, 8, 6, 1],[9, 10, 5, -1]]')
SELECT * FROM FloatArray.MatrixToTable_4(@a) t

--------------

-- Same for MaxArrays

--- Basic array operations

-- From SQL scalars
DECLARE @a varbinary(100) = FloatArrayMax.Vector_5(1, 2, 3, 4, 5)
PRINT FloatArrayMax.ToString(@a)

-- From string using the parser
DECLARE @a varbinary(100) = FloatArrayMax.Parse('[[1, 2],[3, 4],[5, 6]]')
PRINT FloatArrayMax.ToString(@a)

-- Get single item

DECLARE @a varbinary(100) = FloatArrayMax.Parse('[[1, 2],[3, 4],[5, 6]]')
SELECT FloatArrayMax.Item_2(@a, 1, 2)

-- Get all items in a table
---- index as array + item as scalar

DECLARE @a varbinary(100) = FloatArrayMax.Parse('[[1, 2],[3, 4],[5, 6]]')
SELECT * FROM FloatArrayMax.ToTable(@a) t

---- organized in a big table
DECLARE @a varbinary(100) = FloatArrayMax.Parse('[[1, 2],[3, 4],[5, 6]]')
SELECT IntArray.ToString(t.i), t.v FROM FloatArrayMax.ToTable(@a) t

DECLARE @a varbinary(100) = FloatArrayMax.Parse('[1, 2, 3, 4, 5, 6]')
SELECT * FROM FloatArrayMax.ToTable_1(@a) t

DECLARE @a varbinary(500) = FloatArrayMax.Parse('[[1, 2],[3, 4],[5, 6],[7, 8],[9, 10]]')
SELECT * FROM FloatArrayMax.ToTable_2(@a) t

DECLARE @a varbinary(500) = FloatArrayMax.Parse('[[[1, 2],[3, 4],[5, 6]],[[7, 8],[9, 10],[11, 12]]]')
SELECT * FROM FloatArrayMax.ToTable(@a) t

DECLARE @a varbinary(500) = FloatArrayMax.Parse('[[[1, 2],[3, 4],[5, 6]],[[7, 8],[9, 10],[11, 12]]]')
SELECT * FROM FloatArrayMax.ToTable_3(@a) t

DECLARE @a varbinary(500) = FloatArrayMax.Parse('[[[[1, 2],[3, 4],[5, 6]],[[7, 8],[9, 10],[11, 12]]],[[[1, 2],[3, 4],[5, 6]],[[7, 8],[9, 10],[11, 12]]]]')
SELECT * FROM FloatArrayMax.ToTable_4(@a) t

DECLARE @a varbinary(500) = FloatArrayMax.Parse('[[1, 2],[3, 4],[5, 6],[7, 8],[9, 10]]')
SELECT * FROM FloatArrayMax.MatrixToTable_2(@a) t

DECLARE @a varbinary(500) = FloatArrayMax.Parse('[[1, 2, 9],[3, 4, 8],[5, 6, 7],[7, 8, 6],[9, 10, 5]]')
SELECT * FROM FloatArrayMax.MatrixToTable_3(@a) t

DECLARE @a varbinary(500) = FloatArrayMax.Parse('[[1, 2, 9, 7],[3, 4, 8, 5],[5, 6, 7, 3],[7, 8, 6, 1],[9, 10, 5, -1]]')
SELECT * FROM FloatArrayMax.MatrixToTable_4(@a) t

--------------------------------------------------------------

-- Split

DECLARE @a varbinary(500) = FloatArray.Parse('[[1, 2, 9, 7],[3, 4, 8, 5],[5, 6, 7, 3],[7, 8, 6, 1],[9, 10, 5, -1]]')
SELECT SmallIntArray.ToString(t.ci), SmallIntArray.ToString(t.i), FloatArray.ToString(t.v) FROM FloatArray.Split(@a, SmallIntArray.Vector_2(0,0), SmallIntArray.Vector_2(2,1), 0) t

-- Items

DECLARE @a varbinary(500) = FloatArray.Parse('[[1, 2, 9, 7],[3, 4, 8, 5],[5, 6, 7, 3],[7, 8, 6, 1],[9, 10, 5, -1]]')
DECLARE @i varbinary(max) = SmallIntArrayMax.Parse('[[1,2],[1,3],[2,2],[2,3],[3,2],[1,4]]')
SELECT t.li, SmallIntArray.ToString(t.i), t.v FROM FloatArray.ItemsToTable(@a, @i) t

-- Subarrays

DECLARE @a varbinary(500) = FloatArray.Parse('[[1, 2, 9, 7],[3, 4, 8, 5],[5, 6, 7, 3],[7, 8, 6, 1],[9, 10, 5, -1]]')
DECLARE @i varbinary(max) = SmallIntArrayMax.Parse('[[1,2],[2,2],[1,3]]')
SELECT t.li, SmallIntArray.ToString(t.i), FloatArray.ToString(t.v) FROM FloatArray.SubarraysToTable(@a, @i, SmallIntArray.Vector_2(2,2), 0) t



-- Update and item
DECLARE @a varbinary(100) = FloatArray.Parse('[[1, 2],[3, 4],[5, 6]]')
SET @a = FloatArray.UpdateItem_2(@a, 99, 1, 2)
PRINT FloatArray.ToString(@a)



-- Array from tables

--

DECLARE @temp TABLE (i varbinary(100), v float)

INSERT @temp (i, v)
VALUES
	(SmallIntArray.Vector_2(0, 0), 1),
	(SmallIntArray.Vector_2(0, 1), 2),
	(SmallIntArray.Vector_2(1, 0), 3),
	(SmallIntArray.Vector_2(1, 1), 4)
	
--SELECT * FROM @temp
	
DECLARE @a varbinary(100)

SELECT @a = FloatArray.Concat(SmallIntArray.Vector_2(2,2), t.i, t.v) FROM @temp t

PRINT FloatArray.ToString(@a)

-- large array from table

DECLARE @temp TABLE (i varbinary(max), v float)

INSERT @temp (i, v)
VALUES
	(IntArray.Vector_2(0, 0), 1),
	(IntArray.Vector_2(0, 1), 2),
	(IntArray.Vector_2(1, 0), 3),
	(IntArray.Vector_2(1, 1), 4),
	(IntArray.Vector_2(199, 199), 22)
	
--SELECT * FROM @temp
	
DECLARE @a varbinary(max)

SELECT @a = FloatArrayMax.Concat(IntArray.Vector_2(200,200), t.i, t.v) FROM @temp t

PRINT FloatArrayMax.ToString(@a)
PRINT FloatArrayMax.Item_2(@a, 1, 1)
PRINT FloatArrayMax.Item_2(@a, 199, 199)

----------

-- Array from subarrays

CREATE TABLE ##temp (ix varbinary(500), sa varbinary(500))

INSERT ##temp (ix, sa)
VALUES
	(SmallIntArray.Vector_2(0, 0), FloatArray.Matrix_2(1, 2, 3, 4)),
	(SmallIntArray.Vector_2(2, 2), FloatArray.Matrix_2(11, 12, 13, 14))
	
DECLARE @a varbinary(500)

SET @a = FloatArray.FromSubarrayTable('##temp', SmallIntArray.Vector_2(4, 4))

PRINT FloatArray.ToString(@a)

DROP TABLE ##temp


-- Some performance tests
-- PhotoObjAll table contains 10M rows: ObjID, u,g,r,i,z single precision values
-- PhotoObjFix same data except using array for u,g,r,i,z
-- PhotoObjMax same data but varbinary(max)

DBCC DROPCLEANBUFFERS
DBCC FREEPROCCACHE

SELECT avg(g)
FROM PhotoObjAll
-- 0:04 sec

--

DBCC DROPCLEANBUFFERS
DBCC FREEPROCCACHE

SELECT avg(FloatArray.Item_1(photo, 2))
FROM PhotoObjFix
-- 0:07

-- Multiple item extraction per query

DBCC DROPCLEANBUFFERS
DBCC FREEPROCCACHE

SELECT avg(FloatArray.Item_1(photo, 2)), avg(FloatArray.Item_1(photo, 3)), avg(FloatArray.Item_1(photo, 4))
FROM PhotoObjFix
-- 0:10

--

-- Using varbinary(max) is slow for small arrays!

DBCC DROPCLEANBUFFERS
DBCC FREEPROCCACHE

SELECT avg(FloatArrayMax.Item_1(photo, 2))
FROM PhotoObjMax
-- 0:45






-- SqlArray has a header but there's a way to use raw binary data:

SELECT IntArray.TOString(IntArray.Cast(0x0000000001000000, 0, SmallIntArray.Vector_1(2)))

-- Works the other way around: strip header from data:

SELECT IntArray.Vector_2(0, 1)
SELECT IntArray.Raw(IntArray.Vector_2(0, 1))





-- Can do fancy linear algebra using LAPACK

DECLARE @M varbinary(max) = FloatArray.Parse('[[1,2,3],[4,5,6],[7,8,9]]')
DECLARE @s varbinary(max)

SELECT @s = svd.s FROM FloatArray.SVD(@M) svd

SELECT FloatArray.ToString(@s)








-- Also Fourier transforms using FFTW

-- which requires complex arithemtics -> implemented as UDT

DECLARE @c dbo.FloatComplex = '1+2i'
SET @c.Im = 3
SELECT @c.ToString()

-- convert to complex works

DECLARE @a varbinary(8000) = FloatArray.Parse('[1,2,3,4,5,6,7,8]')
PRINT FloatArray.ToString(@a)

DECLARE @c varbinary(8000) = FloatArray.ConvertToFloatComplexArray(@a)
PRINT FloatComplexArray.ToString(@c)

-- And now the FFT

DECLARE @a varbinary(max) = FloatArrayMax.Parse('[1,2,3,4,5,6,7,8]')
PRINT FloatArrayMax.ToString(@a)

DECLARE @f varbinary(max) = FloatArrayMax.FFTForward(@a)
PRINT FloatArrayMax.ToString(@f)









--- vvvvvvvvvv Ezeket át kell nézni

-- Array from smaller arrays

SELECT TOP 10 photo INTO ##temp FROM PhotoObjFix ORDER BY ObjID

--SELECT * FROM ##temp

DECLARE @a varbinary(8000)
SELECT @a = FloatArray.FromTable('##temp', SmallIntArray.Parse('[5,10]'))
SELECT @a
SELECT FloatArray.String(@a)

DROP TABLE ##temp

---

-- Array from scalar values

SELECT TOP 10 cast(u as float) as u,cast(g as float) as g,cast(r as float) as r,cast(i as float) as i,cast(z as float) as z
INTO ##temp
FROM PhotoObjAll ORDER BY ObjID

DECLARE @a varbinary(8000)
SELECT @a = FloatArray.FromTable('##temp', SmallIntArray.Parse('[5,10]'))
SELECT @a
SELECT FloatArray.String(@a)

DROP TABLE ##temp


-- Array from one scalar value

DECLARE @a varbinary(8000)
SELECT @a = FloatArray.FromTable('SELECT TOP 50 cast(u as float) FROM PhotoObjAll ORDER BY ObjID', SmallIntArray.Parse('[5,10]'))
SELECT @a
SELECT FloatArray.String(@a)

-- Array from scalar-indexed values

DECLARE @a varbinary(8000)
SELECT @a = FloatArray.FromTable('SELECT TOP 10 cast(1 as smallint), cast(2 as smallint), cast(u as float) FROM PhotoObjAll ORDER BY ObjID', SmallIntArray.Parse('[5,10]'))
SELECT @a
SELECT FloatArray.String(@a)

-- Array from array-indexed values

DECLARE @a varbinary(8000)
SELECT @a = FloatArray.FromTable('SELECT TOP 10 SmallIntArray.Parse(''[1,2]''), cast(u as float) FROM PhotoObjAll ORDER BY ObjID', SmallIntArray.Parse('[5,10]'))
SELECT @a
SELECT FloatArray.String(@a)



-------------

-- Type mismatch test

SELECT IntArray.Item_1(SmallIntArray.Vector_4(1,2,3,4), 1)
SELECT IntArray.Item_1(SmallIntArray.ConvertToIntArray(SmallIntArray.Vector_4(1,2,3,4)), 1)


------------------

-- Subsample test

DECLARE @a varbinary(500) = FloatArray.Parse('[[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]]')
PRINT FloatArray.ToString(@a)

SELECT ci, FloatArray.Avg(v) AS v
INTO ##temp
FROM FloatArray.Split(@a, SmallIntArray.Vector_2(0,0), SmallIntArray.Vector_2(2,2), 0)

SET @a = FloatArray.FromTable('##temp', SmallIntArray.Vector_2(2, 2))

PRINT FloatArray.ToString(@a)

DROP TABLE ##temp

----------------------------

DECLARE @a varbinary(500) = FloatArray.Parse('[[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]]')
PRINT FloatArray.ToString(@a)

SELECT @a = FloatArray.Concat(SmallIntArray.Vector_2(2,2), ci, FloatArray.Avg(v))
FROM FloatArray.Split(@a, SmallIntArray.Vector_2(0,0), SmallIntArray.Vector_2(2,2), 0)

PRINT FloatArray.ToString(@a)

----------------------------

-- scalar ops

DECLARE @a varbinary(500) = FloatArray.Parse('[[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]]')

PRINT FloatArray.ToString(FloatArray.ScaMul(@a, 2.0))
PRINT FloatArray.ToString(FloatArray.ScaDiv(@a, 2.0))
PRINT FloatArray.ToString(FloatArray.ScaAdd(@a, 2.0))
PRINT FloatArray.ToString(FloatArray.ScaSub(@a, 2.0))

--- Itemwise ops

DECLARE @a varbinary(500) = FloatArray.Parse('[[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]]')

PRINT FloatArray.ToString(FloatArray.Mul(@a, FloatArray.FromScalar(FloatArray.Lengths(@a), 2.0)))
PRINT FloatArray.ToString(FloatArray.Div(@a, FloatArray.FromScalar(FloatArray.Lengths(@a), 2.0)))
PRINT FloatArray.ToString(FloatArray.[Add](@a, FloatArray.FromScalar(FloatArray.Lengths(@a), 2.0)))
PRINT FloatArray.ToString(FloatArray.Sub(@a, FloatArray.FromScalar(FloatArray.Lengths(@a), 2.0)))


--- vector ops

DECLARE @a varbinary(500) = FloatArray.Parse('[1,2,3]')
DECLARE @b varbinary(500) = FloatArray.Parse('[4,5,6]')

PRINT FloatArray.DotProd(@a, @b)
PRINT FloatArray.ToString(FloatArray.CrossProd(@a, @b))
PRINT FloatArray.ToString(FloatArray.TensorProd(@a, @b))

--- END


---------------------

-- Table from array
/*
SELECT SmallIntArray.GetString(i), v FROM FloatArray.GetTable(FloatArray.Parse('[[1,2,3][3,4,6]]'))

SELECT * FROM FloatArray.GetTable_2(FloatArray.Parse('[[1,2,3][3,4,6]]'))
SELECT * FROM FloatArray.GetTable_3(FloatArray.Parse('[[1,2,3][3,4,6]]'))
SELECT * FROM FloatArray.GetTable_4(FloatArray.Parse('[[1,2,3][3,4,6]]'))

SELECT FloatArray.GetString(v) FROM FloatArray.GetTable_N(FloatArray.Parse('[[1,2,3][3,4,6]]'))


SELECT FloatArray.GetItem_2(FloatArray.Parse('[[1,2,3][3,4,6]]'), 0, 1)


SELECT FloatArray.GetString(FloatArray.Parse('[[1,2][3,4]]'))
*/

-------------

/*
TRUNCATE TABLE PhotoObjFix

INSERT photoobjfix
select objid, FloatArray.CreateVector_5(u,g,r,i,z)
from photoobjall


TRUNCATE TABLE PhotoObjMax

INSERT photoobjmax
select objid, FloatArrayMax.CreateVector_5(u,g,r,i,z)
from photoobjall
*/


-------------------------






---------------





----------

DECLARE @c dbo.FloatComplex = '1+2i'
SET @c.Im = 3
SELECT @c.ToString()


--------------

DECLARE @a varbinary(8000) = FloatArray.Parse('[1,2,3,4,5,6,7,8]')
PRINT FloatArray.ToString(@a)

DECLARE @c varbinary(8000) = FloatArray.ConvertToFloatComplexArray(@a)
PRINT FloatComplexArray.ToString(@c)


-------------------------------------------
-- FFT

DECLARE @a varbinary(max) = FloatComplexArrayMax.Parse('[1,2,3,4,5,6,7,8]')
PRINT FloatComplexArrayMax.ToString(@a)

DECLARE @f varbinary(max) = FloatComplexArrayMax.FFTForward(@a)
PRINT FloatComplexArrayMax.ToString(@f)

DECLARE @b varbinary(max) = FloatComplexArrayMax.FFTBackward(@f)
PRINT FloatComplexArrayMax.ToString(@b)



DECLARE @a varbinary(max) = FloatComplexArrayMax.Parse('[36.0000 + 0.0000i,-4.0000 + 9.6569i,-4.0000 + 4.0000i,-4.0000 + 1.6569i,-4.0000 + 0.0000i,-4.0000 - 1.6569i,-4.0000 - 4.0000i,-4.0000 - 9.6569i]')
PRINT FloatComplexArrayMax.ToString(@a)

----



DECLARE @a varbinary(8000) = FloatArray.Parse('[1,2,3,4,5,6,7,8]')
SELECT @a
SELECT FloatArray.Raw(@a)
SELECT FloatArray.ConvertToFloatArrayMax(@a)
SELECT FloatArray.Raw(@a)




-- Subarray

DECLARE @a varbinary(8000) = FloatArray.Parse('[[1,2,3],[4,5,6],[7,8,9]]');

SELECT FloatArray.ToString(FloatArray.Subarray(@a, SmallIntArray.Parse('[0,0]'), SmallIntArray.Parse('[2,2]'), 0));

SELECT SmallIntArray.ToString(f.i), FloatArray.ToString(f.v)
FROM FloatArray.SubarraysToTable(@a, SmallIntArrayMax.Parse('[[0,0],[1,1]]'), SmallIntArray.Parse('[2,2]'), 0) f




---------

DECLARE @a varbinary(8000) = FloatArray.Vector_5(1,2,3,4,5)

---------


--UpdateSubarray

DECLARE     @size varbinary(max), @b varbinary(max), @off varbinary(max);
SELECT      @size = sqlarray.IntArray.Vector_2(5,5),
            @off  = sqlarray.IntArray.Vector_2(3,2)
            
SET @b = sqlarray.RealArrayMax.FromScalar(@size, -1)

PRINT sqlarray.RealArrayMax.ToString(@b)

SET @b = sqlArray.RealArrayMax.UpdateSubarray(@b, @off, sqlArray.RealArrayMax.Matrix_2(1,2,3,4))

PRINT sqlarray.RealArrayMax.ToString(@b)


--- Subarrays

DECLARE @a varbinary(max) = sqlarray.realarraymax.Parse('[[1,2,3,4,5],[6,7,8,9,1],[2,3,4,5,6],[7,8,9,4,5],[6,7,8,9,0]]')

PRINT sqlarray.realarraymax.ToString(@a)

DECLARE @i varbinary(max) = sqlarray.intarraymax.Parse('[[0,0],[1,1]]');

SET @a = sqlarray.RealArrayMax.Subarrays(@a, @i, sqlarray.intarray.vector_2(2, 2), 0)

PRINT sqlarray.realarraymax.ToString(@a)


--- Update subarrays

DECLARE @a varbinary(max) = sqlarray.realarraymax.FromScalar(sqlarray.intarray.Vector_2(5, 5), 0)
PRINT sqlarray.realarraymax.ToString(@a)

DECLARE @off varbinary(max) = sqlarray.intarraymax.Parse('[[0, 0], [2, 2], [3, 3]]')
PRINT sqlarray.intarraymax.ToString(@off)

DECLARE @b varbinary(max) = sqlarray.realarraymax.Parse('[[[1, 2, 3], [1, 2, 3]], [[1, 2, 3], [1, 2, 3]]]')
PRINT sqlarray.realarraymax.ToString(@b)

SET @a = sqlarray.RealArrayMax.UpdateSubarrays(@a, @off, @b)
PRINT sqlarray.realarraymax.ToString(@a)