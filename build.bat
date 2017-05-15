if %1.==. (
    cd src
    make > _build.bat
    _build.bat
    cd ..
) else (
    del /S /Q binary
    del /S /Q *.mcl
    del /S /Q *.dbg
    del /S /Q *.dlt
    del /S /Q *.hex
    del /S /Q *.lst
    del /S /Q *.txt
    del /S /Q *.asm
    del /S /Q *.cp
    del /S /Q _*.bat
)