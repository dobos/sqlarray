SET sol=%1
SET platform=%2
SET config=%3
SET version=%4
SET zip="C:\Program Files\7-Zip\7z.exe"
SET archive="SqlArray-%config%-%platform%-%version%.zip"

del %sol%install\%archive%

%zip% a -tzip %sol%install\%archive% %sol%\sql\%platform%\%config%\install.sql
%zip% a -tzip %sol%install\%archive% %sol%\sql\%platform%\%config%\uninstall.sql
%zip% a -tzip %sol%install\%archive% %sol%\keys\installkey.sql
%zip% a -tzip %sol%install\%archive% %sol%\keys\sqlarray.snk
%zip% a -tzip %sol%install\%archive% %sol%\%platform%\%config%\Jhu.SqlServer.Array.dll
%zip% a -tzip %sol%install\%archive% %sol%\%platform%\%config%\Jhu.SqlServer.Array.pdb
%zip% a -tzip %sol%install\%archive% %sol%\%platform%\%config%\Jhu.SqlServer.Array.Parser.dll
%zip% a -tzip %sol%install\%archive% %sol%\%platform%\%config%\Jhu.SqlServer.Array.Parser.pdb
%zip% a -tzip %sol%install\%archive% %sol%\docs\sqlarray.pdf

copy %sol%install\%archive% %sol%\web\Download
copy %sol%docs\sqlarray.pdf %sol%\web\Download
