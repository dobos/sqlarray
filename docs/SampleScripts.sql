DECLARE @a varbinary(100) = SqlArray.RealArray.Vector_3(1.0, 2.0, 3.0)



EXEC sp_configure 'show advanced options' , '1';
go
reconfigure;
go
EXEC sp_configure 'clr enabled' , '1'
go
reconfigure;
-- Turn advanced options back off
EXEC sp_configure 'show advanced options' , '0';
go



ALTER DATABASE SqlArray
SET TRUSTWORTHY ON
GO


DECLARE @a varbinary(100) = SqlArray.RealArray.Vector_3(1.0, 2.0, 3.0)
SELECT SqlArray.RealArray.Item_1(@a, 2)



DECLARE @a varbinary(100) = SqlArray.RealArray.Vector_3(1.0, 2.0, 3.0)
SELECT SqlArray.RealArray.Item_N(@a, SqlArray.SmallIntArray.Vector_1(2))




DECLARE @a varbinary(100) = FloatArray.Parse('[[1, 2],[3, 4]]')



DECLARE @a varbinary(100) = FloatArray.Parse('[[1, 2],[3, 4]]')
PRINT FloatArray.ToString(@a)


DECLARE @a varbinary(100) = FloatArray.Vector_5(1, 2, 3, 4, 5)

DECLARE @a varbinary(100) = SqlArray.FloatArray.Matrix_2(1, 2, 3, 4)
SELECT SqlArray.FloatArray.Rank(@a) -- returns 2

DECLARE @a varbinary(100) = SqlArray.FloatArray.Matrix_2(1, 2, 3, 4)
SELECT SqlArray.FloatArray.TotalLength(@a) -- return 4


DECLARE @a varbinary(100) = SqlArray.FloatArray.Parse('[[1, 2],[3, 4],[5, 6]]')
SELECT SqlArray.FloatArray.Length(@a, 0)	-- returns 2
SELECT SqlArray.FloatArray.Length(@a, 1)	-- returns 3


DECLARE @a varbinary(100) = SqlArray.FloatArray.Parse('[[1, 2],[3, 4],[5, 6]]')
SELECT SqlArray.SmallIntArray.ToString(SqlArray.FloatArray.Lengths(@a))
-- returns [2,3]



DECLARE @size varbinary(100) = SqlArray.SmallIntArray.Vector_2(2,2)
DECLARE @a varbinary(100) = SqlArray.TinyIntArray.Cast(0x00010203, 0, @size)
SELECT SqlArray.TinyIntArray.ToString(@a) -- returns [[0,1],[2,3]]



DECLARE @a varbinary(100) = SqlArray.SmallIntArray.Parse('[[1, 2],[3, 4],[5, 6]]')
SELECT SqlArray.SmallIntArray.Raw(@a) -- returns 0x010002000300040005000600



DECLARE @a varbinary(100) = SqlArray.FloatArray.Parse('[[1, 2],[3, 4],[5, 6]]')
SELECT SqlArray.SmallIntArray.ToString(SqlArray.FloatArray.Lengths(@a))
	-- returns [2,3]
DECLARE @size varbinary(100) = SqlArray.SmallIntArray.Vector_2(3,2)
SET @a = SqlArray.FloatArray.Reshape(@a, @size)
SELECT SqlArray.SmallIntArray.ToString(SqlArray.FloatArray.Lengths(@a))
	-- returns [3,2]
	
	
DECLARE @a varbinary(100) = SqlArray.FloatArray.Parse('[[1, 2],[3, 4],[5, 6]]')
SET @a = SqlArray.FloatArray.Transpose(@a)
SELECT SqlArray.FloatArray.ToString(@a)
	-- return [[1,3,5],[2,4,6]]
	
	
DECLARE @i varbinary(100) = SqlArray.TinyIntArray.Vector_2(1, 0)
DECLARE @a varbinary(100) = SqlArray.FloatArray.Parse('[[1, 2],[3, 4],[5, 6]]')
SET @a = SqlArray.FloatArray.Permute(@a, @i)
SELECT SqlArray.FloatArray.ToString(@a)
	-- return [[1,3,5],[2,4,6]]
	
GO

-- Item functions	
	
DECLARE @ia varbinary(100) = SqlArray.SmallIntArray.Vector_2(0, 1)
DECLARE @a varbinary(100) = SqlArray.FloatArray.Parse('[[1, 2],[3, 4],[5, 6]]')
SELECT SqlArray.FloatArray.Item(@a, 4)			-- returns 5
SELECT SqlArray.FloatArray.Item_N(@a, @ia)		-- returns 4
SELECT SqlArray.FloatArray.Item_2(@a, 0, 1)		-- returns 4

