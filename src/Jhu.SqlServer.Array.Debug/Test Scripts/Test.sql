DECLARE @a varbinary(100) = SqlArray.FloatArray.Parse('[[[1,2,3,4],[3,4,5,6]],[[5,6,7,8],[7,8,9,0]]]')
DECLARE @offset varbinary(100) = SqlArray.SmallIntArray.Vector_3(0,0,0)
DECLARE @size varbinary(100) = SqlArray.SmallIntArray.Vector_3(4,1,1)
SELECT 
	SqlArray.SmallIntArray.ToString(ci) ci,
	SqlArray.SmallIntArray.ToString(i) i ,
	SqlArray.FloatArray.ToString(v) v
FROM SqlArray.FloatArray.Split(@a, @offset, @size, 0)