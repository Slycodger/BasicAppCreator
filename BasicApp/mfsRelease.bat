@echo off
xcopy textures\ x64\Release\textures\ /y /i /e
xcopy fonts\ x64\Release\fonts\ /y /i /e
xcopy models\ x64\Release\models\ /y /i /e
xcopy shaders\ x64\Release\shaders\ /y /i /e
xcopy environments\ x64\Release\environments\ /y /i /e
@echo on
exit