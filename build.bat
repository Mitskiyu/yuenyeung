@echo off

if "%1"=="release" (
    set flags=/O2 /DNDEBUG
) else (
    set flags=/Od
)

if not exist build mkdir build
pushd build
cl /nologo %flags% /std:c++latest /EHsc /utf-8 /W4 /Zi ..\main.cpp
popd
