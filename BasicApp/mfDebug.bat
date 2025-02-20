@echo off
xcopy textures\ ..\Creator\bin\Debug\net9.0\textures\ /y /i /e
xcopy fonts\ ..\Creator\bin\Debug\net9.0\fonts\ /y /i /e
xcopy models\ ..\Creator\bin\Debug\net9.0\models\ /y /i /e
xcopy shaders\ ..\Creator\bin\Debug\net9.0\shaders\ /y /i /e
xcopy environments\ ..\Creator\bin\Debug\net9.0\environments\ /y /i /e
@echo on
exit