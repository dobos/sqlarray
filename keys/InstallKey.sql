USE master

CREATE MASTER KEY ENCRYPTION BY PASSWORD = 'BRAhe9rEspex'

-- Edit filename to point to actual location --

CREATE ASYMMETRIC KEY SqlArrayKey FROM FILE = 'SqlArray.snk' 

-----------------------------------------------

CREATE LOGIN SqlArrayUser FROM ASYMMETRIC KEY SqlArrayKey
 
GRANT UNSAFE ASSEMBLY TO SqlArrayUser 

GRANT EXTERNAL ACCESS ASSEMBLY TO SqlArrayUser
 
REVOKE CONNECT SQL FROM SqlArrayUser
