set files=src\main.c
set libs=lib\SDL2main.lib lib\SDL2.lib

CL /Zi /I include %files% /link %libs% /out:main.exe