GO


-- Items

DECLARE @a varbinary(100) = SqlArray.FloatArray.Matrix_2(1, 2, 3, 4)
DECLARE @ix varbinary(100) = SqlArray.SmallIntArray.Parse('[[0,0],[1,1],[0,1]]')
DECLARE @b varbinary(100) = SqlArray.FloatArray.Items(@a, @ix)
SELECT SqlArray.FloatArray.ToString(@b)		-- returns [1,4,3]

--SELECT li, SqlArray.SmallIntArray.ToString(i), v FROM SqlArray.FloatArray.ToTable(@a)

GO

DECLARE @ia varbinary(100) = SqlArray.SmallIntArray.Vector_2(0, 1)
DECLARE @a varbinary(100) = SqlArray.FloatArray.Parse('[[0, 0],[0, 0],[0, 0]]')
SET @a = SqlArray.FloatArray.UpdateItem(@a, 4, 1)
SELECT SqlArray.FloatArray.ToString(@a)			-- returns [[0,0],[0,0],[1,0]]
SET @a = SqlArray.FloatArray.UpdateItem_N(@a, @ia, 2)
SELECT SqlArray.FloatArray.ToString(@a)			-- returns [[0,0],[0,2],[1,0]]
SET @a = SqlArray.FloatArray.UpdateItem_2(@a, 0, 1, 3)
SELECT SqlArray.FloatArray.ToString(@a)			-- returns [[0,0],[3,2],[1,0]]

GO

-- Update Items

DECLARE @size varbinary(100) = SqlArray.SmallIntArray.Vector_2(2, 3)
DECLARE @a varbinary(100) = SqlArray.FloatArray.FromScalar(@size, 0)
SELECT SqlArray.FloatArray.ToString(@a)		-- returns [[0,0],[0,0],[0,0]]
DECLARE @ix varbinary(100) = SqlArray.SmallIntArray.Parse('[[0,0],[0,1],[1,0],[1,1]]')
DECLARE @v varbinary(100) = SqlArray.FloatArray.Parse('[1,2,3,4]')
DECLARE @b varbinary(100) = SqlArray.FloatArray.UpdateItems(@a, @ix, @v)
SELECT SqlArray.FloatArray.ToString(@b)		-- returns [[1,3],[2,4],[0,0]]


GO

DECLARE @a varbinary(100) = SqlArray.FloatArray.Parse('[[1, 2, 3],[4, 5, 6],[7, 8, 9]]')
DECLARE @offset varbinary(100) = SqlArray.SmallIntArray.Vector_2(1, 1)
DECLARE @size varbinary(100) = SqlArray.SmallIntArray.Vector_2(2, 2)
DECLARE @s varbinary(100) = SqlArray.FloatArray.SubArray(@a, @offset, @size, 0)
SELECT SqlArray.FloatArray.ToString(@s)		-- returns [[5,6],[8,9]]

GO

-- Subarrays

DECLARE @a varbinary(100) = SqlArray.FloatArray.Parse('[[1, 2, 3],[4, 5, 6],[7, 8, 9]]')
DECLARE @offsets varbinary(100) = SqlArray.SmallIntArray.Parse('[[0, 0],[1, 1]]')
DECLARE @size varbinary(100) = SqlArray.SmallIntArray.Vector_2(2, 2)
DECLARE @s varbinary(100) = SqlArray.FloatArray.SubArrays(@a, @offsets, @size, 0)
SELECT SqlArray.FloatArray.ToString(@s)		-- returns [[[1,5],[2,6]],[[4,8],[5,9]]]


GO

DECLARE @a varbinary(100) = SqlArray.FloatArray.Parse('[[1, 2, 3],[4, 5, 6],[7, 8, 9]]')
DECLARE @offset varbinary(100) = SqlArray.SmallIntArray.Vector_2(1, 1)
DECLARE @s varbinary(100) = SqlArray.FloatArray.Parse('[[0, 0],[0, 0]]')
SET @a = SqlArray.FloatArray.UpdateSubarray(@a, @offset, @s)
SELECT SqlArray.FloatArray.ToString(@a)		-- returns [[1,2,3],[4,0,0],[7,0,0]]

GO
-- SetSubArrays

