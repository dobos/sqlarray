SELECT TOP 10 * FROM genes




SELECT MAX(GeneID) FROM genes
--54675

/*
DBCC DROPCLEANBUFFERS
DBCC FREEPROCCACHE

DECLARE @a varbinary(max)
DECLARE @length varbinary(100) = SqlArrayTest.IntArray.Vector_1(54675)

SELECT ChipID, SqlArrayTest.RealArrayMax.FromTable(@length, SqlArrayTest.IntArray.Vector_1(GeneID), Expression)
FROM Genes
WHERE ChipID <= 10
GROUP BY ChipID


SELECT LEN(@a)

---
*/

SELECT MAX(GeneID) FROM genes
--54675

DBCC DROPCLEANBUFFERS
DBCC FREEPROCCACHE

DECLARE @length varbinary(100) = SqlArrayTest.IntArray.Vector_1(54675)

SELECT ChipID, SqlArrayTest.RealArrayMax.Concat(@length, SqlArrayTest.IntArray.Vector_1(GeneID), Expression)
FROM Genes
WHERE ChipID <= 10
GROUP BY ChipID

/*
---

DBCC DROPCLEANBUFFERS
DBCC FREEPROCCACHE

SELECT AVG(Expression) FROM Genes
WHERE ChipID <= 10

---

SELECT @a = SqlArrayTest.SingleMaxArray.Concat(SqlArrayTest.Int32Array.Vector_1(54675), SqlArrayTest.Int32Array.Vector_1(GeneID), Expression)
FROM Genes
WHERE ChipID = 1

*/
----

--DECLARE @sql nvarchar(max) = 'SELECT GeneID, Expression FROM GeneChip..Genes WHERE ChipID = 1'


--- CONVERT FROM TABLE TO ARRAY

TRUNCATE TABLE GeneChip..GenesArray

DECLARE @ChipID int = 1

WHILE (@ChipID <= 1000)
BEGIN

	SELECT IntArray.Vector_1(GeneID - 1) AS ix, CAST(Expression AS real) AS v
	INTO ##temp
	FROM GeneChip..Genes WHERE ChipID = @ChipID

	--SELECT t.* FROM ##temp AS t

	INSERT GeneChip..GenesArray
	SELECT @ChipID, RealArrayMax.FromTable('##temp', IntArray.Vector_1(54675))

	DROP TABLE ##temp
	
	SET @ChipID = @ChipID + 1

END

--- END CONVERT TABLE TO ARRAY

DECLARE @tt AS TABLE (ix varbinary(50), v real)

INSERT @tt
SELECT Int32Array.Vector_1(GeneID) AS ix, CAST(Expression AS real) AS v
FROM GeneChip..Genes WHERE ChipID = 1

SELECT SingleMaxArray.Concat('@tt', Int32Array.Vector_1(54675))


-----------------------

DBCC DROPCLEANBUFFERS
DBCC FREEPROCCACHE

DECLARE @genes varbinary(max)
SELECT @genes = Value FROM GeneChip..GenesArray WHERE ChipID = 10

-- Get all genes
--SELECT li, v FROM SingleMaxArray.ToTable(@genes)

-- Get only a couple of genes
DECLARE @ids varbinary(max) = IntArrayMax.Parse('[[1],[5],[7],[8],[9],[12],[14],[16],[17],[18]]');

SELECT li, v FROM RealArrayMax.ItemsToTable(@genes, @ids)

---

DBCC DROPCLEANBUFFERS
DBCC FREEPROCCACHE

SELECT a.li, a.v, b.v
FROM
	(SELECT g.li, g.v FROM GeneChip..GenesArray
	CROSS APPLY RealArrayMax.ToTable(Value) g
	WHERE ChipID = 10) a
INNER JOIN
	(SELECT g.li, g.v FROM GeneChip..GenesArray
	CROSS APPLY RealArrayMax.ToTable(Value) g
	WHERE ChipID = 12) b
ON a.li = b.li





DBCC DROPCLEANBUFFERS
DBCC FREEPROCCACHE

SELECT a.GeneID, a.Expression, b.Expression
FROM
	(SELECT GeneID, Expression FROM GeneChip..Genes
	WHERE ChipID = 10) a
INNER JOIN
	(SELECT GeneID, Expression FROM GeneChip..Genes
	WHERE ChipID = 12) b
ON a.GeneID = b.GeneID


---



DBCC DROPCLEANBUFFERS
DBCC FREEPROCCACHE

DECLARE @a varbinary(max), @b varbinary(max)

SELECT @a = RealArrayMax.ConvertToFloatArrayMax(Value) FROM GeneChip..GenesArray WHERE ChipID = 10
SELECT @b = RealArrayMax.ConvertToFloatArrayMax(Value) FROM GeneChip..GenesArray WHERE ChipID = 12

--SELECT @a = Value FROM GeneChip..GenesArray WHERE ChipID = 10
--SELECT @b = Value FROM GeneChip..GenesArray WHERE ChipID = 12

SELECT CAST(FloatArrayMax.DotProd(@a, @b) AS Float)
--1934472
--1934473.8426522
--1934489.20334784



DBCC DROPCLEANBUFFERS
DBCC FREEPROCCACHE

SELECT SUM(a.Expression * b.Expression)
FROM
	(SELECT GeneID, Expression FROM GeneChip..Genes
	WHERE ChipID = 10) a
INNER JOIN
	(SELECT GeneID, Expression FROM GeneChip..Genes
	WHERE ChipID = 12) b
ON a.GeneID = b.GeneID
-- 1934489.20325899







SELECT SUM(a.v * b.v)
FROM
	(SELECT g.li, g.v FROM GeneChip..GenesArray
	CROSS APPLY RealArrayMax.ToTable(Value) g
	WHERE ChipID = 10) a
INNER JOIN
	(SELECT g.li, g.v FROM GeneChip..GenesArray
	CROSS APPLY RealArrayMax.ToTable(Value) g
	WHERE ChipID = 12) b
ON a.li = b.li





----


SELECT a.li, a.v, b.Expression, a.v - b.Expression
FROM
	(SELECT g.li, g.v FROM GeneChip..GenesArray
	CROSS APPLY RealArrayMax.ToTable(Value) g
	WHERE ChipID = 10) a
RIGHT OUTER JOIN
	(SELECT GeneID as li, CAST(Expression AS real) AS Expression FROM GeneChip..Genes
	WHERE ChipID = 10) b
ON a.li = b.li - 1

