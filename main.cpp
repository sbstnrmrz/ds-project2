// Participantes: 
// Sebastian Ramirez C.I:31567908
// Angel Vivas       C.I:30890743

#include "defs.h"

void vec_productos_quick_sort(vector<producto_t> *productos, int start, int end) {
    if (end <= start) {
        return;
    }

    char *pivot = productos->at(end).descripcion;
    int i = start-1;

    for (int j = start; j <= end; j++) {
        if (strcasecmp(productos->at(j).descripcion, pivot) < 0) {
            i++;
            swap(productos->at(j), productos->at(i));
        }
    }
    i++;
    swap(productos->at(end), productos->at(i));

    vec_productos_quick_sort(productos, start, i-1);
    vec_productos_quick_sort(productos, i+1, end);
}

void set_binario_clientes(fstream& clientes1, int pos1, fstream& clientes2, int pos2) {
    cliente_t tmp_cliente = {0};

    clientes2.seekg(pos2 * sizeof(cliente_t));
    clientes2.read((char*)&tmp_cliente, sizeof(cliente_t));

    clientes1.seekp(pos1 * sizeof(cliente_t));
    clientes1.write((char*)&tmp_cliente, sizeof(cliente_t));
}

int obtener_tamano_clientes(fstream& clientes) {
    clientes.seekg(0, ios::end);
    int result = (int)clientes.tellg()/sizeof(cliente_t);
    clientes.clear();
    clientes.seekg(0, ios::beg);

    return result;
}

std::string obtener_nombre_clientes(fstream& clientes, int pos) {
    cliente_t cliente = {0};
    clientes.seekg(pos * sizeof(cliente_t));
    clientes.read((char*)&cliente, sizeof(cliente_t));
    clientes.clear();
    clientes.seekg(0, ios::beg);

    return cliente.nombre;
}

void clientes_merge(fstream& clientes1, const char* str1, fstream& clientes2, const char* str2, fstream& clientes) {
    int len = obtener_tamano_clientes(clientes);
    int left_len = len/2;
    int right_len = len - left_len;
    int i = 0;
    int l = 0;
    int r = 0;

    while (l < left_len && r < right_len) {
        if (strcasecmp(obtener_nombre_clientes(clientes1, l).c_str(), 
                       obtener_nombre_clientes(clientes2, r).c_str()) < 0) 
        {
            set_binario_clientes(clientes, i, clientes1, l);
            i++;
            l++;
        } else {
            set_binario_clientes(clientes, i, clientes2, r);
            i++;
            r++;
        }
    }
    while (l < left_len) {
        set_binario_clientes(clientes, i, clientes1, l);
        i++;
        l++;
    }
    while (r < right_len) {
        set_binario_clientes(clientes, i, clientes2, r);
        i++;
        r++;
    }
    clientes1.close();
    clientes2.close();
    DELETE_FILE(str1);
    DELETE_FILE(str2);
}

void clientes_merge_sort(fstream& clientes, int itr) {
    int len = obtener_tamano_clientes(clientes);
    if (len <= 1) {
        return;
    }

    int mid = len/2;
    fstream clientes1; 
    fstream clientes2; 

    cliente_t cliente = {0};
    char str1[128] = {0};
    char str2[128] = {0};
    snprintf(str1, 128, "clientes%d.bin", itr++);
    snprintf(str2, 128, "clientes%d.bin", itr++);

    clientes1.open(str1, ios::app | ios::binary);
    clientes2.open(str2, ios::app | ios::binary);
    if (!clientes1.is_open() && !clientes2.is_open()) {
        printf("Error clientes 1 y 2\n");
        exit(1);
    }

    int j = 0;
    for (int i = 0; i < len; i++) {
        clientes.read((char*)&cliente, sizeof(cliente_t));
        if (i < mid) {
            clientes1.write((char*)&cliente, sizeof(cliente_t));
        } else {
            clientes2.write((char*)&cliente, sizeof(cliente_t));
            j++;
        }
    }
    clientes1.close();
    clientes2.close();
    clientes1.open(str1, ios::in | ios::out | ios::binary);
    clientes2.open(str2, ios::in | ios::out | ios::binary);

    clientes_merge_sort(clientes1, itr);
    clientes_merge_sort(clientes2, itr);
    clientes_merge(clientes1, str1, clientes2, str2, clientes);
}

void consultar_clientes() {
    cliente_t cliente = {0};
    int cant_clientes = 0;
    fstream f;

    f.open("clientes.bin", ios::binary | ios::in);
    if (!f.is_open()) {
        printf("No existen clientes guardados!\n");
        f.close();
        return;
    }

    printf("____________________________________________________________________________________\n");
    printf("|                                     CLIENTES                                     |\n");
    printf("|__________________________________________________________________________________|\n");
    printf("|     ID     |       Nombre      |     Telefono    |           Direccion           |\n");
    printf("|----------------------------------------------------------------------------------|\n");

    f.read((char*)&cliente, sizeof(cliente_t));
    while(!f.eof()) {
        print_info_cliente(cliente);
        f.read((char*)&cliente, sizeof(cliente_t));

        cant_clientes++;
    }
    printf("-----------------------------------------------------------------------------------|\n");

    f.close();
}

