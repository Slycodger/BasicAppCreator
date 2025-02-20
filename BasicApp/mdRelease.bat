@echo off
xcopy .\*.dll x64\Release\ /y /i
xcopy x64\Release\*.dll ..\Creator\bin\Release\net9.0\ /y /i
@echo on
exit