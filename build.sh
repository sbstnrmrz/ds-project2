#!/bin/bash

CC="clang++"
CCFLAGS="-ftime-trace"
EXE="main"
SRC="*.cpp"

$CC $CCFLAGS $SRC -o $EXE

rm clientes1.bin clientes2.bin clientes1.dat clientes2.dat clientes.bin log.txt
cp bak.clientes.bin clientes.bin
cp bak.clientes.bin clientes.dat
cp bak.productos.bin productos.dat
#cp clientes.def.bin clientes.bin 
#cp proveedores.def.bin proveedores.bin
