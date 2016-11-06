@echo off

call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" amd64

if not exist .\bin mkdir .\bin

set binary=sge.exe
set project_dependencies=glew32.lib glfw3dll.lib opengl32.lib
set additional_dependencies=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib

pushd .\build
set compiler_flags=-Od -EHsc -W3 -WX -nologo -Gm -GR -FC -ZI -std:c++latest -I ..\include -Fe..\bin\%binary%
set link_flags=-incremental:no /libpath:..\lib -opt:ref %project_dependencies% %additional_dependencies% 
cl %compiler_flags% ..\src\*.cpp /link %link_flags% 
popd