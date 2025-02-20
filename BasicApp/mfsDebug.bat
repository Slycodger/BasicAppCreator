@echo off
xcopy textures\ x64\Debug\textures\ /y /i /e
xcopy fonts\ x64\Debug\fonts\ /y /i /e
xcopy models\ x64\Debug\models\ /y /i /e
xcopy shaders\ x64\Debug\shaders\ /y /i /e
xcopy environments\ x64\Debug\environments\ /y /i /e
@echo on
exit