void consultar_productos(vector<producto_t> productos) {
    printf("_________________________________________________________________________\n");
    printf("|                               PRODUCTOS                               |\n");
    printf("|_______________________________________________________________________|\n");
    printf("| ID  | ID Proveedor |   Descripcion   |  Precio | Stock | Stock minimo |\n");
    printf("|-----------------------------------------------------------------------|\n");

    for (producto_t producto : productos) {
        print_info_producto(producto);
    } 
    printf("-------------------------------------------------------------------------\n");
}

void print_info_cliente(cliente_t cliente) {
    printf("| %-10d | %-17s | %-15s | %-29s |\n", cliente.id,
                                                  cliente.nombre,
                                                  cliente.telefono,
                                                  cliente.direccion);
}

void print_info_producto(producto_t producto) {
    printf("| %-3d | %-12d | %-15s | %-7.2f | %-5d | %-12d |\n", producto.id,
                                                                 producto.id_proveedor,
                                                                 producto.descripcion,
                                                                 producto.precio,
                                                                 producto.stock,
                                                                 producto.stock_min);
}

vector<producto_t> crear_vector_productos() {
    vector<producto_t> productos;
    producto_t producto = {0};
    fstream binario;
    binario.open("productos.bin", ios::in | ios::binary);

    binario.read((char*)&producto, sizeof(producto_t));
    while (!binario.eof()) {
        productos.push_back(producto);
        binario.read((char*)&producto, sizeof(producto_t));
    }

    return productos;
}

int vec_productos_binary_search(vector<producto_t> vec, const char *target) {
    int l = 0;
    int r = vec.size()-1;

    while (l <= r) {
        int m = (l+r)/2;
        const char *str = vec.at(m).descripcion; 
        if (strcasecmp(str, target) < 0) {
            l = (m+1);
        } else if (strcasecmp(str, target) > 0) {
            r = (m-1);
        } else {
            return m;
        } 
    }
    return -1;
}

int clientes_binary_search(fstream& clientes, const char *target) {
    int len = obtener_tamano_clientes(clientes);

    int l = 0;
    int r = len-1;

    while (l <= r) {
        cliente_t cliente = {0};
        int m = (l+r)/2;
        clientes.seekg(m * sizeof(cliente_t));
        clientes.read((char *)&cliente, sizeof(cliente_t));

        char c1 = tolower(cliente.nombre[0]);
        char c2 = tolower(target[0]);

        if (strcasecmp(cliente.nombre, target) < 0) {
            l = (m+1);// * sizeof(cliente_t);
        } else if (strcasecmp(cliente.nombre, target) > 0) {
            r = (m-1);// * sizeof(cliente_t);
        } else {
            return m;
        } 
    }
    return -1;
}

int main(int argc, char *argv[]) {
    auto t1 = std::chrono::system_clock::now();
    std::srand(std::time(nullptr));
    
    vector<producto_t> vec_productos = crear_vector_productos();

    printf("UNSORTED\n");
    consultar_productos(vec_productos);
    vec_productos_quick_sort(&vec_productos, 0, vec_productos.size()-1);

    auto t2 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_secs = t2-t1;
    float tiempo_quick_sort = elapsed_secs.count();

    printf("SORTED\n\n\n");
    consultar_productos(vec_productos);

    printf("Tiempo de ordenacion de productos alfabeticamente por quicksort: %lf\n\n", tiempo_quick_sort);
    
    const char *str = "melon";
    printf("Binary search: %s, pos: %d\n", str, vec_productos_binary_search(vec_productos, str));

//  vector<cliente_t> clientes = crear_vector_clientes();
//  consultar_clientes();
//  clientes_merge_sort(&clientes);
//  consultar_clientes(clientes);

//  consultar_clientes();
//  printf("\n\n\n\n");
//  fstream clientes;
//  clientes.open("clientes.bin", ios::in | ios::out | ios::binary);
//  binario_clientes_merge_sort(clientes, 0);
//  consultar_clientes();
//  int result = clientes_binary_search(clientes, "Emily Mitchell");
//  printf("result: %d\n", result);

//  if (result == -1) {
//      printf("No se ha encontrado a Zoe Miller");
//  } else {
//      printf("Se ha encontrado a Zoe Miller en la posicion: %d ", result);
//  }

//  vec_quick_sort(&vec, 0, vec.size()-1);
//  for (int i : vec) {
//      printf("%d ", i);
//  }
//  printf("\n");
//  int num = 4;
//  int pos = vec_binary_search(vec, num);
//  if (pos != -1) {
//      printf("element %d | pos %d\n", num, pos);
//  } else {
//      printf("element not found\n");
//  }
}