DECLARE @a varbinary(100) = SqlArray.FloatArray.Parse('[[0, 0, 0],[0, 0, 0],[0, 0, 0]]')
DECLARE @offsets varbinary(100) = SqlArray.SmallIntArray.Parse('[[0, 0],[1, 1]]')
DECLARE @s varbinary(100) = SqlArray.FloatArray.Parse('[[[1,5],[2,6]],[[4,8],[5,9]]]')
SET @a = SqlArray.FloatArray.UpdateSubarrays(@a, @offsets, @s)
SELECT SqlArray.FloatArray.ToString(@a)		-- returns [[1,2,0],[4,5,6],[0,8,9]]

GO

DECLARE @a varbinary(100) = SqlArray.FloatArray.Parse('[1, 2, 3,4, 5, 6,7, 8, 9]')
SELECT * FROM SqlArray.FloatArray.ToTable_1(@a)

DECLARE @a varbinary(100) = SqlArray.FloatArray.Parse('[[1, 2, 3],[4, 5, 6],[7, 8, 9]]')
SELECT li, SqlArray.SmallIntArray.ToString(i), v FROM SqlArray.FloatArray.ToTable(@a)

DECLARE @a varbinary(100) = SqlArray.FloatArray.Parse('[[1, 2, 3],[4, 5, 6],[7, 8, 9]]')
SELECT * FROM SqlArray.FloatArray.ToTable_2(@a)


DECLARE @a varbinary(100) = SqlArray.FloatArray.Parse('[[1, 2, 3],[4, 5, 6],[7, 8, 9]]')
SELECT * FROM SqlArray.FloatArray.MatrixToTable_3(@a)

GO

-- Split

DECLARE @a varbinary(200) = SqlArray.FloatArray.Parse('[[[1,2,3,4],[3,4,5,6]],[[5,6,7,8],[7,8,9,0]]]')
DECLARE @offset varbinary(100) = SqlArray.SmallIntArray.Vector_3(1,0,0)
DECLARE @size varbinary(100) = SqlArray.SmallIntArray.Vector_3(2,1,1)
SELECT 
	SqlArray.SmallIntArray.ToString(ci) ci,
	SqlArray.SmallIntArray.ToString(i) i ,
	SqlArray.FloatArray.ToString(v) v
FROM SqlArray.FloatArray.Split(@a, @offset, @size, 1)

GO


DECLARE @a varbinary(100) = SqlArray.FloatArray.Parse('[[1, 2, 3],[4, 5, 6],[7, 8, 9]]')
DECLARE @items varbinary(100) = SqlArray.SmallIntArray.Parse('[[0,0],[0,1],[2,2]]')
SELECT li, SqlArray.SmallIntArray.ToString(i) i, v FROM SqlArray.FloatArray.ItemsToTable(@a, @items)


GO


DECLARE @a varbinary(100) = SqlArray.FloatArray.Parse('[[1, 2, 3],[4, 5, 6],[7, 8, 9]]')
DECLARE @offsets varbinary(100) = SqlArray.SmallIntArray.Parse('[[0,0],[0,1],[2,2]]')
DECLARE @size varbinary(100) = SqlArray.SmallIntArray.Parse('[1,1]')
SELECT
	li,
	SqlArray.SmallIntArray.ToString(i) i,
	SqlArray.FloatArray.ToString(v) v
FROM SqlArray.FloatArray.SubarraysToTable(@a, @offsets, @size, 0)



GO

DECLARE @a varbinary(100) = SqlArray.RealArray.Vector_3(1.0, 2.0, 3.0)
DECLARE @b varbinary(100) = SqlArray.RealArray.ScaMul(@a, 2)
SELECT SqlArray.RealArray.ToString(@b)	-- returns [2,4,6]
SET @b = SqlArray.RealArray.ScaDiv(@a, 2)
SELECT SqlArray.RealArray.ToString(@b)	-- returns [0.5,1,1.5]
SET @b = SqlArray.RealArray.ScaAdd(@a, 2)
SELECT SqlArray.RealArray.ToString(@b)	-- returns [3,4,5]
SET @b = SqlArray.RealArray.ScaSub(@a, 2)
SELECT SqlArray.RealArray.ToString(@b)	-- returns [-1,0,1]



GO

DECLARE @size varbinary(100) = SqlArray.SmallIntArray.Vector_3(2, 3, 2)
DECLARE @a varbinary(200) = SqlArray.FloatArray.FromScalar(@size, 1)
SELECT SqlArray.FloatArray.ToString(@a)
	-- returns [[[1,1],[1,1],[1,1]],[[1,1],[1,1],[1,1]]]
	
	
	
