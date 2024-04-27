// Participantes: 
// Sebastian Ramirez C.I:31567908
// Angel Vivas       C.I:30890743

#ifndef DEFS_H
#define DEFS_H

#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <string.h>
using namespace std;

#if __WIN32
#define CLEAR system("cls")
#define SLEEP(secs) {                                   \
    char buf[32] = {0}                                  \
    sprintf(buf, "timeout /t %d /nobreak > nul", secs); \
    system(buf);                                        \
}
#define DELETE_FILE(file) {            \
    char str[32] = {0};                \
    snprintf(str, 32, "del %s", file); \
    system(str);                       \
}
#elif __APPLE__
#define CLEAR system("clear")
#define SLEEP(secs) {                    \
    char str[32] = {0};                  \
    snprintf(str, 32, "sleep %d", secs); \
    system(str);                         \
}
#define DELETE_FILE(file) {           \
    char str[32] = {0};               \
    snprintf(str, 32, "rm %s", file); \
    system(str);                      \
}
#endif

#define ARRAY_LEN(x) sizeof(x)/sizeof(x[0])

typedef struct {
    int id;
    char nombre[45];
    char direccion[70];
    char telefono[18];
} cliente_t;

typedef struct {
    int   id;
    int   id_proveedor;
    int   stock;
    float precio;
    char  descripcion[45];
    int   stock_min;
} producto_t;

int consultar_productos();
void consultar_clientes();

void print_info_producto(producto_t producto);
void print_info_cliente(cliente_t cliente);

#endif
