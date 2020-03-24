@ECHO OFF
set pwd=%~dp0
set config=build
set output_path= "%pwd%/%config%"
rmdir /s/q %output_path%
md %output_path%

:: Build the side module
call emcc^
 side.cpp^
 -g4^
 -O1^
 -fPIC^
 -s WASM=1^
 -s SIDE_MODULE=1^
 -s ASSERTIONS=2^
 -s DEMANGLE_SUPPORT=1^
 -s DISABLE_EXCEPTION_CATCHING=0^
 -s BINARYEN=1^
 -s BINARYEN_METHOD='native-wasm'^
 -s ERROR_ON_UNDEFINED_SYMBOLS=0^
 -o %config%\side.wasm

:: Build the main module
call emcc^
 main.cpp^
 -g4^
 -fPIC^
 -O1^
 -lnodefs.js^
 -s WASM=1^
 -s MAIN_MODULE=2^
 -s EXPORTED_FUNCTIONS=@exports.json^
 -o %config%\index.js^
 --pre-js preload.js^
 -s ASSERTIONS=2^
