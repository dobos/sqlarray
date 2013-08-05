--



DBCC DROPCLEANBUFFERS
DBCC FREEPROCCACHE

DECLARE @len varbinary(100) = SqlArray.IntArray.Parse('[72, 72, 72, 4]');
DECLARE @from varbinary(100) = SqlArray.IntArray.Parse('[64, 64, 64, 0]');
DECLARE @size varbinary(100) = SqlArray.IntArray.Parse('[8, 8, 8, 4]');

SELECT SqlArray.RealArrayMax.TotalLength(data) FROM TurbTest11Array..isotropic1024data

SELECT SqlArray.IntArray.ToString(SqlArray.RealArrayMax.Lengths(data)) FROM TurbTest11Array..isotropic1024data

SELECT TOP 1000 SqlArray.RealArrayMax.TotalLength(SqlArray.RealArrayMax.Subarray(data, @from, @size, 0))
FROM TurbTest11Array..isotropic1024data

SELECT SqlArray.RealArrayMax.Item_4(data, 10, 10, 10, 1)
FROM TurbTest11Array..isotropic1024data

SELECT SqlArray.RealArrayMax.Item_N(data, @from)
FROM TurbTest11Array..isotropic1024data

SELECT SqlArray.RealArrayMax.Item(data, 0)
FROM TurbTest11Array..isotropic1024data

-------------

-- Cast RAW data in the original Turbulace DB - slow

DECLARE @len varbinary(100) = SqlArray.IntArray.Parse('[72, 72, 72, 4]');
DECLARE @from varbinary(100) = SqlArray.IntArray.Parse('[64, 64, 64, 0]');

SELECT TOP 10 SqlArray.RealArrayMax.Item_4(SqlArray.RealArrayMax.Cast(data, 0, @len), 10, 10, 10, 1)
FROM TurbTest11Two..isotropic1024data

SELECT TOP 10 SqlArray.RealArrayMax.Item_N(SqlArray.RealArrayMax.Cast(data, 0, @len), @from)
FROM TurbTest11Two..isotropic1024data

SELECT TOP 10 SqlArray.RealArrayMax.Item(SqlArray.RealArrayMax.Cast(data, 0, @len), 0)
FROM TurbTest11Two..isotropic1024data



----
SELECT TOP 100 LEN(data)
FROM TurbTest11Two..isotropic1024data

-------------------

-- Convert RAW data into a new DB which has the array headers

DROP TABLE TurbTest11Array..isotropic1024data

DECLARE @len varbinary(100) = SqlArray.IntArray.Parse('[72, 72, 72, 4]');

SELECT timestep, zindex, SqlArray.RealArrayMax.Cast(data, 0, @len) as data
INTO TurbTest11Array..isotropic1024data
FROM TurbTest11Two..isotropic1024data





-----------


SELECT data
FROM TurbTest11Array..isotropic1024data
WHERE timestep = 2 and zindex = 813694976

SELECT data
FROM TurbTest11Two..isotropic1024data
WHERE timestep = 2 and zindex = 813694976