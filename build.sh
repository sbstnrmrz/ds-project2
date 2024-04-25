#!/bin/bash

CC="clang++"
CCFLAGS=""
EXE="main"
SRC="*.cpp"

$CC $CCFLAGS $SRC -o $EXE

rm clientes.bin log.txt
cp bak.clientes.bin clientes.bin
#cp clientes.def.bin clientes.bin 
#cp proveedores.def.bin proveedores.bin