GO

DECLARE @a varbinary(100) = SqlArray.FloatArray.Vector_3(1.0, 2.0, 3.0)
DECLARE @b varbinary(100) = SqlArray.FloatArray.Vector_3(2.0, 4.0, 6.0)
SELECT SqlArray.FloatArray.ToString(SqlArray.FloatArray.Mul(@a, @b))
	-- returns [2,8,18]
SELECT SqlArray.FloatArray.ToString(SqlArray.FloatArray.Div(@a, @b))
	-- returns [0.5,0.5,0.5]
SELECT SqlArray.FloatArray.ToString(SqlArray.FloatArray.[Add](@a, @b))
	-- returns [3,6,9]
SELECT SqlArray.FloatArray.ToString(SqlArray.FloatArray.Sub(@a, @b))
	-- returns [-1,-2,-3]
	
	
GO

DECLARE @a varbinary(100) = SqlArray.FloatArray.Vector_3(1.0, 2.0, 3.0)
DECLARE @b varbinary(100) = SqlArray.FloatArray.Vector_3(2.0, 4.0, 6.0)
SELECT SqlArray.FloatArray.DotProd(@a, @b)	-- returns 28


GO

DECLARE @a varbinary(100) = SqlArray.FloatArray.Vector_3(0.0, 2.0, 3.0)
DECLARE @b varbinary(100) = SqlArray.FloatArray.Vector_3(2.0, 4.0, 6.0)
DECLARE @c varbinary(100) = SqlArray.FloatArray.CrossProd(@a, @b)
SELECT 	SqlArray.FloatArray.ToString(@c)	-- returns [0,6,-4]

GO

DECLARE @a varbinary(100) = SqlArray.FloatArray.Vector_3(0.0, 2.0, 3.0)
DECLARE @b varbinary(100) = SqlArray.FloatArray.Vector_3(2.0, 4.0, 6.0)
DECLARE @c varbinary(100) = SqlArray.FloatArray.TensorProd(@a, @b)
SELECT 	SqlArray.FloatArray.ToString(@c)	
-- returns [[0,4,6],[0,8,12],[0,12,18]]


GO

DECLARE @a varbinary(300) = SqlArray.FloatArray.Matrix_3(1,2,3,4,5,6,7,8,9)
DECLARE @b varbinary(300) = SqlArray.FloatArray.Matrix_3(7,4,5,6,7,3,4,8,9)
DECLARE @c varbinary(300) = SqlArray.FloatArray.InnerProd(@a, @b)
SELECT 	SqlArray.FloatArray.ToString(@c)	
	-- returns [[30,78,126],[29,77,125],[47,110,173]]

GO

DECLARE @a varbinary(100) = SqlArray.FloatArray.Matrix_3(1,2,3,4,5,6,7,8,9)
SELECT SqlArray.FloatArray.Avg(@a)		-- returns 3.5


GO

CREATE TABLE ##arr (li smallint, v float)

INSERT ##arr (li, v)
VALUES (0,1), (1,2), (2,3), (3,4), (6,7), (7,8), (8,9)

DECLARE @size varbinary(100) = SqlArray.SmallIntArray.Vector_2(3, 3)
DECLARE @a varbinary(100) = SqlArray.FloatArray.FromTable('##arr', @size)
SELECT SqlArray.FloatArray.ToString(@a)		
	-- returns [[1,2,3],[4,0,0],[7,8,9]]

DROP TABLE ##arr


GO


CREATE TABLE ##arr (i varbinary(100), v varbinary(100))

INSERT ##arr (i, v)
VALUES (SqlArray.SmallIntArray.Vector_2(0,0), SqlArray.FloatArray.Matrix_2(1,1,1,1)),
       (SqlArray.SmallIntArray.Vector_2(0,2), SqlArray.FloatArray.Matrix_2(2,2,2,2)),
       (SqlArray.SmallIntArray.Vector_2(2,0), SqlArray.FloatArray.Matrix_2(3,3,3,3)),
       (SqlArray.SmallIntArray.Vector_2(2,2), SqlArray.FloatArray.Matrix_2(4,4,4,4))

DECLARE @size varbinary(100) = SqlArray.SmallIntArray.Vector_2(4, 4)
DECLARE @a varbinary(100) = SqlArray.FloatArray.FromSubarrayTable('##arr', @size)
SELECT SqlArray.FloatArray.ToString(@a)		
	-- returns [[1,2,3],[4,0,0],[7,8,9]]

DROP TABLE ##arr