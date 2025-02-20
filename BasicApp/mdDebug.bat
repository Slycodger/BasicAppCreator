@echo off
xcopy .\*.dll x64\Release\ /y /i
xcopy x64\Release\*.dll ..\Creator\bin\Debug\net9.0\ /y /i
@echo on
exit