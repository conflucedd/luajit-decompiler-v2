## LuaJIT Decompiler v2 (with Linux support)
This is fork from marsinator358/luajit-decompiler-v2, thanks him.
I use claude code and deepseek api to build this version.
Add support to linux and drop support to windows(well just because I want to make things simple, if you want windows version please just use his origin version)

## Usage
luajit-decompiler-v2 input.lua
and the output will in output folder

## Compile
g++ -std=c++20 -funsigned-char -I. -o luajit-decompiler-v2 main.cpp bytecode/bytecode.cpp bytecode/prototype.cpp ast/ast.cpp lua/lua.cpp

my g++ version is 15.2.1 20260209 and I use Archlinux in 2026.3.1(latest) build this.