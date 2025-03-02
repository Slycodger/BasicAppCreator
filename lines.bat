@echo off
echo Basic App has : 
powershell.exe -command "(gci -path "./BasicApp/Src/" | select-string .).count"
echo lines
echo:
echo Basic App Shaders have : 
powershell.exe -command "(gci -recurse -path "./BasicApp/shaders/" | select-string .).count"
echo lines
echo:
echo Creator has :
powershell.exe -command "(gci -include "*.cs" -path "./Creator/" -recurse | select-string .).count"
echo lines
@echo on